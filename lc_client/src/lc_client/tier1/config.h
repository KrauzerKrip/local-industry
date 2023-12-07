#pragma once

#include "lc_client/tier0/conpar/parameters.h"


class Config {
public:
	Config(Parameters* pParameters);

	void setParameters();

private:
	Parameters* m_pParameters;
};
