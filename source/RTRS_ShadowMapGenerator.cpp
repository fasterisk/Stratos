#include "RTRS_ShadowMapGenerator.h"
#include "RTRS_ObjectManager.h"

#include "glm/gtc/matrix_transform.hpp"

#define SHADOWMAP_WIDTH	 8192//16384//
#define SHADOWMAP_HEIGHT 8192//16384//


RTRS::ShadowMapGenerator* RTRS::ShadowMapGenerator::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::ShadowMapGenerator*	RTRS::ShadowMapGenerator::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::ShadowMapGenerator();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::ShadowMapGenerator::ShadowMapGenerator()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::ShadowMapGenerator::~ShadowMapGenerator()
{}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ShadowMapGenerator::SetViewParameters(glm::vec3 v3LightPosition, glm::vec3 v3LightDirection)
{
	glm::mat4 m4ViewMatrix = glm::lookAt(v3LightPosition / 4.0f, v3LightDirection, glm::vec3(0.0, 1.0, 0.0));
	m_m4ViewProjectionMatrix =  m_m4ProjectionMatrix * m4ViewMatrix;
	m_m4ShadowMatrix = m_m4Bias * m_m4ViewProjectionMatrix;
}

/**************************************************************************************************
 **************************************************************************************************/
glm::mat4	RTRS::ShadowMapGenerator::GetShadowMatrix()
{
	return m_m4ShadowMatrix;
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ShadowMapGenerator::Render()
{
	glViewport(0, 0, SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBuffer);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
	
	ObjectManager::GetInstance()->RenderObjectsForShadowMap(m_m4ViewProjectionMatrix);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glViewport(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ShadowMapGenerator::ItlInitialize()
{
	//initialize projection matrix
	m_m4ProjectionMatrix = glm::perspective(90.0f, 1.0f, 0.1f, 100.0f);

	//initialize bias matrix
	m_m4Bias = glm::mat4(0.5, 0.0, 0.0, 0.0,
						 0.0, 0.5, 0.0, 0.0,
						 0.0, 0.0, 0.5, 0.0,
						 0.5, 0.5, 0.5, 1.0);

	//initialize the shadow map depth texture
	glGenTextures(1, &m_glnShadowMap);
	glBindTexture(GL_TEXTURE_2D, m_glnShadowMap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//create the FBO
	glGenFramebuffers(1, &m_glnFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBuffer);

	//attach the shadow map texture to the FBO depth attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_glnShadowMap, 0);

	//we don't bind a color texture
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum gleFBOStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(gleFBOStatus != GL_FRAMEBUFFER_COMPLETE)
		g_stLogger.error() << "Framebuffer of the Shadow Map is not completed" << g_stLogger.endl();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}