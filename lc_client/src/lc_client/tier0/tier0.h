#pragma once

#include "conpar/parameters.h"
#include "console/i_console.h"
#include "console/console.h"
#include "imgui_fonts.h"
#include "logger/logger.h"

/**
 * 
 * 
 */
class Tier0 {
public:
	Tier0();
	~Tier0();

	Parameters* getParameters();
	Console* getConsole();
	Logger* getLogger();
	ImGuiFonts* getImGuiFonts();

	static IConsole* getIConsole();

protected:

	Parameters* m_pParameters = nullptr;
	Console* m_pConsole = nullptr;
	ImGuiFonts* m_pImGuiFonts;
	Logger* m_pLogger = nullptr;

	static IConsole* m_pIConsole;
};