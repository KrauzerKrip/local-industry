#pragma once

#include <vector>

#include "lc_client/eng_gui/paint_objects/text.h"

class TextPresenter {
public: 
	virtual ~TextPresenter() = 0;

	virtual std::vector<Text>& getText() = 0;
};
