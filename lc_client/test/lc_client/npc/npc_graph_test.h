#pragma once

#include <gtest/gtest.h>

#include "lc_client/eng_npc/npc_graph.h"


class NpcGraphTest : public testing::Test {
protected:
	void SetUp();
	void TearDown();

	NpcGraph* m_pNpcGraph = nullptr;
};

TEST_F(NpcGraphTest, npc_graph_test) { 
	Path path = m_pNpcGraph->getShortestPath(0, 3);

	EXPECT_EQ(path.distance, glm::distance(glm::vec3(0, 0, 0), glm::vec3(10, 0, 0)));
};
