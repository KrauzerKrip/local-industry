#include "tier1.h"
#include "tier1.h"
#include "tier1.h"

#include <map>
#include <string>

#include "game_info.h"
#include "lc_client/util/pack.h"
#include "config.h"


Tier1::Tier1(eng::IResource* pResource, Tier0* pTier0) : m_config(pTier0->getParameters()) {
	m_pTier0 = pTier0;

	GameInfo::parse(pResource);

	m_config.initEngineConfig();

	loadPacks(pResource);
}

void Tier1::initGameConfig() { m_config.initGameConfig(); }

void Tier1::loadPacks(eng::IResource* pResource) {
	GameInfo gameInfo;
	std::map<std::string, std::string> packs = gameInfo.getPacks();

	for (auto const& [name, path] : packs) {
		Pack::loadPack(name, path, pResource);
	}
}
