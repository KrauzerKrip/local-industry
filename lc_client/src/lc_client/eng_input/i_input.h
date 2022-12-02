#pragma once

#include <string>

class IInput {
public:
	virtual ~IInput() {};

	virtual bool isKeyPressed(std::string key) = 0;
	virtual double getMousePosX() = 0;
	virtual double getMousePosY() = 0;
	//virtual asd getWheelOffsets() = 0;
};