#include "components.h"
#include "components.h"
#include "components.h"

#include "lc_client/eng_script/script_system.h"


TransformHelper::TransformHelper(entt::entity entity, entt::registry* pSceneRegistry)
	: m_transform(&pSceneRegistry->get<Transform>(entity)) {
	std::string id = ScriptSystem::m_currentId;

	long iPtr = (long)&m_transform;

	std::string str = std::to_string(iPtr);

	m_entity = entity;
	m_pRegistry = pSceneRegistry;

	Tier0::getIConsole()->devMessage("Transform ptr helper constructor: " + id + " " + str);
}

Vec3fHelper TransformHelper::getPosition() {
	Transform& transform = m_pRegistry->get<Transform>(m_entity);
	m_transform2 = &m_pRegistry->get<Transform>(m_entity);

	std::string id = ScriptSystem::m_currentId;

	long iPtr = (long)&m_transform;

	std::string str = std::to_string(iPtr);

	Tier0::getIConsole()->devMessage("HELPER: GET_POSITION: Transform ptr: ============ " + id + " " + str);

	return Vec3fHelper(transform.position);
}

void TransformHelper::setPosition(Vec3fHelper vector) {
	Transform* transform = m_transform; // m_pRegistry->get<Transform>(m_entity);

	std::string id = ScriptSystem::m_currentId;

	glm::vec3 vec = glm::vec3(vector.x(), vector.y(), vector.z());

	transform->position = vec;

	long iPtr = (long)&transform;

	std::string str = std::to_string(iPtr);

	Tier0::getIConsole()->devMessage("HELPER: SET_POSITION: Transform ptr: ============ " + id + " " + str);
	Tier0::getIConsole()->devMessage("HELPER: SET_POSITION: position" + id + " " +
									 std::to_string(transform->position.x) + " " +
		std::to_string(transform->position.y) + " " + std::to_string(transform->position.z));

	auto vec2 = transform->position;
}
