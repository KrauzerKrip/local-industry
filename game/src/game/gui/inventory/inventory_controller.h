#pragma once

#include <entt/entt.hpp>
#include "lc_client/eng_graphics/graphics_settings.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "inventory_view.h"


class InventoryController {
public:
	InventoryController(
		InventoryView* pView, GraphicsSettings* pSettings, Camera* pCamera, entt::registry* pRegistry);

	void input();

private:
	InventoryView* m_pView = nullptr;
	GraphicsSettings* m_pGraphicsSettings = nullptr;
	Camera* m_pCamera = nullptr;
	entt::registry* m_pRegistry = nullptr;
};