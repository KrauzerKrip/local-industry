#pragma once

#include <string>

#include "lc_client/tier0/conpar/parameters.h"
#include "i_console.h"


class Command {
public:
	Command(Parameters* pParameters, IConsole* pConsole);

	void execute(std::string text);

private:
	bool checkSetBool(std::string op, std::string arg);
	bool checkSetString(std::string op, std::string arg);
	bool checkSetInt(std::string op, std::string arg);
	bool checkSetFloat(std::string op, std::string arg);

	Parameters* m_pParameters = nullptr;
	IConsole* m_pConsole = nullptr;
};

