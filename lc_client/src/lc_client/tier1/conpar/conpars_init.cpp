#include "conpars_init.h"

#define ADD_PARAMETER_BOOL(name, value) (parameters.addParameter(ConPar<bool>(name, (bool)value)))
#define ADD_PARAMETER_STRING(name, value) (parameters.addParameter(ConPar<std::string>(name, (std::string)value)))
#define ADD_PARAMETER_INT(name, value) (parameters.addParameter(ConPar<int>(name, (int)value)))
#define ADD_PARAMETER_FLOAT(name, value) (parameters.addParameter(ConPar<float>(name, (float)value)))

#define ADD_PARAMETER_BOOL_F(name, value, flags) (parameters.addParameter(ConPar<bool>(name, (bool)value, flags)))
#define ADD_PARAMETER_STRING_F(name, value, flags)                                                                     \
	(parameters.addParameter(ConPar<std::string>(name, (std::string)value, flags)))
#define ADD_PARAMETER_INT_F(name, value, flags) (parameters.addParameter(ConPar<int>(name, (int)value, flags)))
#define ADD_PARAMETER_FLOAT_F(name, value, flags) (parameters.addParameter(ConPar<float>(name, (float)value, flags)))


void initParameters(Parameters& parameters) {
	initKeybinds(parameters);
	initGraphicsParameters(parameters);
}

static void initKeybinds(Parameters& parameters) {
	ADD_PARAMETER_STRING("kb_forward", "W");
	ADD_PARAMETER_STRING("kb_left", "A");
	ADD_PARAMETER_STRING("kb_back", "S");
	ADD_PARAMETER_STRING("kb_right", "D");
	ADD_PARAMETER_STRING("kb_up", "SPACE");
	ADD_PARAMETER_STRING("kb_fast", "LEFT_SHIFT");
	ADD_PARAMETER_STRING("kb_down", "CONTROL");
	ADD_PARAMETER_STRING("kb_use", "E");
	ADD_PARAMETER_STRING("kb_menu", "ESC");
	ADD_PARAMETER_STRING("kb_select", "LEFT_CLICK");
}

void initGraphicsParameters(Parameters& parameters) {
	ADD_PARAMETER_BOOL_F("gh_triggers_display", true, std::vector<Flags>({Flags::CHEATS}));
}
