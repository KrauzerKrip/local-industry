#include "gl_lighting.h"

#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"

LightingGl::LightingGl(entt::registry* pMapRegistry, entt::registry* pSceneRegistry, Camera* pCamera, Skybox* pSkybox) {
	m_pMapRegistry = pMapRegistry;
	m_pSceneRegistry = pSceneRegistry;
	m_pCamera = pCamera;
	m_pSkybox = pSkybox;
}

void LightingGl::setLighting(unsigned int shaderProgram) {
	setUniform(shaderProgram, "ambientLight.color", m_pSkybox->getLightColor());
	setUniform(shaderProgram, "ambientLight.strength", m_pSkybox->getLightStrength());

	setUniform(shaderProgram, "spotLight.position", m_pCamera->getPosition());
	setUniform(shaderProgram, "spotLight.direction", m_pCamera->getCameraFront());
	setUniform(shaderProgram, "spotLight.cutOff", (float)glm::cos(glm::radians(12.5)));
	setUniform(shaderProgram, "spotLight.outerCutOff", (float)glm::cos(glm::radians(17.5)));
	setUniform(shaderProgram, "spotLight.diffuse", glm::vec3(1.0f));
	setUniform(shaderProgram, "spotLight.specular", glm::vec3(0.5f));
	setUniform(shaderProgram, "spotLight.constant", 1.0f);
	setUniform(shaderProgram, "spotLight.linear", 0.09f);
	setUniform(shaderProgram, "spotLight.quadratic", 0.032f);

	auto pointLights = m_pSceneRegistry->view<Transform, PointLight>();

	int i = 0;
	for (entt::entity entity : pointLights) {
		setPointLight(shaderProgram, i, pointLights.get<PointLight>(entity), pointLights.get<Transform>(entity));
		i++;
	}

	setUniform(shaderProgram, "pointLightsCount", i);

	setUniform(shaderProgram, "directionalLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	setUniform(shaderProgram, "directionalLight.diffuse", glm::vec3(1.0f, 1.0f, 0.8f));
	setUniform(shaderProgram, "directionalLight.specular", glm::vec3(1.0f, 1.0f, 0.8f));
}

void LightingGl::setPointLight(unsigned int shaderProgram, int number, PointLight& pointLight, Transform& transform) {
	std::string iStr = std::to_string(number);

	glm::vec3 color = pointLight.color;
	glm::vec3 pos = transform.position;

	setUniform(shaderProgram, "pointLights[" + iStr + "].position", pos);
	setUniform(shaderProgram, "pointLights[" + iStr + "].diffuse", color * 0.5f);
	setUniform(shaderProgram, "pointLights[" + iStr + "].specular", color * 0.25f);
	setUniform(shaderProgram, "pointLights[" + iStr + "].constant", 1.0f);
	setUniform(shaderProgram, "pointLights[" + iStr + "].linear", 0.09f);
	setUniform(shaderProgram, "pointLights[" + iStr + "].quadratic", 0.032f);
}
