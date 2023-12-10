#pragma once

#include <glm/glm.hpp>

#include "lc_client/eng_graphics/skybox_render.h"
#include "lc_client/eng_cubemaps/cubemap_loader.h"
#include "lc_client/util/i_eng_resource.h"


class Skybox {
public:
	Skybox(SkyboxRender* pSkyboxRender, eng::IResource* pResource);
	~Skybox() = default;

	void loadSkybox(std::string name);
	void render(glm::mat4& projection, glm::mat4& view);
	void bindTexture();

	glm::vec3 getLightColor() const;
	void setLightColor(glm::vec3 color);
	void setLightColor(float r, float g, float b);
	void setLightColor(glm::uvec3 color);
	void setLightColor(int r, int g, int b);
	float getLightStrength();
	void setLightStrength(float strength);

private:
	SkyboxRender* m_pSkyboxRender = nullptr;
	eng::IResource* m_pResource = nullptr;

	glm::vec3 m_lightColor;
	float m_lightStrength;
};