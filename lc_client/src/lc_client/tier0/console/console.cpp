#include "console.h"

#include <functional>

#include "lc_client/tier0/console/command.h"


Console::Console(Parameters* pParameters) : m_command(pParameters, this) { m_pParameters = pParameters; }

void Console::devMessage(std::string text) {
	if (m_pCallbacks) {
		m_pCallbacks->pDevMessageCallback(text);
	}
}

void Console::message(std::string text) {
	if (m_pCallbacks) {
		m_pCallbacks->pMessageCallback(text);
	}
}

void Console::warn(std::string text) {
	if (m_pCallbacks) {
		m_pCallbacks->pWarnCallback(text);
	}
}

void Console::enter(std::string command) { m_command.execute(command); }

void Console::setCallbacks(Callbacks* pCallbacks) { m_pCallbacks = pCallbacks; }
