#pragma once

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_script/api/helpers/glm_helpers.h"

class TransformHelper {
public:
	TransformHelper(Transform* transform) : m_transform(transform){
		
	}
	
	Vec3fHelper getPosition() { return Vec3fHelper(m_transform->position); };

	void setPosition(Vec3fHelper vector) {
		m_transform->position = glm::vec3(vector.x(), vector.y(), vector.z());
	};

	Vec3fHelper getScale() { return Vec3fHelper(m_transform->scale); };

	void setScale(Vec3fHelper vector) { m_transform->scale = glm::vec3(vector.x(), vector.y(), vector.z());
	};

private:
	Transform* m_transform;
};
