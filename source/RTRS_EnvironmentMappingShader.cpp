#include "RTRS_EnvironmentMappingShader.h"
#include "RTRS_TexturedModel.h"

RTRS::EnvironmentMappingShader* RTRS::EnvironmentMappingShader::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::EnvironmentMappingShader*	RTRS::EnvironmentMappingShader::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::EnvironmentMappingShader();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::EnvironmentMappingShader::EnvironmentMappingShader()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::EnvironmentMappingShader::~EnvironmentMappingShader()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::EnvironmentMappingShader::ItlInitialize()
{
	bool bOk = ItlLoadShaders("shader/EnvironmentMapping.vert", "shader/EnvironmentMapping.frag");
	assert(bOk == true);

	m_glnm4MVPLoc					= glGetUniformLocation(m_glnShaderProgram, "m4ModelViewProjectionMatrix");
	m_glnm4MVLoc					= glGetUniformLocation(m_glnShaderProgram, "m4ModelViewMatrix");
	m_glnm4MLoc						= glGetUniformLocation(m_glnShaderProgram, "m4ModelMatrix");
	m_glnm3NormalMatrixLoc			= glGetUniformLocation(m_glnShaderProgram, "m3NormalMatrix");
	m_glnv3LightPosLoc				= glGetUniformLocation(m_glnShaderProgram, "v3LightPosition");
	m_glnv3TransformedLightPosLoc	= glGetUniformLocation(m_glnShaderProgram, "v3TransformedLightPosition");
	m_glnv3CameraPosLoc				= glGetUniformLocation(m_glnShaderProgram, "v3CameraPosition");
	m_glnv3TransformedCameraPosLoc	= glGetUniformLocation(m_glnShaderProgram, "v3TransformedCameraPosition");
	m_glntCubeMapTextureLoc			= glGetUniformLocation(m_glnShaderProgram, "tCubeMap");
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::EnvironmentMappingShader::Render(RTRS::IModel* pModel, GLuint glnCubeMapTexture, glm::mat4 m4ViewProjection, glm::mat4 m4View, glm::vec3 v3LightPosition, glm::vec3 v3CameraPosition)
{
	assert(pModel != NULL);

	glUseProgram(m_glnShaderProgram);

	glm::mat4	m4Model = pModel->GetModelMatrix();
	glm::mat4	m4MVPMatrix = m4ViewProjection * m4Model;
	glm::mat4	m4MVMatrix	= m4View * m4Model;
	glm::mat3	m3NormalMatrix = glm::transpose(glm::inverse(glm::mat3(m4Model)));

	glUniformMatrix4fv(m_glnm4MVPLoc, 1, GL_FALSE, (GLfloat*)&m4MVPMatrix);
	glUniformMatrix4fv(m_glnm4MVLoc, 1, GL_FALSE, (GLfloat*)&m4MVMatrix);
	glUniformMatrix4fv(m_glnm4MLoc, 1, GL_FALSE, (GLfloat*)&m4Model);
	glUniformMatrix3fv(m_glnm3NormalMatrixLoc, 1, GL_FALSE, (GLfloat*)&m3NormalMatrix);
	glUniform3fv(m_glnv3LightPosLoc, 1, (GLfloat*)&v3LightPosition);
	glUniform3fv(m_glnv3TransformedLightPosLoc, 1, (GLfloat*)&glm::vec3(m4View * glm::vec4(v3LightPosition, 1.0f)));
	glUniform3fv(m_glnv3CameraPosLoc, 1, (GLfloat*)&v3CameraPosition);
	glUniform3fv(m_glnv3TransformedCameraPosLoc, 1, (GLfloat*)&glm::vec3(m4View * glm::vec4(v3CameraPosition, 1.0f)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, glnCubeMapTexture);
	glUniform1i(m_glntCubeMapTextureLoc, 0);

	for(unsigned int n = 0; n < pModel->GetNumMeshes(); n++)
	{
		if(pModel->IsEnvironmentMapped(n))
		{
			pModel->Render(n);
		}
	}

	glUseProgram(0);
}