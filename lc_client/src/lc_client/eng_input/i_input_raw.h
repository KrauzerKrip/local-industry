#pragma once

#include <string>
#include <functional>


class IInputRaw {
public:
	virtual ~IInputRaw() {};

	virtual bool isKeyPressed(std::string key) = 0;
	virtual double getMousePosX() = 0;
	virtual double getMousePosY() = 0;
	virtual void addKeyCallback(std::string key, std::function<void()> callback) = 0;
	//virtual asd getWheelOffsets() = 0;
};