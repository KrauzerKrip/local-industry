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

class ConnectionResourceTypeString {
public:
	static std::string getString(ConnectionResourceType resourceType);

private:
	static std::unordered_map<ConnectionResourceType, std::string> m_resourceTypeStrings;
};

enum class MachineType {
	HEATER,
    BOILER,
	LATEX_EXTRACTOR
};

typedef Iterator<MachineType, MachineType::HEATER, MachineType::LATEX_EXTRACTOR> MachineTypeIterator;

class MachineTypeString {
public:
	static std::string getTypeString(MachineType type);

private:
	static std::unordered_map<MachineType, std::string> m_machineTypeString;
};