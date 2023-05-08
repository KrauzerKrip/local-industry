#pragma once

#include <string>
#include <map>
#include <vector>

#include <nlohmann/json.hpp> 

#include "lc_client/util/i_eng_resource.h"


class GameInfo {
public:
	GameInfo(eng::IResource* pResource);
	~GameInfo() = default;

	std::string getProject();
	std::string getVersion();
	std::map<std::string, std::string> getPacks();
	std::vector<std::string> getConfig();

private: 
	nlohmann::json m_json;
};
