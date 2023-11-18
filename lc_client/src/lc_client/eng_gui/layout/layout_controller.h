#pragma once

#include <memory>
#include <vector>
#include "lc_client/eng_gui/controller/i_text_controller.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "layouts/layout.h"

class LayoutController {
public:
	void update();
	void show();
	void hide();

private:
	void updateLayout(std::shared_ptr<Layout> layout, std::vector<std::shared_ptr<Widget>>& widgets);

	std::shared_ptr<Layout> m_layout;
	std::unique_ptr<ITextController> m_textController;
};