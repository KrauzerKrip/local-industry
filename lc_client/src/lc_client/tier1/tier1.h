#pragma once

#include "lc_client/util/i_eng_resource.h"

#include "lc_client/eng_procedures/graphics_entities_loading.h"
#include "lc_client/tier1/i_shaders.h"
#include "lc_client/tier1/texture_manager.h"
#include "lc_client/tier0/tier0.h"
#include "config.h"


/**
 * 
 * 
 */
class Tier1 {
public:
	Tier1(eng::IResource* pResource, Tier0* pTier0);
	~Tier1();

	TextureManager* getTextureManager();
	IShaderManager* getShaderManager();
	void initGameConfig();

protected:
	eng::IResource* m_pResource;
	Tier0* m_pTier0;
	Config m_config;

	TextureManager* m_pTextureManager;
	IShaderManager* m_pShaderManager;
	
private:
	void loadPacks(eng::IResource* pResource);
};