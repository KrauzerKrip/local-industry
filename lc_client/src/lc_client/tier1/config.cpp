#include "config.h"

#include <map>
#include <string>

#include "game_info.h"
#include "lc_client/exceptions/conpar_exceptions.h"


Config::Config(Parameters* pParameters) { m_pParameters = pParameters; }

void Config::setParameters() { 
	GameInfo gameInfo;
	std::map<std::string, std::string> config = gameInfo.getConfig();

	for (auto& [name, value] : config) {
		try {
			m_pParameters->setParameterValueConvert(name, value);
		}
		catch (ConsoleParameterNotFoundException& exception) {
			std::throw_with_nested(ConfigException());
		}
	}
}
