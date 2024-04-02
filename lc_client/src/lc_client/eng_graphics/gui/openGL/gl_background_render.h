#pragma once

#include <glm/glm.hpp>
#include <string>
#include <array>
#include <queue>

#include "lc_client/eng_graphics/gui/background_render.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_gui/paint_objects/text.h"
#include "lc_client/eng_graphics/openGL/gl_shader_loader.h"
#include "lc_client/eng_graphics/texture.h"
#include "lc_client/tier1/texture_manager.h"
#include "gl_blur_framebuffer.h"
#include "lc_client/eng_graphics/openGL/gl_framebuffer_controller.h"


class ShaderLoaderGl;

class BackgroundRenderGl : public BackgroundRender {
public:
	BackgroundRenderGl(IConsole* pConsole, ShaderLoaderGl* pShaderWork, TextureManager* pTextureManager,
		FramebufferController* pFramebufferController, IWindow* pWindow);

	void renderColor(ColorQuad colorQuad) override;
	void renderImage(ImageQuad imageQuad) override;
	Texture* getTexture(std::string path) override;
	void frame() override;

private:
	std::queue<ColorQuad> m_colorQuads;
	std::queue<ImageQuad> m_imageQuads;

	unsigned int m_colorShader;
	unsigned int m_imageShader;
	unsigned int m_blurShader;
	unsigned int m_vao;
	unsigned int m_vbo;
	glm::mat4 m_projection;

	FramebufferController* m_pFramebufferController = nullptr;
	TextureManager* m_pTextureManager = nullptr;
	IWindow* m_pWindow = nullptr;
};