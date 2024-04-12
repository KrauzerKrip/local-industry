#include "gl_loader_fabric.h"


LoaderFabricGl::LoaderFabricGl(eng::IResource* pResource, IConsole* pConsole) {
	m_pMeshLoader = new MeshLoaderGl();
	m_pShaderLoader = new ShaderLoaderGl(pConsole);
	m_pCubemapLoader = new CubemapLoaderGl(pResource);
}

MeshLoader* LoaderFabricGl::getMeshLoader() { return m_pMeshLoader; }

ShaderLoader* LoaderFabricGl::getShaderLoader() { return m_pShaderLoader; }

CubemapLoader* LoaderFabricGl::getCubemapLoader() { return m_pCubemapLoader; }

MeshLoaderGl* LoaderFabricGl::getMeshLoaderGl() { return m_pMeshLoader; }

ShaderLoaderGl* LoaderFabricGl::getShaderLoaderGl() { return m_pShaderLoader; }

CubemapLoaderGl* LoaderFabricGl::getCubemapLoaderGl() { return m_pCubemapLoader; }
