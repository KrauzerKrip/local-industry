#include <fstream>
#include <lc_client/exceptions/io_exceptions.h>

#include "resource_loading.h"

namespace eng {

	auto getFile(std::string path)  -> cmrc::file {
		auto fileSystem = cmrc::eng_resources::get_filesystem();
		auto file = fileSystem.open(path);

		return file;
	}

	auto getFileSystem() -> cmrc::embedded_filesystem {
		return cmrc::eng_resources::get_filesystem();
	}

	auto getFileResource(std::string path) -> std::vector<unsigned char> {
		std::ifstream binaryFile(path, std::ios::binary);

		if (binaryFile.good()) {
			/*Read Binary data using streambuffer iterators.*/
			std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(binaryFile)), (std::istreambuf_iterator<char>()));
			binaryFile.close();
			return buffer;
		}
		else {
			throw ResourceFileNotFound(path.c_str());
		}
	}
}

