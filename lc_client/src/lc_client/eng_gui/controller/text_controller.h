#pragma once

#include "lc_client/eng_gui/view/text_presenter.h"
#include "i_text_controller.h"

class TextController : TextPresenter, ITextController {
public:
	TextController();

	std::vector<Text>& getText();
	void addText(Text text);

private:
	std::vector<Text> m_text;
};
