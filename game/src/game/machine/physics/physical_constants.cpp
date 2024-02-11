#include "physical_constants.h"

#include <format>
#include <ranges>

#include "lc_client/tier0/conpar/conpars_init.h"


PhysicalConstants::PhysicalConstants(Parameters* pParameters, IConsole* pConsole) {
	m_constants = {
        {"combustion_heat_diesel", 0},
	    {"combustion_heat_anthracite", 0},
		{"combustion_heat_wood", 0},
	    {"burning_duration_wood", 0},
		{"heater_efficiency", 0}
	};

    for (const auto& [k, v] : m_constants) {
		ConPar<float> conpar("game_" + k, v);
		conpar.setCallback([this, k](float value) {
		    m_constants[k] = value;
		});
		pParameters->addParameter(conpar);
    }
}

float PhysicalConstants::getConstant(const std::string& name) { return m_constants.at(name); }
