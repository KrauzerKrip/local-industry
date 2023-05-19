#include "gui_console.h"
#include "gui_console.h"

#include <imgui.h>
#include <imgui_stdlib.h>


using namespace ImGui;


ConsoleGui::ConsoleGui(IConsoleInput* pConsole, ImGuiFonts* pImGuiFonts) { 
	m_pConsole = pConsole;
	m_pImGuiFonts = pImGuiFonts;
}

void ConsoleGui::open() { m_isOpened = true; }

void ConsoleGui::close() { m_isOpened = false; }

void ConsoleGui::update() {
	if (!m_isOpened) {
		return;
	}


	// BeginChild("Scrolling");
	// for (int n = 0; n < 50; n++)
	//	Text("%04d: Some text", n);
	// EndChild();

	bool var;

	SetNextWindowPos(ImVec2(100, 80));

	SetNextWindowSize(ImVec2(1080, 720));

	bool isOpened;

	PushFont(m_pImGuiFonts->m_pFontText);

	Begin("Console", &isOpened, ImGuiWindowFlags_NoScrollbar);

	m_isOpened = isOpened;

	BeginChild("Scrolling", ImVec2(1080 - 10, 720 - 120), true);
	for (int n = 0; n < 0; n++)
		Text("%04d: Some text", n);
	EndChild();

	std::string commandText;

	ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue  |
										   ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;

	Separator();


	PushItemWidth(GetWindowWidth()-128);
	if (InputText(" ", &commandText, input_text_flags)) {
		
	}

	SameLine();

	Button("Submit");

	PopFont();

	End();
}

bool ConsoleGui::isOpened() { return m_isOpened; }
