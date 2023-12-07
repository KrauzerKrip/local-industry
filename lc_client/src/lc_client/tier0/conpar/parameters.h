#pragma once

#include <unordered_map>
#include <string>

#include "conpar.h"
#include "lc_client/exceptions/conpar_exceptions.h"


class Parameters {
public:
	Parameters();

	template <IsAppliableType T> T getParameterValue(std::string name);
	template <IsAppliableType T> void setParameterValue(std::string name, T value) {
		ConPar<T>& conpar = getParameter<T>(name); 
		
		if (conpar.checkFlag(ConparFlags::CHEATS) && !getParameterValue<bool>("sv_cheats")) {
			throw ConsoleParameterCheatsException(name);
		}

		conpar.setValue(value);
	}

	void setParameterValueConvert(std::string name, std::string value);

	void addParameter(ConPar<bool> parameter);
	void addParameter(ConPar<std::string> parameter);
	void addParameter(ConPar<int> parameter);
	void addParameter(ConPar<float> parameter);

	template <IsAppliableType T> ConPar<T>& getParameter(std::string name) {
		static_assert("Don`t call me like that. I don`t appreciate the type you have given me.");
	}
	template <> ConPar<bool>& getParameter<bool>(std::string name) {
		try {
			return m_boolConpars.at(name);
		}
		catch (std::out_of_range&) {
			throw ConsoleParameterNotFoundException(name);
		}
	};
	template <> ConPar<std::string>& getParameter<std::string>(std::string name) {
		try {
			return m_stringConpars.at(name);
		}
		catch (std::out_of_range&) {
			throw ConsoleParameterNotFoundException(name);
		}
	};
	template <> ConPar<int>& getParameter<int>(std::string name) {
		try {
			return m_intConpars.at(name);
		}
		catch (std::out_of_range&) {
			throw ConsoleParameterNotFoundException(name);
		}
	};
	template <> ConPar<float>& getParameter<float>(std::string name) {
		try {
			return m_floatConpars.at(name);
		}
		catch (std::out_of_range&) {
			throw ConsoleParameterNotFoundException(name);
		}
	};


private:
	std::unordered_map<std::string, ConPar<bool>> m_boolConpars;
	std::unordered_map<std::string, ConPar<std::string>> m_stringConpars;
	std::unordered_map<std::string, ConPar<int>> m_intConpars;
	std::unordered_map<std::string, ConPar<float>> m_floatConpars;
};

template <IsAppliableType T> T Parameters::getParameterValue(std::string name) { return getParameter<T>(name).getValue(); }

