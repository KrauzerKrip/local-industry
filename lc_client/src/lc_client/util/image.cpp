#include "image.h"

#include <lc_client/util/resource_loading.h>

namespace eng{
	Image::Image(std::string path) {
		std::vector<unsigned char> buffer = eng::getFileResource(path);
		loadData(buffer);
	}

	Image::Image(std::vector<unsigned char>& buffer) {
		loadData(buffer);
	}

	std::vector<unsigned char>& Image::getData() {
		return m_data;
	}

	void Image::loadData(std::vector<unsigned char>& buffer) {
		
	}
}
