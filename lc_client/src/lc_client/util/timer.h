#pragma once

#include <chrono>

class Timer {
public:
	void start() {
		m_startTime = std::chrono::system_clock::now();
	}

	void stop() {
		m_endTime = std::chrono::system_clock::now();
	}

	long long elapsedMilliseconds() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_endTime - m_startTime).count();
	}

	void showWindow();

private:
	std::chrono::time_point<std::chrono::system_clock> m_startTime;
	std::chrono::time_point<std::chrono::system_clock> m_endTime;
};
