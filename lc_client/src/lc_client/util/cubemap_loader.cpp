#include "cubemap_loader.h"

#include <iostream>


CubemapLoader::CubemapLoader(std::string path, eng::IResource* pResource) {

	
	std::vector<std::string> paths{path + "right" + FILE_FORMAT, path + "left" + FILE_FORMAT,
		path + "top" + FILE_FORMAT, path + "bottom" + FILE_FORMAT, path + "back" + FILE_FORMAT,
		path + "front" + FILE_FORMAT};

	std::vector<std::vector<unsigned char>> buffers = pResource->getFileResources(paths);

	const std::vector<unsigned char>& bufferRight = buffers.at(0);
	const std::vector<unsigned char>& bufferLeft = buffers.at(1);
	const std::vector<unsigned char>& bufferTop = buffers.at(2);
	const std::vector<unsigned char>& bufferBottom = buffers.at(3);
	const std::vector<unsigned char>& bufferBack = buffers.at(4);
	const std::vector<unsigned char>& bufferFront = buffers.at(5);

	eng::Image right = eng::Image(bufferRight);
	eng::Image left = eng::Image(bufferLeft);
	eng::Image top = eng::Image(bufferTop);
	eng::Image bottom = eng::Image(bufferBottom);
	eng::Image back = eng::Image(bufferBack);
	eng::Image front = eng::Image(bufferFront);

	m_pMaterial = new CubemapMaterial{
		std::move(right), std::move(left), std::move(top), std::move(bottom), std::move(back), std::move(front)};

}

std::unique_ptr<CubemapMaterial> CubemapLoader::getMaterial() { return std::unique_ptr<CubemapMaterial>(m_pMaterial); }

void CubemapLoader::testLoadImages(eng::IResource* pResource, std::string path) {
	const std::vector<unsigned char>& bufferRight_ = pResource->getFileResource(path + "right" + FILE_FORMAT);
	const std::vector<unsigned char>& bufferLeft_ = pResource->getFileResource(path + "left" + FILE_FORMAT);
	const std::vector<unsigned char>& bufferTop_ = pResource->getFileResource(path + "top" + FILE_FORMAT);
	const std::vector<unsigned char>& bufferBottom_ = pResource->getFileResource(path + "bottom" + FILE_FORMAT);
	const std::vector<unsigned char>& bufferBack_ = pResource->getFileResource(path + "back" + FILE_FORMAT);
	const std::vector<unsigned char>& bufferFront_ = pResource->getFileResource(path + "front" + FILE_FORMAT);
}

const std::string CubemapLoader::FILE_FORMAT = ".png";
