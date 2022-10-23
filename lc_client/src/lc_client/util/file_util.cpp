#include "file_util.h"

namespace eng {
	
	std::string getFileNameWithoutExtension(std::string fileName)
	{
		size_t lastIndex = fileName.find_last_of(".");
		if (lastIndex == std::string::npos) {
			return fileName;
		}

		return fileName.substr(0, lastIndex);
	}
}


