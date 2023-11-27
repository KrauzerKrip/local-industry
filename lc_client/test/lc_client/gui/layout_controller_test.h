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

	Background background(glm::vec4(255, 255, 255, 1.0));

	std::shared_ptr<Widget> widget = std::make_shared<Widget>(background, nullptr);
	widget->setPosition(glm::vec2(100, 100));
	widget->setSize(glm::vec2(400, 400));
	layout->addChild(widget);

	std::shared_ptr<Layout> layout2 = std::make_shared<Frame>();
	widget->setLayout(layout2);
	std::shared_ptr<Widget> widget2 = std::make_shared<Widget>(background, nullptr);
	widget2->setPosition(glm::vec2(400, 400));
	widget2->setSize(glm::vec2(100, 50));
	layout2->addChild(widget2);


	m_pLayoutController->setLayout(layout);

	m_pLayoutController->update();

	std::vector<WidgetData> widgets = m_pLayoutController->getWidgets();

	ASSERT_EQ(widgets.size(), 2);
	EXPECT_EQ(widgets.at(0).position, glm::vec2(100, 100));
	EXPECT_EQ(widgets.at(0).size, glm::vec2(400, 400));
	EXPECT_EQ(widgets.at(0).layer, 0);
	EXPECT_EQ(widgets.at(1).position, glm::vec2(500, 500));
	EXPECT_EQ(widgets.at(1).size, glm::vec2(100, 50));
	EXPECT_EQ(widgets.at(1).layer, 1);
};

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}