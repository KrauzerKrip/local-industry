#include <stdexcept>

class UnknownKeyCodeException : public std::runtime_error {
public:
	UnknownKeyCodeException(const char* key) : std::runtime_error("Unknown key code: " + *key) { }
};