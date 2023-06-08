#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_script/api/helpers/glm_helpers.h"
#include "lc_client/tier0/tier0.h"


class TransformHelper {
public:
	TransformHelper(entt::entity entity, entt::registry* pSceneRegistry);
	
	Vec3fHelper getPosition() { //
		Transform& transform = m_pRegistry->get<Transform>(m_entity);
		
		return Vec3fHelper(transform.position); 
	};

	void setPosition(Vec3fHelper vector);

	Vec3fHelper getScale() { return Vec3fHelper(m_transform.scale); };

	void setScale(Vec3fHelper vector) { m_transform.scale = glm::vec3(vector.x(), vector.y(), vector.z());
	};

private:
	Transform& m_transform;
	entt::entity m_entity;
	entt::registry* m_pRegistry;
};
