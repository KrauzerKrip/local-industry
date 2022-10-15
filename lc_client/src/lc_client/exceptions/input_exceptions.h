#include <stdexcept>

class UnknownKeyCode : public std::runtime_error {
public:
	UnknownKeyCode(const char* key) : std::runtime_error("Unknown key code: " + *key) { }
};