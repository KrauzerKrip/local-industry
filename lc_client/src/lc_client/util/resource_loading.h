#pragma once

#include <cmrc/cmrc.hpp>
#include <filesystem>

CMRC_DECLARE(eng_resources);

namespace eng {

	auto getFile(std::string path) -> cmrc::file;

	/**
	 * \brief A good choice will be to use it for directories iteration.
	 */
	auto getFileSystem() -> cmrc::embedded_filesystem;

	auto getFileResource(std::string path) -> std::vector<unsigned char>;
}
