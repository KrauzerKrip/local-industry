#pragma once

#include <string>


enum class CommandType { SET, GET, EXECUTE };

class CommandParser {
public:
	CommandParser(std::string text);

	CommandType getType();
	std::string getOperator();
	std::string getArgument();

private:
	CommandType m_type;
	std::string m_operator;
	std::string m_argument;
};
