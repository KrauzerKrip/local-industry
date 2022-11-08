#pragma once

#include <cmrc/cmrc.hpp>
#include <filesystem>
#include <string>

#include "i_resource_loading.h"


CMRC_DECLARE(eng_resources);

namespace eng {

	class ResourceLoading {
	public:
		ResourceLoading(std::string resourceRootPath);

		auto getFile(std::string path)->cmrc::file;

		/**
		 * \brief A good choice will be to use it for directories iteration.
		 */
		auto getFileSystem()->cmrc::embedded_filesystem;

		auto getFileResource(std::string path)->std::vector<unsigned char>;

	private:
		std::string m_resourceRootPath;
	};
}
