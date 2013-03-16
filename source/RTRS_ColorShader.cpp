#include "RTRS_ColorShader.h"
#include "RTRS_IModel.h"

RTRS::ColorShader* RTRS::ColorShader::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::ColorShader*	RTRS::ColorShader::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::ColorShader();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::ColorShader::ColorShader()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::ColorShader::~ColorShader()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ColorShader::ItlInitialize()
{
	bool bOk = ItlLoadShaders("shader/SimpleColoring.vert", "shader/SimpleColoring.frag");
	assert(bOk == true);

	m_glnm4MVPLoc	= glGetUniformLocation(m_glnShaderProgram, "m4ModelViewProjectionMatrix");
	m_glnv3ColorLoc	= glGetUniformLocation(m_glnShaderProgram, "v3Color");
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ColorShader::Render(RTRS::IModel* pModel, glm::mat4 m4ViewProjection)
{
	assert(pModel != NULL);
	
	glUseProgram(m_glnShaderProgram);

	glm::mat4	m4MVPMatrix = m4ViewProjection * pModel->GetModelMatrix();

	glUniformMatrix4fv(m_glnm4MVPLoc, 1, GL_FALSE, (GLfloat*)&m4MVPMatrix);
	glUniform3fv(m_glnv3ColorLoc, 1, (GLfloat*)&pModel->GetColor());
	
	pModel->Render();

	glUseProgram(0);
}