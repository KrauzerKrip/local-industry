#pragma once

#include <string>
#include "events.h"


class InputReceiver {
public:
	virtual ~InputReceiver(){};

	virtual void mouseClick(MouseClickEvent event) = 0;
	virtual void keyPressed(KeyEvent event) = 0;
	virtual void characterInput(std::string character) = 0;
};
