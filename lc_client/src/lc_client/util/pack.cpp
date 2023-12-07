#include "pack.h"

#include <iostream>

#include "lc_client/exceptions/io_exceptions.h"


using json = nlohmann::json;


void Pack::loadPack(const std::string name, std::string path, eng::IResource* pResource) {
	Pack pack(name, path, pResource);
	m_packs.emplace(name, std::forward<Pack>(pack));
	std::cout << "Pack '" << name << "' with the path '" << path << "' has been loaded. " << std::endl;
}

Pack& Pack::getPack(std::string name) {
	try {
		return m_packs.at(name);
	}
	catch (std::out_of_range&) {
		throw std::runtime_error("Pack: pack '" + name + "' not loaded");
	}
}

Pack::Pack(std::string name, std::string path, eng::IResource* pResource) {
	m_name = name;
	m_path = path;

	try {
		std::vector<unsigned char> buffer = pResource->getFileResource(path);
		m_descriptor = json::parse(buffer);
	}
	catch (ResourceFileNotFoundException& exception) {
		throw ResourceFileNotFoundException("Incorrect pack '" + name + "':" + exception.what());
	}
}

Pack::~Pack() = default;


Pack::Model::Model(Pack& parent, std::string name) : m_parent(parent) {
	auto& models = parent.m_descriptor.at("models");

	bool isFound = false;

	for (auto& model : models.items()) {

		if (model.key() == name) {

			if (isFound) {
				std::cerr << "Pack::Model::Model: model with the name '" << name
						  << "' occured more than one time in the pack '" << m_parent.m_name << "'." << std::endl;
				break;
			}

			isFound = true;

			m_modelPath = model.value().at("model_path");
			m_texturesPath = model.value().at("textures_path");
			m_materialType = model.value().at("material_type");
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
std::string Pack::Model::getMaterialType() { return m_materialType; }
std::string Pack::Model::getVertexShader() { return m_vertexShader; }
std::string Pack::Model::getFragmentShader() { return m_fragmentShader; }

Pack::Skybox::Skybox(Pack& parent, std::string name) : m_parent(parent){ 
	auto& skyboxes = parent.m_descriptor.at("skyboxes");

	bool isFound = false;

	for (auto& skybox : skyboxes.items()) {

		if (skybox.key() == name) {

			if (isFound) {
				std::cerr << "Pack::Skybox::Skybox: skybox with the name '" << name
						  << "' occured more than one time in the pack '" << m_parent.m_name << "'." << std::endl;
				break;
			}

			isFound = true;

			m_path = skybox.value().at("path");
		}
	}

	if (isFound) {
		std::cout << "Skybox '" << name << "' has been found in the pack '" << parent.m_name << "'." << std::endl;
	}
	else {
		throw ModelNotFoundException("Skybox '" + name + "' in the pack '" + parent.m_name + "' not found.");
	}
}

std::string Pack::Skybox::getPath() {
	return m_path;
}


Pack::Shader::Shader() = default;
Pack::Shader::~Shader() = default;

std::map<std::string, std::string> Pack::Shader::getShaders(nlohmann::json& shadersJson) {
	std::map<std::string, std::string> shaders;

	for (auto& shader : shadersJson.items()) {
		shaders.emplace(shader.key(), shader.value());
	}

	return shaders;
}
//std::string Pack::Shader::getPath() { return m_shaderPath; }


Pack::VertexShader::VertexShader(Pack& parent, std::string name) {

	auto& shaders = parent.m_descriptor.at("shaders");
	auto& vertexShaders = shaders.at("vertex");

	//for (auto& sh : models.items()) {

	//	if (model.key() == name) {

	//		if (isFound) {
	//			std::cerr << "Pack::Model::Model: model with the name '" << name
	//					  << "' occured more than one time in the pack '" << m_parent.m_name << "'." << std::endl;
	//			break;
	//		}

	//		isFound = true;

	//		m_modelPath = model.value().at("model_path");
	//		m_texturesPath = model.value().at("textures_path");
	//		m_materialType = model.value().at("material_type");
	//		m_vertexShader = model.value().at("vertex_shader");
	//		m_fragmentShader = model.value().at("fragment_shader");
	//	}
	//}

	//if (isFound) {
	//	std::cout << "Model '" << name << "' has been found in the pack '" << parent.m_name << "'." << std::endl;
	//}
	//else {
	//	throw ModelNotFoundException("model '" + name + "' in the pack '" + parent.m_name + "' not found.");
	//}
}

/**
 * @return all the *vertex shaders* in the pack in the format std::map<std::string, std::string> (shader name, shader
 * path).
 */
std::map<std::string, std::string> Pack::VertexShader::getShaders(Pack& parent) { 
	auto& shaders = parent.m_descriptor.at("shaders");
	auto& vertexShaders = shaders.at("vertex");

	return Shader::getShaders(vertexShaders);
}

/**
 * @return all the *fragment shaders* in the pack in the format std::map<std::string, std::string> (shader name, shader path).
 */
std::map<std::string, std::string> Pack::FragmentShader::getShaders(Pack& parent) {
	auto& shaders = parent.m_descriptor.at("shaders");
	auto& fragmentShaders = shaders.at("fragment");

	return Shader::getShaders(fragmentShaders);
}



std::unordered_map<std::string, Pack> Pack::m_packs;
