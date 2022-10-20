#include "resource_loading.h"

namespace eng {

	auto getResource(std::string path) {
		auto fileSystem = cmrc::eng_resources::get_filesystem();
		auto file = fileSystem.open(path);

		return file.begin();
	}

	auto getFileSystem() -> cmrc::embedded_filesystem {
		return cmrc::eng_resources::get_filesystem();
	}
}

