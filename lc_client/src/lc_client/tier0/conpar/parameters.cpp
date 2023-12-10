#include "parameters.h"
#include "parameters.h"

#include <vector>
#include <map>


Parameters::Parameters() {}

void Parameters::setParameterValueConvert(std::string name, std::string value) {

	if (name == "sv_cheats") {
		int i = 0;
	}

	try {
		ConPar<bool>& conpar = m_boolConpars.at(name);

		if (conpar.checkFlag(ConparFlags::CHEATS) && !getParameterValue<bool>("sv_cheats")) {
			throw ConsoleParameterCheatsException(name);
		}

		conpar.setValueConvert(value);

		return;
	}
	catch (std::out_of_range&) {
	}

	try {
		ConPar<std::string>& conpar = m_stringConpars.at(name);

		if (conpar.checkFlag(ConparFlags::CHEATS) && !getParameterValue<bool>("sv_cheats")) {
			throw ConsoleParameterCheatsException(name);
		}

		conpar.setValue(value);

		return;
	}
	catch (std::out_of_range&) {
	}

	try {
		ConPar<int>& conpar = m_intConpars.at(name);

		if (conpar.checkFlag(ConparFlags::CHEATS) && !getParameterValue<bool>("sv_cheats")) {
			throw ConsoleParameterCheatsException(name);
		}

		conpar.setValueConvert(value);

		return;
	}
	catch (std::out_of_range&) {
	}

	try {
		ConPar<float>& conpar = m_floatConpars.at(name);

		if (conpar.checkFlag(ConparFlags::CHEATS) && !getParameterValue<bool>("sv_cheats")) {
			throw ConsoleParameterCheatsException(name);
		}

		conpar.setValueConvert(value);

		return;
	}
	catch (std::out_of_range&) {

	}

	throw ConsoleParameterNotFoundException(name);
}

void Parameters::addParameter(ConPar<bool> parameter) { m_boolConpars.emplace(parameter.getName(), parameter); }
void Parameters::addParameter(ConPar<std::string> parameter) {
	m_stringConpars.emplace(parameter.getName(), parameter);
}
void Parameters::addParameter(ConPar<int> parameter) { m_intConpars.emplace(parameter.getName(), parameter); }
void Parameters::addParameter(ConPar<float> parameter) { m_floatConpars.emplace(parameter.getName(), parameter); }
