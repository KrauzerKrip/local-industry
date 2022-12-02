#include <stdexcept>

class UnknownKeyCodeException : public std::runtime_error {
public:
	UnknownKeyCodeException(std::string key) : std::runtime_error("Unknown key code: " + key) { }
};