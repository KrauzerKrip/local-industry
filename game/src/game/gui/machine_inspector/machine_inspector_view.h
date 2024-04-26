#pragma once

#include <unordered_map>
#include <string>

#include "lc_client/eng_gui/widgets/dependencies.h"


class MachineInspectorView {
public:
	MachineInspectorView(const GuiDependencies& dependencies);

	void frame();
	void setPurchasesData(std::unordered_map<std::string, std::string> data);
	void enable(bool value);
	void setPosition(glm::vec2 position);
	void setWindowName(std::string name);

	void setDataBool(std::unordered_map<std::string, bool*> data);
	void setDataFloat(std::unordered_map<std::string, float*> data);

private:
	std::unordered_map<std::string, std::string> m_data;
	std::unordered_map<std::string, bool*> m_dataBool;
	std::unordered_map<std::string, float*> m_dataFloat;
	bool m_enable;
	glm::vec2 m_position;
	std::string m_windowName;
};