#pragma once

#include <array>
#include <functional>

#include "lc_client/tier0/conpar/parameters.h"


class GraphicsSettings {
public:
	GraphicsSettings(Parameters* pParameters);

	float getFov();
	bool getVSync();
	std::array<int, 2> getWindowSize();
	std::array<int, 2> getWindowAspectRatio();

	void addUpdateCallback(std::function<void(GraphicsSettings* pGraphicsSettings)> callback);


private:
	void updateCallbacks();

	Parameters* m_pParameters = nullptr;
	
	float m_fov = 90.0f;
	bool m_vSync = false;
	std::array<int, 2> m_windowSize;
	std::array<int, 2> m_windowAspectRatio;

	std::vector<std::function<void(GraphicsSettings* pGraphicsSettings)>> m_updateCallbacks;
};
