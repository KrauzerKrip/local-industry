#include "gui_console.h"
#include "gui_console.h"

#include <imgui.h>
#include <imgui_stdlib.h>


using namespace ImGui;


ConsoleGui::ConsoleGui(IConsoleInput* pConsole) { 
	m_pConsole = pConsole;

	ImGuiIO io;

	//ImFont* m_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 17.0f);
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

	Begin("Console", &isOpened, ImGuiWindowFlags_NoScrollbar);

	m_isOpened = isOpened;

	//PushFont(m_font);

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


	End();
}

bool ConsoleGui::isOpened() { return m_isOpened; }
