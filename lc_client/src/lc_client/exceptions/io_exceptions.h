#include <stdexcept>

class ResourceFileNotFoundException : public std::runtime_error {
public:
	ResourceFileNotFoundException(std::string path) : std::runtime_error("Resource file not found: " + path) { }
};

class ImageLoadFailureException : public std::runtime_error {
public:
	ImageLoadFailureException(std::string info) : std::runtime_error("Fail to load image:\n" + info + "\n") { }
};

class FileTooLargeException : public std::runtime_error {
public:
	FileTooLargeException(std::string info) : std::runtime_error("File is too large to load it:\n" + info + "\n") { }
};

class AssimpException : public std::runtime_error {
public:
	AssimpException(std::string info) : std::runtime_error("Assimp fail:\n" + info + "\n") { }
};
