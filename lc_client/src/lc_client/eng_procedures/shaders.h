#pragma once

#include <unordered_map>

#include <cmrc/cmrc.hpp>

#include "i_shaders.h"


class ShaderManager : IShaderManager{
public:
	ShaderManager();
	~ShaderManager();

	void loadShaders();

private:
	std::unordered_map<std::string, int>* m_pVertexShaders;
	std::unordered_map<std::string, int>* m_pFragmentShaders;

	void compileShader(int shader, std::string shaderName);
};
