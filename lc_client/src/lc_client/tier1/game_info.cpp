#include "game_info.h"

#include "lc_client/util/pack.h"


using json = nlohmann::json;


GameInfo::GameInfo() {
	if (m_json.empty()) {
		assert("GameInfo json isn`t parsed.");
	}
}

void GameInfo::parse(eng::IResource* pResource) {
	std::vector<unsigned char> buffer = pResource->getFileResource("info.json");
	m_json = json::parse(buffer);
}

std::string GameInfo::getProject() { return m_json.at("project"); }
 
std::string GameInfo::getVersion() { return m_json.at("version"); }

std::map<std::string, std::string> GameInfo::getPacks() {
	std::map<std::string, std::string> packs;

	for (auto& pack : m_json.at("packs").items()) {
		packs.emplace(pack.key(), pack.value());
	}

	return packs;
}

std::map<std::string, std::string> GameInfo::getEngineConfig() { 
	std::map<std::string, std::string> config;

	for (auto& parameter : m_json.at("engine_config").items()) {
		config.emplace(parameter.key(), parameter.value());
	}

	return config;
}

std::map<std::string, std::string> GameInfo::getGameConfig() {
	std::map<std::string, std::string> config;

	for (auto& parameter : m_json.at("game_config").items()) {
		config.emplace(parameter.key(), parameter.value());
	}

	return config;
}

nlohmann::json GameInfo::m_json;