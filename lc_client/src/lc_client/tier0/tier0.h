#pragma once

#include "conpar/parameters.h"


/**
 * 
 * 
 */
class Tier0 {
public:
	Tier0();
	~Tier0();

	Parameters* getParameters();
protected:

	Parameters* m_pParameters;
};