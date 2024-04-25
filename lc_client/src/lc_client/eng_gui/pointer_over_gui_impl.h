#pragma once

#include "pointer_over_gui.h"


class PointerOverGuiImpl : public PointerOverGui {
public:
	PointerOverGuiImpl();

	bool isPointerOverGui() override;
	void setPointerOverGui(bool value);

private:
	bool m_pointerIsOverGui;
};