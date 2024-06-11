#include "deposit_extraction_system.h"

#include "components.h"
#include "internal_components.h"
#include "game/inventory/components.h"


DepositExtractionSystem::DepositExtractionSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void DepositExtractionSystem::update(double updateInterval) { 
	auto extractionsInProcess = m_pRegistry->view<ExtractionInProcess>();
	for (auto&& [entity, extractionInProcess] : extractionsInProcess.each()) {
		bool placementResult = m_pRegistry->all_of<InventoryLoaded>(extractionInProcess.placerTempEntity);
		if (placementResult) {
			m_pRegistry->emplace<Extracted>(entity);
		}
		else {
			m_pRegistry->emplace<CantExtract>(entity);
		}

		m_pRegistry->remove<ExtractionInProcess>(entity);
		m_pRegistry->destroy(extractionInProcess.placerTempEntity);
	}

	auto extractionRequests = m_pRegistry->view<ExtractRequest, Inventory>();
	for (auto&& [entity, extractRequest, inventory] : extractionRequests.each()) {
		ResourceDeposit& deposit = m_pRegistry->get<ResourceDeposit>(extractRequest.resourceDeposit);

		float massToPlace = 1.0f;

		entt::entity placer = m_pRegistry->create();
		InventoryLoad placement(entity, deposit.resource, massToPlace);
		m_pRegistry->emplace<InventoryLoad>(placer, placement);

		ExtractionInProcess extraction(placer, deposit.resource, 1);
		m_pRegistry->emplace<ExtractionInProcess>(entity, extraction);

		m_pRegistry->remove<ExtractRequest>(entity);
	}
}