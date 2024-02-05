
#include <string>

#include <entt/entt.hpp>

#include "../task_list.h"
#include "../task_list_controller.h"
#include "../task_list_layout.h"
#include "lc_client/eng_gui/widgets/dependencies.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "../task_view.h"


class CharacterTaskList : public TaskList {
public:
	CharacterTaskList(std::string name, GuiDependencies dependencies);
};