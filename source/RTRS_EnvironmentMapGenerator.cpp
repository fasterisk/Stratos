#include "RTRS_EnvironmentMapGenerator.h"
#include "RTRS_ObjectManager.h"

#include "glm/gtc/matrix_transform.hpp"

#define CUBEMAP_SIZE	1024


RTRS::EnvironmentMapGenerator* RTRS::EnvironmentMapGenerator::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::EnvironmentMapGenerator*	RTRS::EnvironmentMapGenerator::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::EnvironmentMapGenerator();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::EnvironmentMapGenerator::EnvironmentMapGenerator()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::EnvironmentMapGenerator::~EnvironmentMapGenerator()
{}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::EnvironmentMapGenerator::Render(glm::vec3 v3CameraPosition, glm::vec3 v3LightPosition)
{
	glm::mat4 m4VMatrix;
	glm::mat4 m4Projection = glm::perspective(90.0f, 1.0f, 0.001f, 100.0f);

	glViewport(0,0, CUBEMAP_SIZE, CUBEMAP_SIZE);

	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBuffer);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_glnDepthBuffer);

	for(int i = 0; i < 6; i++)
	{
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_glnCubeColorMap, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int iCubeMapIndex = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		switch(iCubeMapIndex)
		{
		case GL_TEXTURE_CUBE_MAP_POSITIVE_X: m4VMatrix = glm::lookAt(v3CameraPosition, v3CameraPosition + glm::vec3( 1,  0,  0), glm::vec3(0,  -1,  0)); break;
		case GL_TEXTURE_CUBE_MAP_NEGATIVE_X: m4VMatrix = glm::lookAt(v3CameraPosition, v3CameraPosition + glm::vec3(-1,  0,  0), glm::vec3(0,  -1,  0)); break;
		case GL_TEXTURE_CUBE_MAP_POSITIVE_Y: m4VMatrix = glm::lookAt(v3CameraPosition, v3CameraPosition + glm::vec3( 0,  1,  0), glm::vec3(0,  0,  1)); break;
		case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y: m4VMatrix = glm::lookAt(v3CameraPosition, v3CameraPosition + glm::vec3( 0, -1,  0), glm::vec3(0,  0, -1)); break;
		case GL_TEXTURE_CUBE_MAP_POSITIVE_Z: m4VMatrix = glm::lookAt(v3CameraPosition, v3CameraPosition + glm::vec3( 0,  0,  1), glm::vec3(0,  -1,  0)); break;
		case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z: m4VMatrix = glm::lookAt(v3CameraPosition, v3CameraPosition + glm::vec3( 0,  0, -1), glm::vec3(0,  -1,  0)); break;
		}
		glm::mat4 m4VPMatrix = m4Projection * m4VMatrix;

		ObjectManager::GetInstance()->RenderObjects(m4VPMatrix, m4VMatrix, v3CameraPosition);

	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glViewport(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::EnvironmentMapGenerator::ItlInitialize()
{
	//create the cubemap
	glEnable(GL_TEXTURE_CUBE_MAP);

	glGenTextures(1, &m_glnCubeColorMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_glnCubeColorMap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	std::vector<GLubyte> testData(CUBEMAP_SIZE * CUBEMAP_SIZE * 256, 128);
	std::vector<GLubyte> xData(CUBEMAP_SIZE * CUBEMAP_SIZE * 256, 255);
	
	for(int i = 0; i < 6; ++i)
	{
		if(i == 0)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
				CUBEMAP_SIZE, CUBEMAP_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, &xData[0]);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
				CUBEMAP_SIZE, CUBEMAP_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, &testData[0]);
		}
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	//create the FBO
	glGenFramebuffers(1, &m_glnFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBuffer);

	//create the depth buffer and attach it to the FBO
	glGenRenderbuffers(1, &m_glnDepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glnDepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, CUBEMAP_SIZE, CUBEMAP_SIZE);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_glnFrameBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}