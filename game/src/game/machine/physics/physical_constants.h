#pragma once

#include <string>
#include <unordered_map>

#include "lc_client/tier0/conpar/parameters.h"
#include "lc_client/tier0/console/i_console.h"


class PhysicalConstants {
public:
	PhysicalConstants(Parameters* pParameters, IConsole* pConsole);
	float getConstant(const std::string& name);

private:
	std::unordered_map<std::string, float> m_constants;

};