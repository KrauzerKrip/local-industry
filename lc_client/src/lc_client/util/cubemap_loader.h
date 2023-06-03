#pragma once

#include <string>
#include <memory>

#include "image.h"
#include "eng_resource.h"


struct CubemapMaterial {
	eng::Image right;
	eng::Image left;
	eng::Image top;
	eng::Image bottom;
	eng::Image back;
	eng::Image front;
	
	CubemapMaterial(eng::Image right, eng::Image left, eng::Image top, eng::Image bottom, eng::Image back, eng::Image front) 
		: right(right),
		  left(left),
		  top(top),
		  bottom(bottom),
		  back(back),
		  front(front) {}

	CubemapMaterial(CubemapMaterial&& material) noexcept
		: right(std::move(material.right)),
		  left(std::move(material.left)),
		  top(std::move(material.top)),
		  bottom(std::move(material.bottom)),
		  back(std::move(material.back)),
		  front(std::move(material.front)) {}
};

class CubemapLoader {
public:
	CubemapLoader(std::string path, eng::IResource* pResource);

	std::unique_ptr<CubemapMaterial> getMaterial();

private:
	CubemapMaterial* m_pMaterial;

	const static std::string FILE_FORMAT;
};
