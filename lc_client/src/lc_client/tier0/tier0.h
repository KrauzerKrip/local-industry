#pragma once

#include "conpar/parameters.h"
#include "console/i_console.h"
#include "console/console.h"


/**
 * 
 * 
 */
class Tier0 {
public:
	Tier0();
	~Tier0();

	Parameters* getParameters();
	Console* getConsole();

protected:

	Parameters* m_pParameters = nullptr;
	Console* m_pConsole = nullptr;
};