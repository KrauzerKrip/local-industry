#include "material_system.h"

MaterialSystem::MaterialSystem(entt::registry* pUtilRegistry) { m_pUtilRegistry = pUtilRegistry; }

void MaterialSystem::loadMaterials() {
	auto entitiesSg = m_pUtilRegistry->view<MaterialLoadRequest, MaterialSG>();

	for (auto& entity : entitiesSg) {
		MaterialSG& material = entitiesSg.get<MaterialSG>(entity);
		
		material.aoTexture->load();
		material.diffuseTexture->load();
		material.glossinessTexture->load();
		material.normalMap->load();
		material.specularTexture->load();

		m_pUtilRegistry->erase<MaterialLoadRequest>(entity);
	}


	auto entitiesMr = m_pUtilRegistry->view<MaterialLoadRequest, MaterialMR>();

	for (auto& entity : entitiesMr) {
		MaterialMR& material = entitiesMr.get<MaterialMR>(entity);

		material.aoTexture->load();
		material.colorTexture->load();
		material.metallicTexture->load();
		material.normalMap->load();
		// TODO

		m_pUtilRegistry->erase<MaterialLoadRequest>(entity);
	}
}

void MaterialSystem::unloadMaterials() {}