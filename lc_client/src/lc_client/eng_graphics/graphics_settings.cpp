#include "graphics_settings.h"

GraphicsSettings::GraphicsSettings(Parameters* pParameters) { 
	m_pParameters = pParameters;

	m_fov = pParameters->getParameter<float>("gh_fov").getValue();
	m_windowSize[0] = pParameters->getParameter<int>("gh_window_width").getValue();
	m_windowSize[1] = pParameters->getParameter<int>("gh_window_height").getValue();
	m_windowAspectRatio[0] = pParameters->getParameter<int>("gh_window_aspect_ratio_x").getValue();
	m_windowAspectRatio[1] = pParameters->getParameter<int>("gh_window_aspect_ratio_y").getValue();
	m_windowMode = this->windowModeStrToEnum(pParameters->getParameter<std::string>("gh_window_mode").getValue());


	pParameters->getParameter<float>("gh_fov").setCallback([this](float value) {
		m_fov = value;
		this->updateCallbacks();
		});
	pParameters->getParameter<bool>("gh_vsync").setCallback([this](bool value) {
		m_vSync = value;
		this->updateCallbacks();
	});
	pParameters->getParameter<int>("gh_window_width").setCallback([this](int value) {
		m_windowSize[0] = value;
		this->updateCallbacks();
	});
	pParameters->getParameter<int>("gh_window_height").setCallback([this](int value) {
		m_windowSize[1] = value;
		this->updateCallbacks();
	});
	pParameters->getParameter<int>("gh_window_aspect_ratio_x").setCallback([this](int value) {
		m_windowAspectRatio[0] = value;
		this->updateCallbacks();
	});
	pParameters->getParameter<int>("gh_window_aspect_ratio_y").setCallback([this](int value) {
		m_windowAspectRatio[1] = value;
		this->updateCallbacks();
	});
	pParameters->getParameter<std::string>("gh_window_mode").setCallback([this](std::string value) {
		m_windowMode = this->windowModeStrToEnum(value);
		this->updateCallbacks();
	});
}

float GraphicsSettings::getFov() { return m_fov; }

bool GraphicsSettings::getVSync() {
	return m_vSync;
}

std::array<int, 2> GraphicsSettings::getWindowSize() { return m_windowSize; }

std::array<int, 2> GraphicsSettings::getWindowAspectRatio() { return m_windowAspectRatio; }

WindowMode GraphicsSettings::getWindowMode() { return m_windowMode; }

void GraphicsSettings::addUpdateCallback(std::function<void(GraphicsSettings* pGraphicsSettings)> callback) {
	m_updateCallbacks.push_back(callback);
}

void GraphicsSettings::updateCallbacks() {
	for (auto& callback : m_updateCallbacks) {
		callback(this);
	}
}

WindowMode GraphicsSettings::windowModeStrToEnum(std::string modeStr) {
	if (modeStr == "windowed") {
		return WindowMode::WINDOWED;
	}
	else if (modeStr == "fullscreen") {
		return WindowMode::FULLSCREEN;
	}
}