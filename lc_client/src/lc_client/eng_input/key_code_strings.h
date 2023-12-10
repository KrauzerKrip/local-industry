#pragma once

#include <unordered_map>
#include <string>

#include "key_code.h"


class KeyCodeStrings {
public:
	KeyCodeStrings();

	KeyCode getKeyCode(std::string key);

private:
	std::unordered_map<std::string, KeyCode> m_keyCodeStrings;
};
