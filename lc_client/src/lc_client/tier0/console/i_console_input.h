#pragma once

#include <string>
#include <functional>


struct Callbacks {
	std::function<void(std::string)> pDevMessageCallback;
	std::function<void(std::string)> pMessageCallback;
	std::function<void(std::string)> pWarnCallback;
};


class IConsoleInput {
public:
	virtual ~IConsoleInput(){};

	virtual void enter(std::string command) = 0;
	virtual void setCallbacks(Callbacks* callbacks) = 0;
};