#include "image.h"
#include "image.h"
#include "image.h"
#include "image.h"
#include "image.h"

#include <limits>

#include "lc_client/exceptions/io_exceptions.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


namespace eng{

	Image::Image(std::vector<unsigned char>& buffer) {
		loadData(buffer);
	}

	Image::~Image() {}

	Image::Image(const Image& image) { 
		m_data = std::vector<unsigned char>(image.m_data);
		m_width = image.m_width;
		m_height = image.m_height;
		m_nrChannels = image.m_nrChannels;
	}

	Image::Image(Image&& image) noexcept {
		m_data = std::move(image.m_data);
		m_width = image.m_width;
		m_height = image.m_height;
		m_nrChannels = image.m_nrChannels;
	};

	const unsigned char* Image::getData() const { 
		return m_data.data(); }

	std::vector<unsigned char>& Image::getDataVector() { return m_data;}

	void Image::loadData(std::vector<unsigned char>& buffer) {

		if (buffer.size() > std::numeric_limits<int>::max()) {
			throw FileTooLargeException("Image buffer is too large for stb_image! It`s size shouldn`t be larger than max value of int type.");
		}

		int size = static_cast<int>(buffer.size());

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load_from_memory(buffer.data(), size, &m_width, &m_height, &m_nrChannels, 0);

		if (data == NULL) {
			throw ImageLoadFailureException(stbi_failure_reason());
		}

		unsigned long long imageDataSize = m_width * m_height * m_nrChannels * sizeof(unsigned char);

		m_data = std::vector<unsigned char>(size);
		m_data.assign(data, data + imageDataSize);
		/*m_data.assign(data, data + sizeof(data));*/
		/*delete[] data;*/
	}

	int Image::getWidth() {
		return m_width;
	}

	int Image::getHeight() {
		return m_height; }
	int eng::Image::getChannelsNumber() { return m_nrChannels; }
}
