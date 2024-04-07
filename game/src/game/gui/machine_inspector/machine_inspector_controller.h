#pragma once

#include <entt/entt.hpp>
#include "lc_client/eng_graphics/graphics_settings.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "machine_inspector_view.h"


class MachineInspectorController {
public:
	MachineInspectorController(MachineInspectorView* pView, GraphicsSettings* pSettings, Camera* pCamera, entt::registry* pRegistry);

	void input();

private:
	MachineInspectorView* m_pView = nullptr;
	GraphicsSettings* m_pGraphicsSettings = nullptr;
	Camera* m_pCamera = nullptr;
	entt::registry* m_pRegistry = nullptr;
};