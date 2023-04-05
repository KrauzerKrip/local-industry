#pragma once

#include <string>

namespace eng {

	std::string getFileNameWithoutExtension(std::string& fileName);
	std::string getFileExtension(std::string& fileName);

}