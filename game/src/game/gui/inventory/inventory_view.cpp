#include "inventory_view.h"

#include <imgui.h>

using namespace ImGui;


InventoryView::InventoryView(const GuiDependencies& dependencies) { 
	m_enable = false;
	m_position = glm::vec2(0);
}

void InventoryView::frame() {
	if (!m_enable) {
		return;
	}

	SetNextWindowPos(ImVec2(m_position.x, m_position.y));

	float height = 0.0f;

	if (m_data.size() == 1) {
		height = 100;
	}
	else {
		height = m_data.size() * 72;
	}

	SetNextWindowSize(ImVec2(256, height));

	if (Begin(m_windowName.c_str(), NULL,
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus)) {
		for (auto& [k, v] : m_data) {
			ImGui::Text(k.c_str());
			SameLine();
			ImGui::Text(std::to_string(v).c_str());
		}
		End();
	}
}

void InventoryView::enable(bool value) { m_enable = value; }

void InventoryView::setPosition(glm::vec2 position) { m_position = position; }

void InventoryView::setWindowName(std::string name) { m_windowName = name; }

void InventoryView::setData(std::unordered_map<std::string, float> data) { m_data = data; }
