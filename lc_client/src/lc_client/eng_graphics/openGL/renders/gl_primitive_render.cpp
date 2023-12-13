#include "gl_primitive_render.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "lc_client/eng_physics/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"


PrimitiveRender::PrimitiveRender(ShaderLoaderGl* pShaderLoader, entt::registry* pSceneRegisry, entt::registry* pMapRegistry) {
	m_pSceneRegistry = pSceneRegisry;
	m_pMapRegistry = pMapRegistry;

	m_shader = pShaderLoader->createShaderProgram("primitive", "primitive");

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void PrimitiveRender::render(glm::mat4 projection, glm::mat4 view) { renderLines(projection, view); }

void PrimitiveRender::renderLines(glm::mat4 projection, glm::mat4 view) { 
	auto lineEntities = m_pSceneRegistry->view<PrimitiveLine>();

	glm::mat4 mvp = projection * view;

	glUseProgram(m_shader);

	unsigned int mvpLoc = glGetUniformLocation(m_shader, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

	for (auto&& [entity, line] : lineEntities.each()) {
		glBindVertexArray(m_vao);

		setUniform(m_shader, "color", line.color);

		float vertices[] = {
			line.startPoint.x,
			line.startPoint.y,
			line.startPoint.z,
			line.endPoint.x,
			line.endPoint.y,
			line.endPoint.z,
		};

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_LINES, 0, 2);
		
		glBindVertexArray(0);
	}

}
