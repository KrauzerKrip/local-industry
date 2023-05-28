#pragma once

#include <string>
#include <vector>


#include "lc_client/exceptions/conpar_exceptions.h"
  

enum class Flags { CONFIRMATION, CHEATS, CONSTANT };

template <typename T>
concept IsAppliableType = std::is_same<T, bool>::value || std::is_same<T, std::string>::value ||
						  std::is_same<T, int>::value || std::is_same<T, float>::value;


template <IsAppliableType T> class ConPar {
public:
	ConPar(std::string name, T value, std::vector<Flags> flags);
	ConPar(std::string name, T value);
	const std::string getName() const;
	const std::vector<Flags>& getFlags() const;
	bool checkFlag(const Flags flag) const;

	T getValue() const;
	void setValue(T value);

private:
	const std::string m_name;
	const std::vector<Flags> m_flags;

	T m_value;
};

template <IsAppliableType T>
ConPar<T>::ConPar(std::string name, T value, std::vector<Flags> flags) : m_name(name),
																		 m_value(value),
																		 m_flags(flags) {}

template <IsAppliableType T>
ConPar<T>::ConPar(std::string name, T value) : m_name(name),
											   m_value(value),
											   m_flags(std::vector<Flags>()) {}

template <IsAppliableType T> const std::string ConPar<T>::getName() const { return m_name; }

template <IsAppliableType T> const std::vector<Flags>& ConPar<T>::getFlags() const { return m_flags; }

template <IsAppliableType T> bool ConPar<T>::checkFlag(const Flags flag) const {
	for (auto& f : m_flags) {
		if (f == flag) {
			return true;
		}
	}

	return false;
}


template <IsAppliableType T> T ConPar<T>::getValue() const { return m_value; }

template <IsAppliableType T> void ConPar<T>::setValue(T value) {
	if (checkFlag(Flags::CONSTANT)) {
		throw ConsoleParameterConstantValueException(m_name);
	}
	else {
		m_value = value;
	}
}