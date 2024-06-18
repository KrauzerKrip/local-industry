#include "logger_console.h"

LoggerConsole::LoggerConsole(IConsole* pConsole) { m_pConsole = pConsole; }

void LoggerConsole::logInfo(std::string message) { m_pConsole->message(message); }

void LoggerConsole::logDebug(std::string message) { m_pConsole->devMessage(message); }

void LoggerConsole::logWarn(std::string message) { m_pConsole->warn(message); }

void LoggerConsole::logError(std::string message) { m_pConsole->warn("ERROR: " + message); }
