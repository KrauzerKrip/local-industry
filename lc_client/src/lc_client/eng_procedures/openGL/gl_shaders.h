#pragma once

#include <unordered_map>

#include "lc_client/eng_procedures/i_shaders.h"
#include "lc_client/util/i_eng_resource.h"


class ShaderManagerGl : public IShaderManager{
public:
	ShaderManagerGl(eng::IResource* pResource);
	~ShaderManagerGl();

	void loadShaders();
	int getVertexShader(std::string shaderName) const;
	int getFragmentShader(std::string shaderName) const;
private:
	std::unordered_map<std::string, int>* m_pVertexShaders;
	std::unordered_map<std::string, int>* m_pFragmentShaders;

	eng::IResource* m_pResource;

	void compileShader(int shader, std::string fileName);
};
