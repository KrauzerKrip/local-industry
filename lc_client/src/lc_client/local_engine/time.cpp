#include "ldk_client/local_engine/time.h"

float Time::getDeltaTime() {
		return m_deltaTime;
}

float Time::m_deltaTime = 0.0f;