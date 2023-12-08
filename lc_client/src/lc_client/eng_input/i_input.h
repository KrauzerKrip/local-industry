#pragma once

#include <string>
#include <functional>

#include <glm/glm.hpp>
#include "key_code.h"


class IInput {
public:
	virtual ~IInput() {};

	virtual bool isKeyPressed(KeyCode key) = 0;
	virtual glm::vec2 getMousePosition() = 0;
	virtual glm::vec2 getMouseWheelOffset() = 0;
	virtual void addKeyCallback(std::function<void(KeyCode key)> callback) = 0;
	virtual void addMappedKeyCallback(KeyCode key, std::function<void()> callback) = 0;
	virtual void addMouseCallback(std::function<void(glm::vec2)> callback) = 0;
	virtual void addMouseWheelCallback(std::function<void(glm::vec2)> callback) = 0;
	//virtual asd getWheelOffsets() = 0;
};