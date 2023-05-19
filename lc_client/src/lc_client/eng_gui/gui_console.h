#pragma once

#include <vector>
#include <chrono>

#include "lc_client/tier0/console/i_console_input.h"

enum class MessageType { DEV_MESSAGE, MESSAGE, WARN };

struct Message {
	MessageType type;
	std::chrono::time_point<std::chrono::system_clock> time;
	std::string timeString;
	std::string text;
};

class ConsoleGui {
public:
	ConsoleGui(IConsoleInput* pConsole);

	void open();
	void close();
	void update();

private:
	std::vector<Message> m_messages;
	IConsoleInput* m_pConsole;
	bool isOpened = false;
};