#include "inventory_controller.h"

#include "game/inventory/components.h"
#include "game/control/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include "game/item/components.h"



InventoryController::InventoryController(
	InventoryView* pView, GraphicsSettings* pSettings, Camera* pCamera, entt::registry* pRegistry) {
	m_pView = pView;
	m_pGraphicsSettings = pSettings;
	m_pCamera = pCamera;
	m_pRegistry = pRegistry;
}

void InventoryController::input() {
	std::unordered_map<std::string, float> data;

	m_pView->enable(false);

	auto inventories = m_pRegistry->view<Inventory, Selected, Transform>();

	for (auto&& [entity, inventory, transform] : inventories.each()) {
		// if (m_pRegistry->all_of<CombustionFuelStorage>(entity)) {
		//	data.emplace("Fuel:", std::format("{:.2f} kg", m_pRegistry->get<CombustionFuelStorage>(entity).mass));
		// }
		// if (m_pRegistry->all_of<HeatOut>(entity)) {
		//	data.emplace("HeatOut:", std::format("{:.2f} J", m_pRegistry->get<HeatOut>(entity).heat));
		// }
		// if (m_pRegistry->all_of<HeatIn>(entity)) {
		//	data.emplace("HeatIn:", std::format("{:.2f} J", m_pRegistry->get<HeatIn>(entity).heat));
		// }
		// if (m_pRegistry->all_of<MachineMode>(entity)) {
		//	data.emplace("Toggle:", m_pRegistry->get<MachineMode>(entity).toggle ? "on" : "off");
		// }

		for (auto [itemEnt, mass] : inventory.items) {
			data.emplace(m_pRegistry->get<Item>(itemEnt).name, mass);
		}

		m_pView->enable(true);
		m_pView->setPurchasesData(data);
		m_pView->setWindowName("Inventory");

		glm::mat4 projection =
			glm::perspective(glm::radians(m_pGraphicsSettings->getFov()), 16.0f / 9.0f, 0.1f, 1000.0f);

		glm::mat4 model(1.0f);
		model = glm::translate(model, transform.position);
		model *= glm::mat4_cast(transform.rotation);
		model = glm::scale(model, transform.scale);

		glm::vec4 vec4 = projection * m_pCamera->getViewMatrix() * model * glm::vec4(1.0f);
		glm::vec3 clipSpacePos = vec4 / vec4.w;
		glm::vec2 screenSpace =
			glm::vec2((clipSpacePos.x * 0.5 + 0.5) * 1920.0f, (-clipSpacePos.y * 0.5 + 0.5) * 1080.0f);

		m_pView->setPosition(screenSpace);
	}
}
