#pragma once

#include <unordered_map>
#include<stdexcept>

#include "lc_client/eng_input/key_code.h"
#include "lc_client/tier0/conpar/parameters.h"
#include "lc_client/eng_input/key_code_strings.h"
#include "lc_client/tier0/console/i_console.h"


class ActionNotFound : public std::runtime_error {
public:
	ActionNotFound(std::string action) : std::runtime_error("Action not found: " + action) {}
};

class ActionBind {
public:
	ActionBind(Parameters* pParameters, IConsole* pConsole, KeyCodeStrings* pKeyCodeStrings);

	KeyCode getActionKey(std::string action);

private:
	std::vector<std::string> m_actions;

	std::unordered_map<std::string, KeyCode> m_actionBinds;
};
