#include "gui_console.h"
#include "gui_console.h"

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

#include <imgui.h>
#include <imgui_stdlib.h>

#include "lc_client/exceptions/conpar_exceptions.h"
#include "lc_client/exceptions/command_exceptions.h"


using namespace ImGui;


ConsoleGui::ConsoleGui(IConsoleInput* pConsole, ImGuiFonts* pImGuiFonts) { 
	m_pConsole = pConsole;
	m_pImGuiFonts = pImGuiFonts;

	Callbacks* callbacks = new Callbacks();

	callbacks->pDevMessageCallback = [this](std::string text) {
		
		Message message;

		message.type = MessageType::DEV_MESSAGE;
		std::time_t t = std::time(nullptr);
		std::tm tm = *std::localtime(&t);
		std::stringstream buffer;
		buffer << std::put_time(&tm, "%T");
		std::string timeString = buffer.str();
		message.text = "[" + timeString + "] " + "[DEV] " + text;
		addMessage(std::move(message));
	};

	callbacks->pMessageCallback = [this](std::string text) {
		Message message;

		message.type = MessageType::MESSAGE;
		std::time_t t = std::time(nullptr);
		std::tm tm = *std::localtime(&t);
		std::stringstream buffer;
		buffer << std::put_time(&tm, "%T");
		std::string timeString = buffer.str();
		message.text = "[" + timeString + "] " + "[INFO] " + text;
		addMessage(std::move(message));
	};

	callbacks->pWarnCallback = [this](std::string text) {
		Message message;

		message.type = MessageType::WARN;
		std::time_t t = std::time(nullptr);
		std::tm tm = *std::localtime(&t);
		std::stringstream buffer;
		buffer << std::put_time(&tm, "%T");
		std::string timeString = buffer.str();
		message.text = "[" + timeString + "] " + "[WARNING] " + text;
		addMessage(std::move(message));
	};


	
	m_pConsole->setCallbacks(callbacks);
}

void ConsoleGui::open() { m_isOpened = true; }

void ConsoleGui::close() { m_isOpened = false; }

void ConsoleGui::update() {

	if (!m_isOpened) {
		return;
	}

	SetNextWindowPos(ImVec2(100, 80));

	SetNextWindowSize(ImVec2(1080, 720));


	PushFont(m_pImGuiFonts->m_pFontText);

	Begin("Console", &this->m_isOpened, ImGuiWindowFlags_NoScrollbar);

	BeginChild("Scrolling", ImVec2(1080 - 10, 720 - 90), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);

	for (auto& message : m_messages) {
		if (message.type == MessageType::DEV_MESSAGE) {
			TextColored(ImVec4(52 / 255.0f, 152 / 255.0f, 219 / 255.0f, 1.0f), message.text.c_str());
		}
		else if (message.type == MessageType::MESSAGE) {
			TextColored(ImVec4(46 / 255.0f, 204 / 255.0f, 113 / 255.0f, 1.0f), message.text.c_str());
		}
		else if (message.type == MessageType::WARN) {
			TextColored(ImVec4(231 / 255.0f, 76 / 255.0f, 60 / 255.0f, 1.0f), message.text.c_str());
		}
		else if (message.type == MessageType::ANSWER) {
			auto str = "^ \n" + message.text;
			Text(str.c_str());
		}
		else if (message.type == MessageType::ANSWER_ERROR) {
			auto str = "^ \n" + message.text;
			TextColored(ImVec4(231 / 255.0f, 76 / 255.0f, 60 / 255.0f, 1.0f), str.c_str());
		}
		else if (message.type == MessageType::USER_INPUT) {
			auto str = "> " + message.text;
			TextColored(ImVec4(189 / 255.0f, 195 / 255.0f, 199 / 255.0f, 1.0f), str.c_str());
		}
	}


	if (m_scrollToBottom && m_autoScroll) {
		SetScrollHereY(1.0f);
	}

	
	if (GetScrollY() == GetScrollMaxY()) {
		m_autoScroll = true;
	}
	else {
		m_autoScroll = false;
	}

	m_scrollToBottom = false;


	EndChild();

	std::string commandText;

	ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue  |
										   ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;

	Separator();


	PushItemWidth(GetWindowWidth()-128);
	if (InputText(" ", &commandText, input_text_flags)) {
		enterCommand(commandText);
	}

	SameLine();

	if (Button("Submit")) {
		enterCommand(commandText);
	}

	PopFont();

	End();
}

bool ConsoleGui::isOpened() { return m_isOpened; }

void ConsoleGui::enterCommand(std::string commandText) {
	try {
		Message message{MessageType::USER_INPUT, commandText};
		addMessage(std::move(message));
		m_pConsole->enter(commandText);
	}
	catch (ConsoleParameterNotFoundException& exception) {
		Message message{MessageType::ANSWER_ERROR, exception.what()};
		addMessage(std::move(message));
	}
	catch (IncorrectCommandException& exception) {
		Message message{MessageType::ANSWER_ERROR, exception.what()};
		addMessage(std::move(message));
	}
	catch (ConsoleParameterCheatsException& exception) {
		Message message{MessageType::ANSWER_ERROR, exception.what()};
		addMessage(std::move(message));
	}
	catch (std::invalid_argument& exception) {
		Message message{MessageType::ANSWER_ERROR, "Inappropriate argument."};
		addMessage(std::move(message));
	}

	m_autoScroll = true;
}

void ConsoleGui::addMessage(Message&& message) { 
	m_messages.push_back(message);
	m_scrollToBottom = true;
}
