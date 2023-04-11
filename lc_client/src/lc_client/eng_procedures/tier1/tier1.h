#pragma once

#include "lc_client/util/i_eng_resource.h"

#include "lc_client/eng_procedures/graphics_entities_loading.h"
#include "lc_client/eng_procedures/i_shaders.h"
#include "lc_client/eng_procedures/texture_manager.h"


class Tier1 {
public:
	Tier1(eng::IResource* pResource);
	~Tier1() = default;

	TextureManager* getTextureManager();
	IShaderManager* getShaderManager();

protected:
	eng::IResource* m_pResource;

	TextureManager* m_pTextureManager;
	IShaderManager* m_pShaderManager;
	
private:
	void loadPacks(eng::IResource* pResource);
};