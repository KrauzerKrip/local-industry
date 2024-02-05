#pragma once

#include "game_info.h"
#include "lc_client/tier0/conpar/parameters.h"


class Config {
public:
	Config(Parameters* pParameters);

	void initEngineConfig();
	void initGameConfig();

private:
	Parameters* m_pParameters;
	GameInfo m_gameInfo;
};
