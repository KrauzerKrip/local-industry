#include "eng_resource.h"

#include <fstream>
#include <lc_client/exceptions/io_exceptions.h>

namespace eng {

		Resource::Resource(std::string resourceRootPath) {
			m_resourceRootPath = resourceRootPath;
		}

		auto Resource::getFile(std::string path) const -> cmrc::file {
			auto fileSystem = cmrc::eng_resources::get_filesystem();
			auto file = fileSystem.open(path);

			return file;
		}

		auto Resource::getFileSystem() const -> cmrc::embedded_filesystem {
			return cmrc::eng_resources::get_filesystem();
		}

		auto Resource::getFileResource(std::string path) const -> std::vector<unsigned char> {
			std::ifstream binaryFile(m_resourceRootPath + path, std::ios::binary);

			if (binaryFile.good()) {
				/*Read Binary data using streambuffer iterators.*/
				std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(binaryFile)), (std::istreambuf_iterator<char>()));
				binaryFile.close();
				return buffer;
			}
			else {
				throw ResourceFileNotFoundException(path); 
			}
		}
}

