#pragma once

#include <unordered_map>

#include "lc_client/tier1/i_shaders.h"
#include "lc_client/util/i_eng_resource.h"


class ShaderManagerGl : public IShaderManager{
public:
	ShaderManagerGl(eng::IResource* pResource);
	~ShaderManagerGl();

	void loadShaders();
	int getVertexShader(std::string path) const;
	int getFragmentShader(std::string path) const;

private:
	std::unordered_map<std::string, int>* m_pVertexShaders;
	std::unordered_map<std::string, int>* m_pFragmentShaders;

	eng::IResource* m_pResource;

	void compileShader(int shader, std::string path);
};
