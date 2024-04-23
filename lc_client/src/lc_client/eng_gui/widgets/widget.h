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

enum class SizePolicy { FIXED, RESIZE };

class Widget {
public:
	Widget(Background* pBackground);
	Widget(GuiDependencies dependencies);
	Widget();
	virtual ~Widget() = default;
	
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
	Layout* getLayout();
	void setLayout(Layout* pLayout);
	void setBackground(Background* background);
	Background* getBackground();
	void setName(std::string);
	SizePolicy getSizePolicy();
	void setSizePolicy(SizePolicy policy);
	virtual void render();
	Rectangle& getRectangle();
	Layer& getLayer();
	void setInteractiveArea(Rectangle rectangle);

protected:
	glm::vec2 m_size;
	glm::vec2 m_position;
	std::unique_ptr<Layout> m_layout;
	bool m_isVisible = false;
	Background* m_background;
	std::string m_name;
	SizePolicy m_sizePolicy;
	Rectangle m_rectangle;
	Layer m_layer;

	Rectangle m_interactiveArea;
};
