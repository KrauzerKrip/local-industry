#pragma once

#include <glm/glm.hpp>

#include "lc_client/util/image.h"
#include "lc_client/eng_cubemaps/cubemap_texture_loader.h"


struct SkyboxMaterial {
	eng::Image right;
	eng::Image left;
	eng::Image top;
	eng::Image bottom;
	eng::Image back;
	eng::Image front;
};

class SkyboxRender {
public:
	virtual void render(glm::mat4& projection, glm::mat4& view) = 0;
	virtual void bindTexture() = 0;
	/**
	 * @brief 
	 * @param pMat should pass ownership. 
	 */
	virtual void load(CubemapMaterial* pMat) = 0;
	virtual void reload() = 0;

protected:
	CubemapMaterial* m_pMaterial = nullptr;
};
