#pragma once 

#include <vector>
#include <string>
//#include <cmrc/cmrc.hpp>
#include "../../../../out/build/x64-debug/_cmrc/include/cmrc/cmrc.hpp"


namespace eng {
	class IResource {
	public:
		virtual auto getFile(std::string path) const -> cmrc::file = 0;

		/**
		 * \brief A good choice will be to use it for directories iteration.
		 */
		virtual auto getFileSystem() const -> cmrc::embedded_filesystem = 0;

		virtual auto getFileResource(std::string path) const ->std::vector<unsigned char> = 0;
		virtual auto getFileResources(std::vector<std::string>& paths) const -> std::vector<std::vector<unsigned char>> = 0;
	};
}
