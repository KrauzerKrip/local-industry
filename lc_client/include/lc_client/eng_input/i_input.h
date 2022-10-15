#pragma once

class IInput {
public:
	virtual ~IInput() {};

	virtual bool getKeyPressed(const char* key) = 0;
	//virtual asd getWheelOffsets() = 0;
};