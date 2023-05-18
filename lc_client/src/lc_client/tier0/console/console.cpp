#include "console.h"

Console::Console() {}

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

void Console::setCallbacks(Callbacks* pCallbacks) { m_pCallbacks = pCallbacks; }
