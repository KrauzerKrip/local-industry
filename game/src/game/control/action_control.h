#pragma once

#include "lc_client/eng_input/i_input.h"
#include "game/control/action_bind.h"
#include "lc_client/tier0/conpar/parameters.h"
#include "lc_client/tier0/console/i_console.h"


class ActionControl {
public:
	ActionControl(IInput* pInput, Parameters* pParameters, IConsole* pConsole, std::vector<std::string> actions);
	~ActionControl();

	bool isAction(std::string action);
	void addActionCallback(std::string action, std::function<void()> callback);

private:
	IInput* m_pInput = nullptr;
	ActionBind* m_pActionBind = nullptr;
	KeyCodeStrings* m_pKeyCodeStrings = nullptr;
};
