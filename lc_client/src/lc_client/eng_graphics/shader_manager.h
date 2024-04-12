#pragma once

#include <string>

class ShaderManager {
public:
	virtual ~ShaderManager() {};

	virtual void loadShaders() = 0;
	virtual int getVertexShader(std::string shaderName) const = 0;
	virtual int getFragmentShader(std::string shaderName) const = 0;
};