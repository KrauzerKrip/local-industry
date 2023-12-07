#include "gl_shaders.h"

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "lc_client/util/directories.h"
#include "lc_client/util/file_util.h"
#include "lc_client/util/pack.h"
#include "lc_client/tier1/game_info.h"


ShaderManagerGl::ShaderManagerGl(eng::IResource* pResource) {
	m_pVertexShaders = new std::unordered_map<std::string, int>();
	m_pFragmentShaders = new std::unordered_map<std::string, int>();

	m_pResource = pResource;
};

ShaderManagerGl::~ShaderManagerGl() {

	for (auto const& [name, id] : *m_pVertexShaders) {
		glDeleteShader(id);
	}

	for (auto const& [name, id] : *m_pFragmentShaders) {
		glDeleteShader(id);
	}

	delete (m_pVertexShaders);
	delete (m_pFragmentShaders);
}

/**
 * \brief Loads shaders, compiles them and adds them into the storage so its possible to access shaders with theirs ids.
 */
void ShaderManagerGl::loadShaders() {

	GameInfo gameInfo;
	std::map<std::string, std::string> packs = gameInfo.getPacks();

	for (auto& [name, path] : packs) {
		Pack pack = Pack::getPack(name);
		auto packShaders = Pack::VertexShader::getShaders(pack);

		std::map<std::string, std::string> vertexShaders = Pack::VertexShader::getShaders(pack);
		std::map<std::string, std::string> fragmentShaders = Pack::FragmentShader::getShaders(pack);

		for (auto& [name, path] : vertexShaders) {
			unsigned int shader;
			shader = glCreateShader(GL_VERTEX_SHADER);

			compileShader(shader, path);

			m_pVertexShaders->emplace(name, shader);
		}

		for (auto& [name, path] : fragmentShaders) {
			unsigned int shader;
			shader = glCreateShader(GL_FRAGMENT_SHADER);

			compileShader(shader, path);

			m_pFragmentShaders->emplace(name, shader);
		}
	}
}

/**
 *  \returns OpenGL vertex shader ID.
 *  \throws std::out_of_range if shader is not found.
 */
int ShaderManagerGl::getVertexShader(std::string shaderName) const {
	try {
		return m_pVertexShaders->at(shaderName);
	}
	catch (std::out_of_range) {
		throw std::out_of_range("ShaderManagerGl: vertex shader not found: " + shaderName);
	}
}

/**
 * \returns OpenGL fragment shader ID.
 * \throws std::out_of_range if shader is not found.
 */
int ShaderManagerGl::getFragmentShader(std::string shaderName) const {
	try {
		return m_pFragmentShaders->at(shaderName);
	}
	catch (std::out_of_range) {
		throw std::out_of_range("ShaderManagerGl: fragment shader not found: " + shaderName);
	}
}

void ShaderManagerGl::compileShader(int shader, std::string path) {

	std::vector<unsigned char> buffer = m_pResource->getFileResource(path);
	std::string shaderCode{buffer.begin(), buffer.end()};
	GLchar const* files[] = {shaderCode.c_str()};

	glShaderSource(shader, 1, files, NULL);

	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (success) {
		std::cout << "shaders: shader compiled: " << path << std::endl;
	}
	else {
		glGetShaderInfoLog(shader, 512, 0, infoLog);
		std::cerr << "shaders: shader '" << path << "' compilation failure : \n " << infoLog << std::endl;
	}
}
