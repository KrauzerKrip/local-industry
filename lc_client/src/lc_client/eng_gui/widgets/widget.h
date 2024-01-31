#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <array>
#include <optional>
#include "lc_client/eng_gui/layout/layouts/layout.h"
#include "lc_client/eng_gui/paint_objects/color_background.h"
#include "lc_client/eng_gui/paint_objects/text.h"
#include "lc_client/eng_graphics/gui/background_render.h"
#include "rectangle.h"
#include "layer.h"
#include "dependencies.h"

class Layout;

class Widget {
public:
	Widget(Background* pBackground);
	Widget(GuiDependencies dependencies);
	Widget();
	//virtual ~Widget() = 0;
	
	void show();
	void showWithChildren();
	void hide();
	void hideWithChildren();
	void toggle();
	void toggleWithChildren();
	bool isVisible();
	glm::vec2 getSize();
	void setSize(glm::vec2 size);
	void setSize(unsigned int width, unsigned height);
	glm::vec2 getPosition();
	void setPosition(glm::vec2 position);
	void setPosition(unsigned int x, unsigned int y);
	std::shared_ptr<Layout> getLayout();
	void setLayout(std::shared_ptr<Layout> layout);
	void setLayout(Layout* pLayout);
	void setBackground(Background* background);
	Background* getBackground();
	void setName(std::string);
	virtual void render();
	Rectangle& getRectangle();
	Layer& getLayer();

protected:
	glm::vec2 m_size;
	glm::vec2 m_position;
	std::shared_ptr<Layout> m_layout;
	bool m_isVisible = false;
	std::unique_ptr<Background> m_background;
	std::string m_name;
	Rectangle m_rectangle;
	Layer m_layer;
};
