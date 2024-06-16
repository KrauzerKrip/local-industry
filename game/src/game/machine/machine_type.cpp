#pragma once

#include "machine_type.h"

std::string MachineTypeString::getTypeString(MachineType type) { return m_machineTypeString.at(type); }

std::unordered_map<MachineType, std::string> MachineTypeString::m_machineTypeString = {{MachineType::HEATER, "heater"},
	{MachineType::BOILER, "boiler"}, {MachineType::LATEX_EXTRACTOR, "latex_extractor"}};

std::string ConnectionResourceTypeString::getString(ConnectionResourceType resourceType) { return m_resourceTypeStrings.at(resourceType); }

std::unordered_map<ConnectionResourceType, std::string> ConnectionResourceTypeString::m_resourceTypeStrings = {
	{ConnectionResourceType::NONE, "none"},
	{ConnectionResourceType::HEAT, "heat"}, {ConnectionResourceType::LATEX, "latex"}};
