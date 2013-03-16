#include "RTRS_LensFlareShader.h"

RTRS::LensFlareShader* RTRS::LensFlareShader::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::LensFlareShader*	RTRS::LensFlareShader::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::LensFlareShader();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::LensFlareShader::LensFlareShader()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::LensFlareShader::~LensFlareShader()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::LensFlareShader::ItlInitialize()
{
	bool bOk = ItlLoadShaders("shader/LensFlare.vert", "shader/LensFlare.frag");
	assert(bOk == true);

	m_glntLensFlareTextureLoc	= glGetUniformLocation(m_glnShaderProgram, "tLensFlareTexture");
	m_glntDepthTextureLoc		= glGetUniformLocation(m_glnShaderProgram, "tDepthTexture");
	m_glnv4SunPositionLoc		= glGetUniformLocation(m_glnShaderProgram, "v4SunPosition");
	m_glnv2AspectLoc			= glGetUniformLocation(m_glnShaderProgram, "v2Aspect");
	m_glnv2LensFlarePosition	= glGetUniformLocation(m_glnShaderProgram, "v2LensFlarePosition");
	m_glnfLensFlareScale		= glGetUniformLocation(m_glnShaderProgram, "fLensFlareScale");
	m_glnv4LensFlareColor		= glGetUniformLocation(m_glnShaderProgram, "v4LensFlareColor");
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::LensFlareShader::Render(RTRS::TexturedModel* pTexturedModel, glm::vec4 v4SunPositionInScreenSpace, glm::vec2 v2LensFlarePositionScreenSpace, float fLensFlareScale, glm::vec4 v4LensFlareColor, GLuint glnLensFlareTexture, GLuint glnDepthTexture)
{
	assert(pTexturedModel != NULL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	glUseProgram(m_glnShaderProgram);

	glUniform4fv(m_glnv4SunPositionLoc, 1, (GLfloat*)&v4SunPositionInScreenSpace);
	glUniform4fv(m_glnv4LensFlareColor, 1, (GLfloat*)&v4LensFlareColor);
	glUniform2f(m_glnv2AspectLoc, SCREEN_WIDTH / (float)glm::max(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_HEIGHT / (float)glm::max(SCREEN_WIDTH, SCREEN_HEIGHT));
	glUniform2fv(m_glnv2LensFlarePosition, 1, (GLfloat*)&v2LensFlarePositionScreenSpace);
	glUniform1f(m_glnfLensFlareScale, fLensFlareScale);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, glnDepthTexture);
	glUniform1i(m_glntDepthTextureLoc, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, glnLensFlareTexture);
	glUniform1i(m_glntLensFlareTextureLoc, 1);

	for(unsigned int n = 0; n < pTexturedModel->GetNumMeshes(); n++)
	{
		
		pTexturedModel->Render(n);
	}

	glUseProgram(0);
}