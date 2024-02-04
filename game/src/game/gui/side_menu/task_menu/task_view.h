#pragma once

#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_gui/widgets/text_widget.h"

import character;


struct TaskData {
	std::string name;
	TaskProgress progress;
};


class TaskView : public Widget {
public:
	TaskView(GuiDependencies dependencies);

	void setData(const TaskData& taskData);

private:
	TextWidget* m_pLabel = nullptr;
};