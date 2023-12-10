#include "skybox.h"

#include "lc_client/util/pack.h"
#include "lc_client/eng_cubemaps/cubemap_texture_loader.h"
#include "lc_client/util/i_eng_resource.h"


Skybox::Skybox(SkyboxRender* pSkyboxRender, eng::IResource* pResource)
	: m_lightColor(glm::vec3()),
	  m_lightStrength(1.0f) {
	m_pSkyboxRender = pSkyboxRender;
	m_pResource = pResource;
}

void Skybox::loadSkybox(std::string name) {
	Pack pack = Pack::getPack("dev");
	std::string skyboxPath = Pack::Skybox(pack, name).getPath();
	std::unique_ptr<CubemapMaterial> skyboxMaterial = CubemapTextureLoader(skyboxPath, m_pResource).getMaterial();
	m_pSkyboxRender->load(skyboxMaterial.get());
}

void Skybox::render(glm::mat4& projection, glm::mat4& view) { m_pSkyboxRender->render(projection, view); }

void Skybox::bindTexture() { m_pSkyboxRender->bindTexture(); }

glm::vec3 Skybox::getLightColor() const { return m_lightColor; }

void Skybox::setLightColor(glm::vec3 color) { m_lightColor = color; }

void Skybox::setLightColor(float r, float g, float b) {
	m_lightColor.r = r;
	m_lightColor.g = g;
	m_lightColor.b = b;
}

void Skybox::setLightColor(glm::uvec3 color) {
	const float i = 255.0f;
	m_lightColor = glm::vec3(color.r / i, color.g / i, color.b / i);
}

void Skybox::setLightColor(int r, int g, int b) { setLightColor(glm::uvec3(r, g, b)); }

float Skybox::getLightStrength() { return m_lightStrength; }

void Skybox::setLightStrength(float strength) { m_lightStrength = strength; }
