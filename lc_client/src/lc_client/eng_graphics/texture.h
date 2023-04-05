#pragma once

#include <string>
#include <memory>

#include "lc_client/util/image.h"


enum TextureType {
	NONE = -1,
	COLOR = 0,
	NORMAL = 1,
	AO = 2,
	METALLIC = 3,
	DIFFUSE = 4,
	GLOSSINESS = 5,
	SPECULAR = 6,
};

class Texture {
public:
	/**
	 * \brief Load into video memory.
	 */
	virtual void load() = 0;

	/**
	* \brief Unload from video memory.
	*/
	virtual void unload() = 0;

	/**
	* \brief Bind texture to use it.
	*/
	virtual void bind() = 0;

	/**
	* \brief Bind texture to use it.
	*/
	virtual void setTextureType(TextureType textureType) = 0;

protected:
	std::string m_name;
	std::shared_ptr<eng::Image> m_image;
	TextureType m_textureType = TextureType::NONE;
};
