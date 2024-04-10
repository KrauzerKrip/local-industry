#include "gl_lighting.h"

#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"

LightingGl::LightingGl(entt::registry* pRegistry, Camera* pCamera) {
	m_pRegistry = pRegistry;
	m_pCamera = pCamera;
}

void LightingGl::setLighting(unsigned int shaderProgram) {
	auto skyboxes = m_pRegistry->view<Skybox>();

	Skybox skybox;
	skybox.lightColor = glm::vec3(1, 1, 1);
	skybox.lightStrength = 1.0f;

	for (auto&& [entity, sbox] : skyboxes.each()) {
		skybox = sbox;
	}

	setUniform(shaderProgram, "ambientLight.color", skybox.lightColor);
	setUniform(shaderProgram, "ambientLight.strength", skybox.lightStrength);

	setUniform(shaderProgram, "spotLight.position", m_pCamera->getPosition());
	setUniform(shaderProgram, "spotLight.direction", m_pCamera->getCameraFront());
	setUniform(shaderProgram, "spotLight.cutOff", (float)glm::cos(glm::radians(12.5)));
	setUniform(shaderProgram, "spotLight.outerCutOff", (float)glm::cos(glm::radians(17.5)));
	setUniform(shaderProgram, "spotLight.diffuse", glm::vec3(1.0f));
	setUniform(shaderProgram, "spotLight.specular", glm::vec3(0.5f));
	setUniform(shaderProgram, "spotLight.constant", 1.0f);
	setUniform(shaderProgram, "spotLight.linear", 0.09f);
	setUniform(shaderProgram, "spotLight.quadratic", 0.032f);

	auto pointLights = m_pRegistry->view<Transform, PointLight>();

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
