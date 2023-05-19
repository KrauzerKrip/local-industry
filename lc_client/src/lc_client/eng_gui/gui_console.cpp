#include "gui_console.h"

ConsoleGui::ConsoleGui(IConsoleInput* pConsole) { m_pConsole = pConsole; }

void ConsoleGui::open() { isOpened = true; }

void ConsoleGui::close() { isOpened = false; }

void ConsoleGui::update() {
	if (!isOpened) {
		return;
	}


}
