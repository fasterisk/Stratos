#include "RTRS_GaussShader1.h"

RTRS::GaussShader1* RTRS::GaussShader1::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::GaussShader1*	RTRS::GaussShader1::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::GaussShader1();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::GaussShader1::GaussShader1()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::GaussShader1::~GaussShader1()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::GaussShader1::ItlInitialize()
{
	bool bOk = ItlLoadShaders("shader/GaussPass.vert", "shader/GaussPass1.frag");
	assert(bOk == true);

	m_glntColorTextureLoc	= glGetUniformLocation(m_glnShaderProgram, "tColorTexture");
	m_glnfPixelOffsetLoc	= glGetUniformLocation(m_glnShaderProgram, "fPixelOffset");
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::GaussShader1::Render(RTRS::TexturedModel* pTexturedModel)
{
	assert(pTexturedModel != NULL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	glUseProgram(m_glnShaderProgram);

	glUniform1f(m_glnfPixelOffsetLoc, 1.0f / (SCREEN_WIDTH / 4.0f));

	for(unsigned int n = 0; n < pTexturedModel->GetNumMeshes(); n++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pTexturedModel->GetTextureID(n, TextureManager::TEXTURETYPE::COLOR));
		glUniform1i(m_glntColorTextureLoc, 0);
		pTexturedModel->Render(n);
	}

	glUseProgram(0);
}