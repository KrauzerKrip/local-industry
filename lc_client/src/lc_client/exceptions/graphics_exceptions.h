#pragma once

#include <stdexcept>

class TextureLoadException : public std::runtime_error {
public:
	TextureLoadException(std::string path, std::string info)
		: std::runtime_error("Failed to load texture '" + path + "'. " + info) {}
	TextureLoadException(std::string info)
		: std::runtime_error("Failed to load texture '" + info) {}
};
