#pragma once

#include "lc_client/tier0/conpar/parameters.h"


class GraphicsSettings {
public:
	GraphicsSettings(Parameters* pParameters);

	float getFov();
	bool getVSync();

private:

	Parameters* m_pParameters = nullptr;
	
	float m_fov = 90.0f;
	bool m_vSync = false;;
};
