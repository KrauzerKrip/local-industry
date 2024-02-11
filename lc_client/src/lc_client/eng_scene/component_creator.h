#pragma once

#include <memory>

#include <entt/entt.hpp>
#include <pugixml.hpp>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_model/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_script/entt/components.h"
#include "lc_client/util/i_eng_resource.h"



Transform getTransform(pugi::xml_node node);
ModelRequest getModelData(pugi::xml_node node);
Script getScript(pugi::xml_node node, eng::IResource* resource);
// std::shared_ptr<Trigger> getTrigger(pugi::xml_node node);

namespace pseudo {
	class Object {
	public:
		Object(pugi::xml_node objectNode);
		~Object();

		ModelRequest getModelData();

	};
}


glm::vec3 makeVector3(pugi::xml_node node);
