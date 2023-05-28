#pragma once

#include <vector>
#include <string>
#include <tuple>

#include <imgui.h>

#include "lc_client/tier0/console/i_console_input.h"
#include "lc_client/tier0/imgui_fonts.h"
#include "lc_client/tier1/texture_manager.h"
#include "lc_client/tier0/conpar/parameters.h"


enum class MessageType { DEV_MESSAGE, MESSAGE, WARN, ANSWER, ANSWER_ERROR, USER_INPUT };

struct Message {
	MessageType type;
	std::string text;
};

class ConsoleGui {
public:
	ConsoleGui(
		IConsoleInput* pConsole, ImGuiFonts* pImGuiFonts, TextureManager* pTextureManager, Parameters* pParameters);

	void open();
	void close();
	void update();
	
	bool isOpened();

private:
	std::vector<Message> m_messages;
	std::vector<std::string> m_history;
	int m_historyPos = 0;
	IConsoleInput* m_pConsole = nullptr;
	ImGuiFonts* m_pImGuiFonts = nullptr;
	Parameters* m_pParameters = nullptr;
	bool m_isOpened = false;
	bool m_scrollToBottom = false;
	bool m_autoScroll = false;
	unsigned int m_copyIconTexture = 0;

	void enterCommand(std::string commandText);
	void addMessage(Message&& message);
	std::tuple<ImVec2, ImVec2> getTextSize(Message& message);

	static int textEditCallbackStub(ImGuiInputTextCallbackData* data);
	int textEditCallback(ImGuiInputTextCallbackData* data);
};