#pragma once

#include <gtest/gtest.h>

#include "lc_client/eng_gui/layout/layout_controller.h"
#include "lc_client/eng_gui/layout/layouts/frame.h"
#include "lc_client/eng_gui/paint_objects/background.h"

class LayoutControllerTest : public testing::Test {
protected:
	void SetUp();
	void TearDown();

	LayoutController* m_pLayoutController;
};

TEST_F(LayoutControllerTest, layout_controller_test) { 
	std::shared_ptr<Frame> layout = std::make_shared<Frame>();

    GuiDependencies widgetDependecies;

	Widget* pWidget = new Widget(widgetDependecies);
	pWidget->setPosition(glm::vec2(100, 100));
	pWidget->setSize(glm::vec2(400, 400));
	layout->addChild(pWidget);

	std::shared_ptr<Layout> layout2 = std::make_shared<Frame>();
	pWidget->setLayout(layout2);
	Widget* pWidget2 = new Widget(widgetDependecies);
	pWidget2->setPosition(glm::vec2(400, 400));
	pWidget2->setSize(glm::vec2(100, 50));
	layout2->addChild(pWidget2);


	m_pLayoutController->setLayout(layout);

	m_pLayoutController->update();

	std::vector<Widget*> widgets = m_pLayoutController->getWidgets();

	ASSERT_EQ(widgets.size(), 2);
	EXPECT_EQ(widgets.at(0)->getRectangle().m_absolutePosition, glm::vec2(100, 100));
	EXPECT_EQ(widgets.at(0)->getRectangle().m_size, glm::vec2(400, 400));
	EXPECT_EQ(widgets.at(1)->getRectangle().m_absolutePosition, glm::vec2(500, 500));
	EXPECT_EQ(widgets.at(1)->getRectangle().m_size, glm::vec2(100, 50));
};

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}