#include "ldk_client/local_engine/time.h"

float Time::getTime() {
		return m_deltaTime;
}

float Time::m_deltaTime = 0.0f;