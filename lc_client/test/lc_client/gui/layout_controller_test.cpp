#include "layout_controller_test.h"

void LayoutControllerTest::SetUp() { 
	m_pLayoutController = new LayoutController();
}

void LayoutControllerTest::TearDown() { delete m_pLayoutController; }
