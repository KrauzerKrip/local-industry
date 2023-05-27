#pragma once

#include <vector>
#include <string>

#include <imgui.h>

#include "lc_client/tier0/console/i_console_input.h"
#include "lc_client/tier0/imgui_fonts.h"

enum class MessageType { DEV_MESSAGE, MESSAGE, WARN, ANSWER, ANSWER_ERROR, USER_INPUT };

struct Message {
	MessageType type;
	std::string text;
};

class ConsoleGui {
public:
	ConsoleGui(IConsoleInput* pConsole, ImGuiFonts* pImGuiFonts);

	void open();
	void close();
	void update();
	
	bool isOpened();

private:
	std::vector<Message> m_messages;
	IConsoleInput* m_pConsole = nullptr;
	bool m_isOpened = false;
	ImGuiFonts* m_pImGuiFonts = nullptr;
	bool m_scrollToBottom = false;
	bool m_autoScroll = false;

	void enterCommand(std::string commandText);
	void addMessage(Message&& message);
};