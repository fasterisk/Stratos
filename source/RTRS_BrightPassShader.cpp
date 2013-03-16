#include "RTRS_BrightPassShader.h"

RTRS::BrightPassShader* RTRS::BrightPassShader::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::BrightPassShader*	RTRS::BrightPassShader::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::BrightPassShader();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::BrightPassShader::BrightPassShader()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::BrightPassShader::~BrightPassShader()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::BrightPassShader::ItlInitialize()
{
	bool bOk = ItlLoadShaders("shader/BrightPass.vert", "shader/BrightPass.frag");
	assert(bOk == true);

	m_glntColorTextureLoc		= glGetUniformLocation(m_glnShaderProgram, "tColorTexture");
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::BrightPassShader::Render(RTRS::TexturedModel* pTexturedModel)
{
	assert(pTexturedModel != NULL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	glUseProgram(m_glnShaderProgram);

	for(unsigned int n = 0; n < pTexturedModel->GetNumMeshes(); n++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pTexturedModel->GetTextureID(n, TextureManager::TEXTURETYPE::COLOR));
		glUniform1i(m_glntColorTextureLoc, 0);
		pTexturedModel->Render(n);
	}

	glUseProgram(0);
}