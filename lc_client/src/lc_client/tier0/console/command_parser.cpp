#include "command_parser.h"

#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>


#include "lc_client/exceptions/command_exceptions.h"


CommandParser::CommandParser(std::string text) { 

	//std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) { return std::tolower(c); });

	std::stringstream ss(text);
	std::string item;
	std::vector<std::string> tokens;
	
	while (std::getline(ss, item, ' ')) {
		tokens.push_back(item);
	}

	if (tokens.size() == 0) {
		throw IncorrectCommandException(text);
	}

	if (tokens.size() > 3) {
		throw IncorrectCommandException(text);
	}

	if (tokens.at(0) == "set") {
		m_type = CommandType::SET;

		try {
			m_operator = tokens.at(1);

			m_argument = tokens.at(2);
		}
		catch (std::out_of_range&) {
			throw IncorrectCommandException(text);
		}
	
	}
	else if (tokens.at(0) == "get") {
		m_type = CommandType::GET;

		try {
			m_operator = tokens.at(1);
		}
		catch (std::out_of_range&) {
			throw IncorrectCommandException(text);
		}
	}
	else if (tokens.at(0) == "execute") {
		m_type = CommandType::EXECUTE;
	}
	else if ((tokens.at(0) == "exit") || (tokens.at(0) == "quit")) {
		exit(0);
	}
	else {
		throw IncorrectCommandException(text);
	}


}

CommandType CommandParser::getType() { return m_type; }

std::string CommandParser::getOperator() { return m_operator; }

std::string CommandParser::getArgument() { return m_argument; }
