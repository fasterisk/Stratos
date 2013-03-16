#include "RTRS_BlendingShader.h"

RTRS::BlendingShader* RTRS::BlendingShader::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::BlendingShader*	RTRS::BlendingShader::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::BlendingShader();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::BlendingShader::BlendingShader()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::BlendingShader::~BlendingShader()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::BlendingShader::ItlInitialize()
{
	bool bOk = ItlLoadShaders("shader/Blending.vert", "shader/Blending.frag");
	assert(bOk == true);

	m_glntColorTexture1Loc		= glGetUniformLocation(m_glnShaderProgram, "tColorTexture1");
	m_glntColorTexture2Loc		= glGetUniformLocation(m_glnShaderProgram, "tColorTexture2");
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::BlendingShader::Render(RTRS::TexturedModel* pTexturedModel)
{
	assert(pTexturedModel != NULL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	glUseProgram(m_glnShaderProgram);

	for(unsigned int n = 0; n < pTexturedModel->GetNumMeshes(); n++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pTexturedModel->GetTextureID(n, TextureManager::TEXTURETYPE::COLOR));
		glUniform1i(m_glntColorTexture1Loc, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, pTexturedModel->GetTextureID(n, TextureManager::TEXTURETYPE::NORMAL));
		glUniform1i(m_glntColorTexture2Loc, 1);
		pTexturedModel->Render(n);
	}

	glUseProgram(0);
}