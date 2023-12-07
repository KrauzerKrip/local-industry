#pragma once

#include <string>
#include <functional>

#include <glm/glm.hpp>


class IInput {
public:
	virtual ~IInput() {};

	virtual bool isKeyPressed(std::string key) = 0;
	virtual glm::vec2 getMousePosition() = 0;
	virtual void addKeyCallback(std::function<void(std::string key)> callback) = 0;
	virtual void addMappedKeyCallback(std::string key, std::function<void()> callback) = 0;
	virtual void addMouseClickCallback(std::function<void(glm::vec2)> callback) = 0;
	//virtual asd getWheelOffsets() = 0;
};