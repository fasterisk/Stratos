#include "RTRS_TextureShader.h"
#include "RTRS_TexturedModel.h"

RTRS::TextureShader* RTRS::TextureShader::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::TextureShader*	RTRS::TextureShader::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::TextureShader();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::TextureShader::TextureShader()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::TextureShader::~TextureShader()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::TextureShader::ItlInitialize()
{
	bool bOk = ItlLoadShaders("shader/PhongTexturing.vert", "shader/PhongTexturing.frag");
	assert(bOk == true);

	m_glnm4MVPLoc				= glGetUniformLocation(m_glnShaderProgram, "m4ModelViewProjectionMatrix");
	m_glnm4MVLoc				= glGetUniformLocation(m_glnShaderProgram, "m4ModelViewMatrix");
	m_glnm4ShadowMatrixLoc		= glGetUniformLocation(m_glnShaderProgram, "m4ShadowMatrix");
	m_glnm3NormalMatrixLoc		= glGetUniformLocation(m_glnShaderProgram, "m3NormalMatrix");
	m_glnv3LightPositionLoc		= glGetUniformLocation(m_glnShaderProgram, "v3LightPosition");
	m_glnv3CameraPositionLoc	= glGetUniformLocation(m_glnShaderProgram, "v3CameraPosition");
	m_glntColorTextureLoc		= glGetUniformLocation(m_glnShaderProgram, "tColorTexture");
	m_glntSpecularTextureLoc	= glGetUniformLocation(m_glnShaderProgram, "tSpecularTexture");
	m_glntShadowMapLoc			= glGetUniformLocation(m_glnShaderProgram, "tShadowMap");
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::TextureShader::Render(RTRS::TexturedModel* pTexturedModel, GLuint glnShadowMap, glm::mat4 m4Shadow, glm::mat4 m4ViewProjection, glm::mat4 m4View, glm::vec3 v3LightPosition, glm::vec3 v3CameraPosition)
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
	glUniformMatrix3fv(m_glnm3NormalMatrixLoc, 1, GL_FALSE, (GLfloat*)&m3NormalMatrix);
	glUniform3fv(m_glnv3LightPositionLoc, 1, (GLfloat*)&glm::vec3(m4View * glm::vec4(v3LightPosition, 1.0f)));
	glUniform3fv(m_glnv3CameraPositionLoc, 1, (GLfloat*)&glm::vec3(m4View * glm::vec4(v3CameraPosition, 1.0f)));

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, glnShadowMap);
	glUniform1i(m_glntShadowMapLoc, 3);

	for(unsigned int n = 0; n < pTexturedModel->GetNumMeshes(); n++)
	{
		if(!pTexturedModel->IsEnvironmentMapped(n))
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, pTexturedModel->GetTextureID(n, TextureManager::TEXTURETYPE::COLOR));
			glUniform1i(m_glntColorTextureLoc, 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, pTexturedModel->GetTextureID(n, TextureManager::TEXTURETYPE::SPECULAR));
			glUniform1i(m_glntSpecularTextureLoc, 1);
	
			pTexturedModel->Render(n);
		}
	}

	glUseProgram(0);
}