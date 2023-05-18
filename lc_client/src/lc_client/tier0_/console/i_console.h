#pragma once


class IConsole {
public:

	virtual ~IConsole(){};

	virtual void devMessage() = 0;
	virtual void message() = 0;
	virtual void warn() = 0;

};
