#pragma once

#include <string>
#include <vector>
#include <functional>

#include "lc_client/exceptions/conpar_exceptions.h"


enum class ConparFlags : uint32_t { NONE = 0, CONFIRMATION = (1 << 0), CHEATS = (1 << 1), CONSTANT = (1 << 2) };

constexpr enum ConparFlags operator|(const enum ConparFlags selfValue, const enum ConparFlags inValue) {
	return (enum ConparFlags)(uint32_t(selfValue) | uint32_t(inValue));
}

constexpr enum ConparFlags operator&(const enum ConparFlags selfValue, const enum ConparFlags inValue) {
	return (enum ConparFlags)(uint32_t(selfValue) & uint32_t(inValue));
}


template <typename T>
concept IsAppliableType = std::is_same<T, bool>::value || std::is_same<T, std::string>::value ||
						  std::is_same<T, int>::value || std::is_same<T, float>::value;


template <IsAppliableType T> class ConPar {
public:
	ConPar(std::string name, T value, ConparFlags flags);
	ConPar(std::string name, T value);
	const std::string getName() const;
	const std::vector<ConparFlags>& getFlags() const;
	bool checkFlag(const ConparFlags flag) const;
	void setCallback(std::function<void(T value)> callback);

	T getValue() const;
	void setValue(T value);
	inline void setValueConvert(std::string value);

private:
	const std::string m_name;
	const ConparFlags m_flags;
	std::function<void(T value)> m_callback;

	T m_value;
};

template <IsAppliableType T>
ConPar<T>::ConPar(std::string name, T value) : m_name(name),
											   m_value(value),
											   m_flags(ConparFlags::NONE) {}

template <IsAppliableType T>
ConPar<T>::ConPar(std::string name, T value, ConparFlags flags) : m_name(name),
																  m_value(value),
																  m_flags(flags) {}

template <IsAppliableType T> const std::string ConPar<T>::getName() const { return m_name; }

template <IsAppliableType T> const std::vector<ConparFlags>& ConPar<T>::getFlags() const { return m_flags; }

template <IsAppliableType T> bool ConPar<T>::checkFlag(const ConparFlags flag) const {
	return ((m_flags & flag) != ConparFlags::NONE);
}

template <IsAppliableType T> void ConPar<T>::setCallback(std::function<void(T value)> callback) {
	m_callback = callback;
}

template <IsAppliableType T> T ConPar<T>::getValue() const { return m_value; }

template <IsAppliableType T> void ConPar<T>::setValue(T value) {
	if (checkFlag(ConparFlags::CONSTANT)) {
		throw ConsoleParameterConstantValueException(m_name);
	}
	else {
		m_value = value;
		if (m_callback) {
			m_callback(value);
		}
	}
}

template <IsAppliableType T> inline void ConPar<T>::setValueConvert(std::string value){}; 

template <> inline void ConPar<bool>::setValueConvert(std::string value) {
	if (checkFlag(ConparFlags::CONSTANT)) {
		throw ConsoleParameterConstantValueException(m_name);
	}
	if ((value == "true") || (value == "1")) {
		m_value = true;
		if (m_callback) {
			m_callback(true);
		}
	}
	else if ((value == "false") || (value == "0")) {
		m_value = false;
		if (m_callback) {
			m_callback(false);
		}
	}
	else {
		throw std::invalid_argument("Command.cpp: Not valid bool.");
	}
}

template <> inline void ConPar<int>::setValueConvert(std::string value) {
	if (checkFlag(ConparFlags::CONSTANT)) {
		throw ConsoleParameterConstantValueException(m_name);
	}
	int val = std::stoi(value);
	m_value = val;
	if (m_callback) {
		m_callback(val);
	}
}
template <> inline void ConPar<float>::setValueConvert(std::string value) {
	if (checkFlag(ConparFlags::CONSTANT)) {
		throw ConsoleParameterConstantValueException(m_name);
	}
	float val = std::stof(value);
	m_value = val;
	if (m_callback) {
		m_callback(val);
	}
}
