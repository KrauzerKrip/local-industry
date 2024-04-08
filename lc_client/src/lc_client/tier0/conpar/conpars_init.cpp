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
	initGraphicsParameters(parameters);
	initUtilParameters(parameters);
	initGuiParameters(parameters);
	initPhysicsParameters(parameters);
	initNpcParameters(parameters);
}

void initGraphicsParameters(Parameters& parameters) {
	ADD_PARAMETER_BOOL_F("gh_triggers_display", false, ConparFlags::CHEATS);
	ADD_PARAMETER_FLOAT("gh_fov", 90.0f);
	ADD_PARAMETER_BOOL("gh_vsync", false);
	ADD_PARAMETER_INT("gh_window_width", 0);
	ADD_PARAMETER_INT("gh_window_height", 0);
	ADD_PARAMETER_INT("gh_window_aspect_ratio_x", 0);
	ADD_PARAMETER_INT("gh_window_aspect_ratio_y", 0);
	ADD_PARAMETER_STRING("gh_window_mode", "windowed");
}

void initPhysicsParameters(Parameters& parameters) {
	ADD_PARAMETER_BOOL("ph_debug_mode", false);
	ADD_PARAMETER_BOOL("ph_show_colliders", false);
}

void initUtilParameters(Parameters& parameters) {
	ADD_PARAMETER_BOOL_F("sv_cheats", false, ConparFlags::NONE);
	ADD_PARAMETER_BOOL("console_log_time", false);
	ADD_PARAMETER_BOOL("cl_debug_mode", false);
}

void initGuiParameters(Parameters& parameters) {
	ADD_PARAMETER_BOOL("gui_imgui_debug", false);
}

void initNpcParameters(Parameters& parameters) { 
	ADD_PARAMETER_BOOL("npc_show_graph", false);
}
