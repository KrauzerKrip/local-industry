#pragma once

#include <entt/entt.hpp>


struct Harvestable {
	entt::entity yield;
	float massOfYield;

	Harvestable(entt::entity yield, float massOfYield) : yield(yield), massOfYield(massOfYield) {}
};

struct Harvested {
	entt::entity by;

	Harvested(entt::entity by) : by(by) {}
};

struct Bush {

};
