#include "resource_loader.h"

auto getResource(std::string path) {
	auto fileSystem = cmrc::eng_resources::get_filesystem();
	auto file = fileSystem.open(path);
	
	return file.begin();
}
