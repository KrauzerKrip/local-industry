#include "action_control.h"

ActionControl::ActionControl(
	IInput* pInput, Parameters* pParameters, IConsole* pConsole, std::vector<std::string> actions) { 
	m_pInput = pInput;

	m_pKeyCodeStrings = new KeyCodeStrings;

	m_pActionBind = new ActionBind(pParameters, pConsole, m_pKeyCodeStrings, actions);
}

ActionControl::~ActionControl() {
	delete m_pActionBind;
	delete m_pKeyCodeStrings;
}

bool ActionControl::isAction(std::string action) { 
	KeyCode keyCode = m_pActionBind->getActionKey(action);
	return m_pInput->isKeyPressed(keyCode);
}

void ActionControl::addActionCallback(std::string action, std::function<void()> callback) {
	KeyCode keyCode = m_pActionBind->getActionKey(action);
	m_pInput->addMappedKeyCallback(keyCode, callback);
}
