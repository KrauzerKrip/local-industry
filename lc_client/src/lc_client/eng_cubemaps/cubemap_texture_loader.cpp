#include "cubemap_texture_loader.h"

#include <iostream>
#include <thread>
#include <future>
#include <chrono>


CubemapTextureLoader::CubemapTextureLoader(std::string path, eng::IResource* pResource) {
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

	std::future<eng::Image> futureRight = std::async([bufferRight]() -> eng::Image { return eng::Image(bufferRight); });
	std::future<eng::Image> futureLeft = std::async([bufferLeft]() -> eng::Image { return eng::Image(bufferLeft); });
	std::future<eng::Image> futureTop = std::async([bufferTop]() -> eng::Image { return eng::Image(bufferTop); });
	std::future<eng::Image> futureBottom = std::async([bufferBottom]() -> eng::Image { return eng::Image(bufferBottom); });
	std::future<eng::Image> futureBack = std::async([bufferBack]() -> eng::Image { return eng::Image(bufferBack); });
	std::future<eng::Image> futureFront = std::async([bufferFront]() -> eng::Image { return eng::Image(bufferFront); });

	eng::Image right = futureRight.get(); 
	eng::Image left = futureLeft.get();	
	eng::Image top = futureTop.get();	 
	eng::Image bottom = futureBottom.get(); 
	eng::Image back = futureBack.get();	  
	eng::Image front = futureFront.get();	 

	m_pMaterial = new CubemapMaterial{
		std::move(right), std::move(left), std::move(top), std::move(bottom), std::move(back), std::move(front)};

}

std::unique_ptr<CubemapMaterial> CubemapTextureLoader::getMaterial() {
	return std::unique_ptr<CubemapMaterial>(m_pMaterial);
}

void CubemapTextureLoader::testLoadImages(eng::IResource* pResource, std::string path) {
	const std::vector<unsigned char>& bufferRight_ = pResource->getFileResource(path + "right" + FILE_FORMAT);
	const std::vector<unsigned char>& bufferLeft_ = pResource->getFileResource(path + "left" + FILE_FORMAT);
	const std::vector<unsigned char>& bufferTop_ = pResource->getFileResource(path + "top" + FILE_FORMAT);
	const std::vector<unsigned char>& bufferBottom_ = pResource->getFileResource(path + "bottom" + FILE_FORMAT);
	const std::vector<unsigned char>& bufferBack_ = pResource->getFileResource(path + "back" + FILE_FORMAT);
	const std::vector<unsigned char>& bufferFront_ = pResource->getFileResource(path + "front" + FILE_FORMAT);
}

const std::string CubemapTextureLoader::FILE_FORMAT = ".png";
