#include "tier1.h"

#include <map>
#include <string>

#include "game_info.h"
#include "lc_client/util/pack.h"


void tier1::load(eng::IResource* pResource) { loadPacks(pResource); }

void tier1::loadPacks(eng::IResource* pResource) {
	GameInfo gameInfo(pResource);
	std::map<std::string, std::string> packs = gameInfo.getPacks();

	for (auto const& [name, path] : packs) {
		Pack::loadPack(name, path, pResource);
	}

}
