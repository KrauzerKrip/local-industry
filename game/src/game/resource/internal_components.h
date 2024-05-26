#pragma once


struct ExtractionInProcess {
	entt::entity placerTempEntity;
	entt::entity resourceToPlace;
	float massToPlace;

	ExtractionInProcess(entt::entity placerTempEntity, entt::entity resourceToPlace, float massToPlace)
		: placerTempEntity(placerTempEntity), resourceToPlace(resourceToPlace), massToPlace(massToPlace) {}
};