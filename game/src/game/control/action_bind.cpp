#include "action_bind.h"

#include "lc_client/tier0/conpar/conpars_init.h"
#include "lc_client/exceptions/input_exceptions.h"
#include "lc_client/exceptions/conpar_exceptions.h"

ActionBind::ActionBind(
	Parameters* pParameters, IConsole* pConsole, KeyCodeStrings* pKeyCodeStrings, std::vector<std::string>& actions) { 
	for (std::string action : actions) {
		ConPar<std::string>& conpar = pParameters->getParameter<std::string>(action);

		std::string key = conpar.getValue();

		KeyCode keyCode;

		try {
			keyCode = pKeyCodeStrings->getKeyCode(key);
		}
		catch (UnknownKeyCodeException& exception) {
			std::throw_with_nested(ConfigException());
		}
		
		m_actionBinds.emplace(action, keyCode);

		conpar.setCallback(
			[this, action = action, pKeyCodeStrings = pKeyCodeStrings, pConsole = pConsole](std::string value) {
			try {
				KeyCode keyCode_;
				keyCode_ = pKeyCodeStrings->getKeyCode(value);
				m_actionBinds[action] = keyCode_;
			}
			catch (UnknownKeyCodeException& exception) {
				pConsole->warn(exception.what());
			}
			});
	}
}

KeyCode ActionBind::getActionKey(std::string action) {
	try {
		return m_actionBinds.at(action);
	}
	catch (std::out_of_range&) {
		throw ActionNotFound(action);
	}
}
