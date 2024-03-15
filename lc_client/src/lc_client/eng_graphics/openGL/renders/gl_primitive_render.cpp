#include "gl_primitive_render.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "lc_client/eng_physics/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"
#include "lc_client/eng_scene/entt/components.h"


PrimitiveRender::PrimitiveRender(ShaderLoaderGl* pShaderLoader, entt::registry* pSceneRegisry, entt::registry* pMapRegistry) {
	m_pSceneRegistry = pSceneRegisry;
	m_pMapRegistry = pMapRegistry;

	m_shader = pShaderLoader->createShaderProgram("primitive", "primitive_alpha");

	glGenVertexArrays(1, &m_lineVao);
	glGenBuffers(1, &m_lineVbo);
	glBindVertexArray(m_lineVao);

	glBindBuffer(GL_ARRAY_BUFFER, m_lineVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	 float cubeVertices[] = {// front

		-1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0,
		// back
		-1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, -1.0};

	 GLuint cubeIndices[] = {// front
		 0, 1, 2, 2, 3, 0,
		 // right
		 1, 5, 6, 6, 2, 1,
		 // back
		 7, 6, 5, 5, 4, 7,
		 // left
		 4, 0, 3, 3, 7, 4,
		 // bottom
		 4, 5, 1, 1, 0, 4,
		 // top
		 3, 2, 6, 6, 7, 3};

	 unsigned int cubeVbo;
	 unsigned int cubeEbo;

	 glGenVertexArrays(1, &m_cubeVao);
	 glGenBuffers(1, &cubeVbo);
	 glBindVertexArray(m_cubeVao);

	 glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	 glGenBuffers(1, &cubeEbo);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEbo);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	 glEnableVertexAttribArray(0);

	 glBindBuffer(GL_ARRAY_BUFFER, 0);
	 glBindVertexArray(0);
}

void PrimitiveRender::render(glm::mat4 projection, glm::mat4 view) {
	 renderLines(projection, view);
	 renderCubes(projection, view);
}

void PrimitiveRender::renderLines(glm::mat4 projection, glm::mat4 view) { 
	auto lineEntities = m_pSceneRegistry->view<PrimitiveLine>();

	glm::mat4 mvp = projection * view;

	glUseProgram(m_shader);

	unsigned int mvpLoc = glGetUniformLocation(m_shader, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

	for (auto&& [entity, line] : lineEntities.each()) {
		glBindVertexArray(m_lineVao);

		setUniform(m_shader, "color", line.color);

		float vertices[] = {
			line.startPoint.x,
			line.startPoint.y,
			line.startPoint.z,
			line.endPoint.x,
			line.endPoint.y,
			line.endPoint.z,
		};

		glBindBuffer(GL_ARRAY_BUFFER, m_lineVbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_LINES, 0, 2);
		
		glBindVertexArray(0);
	}

}

void PrimitiveRender::renderCubes(glm::mat4 projection, glm::mat4 view) {
	auto cubeEntities = m_pSceneRegistry->view<PrimitiveCube, Transform>();

	glUseProgram(m_shader);

	for (auto&& [entity, cube, transform] : cubeEntities.each()) {
		glm::mat4 mvp = projection * view;

		glBindVertexArray(m_cubeVao);

		setUniform(m_shader, "color", cube.color);

		glm::mat4 model(1.0);

		model = glm::translate(model, transform.position);
		model *= glm::mat4_cast(transform.rotation);
		model = glm::scale(model, transform.scale);

		mvp *= model;

		unsigned int mvpLoc = glGetUniformLocation(m_shader, "mvp");
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
}
