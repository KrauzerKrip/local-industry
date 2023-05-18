#include "tier0.h"

#include "conpar/conpars_init.h"
#include "conpar/parameters.h"


Tier0::Tier0() {
	m_pParameters = new Parameters();
	initParameters(*m_pParameters);
}

Tier0::~Tier0() {
	delete m_pParameters;
}

Parameters* Tier0::getParameters() { return m_pParameters; }
