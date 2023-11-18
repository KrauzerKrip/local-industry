#pragma once

#include "lc_client/eng_gui/paint_objects/text.h"

class ITextController {
public:
	virtual ~ITextController() = 0;
	
	virtual void addText(Text text) = 0;
};
