#pragma once

#include <array>
#include <functional>

#include "lc_client/tier0/conpar/parameters.h"
#include "lc_client/eng_graphics/i_window.h"


class GraphicsSettings {
public:
	GraphicsSettings(Parameters* pParameters);

	float getFov();
	bool getVSync();
	std::array<int, 2> getWindowSize();
	std::array<int, 2> getWindowAspectRatio();
	WindowMode getWindowMode();

	void addUpdateCallback(std::function<void(GraphicsSettings* pGraphicsSettings)> callback);


private:
	void updateCallbacks();

	WindowMode windowModeStrToEnum(std::string modeStr);

	Parameters* m_pParameters = nullptr;
	
	float m_fov;
	bool m_vSync;
	std::array<int, 2> m_windowSize;
	std::array<int, 2> m_windowAspectRatio;
	WindowMode m_windowMode;

	std::vector<std::function<void(GraphicsSettings* pGraphicsSettings)>> m_updateCallbacks;
};
