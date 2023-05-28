#include "gui_console.h"
#include "gui_console.h"
#include "gui_console.h"
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
#include "lc_client/eng_graphics/openGL/gl_texture.h"


using namespace ImGui;


ConsoleGui::ConsoleGui(
	IConsoleInput* pConsole, ImGuiFonts* pImGuiFonts, TextureManager* pTextureManager, Parameters* pParameters) {
	m_pConsole = pConsole;
	m_pImGuiFonts = pImGuiFonts;
	m_pParameters = pParameters;

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

	ImDrawList* pDrawList = ImGui::GetWindowDrawList();

	int i = 0;

	for (auto& message : m_messages) {

		i++;

		ImVec2 textMin;
		ImVec2 textMax;
		std::tie(textMin, textMax) = getTextSize(message);

		auto mousePos = ImGui::GetMousePos();
		int colorSelection = 0;
		if (mousePos.x > textMin.x && mousePos.x < textMax.x && mousePos.y > textMin.y && mousePos.y < textMax.y) {
			colorSelection = 20;
		}

		if (i % 2 == 0) {
			pDrawList->AddRectFilled(textMin, textMax, IM_COL32(255, 255, 255, 20 + colorSelection));
		}
		else {
			pDrawList->AddRectFilled(textMin, textMax, IM_COL32(127, 127, 127, colorSelection));
		}

		PushTextWrapPos(0.0f);

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

		PopTextWrapPos();

		SameLine();

		ImGui::SetCursorPosX(0);
		std::string buttonId = "##" + std::to_string(i);
		if (InvisibleButton(buttonId.c_str(), ImVec2(GetWindowSize().x, textMax.y - textMin.y))) {
			SetClipboardText(message.text.c_str());
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

	if (m_pParameters->getParameterValue<bool>("gui_imgui_debug")) {
		ImGui::ShowMetricsWindow();
	}

	ImGui::EndChild();

	ImGuiInputTextFlags inputTextFlags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion |
										 ImGuiInputTextFlags_CallbackHistory;

	ImGui::Separator();

	SetItemDefaultFocus();

	if (m_reclaimFocus) {
		SetKeyboardFocusHere();
	}

	ImGui::PushItemWidth(GetWindowWidth() - 128);
	if (InputText(" ", &m_commandText, inputTextFlags, &textEditCallbackStub, (void*)this)) {
		enterCommand(m_commandText);
		m_commandText.clear();
	}

	// this workaround doesn`t work
	if ((IsMouseHoveringRect(ImVec2(GetWindowPos().x + GetWindowWidth() - 64, GetWindowPos().y - 64),
			ImVec2(GetWindowPos().x + GetWindowWidth(), GetWindowPos().y + 64)))) {
	}
	else {
		if (IsMouseClicked(ImGuiMouseButton_Left)) {
			if (IsMouseHoveringRect(GetItemRectMin(), GetItemRectMax())) {
				m_reclaimFocus = true;
			}
			else {
				m_reclaimFocus = false;
			}
		}
	}

	//pDrawList->AddRectFilled(ImVec2(GetWindowPos().x + GetWindowWidth() - 64, GetWindowPos().y - 64),
	//	ImVec2(GetWindowPos().x + GetWindowWidth(), GetWindowPos().y + 64),
	//	IM_COL32(255, 255, 255, 255));

	SameLine();
	//if (Button("Submit")) {
	//	enterCommand(commandText);
	//}

	PopFont();

	ImGui::End();
}

bool ConsoleGui::isOpened() { return m_isOpened; }

void ConsoleGui::enterCommand(std::string commandText) {
	try {
		Message message{MessageType::USER_INPUT, commandText};

		m_historyPos = -1;
		for (std::vector<std::string>::iterator itr = m_history.begin(); itr < m_history.end(); itr++) {
			if (*itr == message.text) {
				m_history.erase(itr);
				break;
			}
		}
		m_history.push_back(message.text);

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

std::tuple<ImVec2, ImVec2> ConsoleGui::getTextSize(Message& message) {
	auto textSize = CalcTextSize(message.text.c_str(), NULL, false, GetWindowWidth());

	ImVec2 sPos = ImGui::GetCursorScreenPos();

	if (message.type == MessageType::ANSWER || message.type == MessageType::ANSWER_ERROR) {
		textSize.y *= 2;
	}

	ImVec2 textMin = ImVec2(sPos.x, sPos.y);
	ImVec2 textMax = ImVec2(GetWindowWidth() + sPos.x, textSize.y + sPos.y);

	return std::tuple(textMin, textMax);
}

int ConsoleGui::textEditCallbackStub(ImGuiInputTextCallbackData* data) {
	ConsoleGui* console = (ConsoleGui*)data->UserData;
	return console->textEditCallback(data);
}


/**
 * https://github.com/ocornut/imgui/blob/master/imgui_demo.cpp#L6867
 */
int ConsoleGui::textEditCallback(ImGuiInputTextCallbackData* data) {
	switch (data->EventFlag) {
	//case ImGuiInputTextFlags_CallbackCompletion: {
	//	// Locate beginning of current word
	//	const char* word_end = data->Buf + data->CursorPos;
	//	const char* word_start = word_end;
	//	while (word_start > data->Buf) {
	//		const char c = word_start[-1];
	//		if (c == ' ' || c == '\t' || c == ',' || c == ';')
	//			break;
	//		word_start--;
	//	}

	//	// Build a list of candidates
	//	ImVector<const char*> candidates;
	//	for (int i = 0; i < Commands.Size; i++)
	//		if (Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
	//			candidates.push_back(Commands[i]);

	//	if (candidates.Size == 0) {
	//		// No match
	//		AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
	//	}
	//	else if (candidates.Size == 1) {
	//		// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
	//		data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
	//		data->InsertChars(data->CursorPos, candidates[0]);
	//		data->InsertChars(data->CursorPos, " ");
	//	}
	//	else {
	//		// Multiple matches. Complete as much as we can..
	//		// So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
	//		int match_len = (int)(word_end - word_start);
	//		for (;;) {
	//			int c = 0;
	//			bool all_candidates_matches = true;
	//			for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
	//				if (i == 0)
	//					c = toupper(candidates[i][match_len]);
	//				else if (c == 0 || c != toupper(candidates[i][match_len]))
	//					all_candidates_matches = false;
	//			if (!all_candidates_matches)
	//				break;
	//			match_len++;
	//		}

	//		if (match_len > 0) {
	//			data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
	//			data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
	//		}

	//		// List matches
	//		AddLog("Possible matches:\n");
	//		for (int i = 0; i < candidates.Size; i++)
	//			AddLog("- %s\n", candidates[i]);
	//	}

	//	break;
	//}
	case ImGuiInputTextFlags_CallbackHistory: {
		const int prevHistoryPos = m_historyPos;
		if (data->EventKey == ImGuiKey_UpArrow) {
			if (m_historyPos == -1) {
				m_historyPos = m_history.size() - 1;
			}
			else if (m_historyPos > 0) {
				m_historyPos--;
			}
		}
		else if (data->EventKey == ImGuiKey_DownArrow) {
			if (m_historyPos != -1) {
				if (++m_historyPos >= m_history.size()) {
					m_historyPos = -1;
				}
			}
		}

		if (prevHistoryPos != m_historyPos) {
			const char* history_str = (m_historyPos >= 0) ? m_history[m_historyPos].c_str() : "";
			data->DeleteChars(0, data->BufTextLen);
			data->InsertChars(0, history_str);
		}
	}
	}
	return 0;
}
