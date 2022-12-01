#pragma once

class IInput {
public:
	virtual ~IInput() {};

	virtual bool isKeyPressed(const char* key) = 0;
	virtual double getMousePosX() = 0;
	virtual double getMousePosY() = 0;
	//virtual asd getWheelOffsets() = 0;
};