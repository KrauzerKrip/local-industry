#include "deposit_extraction_system.h"

#include "components.h"
#include "internal_components.h"
#include "game/inventory/components.h"
#include "exceptions.h"
#include <game/economy/internal_components.h>


DepositExtractionSystem::DepositExtractionSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void DepositExtractionSystem::update(double updateInterval) { 
	auto extractions = m_pRegistry->view<ExtractionInProgress, InventoryTriedLoad>();
	for (auto&& [entity, extraction, loadingTry] : extractions.each()) {
		ResourceDeposit& deposit = m_pRegistry->get<ResourceDeposit>(extraction.depositEntity);

		if (deposit.resource != loadingTry.item) {
			throw InvalidExtractionInProgressException();
		}

		deposit.massOfResource -= loadingTry.massLoaded;

		if (loadingTry.massLoaded > 0.00001) {
			m_pRegistry->emplace<Extracted>(loadingTry.inventoryEntity);
		}
		else {
			m_pRegistry->emplace<CantExtract>(loadingTry.inventoryEntity);
		}


		m_pRegistry->remove<InventoryTriedLoad>(entity);
		m_pRegistry->remove<ExtractionInProgress>(entity);
	}

	auto extractionRequests = m_pRegistry->view<ExtractRequest, Inventory>();
	for (auto&& [entity, extractRequest, inventory] : extractionRequests.each()) {
		ResourceDeposit& deposit = m_pRegistry->get<ResourceDeposit>(extractRequest.resourceDeposit);

		entt::entity loader = m_pRegistry->create();
		InventoryTryLoad loading(entity, deposit.resource, extractRequest.massToExtract);
		m_pRegistry->emplace<InventoryTryLoad>(loader, loading);

		ExtractionInProgress extraction(extractRequest.resourceDeposit);
		m_pRegistry->emplace<ExtractionInProgress>(loader, extraction);

		m_pRegistry->remove<ExtractRequest>(entity);
	}
}