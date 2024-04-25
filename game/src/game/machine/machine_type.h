#pragma once

#include <unordered_map>
#include <string>

#include "game/util/enum_iterator.h"

enum class ConnectionType {
    NONE,
    HEAT
};

enum class MachineType {
	HEATER,
    BOILER
};

typedef Iterator<MachineType, MachineType::HEATER, MachineType::BOILER> MachineTypeIterator;

class MachineTypeString {
public:
	static std::string getTypeString(MachineType type);

private:
	static std::unordered_map<MachineType, std::string> m_machineTypeString;
};