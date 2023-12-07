#pragma once

#include <memory>
#include <vector>

#include "input_receiver.h"
#include "lc_client/eng_input/i_input.h"


class InputController {
public:
	InputController(IInput* pInput);

	void update();
	void addReceiver(std::shared_ptr<InputReceiver> receiver);

private:
	std::vector<std::shared_ptr<InputReceiver>> m_receivers;

	IInput* m_pInput;
};
