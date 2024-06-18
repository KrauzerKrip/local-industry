#include "game_conpars_init.h"

#include "lc_client/tier0/conpar/conpars_init.h"

#define ADD_PARAMETER_BOOL(name, value) (pParameters->addParameter(ConPar<bool>(name, (bool)value)))
#define ADD_PARAMETER_STRING(name, value) (pParameters->addParameter(ConPar<std::string>(name, (std::string)value)))
#define ADD_PARAMETER_INT(name, value) (pParameters->addParameter(ConPar<int>(name, (int)value)))
#define ADD_PARAMETER_FLOAT(name, value) (pParameters->addParameter(ConPar<float>(name, (float)value)))

#define ADD_PARAMETER_BOOL_F(name, value, flags) (pParameters->addParameter(ConPar<bool>(name, (bool)value, flags)))
#define ADD_PARAMETER_STRING_F(name, value, flags)                                                                     \
	(pParameters->addParameter(ConPar<std::string>(name, (std::string)value, flags)))
#define ADD_PARAMETER_INT_F(name, value, flags) (pParameters->addParameter(ConPar<int>(name, (int)value, flags)))
#define ADD_PARAMETER_FLOAT_F(name, value, flags) (pParameters->addParameter(ConPar<float>(name, (float)value, flags)))


void Industry::initGameplayConpars(Parameters* pParameters) { 
	ADD_PARAMETER_BOOL("game_require_blueprint", true);
}