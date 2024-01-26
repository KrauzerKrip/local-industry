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

	std::shared_ptr<Widget> widget = std::make_shared<Widget>(widgetDependecies);
	widget->setPosition(glm::vec2(100, 100));
	widget->setSize(glm::vec2(400, 400));
	layout->addChild(widget);

	std::shared_ptr<Layout> layout2 = std::make_shared<Frame>();
	widget->setLayout(layout2);
	std::shared_ptr<Widget> widget2 = std::make_shared<Widget>(widgetDependecies);
	widget2->setPosition(glm::vec2(400, 400));
	widget2->setSize(glm::vec2(100, 50));
	layout2->addChild(widget2);


	m_pLayoutController->setLayout(layout);

	m_pLayoutController->update();

	std::vector<std::shared_ptr<Widget>> widgets = m_pLayoutController->getWidgets();

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