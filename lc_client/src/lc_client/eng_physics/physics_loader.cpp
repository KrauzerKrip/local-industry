#include "physics_loader.h"

#include <iostream>

#include <lc_client/exceptions/io_exceptions.h>
#include "lc_client/exceptions/physics_exception.h"


PhysicsLoader::PhysicsLoader(PhysicsParser* pPhysicsParser, entt::registry* pRegistry) {
	m_pPhysicsParser = pPhysicsParser;
	m_pRegistry = pRegistry;
}

void PhysicsLoader::loadPhysics(entt::entity entity, std::string path) { 
	std::vector<ColliderData> collidersData;

	try {

		collidersData = m_pPhysicsParser->parse(path);
	}
	catch (XmlException& exception) {
		std::throw_with_nested(PhysicsLoadingException("Can't load physics for an entity. Physics file path: " + path));
	}

	Colliders colliders;

	for (const ColliderData& colliderData : collidersData) {
		colliders.colliders.push_back(std::make_tuple(loadCollider(colliderData), colliderData.type));
	}

	m_pRegistry->emplace<Colliders>(entity, colliders);
}

entt::entity PhysicsLoader::loadCollider(const ColliderData& colliderData) {
	entt::entity entity = m_pRegistry->create();

	m_pRegistry->emplace<Transform>(entity, colliderData.transform);

	if (colliderData.type == ColliderType::BOX) {
		m_pRegistry->emplace<BoxCollider>(entity);
	}

	return entity;
}
