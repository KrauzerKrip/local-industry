#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "lc_client/eng_input/i_input.h"
#include "key_code.h"


class InputGlfw : public IInput {
public:
	InputGlfw();
	~InputGlfw();

	bool isKeyPressed(KeyCode key);
	glm::vec2 getMousePosition();
	void addKeyCallback(std::function<void(KeyCode key)> callback);
	void addMappedKeyCallback(KeyCode key, std::function<void()> callback);
	void addMouseCallback(std::function<void(glm::vec2)> callback);
	void invokeKeyCallbacks(int key, int action);
	void invokeMouseCallbacks(glm::vec2 position);

private: 
	std::unordered_map<KeyCode, int> m_keyMap;
	
	std::vector<std::function<void(KeyCode)>> m_keyCallbacks;
	std::unordered_map<KeyCode, std::function<void()>> m_mappedKeyCallbacks;
	std::vector<std::function<void(glm::vec2)>> m_mouseCallbacks;

	std::unordered_map<KeyCode, bool> m_keyStates;
	glm::vec2 m_mousePosition;


	double m_mouseOffsetX = 0;
	double m_mouseOffsetY = 0;

};