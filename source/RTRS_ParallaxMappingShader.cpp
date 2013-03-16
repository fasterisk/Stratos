#include "RTRS_ParallaxMappingShader.h"
#include "RTRS_TexturedModel.h"

RTRS::ParallaxMappingShader* RTRS::ParallaxMappingShader::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::ParallaxMappingShader*	RTRS::ParallaxMappingShader::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::ParallaxMappingShader();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::ParallaxMappingShader::ParallaxMappingShader()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::ParallaxMappingShader::~ParallaxMappingShader()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ParallaxMappingShader::ItlInitialize()
{
	bool bOk = ItlLoadShaders("shader/Parallax.vert", "shader/Parallax.frag");
	assert(bOk == true);

	m_glnm4MVPLoc				= glGetUniformLocation(m_glnShaderProgram, "m4ModelViewProjectionMatrix");
	m_glnm4MVLoc				= glGetUniformLocation(m_glnShaderProgram, "m4ModelViewMatrix");
	m_glnm4ShadowMatrixLoc		= glGetUniformLocation(m_glnShaderProgram, "m4ShadowMatrix");
	m_glnm4VLoc					= glGetUniformLocation(m_glnShaderProgram, "m4ViewMatrix");
	
	m_glnm3NormalMatrixLoc		= glGetUniformLocation(m_glnShaderProgram, "m3NormalMatrix");

	m_glnv3LightPositionLoc		= glGetUniformLocation(m_glnShaderProgram, "v3LightPosition");
	m_glnv3CameraPositionLoc	= glGetUniformLocation(m_glnShaderProgram, "v3CameraPosition");
	
	m_glntColorTextureLoc		= glGetUniformLocation(m_glnShaderProgram, "tColorTexture");
	m_glntSpecularTextureLoc	= glGetUniformLocation(m_glnShaderProgram, "tSpecularTexture");
	m_glntShadowMapLoc			= glGetUniformLocation(m_glnShaderProgram, "tShadowMap");
	m_glntNormalMapLoc			= glGetUniformLocation(m_glnShaderProgram, "tNormalMap");
	m_glntBumpMapLoc			= glGetUniformLocation(m_glnShaderProgram, "tBumpMap");
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ParallaxMappingShader::Render(RTRS::TexturedModel* pTexturedModel, GLuint glnShadowMap, glm::mat4 m4Shadow, glm::mat4 m4ViewProjection, glm::mat4 m4View, glm::vec3 v3LightPosition, glm::vec3 v3CameraPosition)
{
	assert(pTexturedModel != NULL);

	glUseProgram(m_glnShaderProgram);

	glm::mat4	m4Model = pTexturedModel->GetModelMatrix();
	glm::mat4	m4MVPMatrix = m4ViewProjection * m4Model;
	glm::mat4	m4MVMatrix	= m4View * m4Model;

	glm::mat3	m3NormalMatrix = glm::transpose(glm::inverse(glm::mat3(m4MVMatrix)));

	glm::mat4	m4ShadowMatrix = m4Shadow * m4Model;

	glUniformMatrix4fv(m_glnm4MVPLoc, 1, GL_FALSE, (GLfloat*)&m4MVPMatrix);
	glUniformMatrix4fv(m_glnm4MVLoc, 1, GL_FALSE, (GLfloat*)&m4MVMatrix);
	glUniformMatrix4fv(m_glnm4ShadowMatrixLoc, 1, GL_FALSE, (GLfloat*)&m4ShadowMatrix);
	glUniformMatrix4fv(m_glnm4VLoc, 1, GL_FALSE, (GLfloat*)&m4View);
	
	glUniformMatrix3fv(m_glnm3NormalMatrixLoc, 1, GL_FALSE, (GLfloat*)&m3NormalMatrix);
	
	glUniform3fv(m_glnv3LightPositionLoc, 1, (GLfloat*)&v3LightPosition);
	glUniform3fv(m_glnv3CameraPositionLoc, 1, (GLfloat*)&v3CameraPosition);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, glnShadowMap);
	glUniform1i(m_glntShadowMapLoc, 0);

	for(unsigned int n = 0; n < pTexturedModel->GetNumMeshes(); n++)
	{
		if(!pTexturedModel->IsEnvironmentMapped(n))
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, pTexturedModel->GetTextureID(n, TextureManager::TEXTURETYPE::COLOR));
			glUniform1i(m_glntColorTextureLoc, 1);

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, pTexturedModel->GetTextureID(n, TextureManager::TEXTURETYPE::SPECULAR));
			glUniform1i(m_glntSpecularTextureLoc, 2);

			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, pTexturedModel->GetTextureID(n, TextureManager::TEXTURETYPE::NORMAL));
			glUniform1i(m_glntNormalMapLoc, 3);

			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, pTexturedModel->GetTextureID(n, TextureManager::TEXTURETYPE::BUMP));
			glUniform1i(m_glntBumpMapLoc, 4);
	
			pTexturedModel->Render(n);
		}
	}

	glUseProgram(0);
}