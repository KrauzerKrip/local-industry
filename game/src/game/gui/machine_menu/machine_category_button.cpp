#include "machine_category_button.h"

MachineCategoryButton::MachineCategoryButton(
	std::string label, std::string iconPath, const GuiDependencies& dependencies, MachineCategory* pMachineCategory) : Button(dependencies) {
	m_pMachineCategory = pMachineCategory;
	this->setSize(64, 64);

	this->setBackground(new ImageBackground(iconPath, dependencies));
}

void MachineCategoryButton::click() {
	glm::vec2 buttonPos = m_rectangle.m_absolutePosition;
	glm::vec2 buttonSize = m_rectangle.m_size;
	float buttonCenterPos = buttonPos.x + (buttonSize.x * 0.5);
	m_pMachineCategory->setPosition(buttonCenterPos - (m_pMachineCategory->getSize().x * 0.5), 85);
	m_pMachineCategory->toggleWithChildren();
}
