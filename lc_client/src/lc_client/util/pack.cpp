#include "pack.h"

#include <iostream>

#include "lc_client/exceptions/io_exceptions.h"


using json = nlohmann::json;


void Pack::loadPack(const std::string name, std::string path, eng::IResource* pResource) {
	Pack pack(name, path, pResource);
	m_packs.emplace(name, std::forward<Pack>(pack));
	std::cout << "Pack '" << name << "' with the path '" << path << "' has been loaded. " << std::endl;
}

Pack& Pack::getPack(std::string name) { return m_packs.at(name); }

Pack::Pack(std::string name, std::string path, eng::IResource* pResource) {
	m_name = name;
	m_path = path;

	std::vector<unsigned char> buffer = pResource->getFileResource(path);

	m_descriptor = json::parse(buffer);
}

Pack::~Pack() = default;


Pack::Model::Model(Pack& parent, std::string name) : m_parent(parent) {
	auto& models = parent.m_descriptor.at("models");

	bool isFound = false;

	for (auto& model : models.items()) {

		if (model.key() == name) {

			if (isFound) {
				std::cerr << "Pack::Model::Model: model with the name '" << name << "' occured more than one time in the pack '"
						  << m_parent.m_name << "'." << std::endl;
				break;
			}

			isFound = true;

			m_modelPath = model.value().at("model_path");
			m_texturesPath = model.value().at("textures_path");
			m_vertexShader = model.value().at("vertex_shader");
			m_fragmentShader = model.value().at("fragment_shader");
		}
	}

	if (isFound) {
		std::cout << "Model '" << name << "' has been found in the pack '" << parent.m_name << "'." << std::endl;
	}
	else {
		throw ModelNotFoundException("model '" + name + "' in the pack '" + parent.m_name + "' not found.");
	}
		
}

Pack::Model::~Model() = default;

std::string Pack::Model::getPath() { return m_modelPath; }

std::string Pack::Model::getTexturesPath() { return m_texturesPath; }

std::string Pack::Model::getVertexShader() { return m_vertexShader; }

std::string Pack::Model::getFragmentShader() { return m_fragmentShader; }


std::unordered_map<std::string, Pack> Pack::m_packs;