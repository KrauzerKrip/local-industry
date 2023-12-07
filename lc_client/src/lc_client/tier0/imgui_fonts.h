#pragma once

#include <imgui.h>

struct ImGuiFonts {
	ImFont* m_pFontTitles;
	ImFont* m_pFontText;

	ImGuiFonts() { 
		auto io = ImGui::GetIO();
		m_pFontTitles = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 36.0f);
		m_pFontText = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 24.0f);
	}
};
