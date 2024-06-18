#pragma once

#include "logger.h"
#include "lc_client/tier0/console/i_console.h"

class LoggerConsole : public Logger {
public:
	LoggerConsole(IConsole* pConsole);

	void logInfo(std::string message);
	void logDebug(std::string message);
	void logWarn(std::string message);
	void logError(std::string message);

private:
	IConsole* m_pConsole = nullptr;
};