#pragma once

#include <unordered_map>

#include "lc_client/eng_graphics/shader_manager.h"
#include "lc_client/util/i_eng_resource.h"


class ShaderManagerGl : public ShaderManager {
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
