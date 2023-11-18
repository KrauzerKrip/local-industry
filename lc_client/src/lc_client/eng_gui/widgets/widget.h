#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <array>
#include <optional>
#include "lc_client/eng_gui/layout/layouts/layout.h"
#include "lc_client/eng_gui/paint_objects/background.h"
#include "lc_client/eng_gui/paint_objects/text.h"

class Widget {
public:
	Widget();
	virtual ~Widget() = 0;
	
	void show();
	void hide();
	glm::vec2 getSize();
	void setSize(glm::vec2 size);
	glm::vec2 getPosition();
	void setPosition(glm::vec2 position);
	std::shared_ptr<Layout> getLayout();	
	void setBackground(Background background);
	void render();
	std::array<glm::vec2, 4> getVertices();
	void setVertices(std::array<glm::vec2, 4> vertices);

private:
	glm::vec2 m_size;
	glm::vec2 m_position;
	std::shared_ptr<Layout> m_layout;
	bool m_isVisible = false;
	std::array<glm::vec2, 4> m_vertices;
};
