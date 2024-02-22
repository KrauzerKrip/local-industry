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

	private:
		Pack& m_parent;

		std::string m_modelPath;
	};

	class Skybox {
	public:
		Skybox(Pack& parent, std::string name);
		~Skybox() = default;

		std::string getPath();

	private:
		Pack& m_parent;

		std::string m_path;
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
	public:
		VertexShader(Pack& parent, std::string name);
		~VertexShader();

		static std::map<std::string, std::string> getShaders(Pack& parent);

	};

	class FragmentShader : public Shader {
	public:
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
