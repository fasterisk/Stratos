#include "RTRS_SimpleTextureShader.h"

RTRS::SimpleTextureShader* RTRS::SimpleTextureShader::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::SimpleTextureShader*	RTRS::SimpleTextureShader::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::SimpleTextureShader();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::SimpleTextureShader::SimpleTextureShader()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::SimpleTextureShader::~SimpleTextureShader()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::SimpleTextureShader::ItlInitialize()
{
	bool bOk = ItlLoadShaders("shader/SimpleTexturing.vert", "shader/SimpleTexturing.frag");
	assert(bOk == true);

	m_glnm4MVPLoc				= glGetUniformLocation(m_glnShaderProgram, "m4ModelViewProjectionMatrix");
	m_glntColorTextureLoc		= glGetUniformLocation(m_glnShaderProgram, "tColorTexture");
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::SimpleTextureShader::Render(RTRS::TexturedModel* pTexturedModel, glm::mat4 m4ViewProjection)
{
	assert(pTexturedModel != NULL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	glUseProgram(m_glnShaderProgram);

	glm::mat4	m4Model = pTexturedModel->GetModelMatrix();
	glm::mat4	m4MVPMatrix = m4ViewProjection * m4Model;

	glUniformMatrix4fv(m_glnm4MVPLoc, 1, GL_FALSE, (GLfloat*)&m4MVPMatrix);

	for(unsigned int n = 0; n < pTexturedModel->GetNumMeshes(); n++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pTexturedModel->GetTextureID(n, TextureManager::TEXTURETYPE::COLOR));
		glUniform1i(m_glntColorTextureLoc, 0);
		pTexturedModel->Render(n);
	}

	glUseProgram(0);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::SimpleTextureShader::Render(RTRS::Skybox* pSkybox, glm::mat4 m4ViewProjection)
{
	assert(pSkybox != NULL);

	glUseProgram(m_glnShaderProgram);

	glm::mat4	m4Model = pSkybox->GetModelMatrix();
	glm::mat4	m4MVPMatrix = m4ViewProjection * m4Model;

	glUniformMatrix4fv(m_glnm4MVPLoc, 1, GL_FALSE, (GLfloat*)&m4MVPMatrix);

	assert(pSkybox->GetNumMeshes() == 6);

	glActiveTexture(GL_TEXTURE0);
	
	glBindTexture(GL_TEXTURE_2D, pSkybox->GetTextureID(Skybox::TextureIndex::FRONT));
	glUniform1i(m_glntColorTextureLoc, 0);
	pSkybox->Render(Skybox::TextureIndex::FRONT);

	glBindTexture(GL_TEXTURE_2D, pSkybox->GetTextureID(Skybox::TextureIndex::BACK));
	glUniform1i(m_glntColorTextureLoc, 0);
	pSkybox->Render(Skybox::TextureIndex::BACK);

	glBindTexture(GL_TEXTURE_2D, pSkybox->GetTextureID(Skybox::TextureIndex::LEFT));
	glUniform1i(m_glntColorTextureLoc, 0);
	pSkybox->Render(Skybox::TextureIndex::LEFT);

	glBindTexture(GL_TEXTURE_2D, pSkybox->GetTextureID(Skybox::TextureIndex::RIGHT));
	glUniform1i(m_glntColorTextureLoc, 0);
	pSkybox->Render(Skybox::TextureIndex::RIGHT);

	glBindTexture(GL_TEXTURE_2D, pSkybox->GetTextureID(Skybox::TextureIndex::TOP));
	glUniform1i(m_glntColorTextureLoc, 0);
	pSkybox->Render(Skybox::TextureIndex::TOP);

	glBindTexture(GL_TEXTURE_2D, pSkybox->GetTextureID(Skybox::TextureIndex::BOTTOM));
	glUniform1i(m_glntColorTextureLoc, 0);
	pSkybox->Render(Skybox::TextureIndex::BOTTOM);
	
	glUseProgram(0);

	glClear(GL_DEPTH_BUFFER_BIT);
}