#pragma once

#include <unordered_map>

#include "i_shaders.h"


class ShaderManager : public IShaderManager{
public:
	ShaderManager();
	~ShaderManager();

	void loadShaders();
	int getVertexShader(std::string shaderName) const;
	int getFragmentShader(std::string shaderName) const;
private:
	std::unordered_map<std::string, int>* m_pVertexShaders;
	std::unordered_map<std::string, int>* m_pFragmentShaders;

	void compileShader(int shader, std::string fileName);
};
