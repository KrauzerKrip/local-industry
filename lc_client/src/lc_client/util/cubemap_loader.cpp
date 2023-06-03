#include "cubemap_loader.h"

CubemapLoader::CubemapLoader(std::string path, eng::IResource* pResource) {
	std::vector<unsigned char> bufferRight = pResource->getFileResource(path + "right" + FILE_FORMAT);
	eng::Image right = eng::Image(bufferRight);
	std::vector<unsigned char> bufferLeft = pResource->getFileResource(path + "left" + FILE_FORMAT);
	eng::Image left = eng::Image(bufferLeft);
	std::vector<unsigned char> bufferTop = pResource->getFileResource(path + "top" + FILE_FORMAT);
	eng::Image top = eng::Image(bufferTop);
	std::vector<unsigned char> bufferBottom = pResource->getFileResource(path + "bottom" + FILE_FORMAT);
	eng::Image bottom = eng::Image(bufferBottom);
	std::vector<unsigned char> bufferBack = pResource->getFileResource(path + "back" + FILE_FORMAT);
	eng::Image back = eng::Image(bufferBack);
	std::vector<unsigned char> bufferFront = pResource->getFileResource(path + "front" + FILE_FORMAT);
	eng::Image front = eng::Image(bufferFront);

	m_pMaterial = new CubemapMaterial{
		std::move(right), std::move(left), std::move(top), std::move(bottom), std::move(back), std::move(front)};
}

std::unique_ptr<CubemapMaterial> CubemapLoader::getMaterial() { return std::unique_ptr<CubemapMaterial>(m_pMaterial); }

const std::string CubemapLoader::FILE_FORMAT = ".png";
