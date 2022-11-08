#pragma once

#include <vector>

namespace eng {
	class Image {
	public:
		Image(std::string path);
		Image(std::vector<unsigned char>& buffer);
		
		std::vector<unsigned char>& getData();
		
	private:
		void loadData(std::vector<unsigned char>& buffer);

		std::vector<unsigned char> m_data;
	}
}
