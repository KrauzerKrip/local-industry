#pragma once

#include <string>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <map>

#include <nlohmann/json.hpp>

#include "lc_client/util/i_eng_resource.h"


class Pack {
public:
	static void loadPack(const std::string name, const std::string path, eng::IResource* pResource);
	static Pack& getPack(std::string name);

	Pack(const std::string name, const std::string path, eng::IResource* pResource);
	~Pack();


	class Model {
	public:
		Model(Pack& parent, std::string name);
		~Model();

		std::string getPath();
		std::string getTexturesPath();
		std::string getMaterialType();
		std::string getVertexShader();
		std::string getFragmentShader();

	private:
		Pack& m_parent;

		std::string m_modelPath;
		std::string m_texturesPath;
		std::string m_materialType;
		std::string m_vertexShader;
		std::string m_fragmentShader;
	};

	class Shader {
	public:
		Shader();
		~Shader();


		//std::string getPath();

	protected:
		static std::map<std::string, std::string> getShaders(nlohmann::json& shadersJson);
		std::string m_shaderPath;
	};

	class VertexShader : public Shader {
		VertexShader(Pack& parent, std::string name);
		~VertexShader();

		static std::map<std::string, std::string> getShaders(Pack& parent);

	};

	class FragmentShader : public Shader {
		FragmentShader(Pack& parent, std::string name);
		~FragmentShader();

		static std::map<std::string, std::string> getShaders(Pack& parent);

	};

private:
	static std::unordered_map<std::string, Pack> m_packs;

	std::string m_name;
	std::string m_path;
	nlohmann::json m_descriptor;
};
