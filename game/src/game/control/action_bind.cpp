#include "action_bind.h"

#include "lc_client/tier0/conpar/conpars_init.h"
#include "lc_client/exceptions/input_exceptions.h"
#include "lc_client/exceptions/conpar_exceptions.h"

ActionBind::ActionBind(Parameters* pParameters, KeyCodeStrings* pKeyCodeString, std::vector<std::string>& actions) { 
	for (std::string action : actions) {
		std::string key = pParameters->getParameterValue<std::string>(action);

		KeyCode keyCode;

		try {
			keyCode = pKeyCodeString->getKeyCode(key);
		}
		catch (UnknownKeyCodeException& exception) {
			std::throw_with_nested(ConfigException());
		}
		
		m_actionBinds.emplace(action, keyCode);
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
