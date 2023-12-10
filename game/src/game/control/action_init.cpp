#include "action_init.h"


/**
 * Should be called before config init, so before Tier1 init.
 */

void game::initActions(Parameters* pParameters, std::vector<std::string>& actions) {
	for (std::string action : actions) {
		pParameters->addParameter(ConPar<std::string>(action, ""));
	}
}
