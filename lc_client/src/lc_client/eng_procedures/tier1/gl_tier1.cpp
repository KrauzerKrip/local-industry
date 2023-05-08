#include "lc_client/eng_procedures/tier1/gl_tier1.h"

#include "lc_client/eng_procedures/openGL/gl_shaders.h"
#include "lc_client/eng_procedures/openGL/gl_texture_manager.h"


Tier1Gl::Tier1Gl(eng::IResource* pResource) : Tier1(pResource) { 
	m_pResource = pResource; 
	
	m_pTextureManager = new TextureManagerGl(pResource);
	m_pShaderManager = new ShaderManagerGl(pResource);

}

