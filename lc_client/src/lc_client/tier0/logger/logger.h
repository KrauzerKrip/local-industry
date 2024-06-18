#pragma once

#include <string>


class Logger {
public:
	virtual void logInfo(std::string message) = 0;
	virtual void logDebug(std::string message) = 0;
	virtual void logWarn(std::string message) = 0;
	virtual void logError(std::string message) = 0;
};