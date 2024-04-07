#include "machine_inspector_view.h"

#include <imgui.h>
#include <iostream>

using namespace ImGui;


MachineInspectorView::MachineInspectorView(const GuiDependencies& dependencies) { m_enable = false;
	m_position = glm::vec2(0);
	m_windowName = "machine";
}

void MachineInspectorView::frame() {
	if (!m_enable) {
		return;
	}

	SetNextWindowPos(ImVec2(m_position.x, m_position.y));

	float height = 0.0f;

	if (m_data.size() == 1) {
		height = 100;
	} else {
		height = m_data.size() * 72;
	}

	SetNextWindowSize(ImVec2(256, height));
	
	if (Begin(m_windowName.c_str(), NULL,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus)) {
		for (auto& [k, v] : m_dataBool) {
			Checkbox(k.c_str(), v);
		}
		for (auto& [k, v] : m_dataFloat) {
			InputFloat(k.c_str(), v);
		}
		End();
	}
}

void MachineInspectorView::setData(std::unordered_map<std::string, std::string> data) { m_data = data; }

void MachineInspectorView::enable(bool value) { m_enable = value; }

void MachineInspectorView::setPosition(glm::vec2 position) { m_position = position; }

void MachineInspectorView::setWindowName(std::string name) { m_windowName = name; }

void MachineInspectorView::setDataBool(std::unordered_map<std::string, bool*> data) { m_dataBool = data; }

void MachineInspectorView::setDataFloat(std::unordered_map<std::string, float*> data) { m_dataFloat = data; }
