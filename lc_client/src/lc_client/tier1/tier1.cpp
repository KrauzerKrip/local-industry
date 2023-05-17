#include "tier1.h"
#include "tier1.h"
#include "tier1.h"

#include <map>
#include <string>

#include "game_info.h"
#include "lc_client/util/pack.h"
#include "conpar/conpars_init.h"


Tier1::Tier1(eng::IResource* pResource) {
	m_pParameters = new Parameters();
	initParameters(*m_pParameters);
	loadPacks(pResource);
}

Tier1::~Tier1() {
	delete m_pParameters;
	delete m_pShaderManager;
	delete m_pTextureManager;
}

Parameters* Tier1::getParameters() { return m_pParameters; }

TextureManager* Tier1::getTextureManager() { return m_pTextureManager; }
IShaderManager* Tier1::getShaderManager() { return m_pShaderManager; }

void Tier1::loadPacks(eng::IResource* pResource) {
	GameInfo gameInfo(pResource);
	std::map<std::string, std::string> packs = gameInfo.getPacks();

	for (auto const& [name, path] : packs) {
		Pack::loadPack(name, path, pResource);
	}
}
