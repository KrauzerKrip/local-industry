#include "config.h"

#include <map>
#include <string>

#include "game_info.h"


Config::Config(Parameters* pParameters) { m_pParameters = pParameters; }

void Config::setParameters() { 
	GameInfo gameInfo;
	std::map<std::string, std::string> config = gameInfo.getConfig();

	for (auto& [name, value] : config) {
		m_pParameters->setParameterValueConvert(name, value);
	}
}
