#include "latex_extractor_system.h"
#include "components.h"
#include <game/machine/components.h>

LatexExtractorSystem::LatexExtractorSystem(entt::registry* pRegistry, PhysicalConstants* pPhysicalConstants) : BaseMachineSystem(pRegistry, pPhysicalConstants) {}

void LatexExtractorSystem::update(double updateInterval) {}

void LatexExtractorSystem::machineUpdate(double updateInterval) {
	auto latexExtractors = m_pRegistry->view<LatexExtractor, Machine, Connections>();

	for (auto&& [entity, extractor, connections] : latexExtractors.each()) {
		Connection& connection = connections.inputs.at(ConnectionResourceType::LATEX);
		extractor.latexMass += connection.resource;
		connection.resource = 0;
	}
}
