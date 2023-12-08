#pragma once 

#include <memory>

#include "lc_client/eng_graphics/skybox_render.h"
#include "lc_client/eng_graphics/openGL/gl_shader_loader.h"
#include "lc_client/eng_cubemaps/cubemap_loader.h"
#include "lc_client/eng_cubemaps/cubemap_texture_loader.h"


class ShaderLoaderGl;

class SkyboxRenderGl : public SkyboxRender {
public:
	SkyboxRenderGl(CubemapMaterial* material, ShaderLoaderGl* pShaderWork);
	void render(glm::mat4& projection, glm::mat4& view);
	void bindTexture();

private:
	unsigned int m_texture;
	unsigned int m_vao;
	unsigned int m_shader;
};
