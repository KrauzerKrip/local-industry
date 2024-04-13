#pragma once

#include <vector>
#include <string>

namespace eng {
	class Image {
	public:
		/*Image(std::string path);*/
		Image(const std::vector<unsigned char>& buffer);
		~Image();
		Image(const Image& image);
		Image(Image&& image) noexcept;


		const unsigned char* getData() const;
		int getWidth();
		int getHeight();
		int getChannelsNumber();

	private:
		void loadData(const std::vector<unsigned char>& buffer);

		std::vector<unsigned char> m_data;
		int m_width, m_height, m_nrChannels;
	};
}
