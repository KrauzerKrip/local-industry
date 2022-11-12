#pragma once

#include "lc_client/i_game_logic.h"

#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/i_render.h"
#include "lc_client/eng_input/i_input.h"
#include "lc_client/eng_scene/scene.h"
#include "lc_client/eng_procedures/i_shaders.h"
#include "lc_client/eng_procedures/openGL/shaders.h"
#include "lc_client/eng_procedures/i_graphics_entities_loading.h"
#include "lc_client/util/i_eng_resource.h"
#include "lc_client/eng_procedures/openGL/gl_texture_manager.h"


class Game : public IGameLogic {
public:
	Game(IWindow *pWindow);
	virtual ~Game();

	void init();
	void update();
	void render();
	void cleanUp();

private:
	IWindow* m_pWindow;;
	IInput* m_pInput;
	IRender* m_pRender;
	Scene* m_pScene;
	IShaderManager* m_pShaderManager;
	TextureManager* m_pTextureManager;
	IGraphicsEntitiesLoading* m_pGraphicsEntitiesLoading;
	eng::IResource* m_pResource;
};
