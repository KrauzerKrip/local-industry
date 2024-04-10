#include "skybox_system.h"

#include "lc_client/util/pack.h"
#include "lc_client/eng_cubemaps/cubemap_texture_loader.h"
#include "lc_client/util/i_eng_resource.h"
#include "lc_client/eng_world/world.h"
#include "lc_client/eng_scene/entt/components.h"


SkyboxSystem::SkyboxSystem(SkyboxRender* pSkyboxRender, entt::registry* pRegistry, eng::IResource* pResource) {
	m_pSkyboxRender = pSkyboxRender;
	m_pResource = pResource;
	m_pRegistry = pRegistry;
}

void SkyboxSystem::update() { 
	auto requests = m_pRegistry->view<SkyboxRequest>();

	for (auto&& [entity, request] : requests.each()) {
		auto skyboxes = m_pRegistry->view<Skybox>();
		for (auto&& [ent, skybox] : skyboxes.each()) {
			if (ent != entity) {
				m_pRegistry->destroy(ent);
			}
		}

		this->loadSkybox(request.pack, request.name);
		m_pRegistry->emplace_or_replace<Skybox>(entity);
		m_pRegistry->remove<SkyboxRequest>(entity);
	}
}

void SkyboxSystem::loadSkybox(std::string pack, std::string name) {
	std::string skyboxPath = Pack::Skybox(Pack::getPack(pack), name).getPath();
	std::unique_ptr<CubemapMaterial> skyboxMaterial = CubemapTextureLoader(skyboxPath, m_pResource).getMaterial();
	m_pSkyboxRender->load(skyboxMaterial.get());
}
