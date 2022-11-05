#include <stdexcept>

class ResourceFileNotFound : public std::runtime_error {
public:
	ResourceFileNotFound(const char* path) : std::runtime_error("Resource file not found: " + *path) { }
};