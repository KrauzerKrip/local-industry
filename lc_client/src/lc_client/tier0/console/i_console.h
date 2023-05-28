#pragma once


class IConsole {
public:

	virtual ~IConsole(){};

	virtual void devMessage(std::string text) = 0;
	virtual void message(std::string text) = 0;
	virtual void warn(std::string text) = 0;

};
