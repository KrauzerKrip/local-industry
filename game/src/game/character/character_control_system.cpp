#include "character_control_system.h"

#include <glm/ext/matrix_projection.hpp>

#include "lc_client/eng_physics/entt/components.h"
#include <glm/ext/matrix_clip_space.hpp>


CharacterControlSystem::CharacterControlSystem(GraphicsSettings* pSettings, IInput* pInput,
	Camera* pCamera, ActionControl* pActionControl, entt::registry* pSceneRegistry, entt::registry* pMapRegistry) {
	m_pInput = pInput;
	m_pActionControl = pActionControl;
	m_pSceneRegistry = pSceneRegistry;
	m_pMapRegistry = pMapRegistry;
	m_pCamera = pCamera;

	m_windowSize = glm::vec2(1920, 1080);
	m_fov = pSettings->getFov();
	m_aspectRatio = 16.0f / 9.0f;

	m_pActionControl->addActionCallback("kb_select", [this]() { 
		onSelect(m_pInput->getMousePosition());
	});
}

void CharacterControlSystem::input() {
	
}

void CharacterControlSystem::onSelect(glm::vec2 position) { 
	//// first, get the cursor's window position, in pixels.
	//glm::vec2 pos2D = position;

	//// convert pixelPos2D from the range  [(0,0) .. (width,height)] to
	//// the range [(-1,-1) .. (1,1)]
	//pos2D.x = pos2D.x / (0.5f * m_windowSize.x) - 1.0f;
	//pos2D.y = pos2D.y / (0.5f * m_windowSize.y) - 1.0f;

	//// now work out how big our screen is, in world coordinates,
	//// if it's one meter in front of the camera.
	//float vertFOV = m_fov;
	//float halfVertFOV = 0.5f * vertFOV;
	//float screenHalfHeight = tanf(halfVertFOV);
	//float screenHalfWidth = screenHalfHeight * m_aspectRatio;

	//// screenHalfHeight and screenHalfWidth tell us (half) the actual in-game
	//// size of our screen, assuming that it's placed one meter in front of
	//// the camera.
	////
	//// So relative to the camera, our pixel must be located at:
	//glm::vec3 pixelPos3D(pos2D.x * screenHalfWidth, pos2D.y * screenHalfHeight, 1.f);

	//// now, we need our pixel's position relative to the world, instead of
	//// relative to the camera, so we need to apply our camera's 3D
	//// transformation to it.

	//glm::mat4 transform(1.0);

	//glm::vec3 pixelWorldPos3D =  * pixelPos3D;
	//// (or however your maths library performs matrix multiplication)
	
	   
	glm::mat4 projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, 0.1f, 1000.0f);

	glm::vec3 mouseWorld = glm::unProject(glm::vec3(position, 0.0f), m_pCamera->getViewMatrix(), projection, glm::vec4(0, 0, m_windowSize.x, m_windowSize.y));

	glm::vec3 rayDir = m_pCamera->getCameraFront(); // glm::normalize(mouseWorld - m_pCamera->getPosition());
	
	RaycastQuery raycast(mouseWorld, rayDir);
}
