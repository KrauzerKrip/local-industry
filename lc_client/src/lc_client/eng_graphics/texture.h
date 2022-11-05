#pragma once

#include <string>

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

protected:
	std::string m_name;
	unsigned char* image;

private:
};
