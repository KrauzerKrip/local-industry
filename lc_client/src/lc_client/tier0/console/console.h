#pragma once

#include <string>

#include "i_console.h"
#include "i_console_input.h"
#include "command.h"
#include "lc_client/tier0/conpar/parameters.h"


class Console : public IConsole, public IConsoleInput {
public:
	Console(Parameters* pParameters);

	void devMessage(std::string text);
	void message(std::string text);
	void warn(std::string text);

	void enter(std::string command);
	void setCallbacks(Callbacks* callbacks);

private:	
	Callbacks* m_pCallbacks = nullptr;

	Parameters* m_pParameters = nullptr;
	Command m_command;
};
