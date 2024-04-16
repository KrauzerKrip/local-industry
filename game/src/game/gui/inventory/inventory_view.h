#pragma once

#include <unordered_map>
#include <string>

#include "lc_client/eng_gui/widgets/dependencies.h"


class InventoryView {
public:
	InventoryView(const GuiDependencies& dependencies);

	void frame();
	void enable(bool value);
	void setPosition(glm::vec2 position);
	void setWindowName(std::string name);
	void setData(std::unordered_map<std::string, float> data);

private:
	std::unordered_map<std::string, float> m_data;

	bool m_enable;
	glm::vec2 m_position;
	std::string m_windowName;
};