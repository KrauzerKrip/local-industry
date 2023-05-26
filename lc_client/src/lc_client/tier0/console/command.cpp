#include "command.h"

#include <stdlib.h>

#include "command_parser.h"



Command::Command(Parameters* pParameters, IConsole* pConsole) {
	m_pParameters = pParameters;
	m_pConsole = pConsole;
}

void Command::execute(std::string text) {
	CommandParser parser(text);

	CommandType type = parser.getType();
	std::string op = parser.getOperator();
	std::string arg = parser.getArgument();

	if (type == CommandType::SET) {
		if (checkSetBool(op, arg)) {
			return;
		}
		else if (checkSetString(op, arg)) {
			return;
		}
		else if (checkSetInt(op, arg)) {
			return;
		}
		else if (checkSetFloat(op, arg)) {
			return;
		}
		else {
			throw ConsoleParameterNotFoundException(op);
		}
	}
	else if (type == CommandType::GET) {
		try {
			m_pConsole->message(op + " = " + std::to_string(m_pParameters->getParameterValue<bool>(op)));
			return;
		}
		catch (ConsoleParameterNotFoundException&) {
		}
		try {
			m_pConsole->message(op + " = " + m_pParameters->getParameterValue<std::string>(op));
			return;
		}
		catch (ConsoleParameterNotFoundException&) {
		}
		try {
			m_pConsole->message(op + " = " + std::to_string(m_pParameters->getParameterValue<int>(op)));
			return;
		}
		catch (ConsoleParameterNotFoundException&) {
		}
		try {
			m_pConsole->message(op + " = " + std::to_string(m_pParameters->getParameterValue<float>(op)));
			return;
		}
		catch (ConsoleParameterNotFoundException&) {
		}

		throw ConsoleParameterNotFoundException(op);
	}
	else if (type == CommandType::EXECUTE) {}
}

bool Command::checkSetBool(std::string op, std::string arg) { 
	try {

		m_pParameters->getParameterValue<bool>(op);

		if ((arg == "true") || (arg == "1")) {
			m_pParameters->setParameterValue<bool>(op, true);
		}
		else if ((arg == "false") || (arg == "0")) {
			m_pParameters->setParameterValue<bool>(op, false);
		}
		else {
			throw std::invalid_argument("Command.cpp: Not valid bool.");
		}

		return true;
	}
	catch (ConsoleParameterNotFoundException&) {
		return false;
	}
}

bool Command::checkSetString(std::string op, std::string arg) {

	try {
		m_pParameters->setParameterValue<std::string>(op, arg);
		return true;
	}
	catch (ConsoleParameterNotFoundException&) {
		return false;
	}
}
 
bool Command::checkSetInt(std::string op, std::string arg) {
	try {
		m_pParameters->setParameterValue<int>(op, std::stoi(arg));
		return true;
	}
	catch (ConsoleParameterNotFoundException&) {
		return false;
	}
}

bool Command::checkSetFloat(std::string op, std::string arg) {
	try {
		m_pParameters->setParameterValue<float>(op, std::stof(arg));
		return true;
	}
	catch (ConsoleParameterNotFoundException&) {
		return false;
	}
}
