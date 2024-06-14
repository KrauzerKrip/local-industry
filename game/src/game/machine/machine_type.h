#pragma once

#include <unordered_map>
#include <string>

#include "game/util/enum_iterator.h"

/**
* @brief Respectively to the machine we connecting. If IN the machine (e.g. boiler) will be connected as INPUT for another machine (e.g. furnance) OUTPUT.
*/
enum class ConnectionType {
	NONE,
	IN,
	OUT
};

enum class ConnectionResourceType {
    NONE,
    HEAT,
	LATEX,
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