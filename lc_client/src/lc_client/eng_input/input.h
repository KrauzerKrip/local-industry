#pragma once

#include "i_input_raw.h"


class Input {
public:
	Input(IInputRaw* pInputRaw);

	bool isOnAction(const std::string action);
};
