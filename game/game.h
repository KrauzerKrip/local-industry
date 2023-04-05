#pragma once

#include "lc_client/i_game_logic.h"

#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/i_render.h"
#include "lc_client/eng_input/i_input.h"
#include "lc_client/eng_scene/scene.h"
#include "lc_client/eng_procedures/i_shaders.h"
#include "lc_client/eng_procedures/openGL/shaders.h"
#include "lc_client/eng_procedures/graphics_entities_loading.h"
#include "lc_client/util/i_eng_resource.h"
#include "lc_client/eng_procedures/openGL/gl_texture_manager.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "lc_client/eng_model/model_manager.h"


class Game : public IGameLogic {
public:
	Game(IWindow *pWindow);
	virtual ~Game();

	void init();
	void input();
	void update();
	void render();
	void cleanUp();

private:
	IWindow* m_pWindow;;
	IInput* m_pInput;
	Camera* m_pCamera;
	IRender* m_pRender;
	Scene* m_pScene;
	IShaderManager* m_pShaderManager;
	TextureManager* m_pTextureManager;
	eng::IResource* m_pResource;
	ModelManager* m_pModelManager;

	double m_lastMousePosX = 0.0;
	double m_lastMousePosY = 0.0;
	float m_sensivity = 0.1f;
};
