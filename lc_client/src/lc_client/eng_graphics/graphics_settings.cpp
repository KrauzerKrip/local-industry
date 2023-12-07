#include "graphics_settings.h"

GraphicsSettings::GraphicsSettings(Parameters* pParameters) { 
	m_pParameters = pParameters;

	pParameters->getParameter<float>("gh_fov").setCallback([this](float fov) { m_fov = fov;  });
	pParameters->getParameter<bool>("gh_vsync").setCallback([this](bool vSync) { m_vSync = vSync; });
}

float GraphicsSettings::getFov() { return m_fov; }

bool GraphicsSettings::getVSync() {
	return m_vSync;
}
