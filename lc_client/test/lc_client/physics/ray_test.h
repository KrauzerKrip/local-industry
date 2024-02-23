#pragma once

#include <gtest/gtest.h>

#include "lc_client/eng_physics/raycast/ray.h"


class RayTest : public testing::Test {
	protected:
	void SetUp();
	void TearDown();
};

TEST_F(RayTest, ray_test) { 
	float length = 5;
	float width = 100;
	float height = 100;

	glm::vec3 size(length, width, height);

	glm::vec3 boxPosition(10.0f, 0.0f, 0.0f);

	Ray ray(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));

	std::optional<RaycastIntersection> result = ray.getIntersectionWithAABB(size, boxPosition);

	EXPECT_EQ(result.has_value(), true);
};
