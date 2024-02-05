#pragma once

#include <string>
#include <map>
#include <vector>

#include <nlohmann/json.hpp> 

#include "lc_client/util/i_eng_resource.h"


class GameInfo {
public:
	GameInfo();
	~GameInfo() = default;

	static void parse(eng::IResource* pResource);

	std::string getProject();
	std::string getVersion();
	std::map<std::string, std::string> getPacks();
	std::map<std::string, std::string> getEngineConfig();
	std::map<std::string, std::string> getGameConfig();

private: 
	static nlohmann::json m_json;
};
