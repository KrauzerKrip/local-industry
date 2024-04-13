#include "material_system.h"

#include "lc_client/eng_model/entt/components.h"


MaterialSystem::MaterialSystem(TextureManager* pTextureManager, entt::registry* pRegistry, entt::registry* pUtilRegistry) { 
	m_pTextureManager = pTextureManager;
	m_pRegistry = pRegistry;
	m_pUtilRegistry = pUtilRegistry;
}

void MaterialSystem::update() { 
	auto sgRequests = m_pUtilRegistry->view<MaterialSgRequest>();

	for (auto&& [entity, request] : sgRequests.each()) {
		MaterialSG material = this->getMaterialSg(request.materialDir);
		m_pUtilRegistry->emplace_or_replace<MaterialSG>(entity, material);
		m_pUtilRegistry->remove<MaterialSgRequest>(entity);
	}

}

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

MaterialMR MaterialSystem::getMaterialMr(std::string dir) {
	// aiString str;

	// std::cout << "processMaterialMR in model_loading.cpp isn`t ready yet" << std::endl;

	// assert(1);

	// MaterialMR material;

	// pMaterial->GetTexture(aiTextureType_BASE_COLOR, 0, &str);
	// std::cout << "processMaterial BASE_COLOR str: " << str.C_Str() << std::endl;
	// material.colorTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());

	//// pMaterial->GetTexture(aiTextureType_, 0, &str);
	// material.metallicTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());

	// pMaterial->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &str);
	// material.aoTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());

	// pMaterial->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &str);
	// material.aoTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());

	// pMaterial->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &str);
	// material.aoTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());

	// return material;
	return MaterialMR();
}

MaterialSG MaterialSystem::getMaterialSg(std::string dir) {
	MaterialSG material;

	material.diffuseTexture = m_pTextureManager->getTexture(dir + "diffuse"); // str.C_Str());
	material.diffuseTexture->setTextureType(TextureType::DIFFUSE);

	material.specularTexture = m_pTextureManager->getTexture(dir + "specular");
	material.specularTexture->setTextureType(TextureType::SPECULAR);

	material.glossinessTexture = m_pTextureManager->getTexture(dir + "glossiness");
	material.glossinessTexture->setTextureType(TextureType::GLOSSINESS);

	material.aoTexture = m_pTextureManager->getTexture(dir + "ao");
	material.aoTexture->setTextureType(TextureType::AO);

	material.normalMap = m_pTextureManager->getTexture(dir + "normal");
	material.normalMap->setTextureType(TextureType::NORMAL);

	return material;
}