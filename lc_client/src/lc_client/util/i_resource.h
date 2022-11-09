#pragma once 

#include <cmrc/cmrc.hpp>
#include <filesystem>

namespace eng {
	class IResource {
	public:
		virtual auto getFile(std::string path)->cmrc::file = 0;

		/**
		 * \brief A good choice will be to use it for directories iteration.
		 */
		virtual auto getFileSystem()->cmrc::embedded_filesystem = 0;

		virtual auto getFileResource(std::string path)->std::vector<unsigned char> = 0;
	};
}
