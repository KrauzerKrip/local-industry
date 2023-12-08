#include "gl_cubemap_loader.h"

#include <glad/glad.h>

#include "lc_client/eng_cubemaps/entt/components.h"


void CubemapLoaderGl::loadCubemap(entt::registry* pRegistry, entt::entity entity, std::string path) {
	CubemapTextureLoader cubemapLoader(path, m_pResource);
	std::unique_ptr<CubemapMaterial> material = cubemapLoader.getMaterial();

	unsigned int texture = getTexture(std::move(material));

	pRegistry->emplace_or_replace<CubemapGl>(entity, texture);
}

unsigned int CubemapLoaderGl::getTexture(std::unique_ptr<CubemapMaterial> material) { 
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	CubemapMaterial* pMat = material.get();

	int imageFormat;

	if (pMat->right.getChannelsNumber() > 3 || pMat->left.getChannelsNumber() > 3 ||
		pMat->top.getChannelsNumber() > 3 || pMat->bottom.getChannelsNumber() > 3 ||
		pMat->back.getChannelsNumber() > 3 || pMat->front.getChannelsNumber() > 3) {
		imageFormat = GL_RGBA;
		// throw TextureLoadException("There are more than 3 color channels. For a skybox texture the appropriate format
		// is RGB.");
	}
	else {
		imageFormat = GL_RGB;
	}

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, imageFormat, pMat->right.getWidth(), pMat->right.getHeight(), 0,
		imageFormat, GL_UNSIGNED_BYTE, pMat->right.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, imageFormat, pMat->left.getWidth(), pMat->left.getHeight(), 0,
		imageFormat, GL_UNSIGNED_BYTE, pMat->left.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, imageFormat, pMat->top.getWidth(), pMat->top.getHeight(), 0,
		imageFormat, GL_UNSIGNED_BYTE, pMat->top.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, imageFormat, pMat->bottom.getWidth(), pMat->bottom.getHeight(), 0,
		imageFormat, GL_UNSIGNED_BYTE, pMat->bottom.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, imageFormat, pMat->back.getWidth(), pMat->back.getHeight(), 0,
		imageFormat, GL_UNSIGNED_BYTE, pMat->back.getData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, imageFormat, pMat->front.getWidth(), pMat->front.getHeight(), 0,
		imageFormat, GL_UNSIGNED_BYTE, pMat->front.getData());

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return texture;
}
