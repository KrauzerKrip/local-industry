#include "game_info.h"

#include "lc_client/util/pack.h"


using json = nlohmann::json;


GameInfo::GameInfo(eng::IResource* pResource) {
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

std::vector<std::string> GameInfo::getConfig() { 
	std::vector<std::string> config;

	for (auto& command : m_json.at("config").items()) {
		config.push_back(command.value());
	}

	return config;
}
