#pragma once

class IShaderManager {
public:
	virtual ~IShaderManager() {};

	virtual void loadShaders() = 0;
	virtual int getVertexShader(std::string shaderName) = 0;
	virtual int getFragmentShader(std::string shaderName) = 0;
};