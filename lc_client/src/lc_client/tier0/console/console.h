#pragma once

#include <functional>
#include <string>

#include "i_console.h"


struct Callbacks {
	std::function<void(std::string)> pDevMessageCallback;
	std::function<void(std::string)> pMessageCallback;
	std::function<void(std::string)> pWarnCallback;
};


class Console : public IConsole {
public:
	Console();

	void devMessage(std::string text);
	void message(std::string text);
	void warn(std::string text);

	void executeCommand(std::string command);
	
	
	void setCallbacks(Callbacks* callbacks);

private:	
	Callbacks* m_pCallbacks = nullptr;
};
