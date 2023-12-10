#include "key_code_strings.h"

#include <stdexcept>

#include "lc_client/exceptions/input_exceptions.h"


KeyCodeStrings::KeyCodeStrings() {
	m_keyCodeStrings = std::unordered_map<std::string, KeyCode>({
		{"MOUSE_BUTTON_LEFT", KeyCode::MOUSE_BUTTON_LEFT},
		{"MOUSE_BUTTON_RIGHT", KeyCode::MOUSE_BUTTON_RIGHT},
		{"MOUSE_BUTTON_MIDDLE", KeyCode::MOUSE_BUTTON_MIDDLE},
		{"W", KeyCode::W},
		{"D", KeyCode::D},
		{"A", KeyCode::S},
		{"S", KeyCode::S},
		{"B", KeyCode::B},
		{"E", KeyCode::E},
		{"ESC", KeyCode::ESC},
		{"SPACE", KeyCode::SPACE},
		{"LEFT_SHIFT", KeyCode::LEFT_SHIFT},
		{"LEFT_CTRL", KeyCode::LEFT_CTRL},
		{"GRAVE_ACCENT", KeyCode::GRAVE_ACCENT},
		{"F1", KeyCode::F1},
		{"F2", KeyCode::F2},
		{"F3", KeyCode::F3},
		{"F4", KeyCode::F4},
		{"F5", KeyCode::F5},
		{"F6", KeyCode::F6},
		{"F7", KeyCode::F7},
		{"F8", KeyCode::F8},
		{"F9", KeyCode::F9},
		{"F10", KeyCode::F10},
		{"F11", KeyCode::F11},
	});
}

KeyCode KeyCodeStrings::getKeyCode(std::string key) {
	try {
		return m_keyCodeStrings.at(key);
	}
	catch (std::out_of_range&) {
		throw UnknownKeyCodeException(key);
	}
}
