#pragma once


struct ExtractionInProgress {
	entt::entity depositEntity;

	ExtractionInProgress(entt::entity depositEntity) : depositEntity(depositEntity) {}
};
