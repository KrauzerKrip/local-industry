#pragma once

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(eng_resources);

namespace eng {

	auto getResource(std::string path) -> cmrc::file;

	/**
	 * \brief A good choice will be to use it for directories iteration.
	 */
	auto getFileSystem() -> cmrc::embedded_filesystem;
}
