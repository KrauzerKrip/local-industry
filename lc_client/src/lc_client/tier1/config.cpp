#include "config.h"

#include <map>
#include <string>

#include "game_info.h"
#include "lc_client/exceptions/conpar_exceptions.h"


Config::Config(Parameters* pParameters) { m_pParameters = pParameters; }

void Config::initEngineConfig() { 
	std::map<std::string, std::string> config = m_gameInfo.getEngineConfig();

	for (auto& [name, value] : config) {
		try {
			m_pParameters->setParameterValueConvert(name, value);
		}
		catch (ConsoleParameterNotFoundException&) {
			std::throw_with_nested(ConfigException());
		}
	}
}

void Config::initGameConfig() {
	std::map<std::string, std::string> config = m_gameInfo.getGameConfig();

	for (auto& [name, value] : config) {
		try {
			m_pParameters->setParameterValueConvert(name, value);
		}
		catch (ConsoleParameterNotFoundException&) {
			std::throw_with_nested(ConfigException());
		}
	}
}
