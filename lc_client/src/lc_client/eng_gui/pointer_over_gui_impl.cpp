#include "pointer_over_gui_impl.h"

PointerOverGuiImpl::PointerOverGuiImpl() { m_pointerIsOverGui = false; }

bool PointerOverGuiImpl::isPointerOverGui() { return m_pointerIsOverGui; }

void PointerOverGuiImpl::setPointerOverGui(bool value) { m_pointerIsOverGui = value; }
