#pragma once

#include <vector>
#include <string>

namespace eng {
	class Image {
	public:
		/*Image(std::string path);*/
		Image(std::vector<unsigned char>& buffer);
		~Image();

		unsigned char* getData();
		int getWidth();
		int getHeight();

	private:
		void loadData(std::vector<unsigned char>& buffer);

		unsigned char* m_data;
		/*std::vector<unsigned char> m_data;*/
		int m_width, m_height, m_nrChannels;
	};
}
