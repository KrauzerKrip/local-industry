#pragma once

#include <entt/entt.hpp>


struct ResourceDeposit {
	entt::entity resource;
	float massOfResource;

	ResourceDeposit(entt::entity resource, float massOfResource) : resource(resource), massOfResource(massOfResource) {}
};

struct ExtractRequest {
	entt::entity resourceDeposit;
};

struct Extracted {

};

struct CantExtract {

};


