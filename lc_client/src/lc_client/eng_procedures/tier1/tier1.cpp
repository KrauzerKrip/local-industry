#include "tier1.h"

#include <map>
#include <string>

#include "game_info.h"
#include "lc_client/util/pack.h"


Tier1::Tier1(eng::IResource* pResource) { 
	loadPacks(pResource); 
}

TextureManager* Tier1::getTextureManager() { return m_pTextureManager; }
IShaderManager* Tier1::getShaderManager() { return m_pShaderManager; }

void Tier1::loadPacks(eng::IResource* pResource) {
	GameInfo gameInfo(pResource);
	std::map<std::string, std::string> packs = gameInfo.getPacks();

	for (auto const& [name, path] : packs) {
		Pack::loadPack(name, path, pResource);
	}
}
