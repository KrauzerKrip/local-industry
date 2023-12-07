#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "lc_client/eng_input/i_input.h"


class InputGlfw : public IInput {
public:
	InputGlfw();
	~InputGlfw();

	bool isKeyPressed(std::string key);
	glm::vec2 getMousePosition();
	void addKeyCallback(std::function<void(std::string key)> callback);
	void addMappedKeyCallback(std::string key, std::function<void()> callback);
	void addMouseClickCallback(std::function<void(glm::vec2)> callback);
	void invokeKeyCallbacks(int key, int action);
	void invokeMouseCallbacks(glm::vec2 position);

private: 
	std::unordered_map<std::string, int> m_keyMap;
	
	std::vector<std::function<void(std::string)>> m_keyCallbacks;
	std::unordered_map<std::string, std::function<void()>> m_mappedKeyCallbacks;
	std::vector<std::function<void(glm::vec2)>> m_mouseCallbacks;

	std::unordered_map<std::string, bool> m_keyStates;
	glm::vec2 m_mousePosition;


	double m_mouseOffsetX = 0;
	double m_mouseOffsetY = 0;

};