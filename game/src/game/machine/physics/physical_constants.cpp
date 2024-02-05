#include "physical_constants.h"

#include <format>
#include <ranges>

#include "lc_client/tier0/conpar/conpars_init.h"


PhysicalConstants::PhysicalConstants(Parameters* pParameters, IConsole* pConsole) {
	m_constants = {
    {"combustion_heat_diesel", 43400000.0}, {"combustion_heat_anthracite", 32500000.0}};

    for (const auto& [k, v] : m_constants) {
        
    }

 //   		try {
	//	pParameters->getParameterValue<float>("game_" + k);
	//}
	//catch (ConsoleParameterNotFoundException&) {
	//	pConsole->message(std::format("Can't find parameter 'game_{}' to set the value of constant {}", k, k));
	//}
}

float PhysicalConstants::getConstant(const std::string& name) { return m_constants.at(name); }
