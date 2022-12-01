#pragma once

#include "lc_client/loop.h"

class Time {
public:
	static float getTime();

private:
	friend void Loop::startLoop();

	static float m_deltaTime;
	
};
