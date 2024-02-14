#include "action_bind.h"

#include "lc_client/tier0/conpar/conpars_init.h"
#include "lc_client/exceptions/input_exceptions.h"
#include "lc_client/exceptions/conpar_exceptions.h"

ActionBind::ActionBind(
	Parameters* pParameters, IConsole* pConsole, KeyCodeStrings* pKeyCodeStrings) {
	std::vector actions = std::vector<std::string>({"kb_forward", "kb_left", "kb_back", "kb_right", "kb_up", "kb_fast", "kb_down", "kb_use", "kb_menu", "kb_build",
			"kb_select", "kb_rotate_camera", "kb_machine_menu", "kb_rotate_blueprint", "kb_remove_blueprint"});

	for (std::string action : actions) {
		ConPar<std::string> conpar(action, "");

		std::string key = conpar.getValue();
		
		m_actionBinds.emplace(action, KeyCode::NONE);

		conpar.setCallback(
			[this, action = action, pKeyCodeStrings = pKeyCodeStrings, pConsole = pConsole](std::string value) {
			try {
                KeyCode keyCode = pKeyCodeStrings->getKeyCode(value);
				m_actionBinds[action] = keyCode;
			}
			catch (UnknownKeyCodeException& exception) {
				std::string str = std::string(exception.what()) +
								  "\nIf this error appears at startup take a look at info.json 'game_config' keybinds.";
				pConsole->warn(str);
			}
			});

	    pParameters->addParameter(conpar);
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
