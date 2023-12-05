#pragma once

#include <gtest/gtest.h>
#include <memory>
#include "lc_client/eng_gui/layout/layout_controller.h"
#include "lc_client/eng_gui/layout/layouts/vbox.h"
#include "lc_client/eng_gui/paint_objects/background.h"

class VBoxTest : public testing::Test {
protected:
	void SetUp();
	void TearDown();
};

TEST_F(VBoxTest, vbox_test) { 
	VBox vbox;

	WidgetDependecies widgetDependecies;
	widgetDependecies.pBackgroundRender = nullptr;
	widgetDependecies.pZOffsetCalculator = nullptr;

	std::shared_ptr<Widget> widget1 = std::make_shared<Widget>(widgetDependecies);
	widget1->setSize(glm::vec2(100, 200));

	std::shared_ptr<Widget> widget2 = std::make_shared<Widget>(widgetDependecies);
	widget2->setSize(glm::vec2(100, 200));

	vbox.addChild(widget1);
	vbox.addChild(widget2);

	vbox.m_size = glm::vec2(100, 400);
	vbox.m_position = glm::vec2(50, 0);

	vbox.updateChildWidgets();

	EXPECT_EQ(widget1->getRectangle().m_absolutePosition, glm::vec2(50, 0));
	EXPECT_EQ(widget1->getRectangle().m_size, glm::vec2(100, 200));
	EXPECT_EQ(widget2->getRectangle().m_absolutePosition, glm::vec2(50, 200));
	EXPECT_EQ(widget2->getRectangle().m_size, glm::vec2(100, 200));
};