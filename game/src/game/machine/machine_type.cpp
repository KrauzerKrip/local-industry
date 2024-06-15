#pragma once

#include "machine_type.h"

std::string MachineTypeString::getTypeString(MachineType type) { return m_machineTypeString.at(type); }

std::unordered_map<MachineType, std::string> MachineTypeString::m_machineTypeString = {{MachineType::HEATER, "heater"},
	{MachineType::BOILER, "boiler"}, {MachineType::LATEX_EXTRACTOR, "latex_extractor"}};
