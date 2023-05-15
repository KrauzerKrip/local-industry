#pragma once

#include <string>

class IInputRaw {
public:
	virtual ~IInputRaw() {};

	virtual bool isKeyPressed(std::string key) = 0;
	virtual double getMousePosX() = 0;
	virtual double getMousePosY() = 0;
	//virtual asd getWheelOffsets() = 0;
};