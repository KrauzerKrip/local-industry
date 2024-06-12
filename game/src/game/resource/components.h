#pragma once

#include <entt/entt.hpp>


struct ResourceDeposit {
	entt::entity resource;
	float massOfResource;

	ResourceDeposit(entt::entity resource, float massOfResource) : resource(resource), massOfResource(massOfResource) {}
};

struct ExtractRequest {
	entt::entity resourceDeposit;
	float massToExtract;

	ExtractRequest(entt::entity resourceDeposit, float massToExtract)
		: resourceDeposit(resourceDeposit),
		  massToExtract(massToExtract) {}
};

struct Extracted {

};

struct CantExtract {

};


