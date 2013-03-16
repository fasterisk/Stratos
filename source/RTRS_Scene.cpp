#include "RTRS_Scene.h"
#include "RTRS_ObjectManager.h"
#include "RTRS_PostProcessingEffects.h"

#include "glm/gtc/matrix_transform.hpp"

/**************************************************************************************************
 **************************************************************************************************/
RTRS::Scene::Scene()
{
	
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::Scene::~Scene()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Scene::Render(double dDeltaTime)
{
	m_dTime += dDeltaTime;
		
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if(glfwGetKey(GLFW_KEY_F1) == GLFW_PRESS && m_iF1ButtonBefore == GLFW_RELEASE)
	{
		m_bInputLocked = !m_bInputLocked;
	}
	m_iF1ButtonBefore = glfwGetKey(GLFW_KEY_F1);

	//if(!m_bInputLocked)
	//{
		//change camera
		if(glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS && m_iSpaceButtonBefore == GLFW_RELEASE)
		{
			if(m_pCurrentCamera == m_pMovingCamera)
				m_pCurrentCamera = m_pAstronautCamera;
			else if(m_pCurrentCamera == m_pAstronautCamera)
				m_pCurrentCamera = m_pMovingCamera;
		}

		m_iSpaceButtonBefore = glfwGetKey(GLFW_KEY_SPACE);

		//move camera
		if(m_pCurrentCamera == m_pMovingCamera)
		{
			if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS)
				m_pMovingCamera->MoveRelativeToView((float)dDeltaTime, 0, 0);
			if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS)
				m_pMovingCamera->MoveRelativeToView((float)-dDeltaTime, 0, 0);
			if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
				m_pMovingCamera->MoveRelativeToView(0, (float)dDeltaTime, 0);
			if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
				m_pMovingCamera->MoveRelativeToView(0, (float)-dDeltaTime, 0);
			if(glfwGetKey(GLFW_KEY_PAGEUP))
				m_pMovingCamera->MoveRelativeToView(0, 0, (float)dDeltaTime);
			if(glfwGetKey(GLFW_KEY_PAGEDOWN))
				m_pMovingCamera->MoveRelativeToView(0, 0, (float)-dDeltaTime);
		}
	
		//rotate camera
		if(m_pCurrentCamera == m_pMovingCamera || m_pCurrentCamera == m_pAstronautCamera)
		{
			int iMouseX, iMouseY;
			glfwGetMousePos(&iMouseX, &iMouseY);

			m_pCurrentCamera->RotateY(-(iMouseX - m_v2MousePosition.x)*(float)dDeltaTime*2);
			m_pCurrentCamera->RotateX(-(iMouseY - m_v2MousePosition.y)*(float)dDeltaTime*2);
		
			m_v2MousePosition = glm::ivec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			glfwSetMousePos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		}
	//}
	/*else //automatic camera
	{
		if(m_dTime > 0 && m_dTime < 10.0)
			m_pMovingCamera->MoveBy(0, 0, -dDeltaTime / 10.0);

		if(m_dTime > 10.0 && m_dTime < 20.0)
		{
			m_pMovingCamera->RotateY(-dDeltaTime*2.0);
			m_pMovingCamera->RotateX(-dDeltaTime*2.0);
		}

		if(m_dTime > 9.0 && m_dTime < 15)
			m_pMovingCamera->MoveBy(-dDeltaTime / 10.0, 0, -dDeltaTime / 10.0);

	}*/

	// sound
	if(m_pCurrentCamera == m_pAstronautCamera)
	{
		m_pBackgroundChannel->setVolume(0.2);
		m_pVaderChannel->setPaused(false);
	}
	else
	{
		m_pBackgroundChannel->setVolume(1.0);
		m_pVaderChannel->setPaused(true);
	}

	//move light
	glm::vec3 v3CurrentLightPosition = ObjectManager::GetInstance()->GetLightPosition();

	if(m_dTime < 26.0)
		ObjectManager::GetInstance()->MoveLightTo(v3CurrentLightPosition.x, v3CurrentLightPosition.y + dDeltaTime*0.5, v3CurrentLightPosition.z);


	glm::mat4 m4View			= m_pCurrentCamera->GetViewMatrix();
	glm::mat4 m4ViewProjection	= m_pCurrentCamera->GetViewProjectionMatrix();
	glm::vec3 v3CameraPosition	= m_pCurrentCamera->GetPosition();
	
	ObjectManager::GetInstance()->MoveSkyboxTo(m_pCurrentCamera->GetPosition());

	ObjectManager::GetInstance()->GenerateEnvironmentMap();
	ObjectManager::GetInstance()->GenerateShadowMap();

	PostProcessingEffects::GetInstance()->BeginPreparePostProcessing();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	ObjectManager::GetInstance()->RenderObjects(m4ViewProjection, m4View, v3CameraPosition);
	ObjectManager::GetInstance()->RenderEnvironmentMappedObjects(m4ViewProjection, m4View, v3CameraPosition);

	PostProcessingEffects::GetInstance()->EndPreparePostProcessing();

	PostProcessingEffects::GetInstance()->RenderBloom();

	PostProcessingEffects::GetInstance()->RenderLensflares(m4ViewProjection);
	
	PostProcessingEffects::GetInstance()->RenderToScreen();

}


/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Scene::ItlInitialize()
{
	m_pLogger = new RTRS::Logger("RTRSScene.cpp");
	m_dTime = 0;
	m_v2MousePosition = glm::ivec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	glfwSetMousePos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_iSpaceButtonBefore = GLFW_RELEASE;
	m_iF1ButtonBefore = GLFW_RELEASE;
	m_bInputLocked = true;

	glEnable(GL_DEPTH_TEST);

	
	m_pMovingCamera = new RTRS::Camera(45.0f, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
	m_pMovingCamera->MoveTo(0, 1, 3);

	m_pAstronautCamera = new RTRS::Camera(45.0f, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.001f, 1000.0f);
	m_pAstronautCamera->MoveTo(0.0f, 1.04f, 1.36f);
	m_pAstronautCamera->RotateY(180);

	m_pCurrentCamera = m_pMovingCamera;

	//sound init
	FMOD_RESULT fmResult;
	fmResult = FMOD::System_Create(&m_pSoundsystem);
	assert(fmResult == FMOD_OK);

	fmResult = m_pSoundsystem->init(32, FMOD_INIT_NORMAL, 0);
	assert(fmResult == FMOD_OK);

	fmResult = m_pSoundsystem->createStream("resources/sounds/sound1.mp3", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &m_pBackgroundSound);
	assert(fmResult == FMOD_OK);
	
	fmResult = m_pSoundsystem->playSound(FMOD_CHANNEL_FREE, m_pBackgroundSound, false, &m_pBackgroundChannel);
	assert(fmResult == FMOD_OK);

	fmResult = m_pSoundsystem->createSound("resources/sounds/vader.wav", FMOD_HARDWARE, 0, &m_pVaderSound);
	assert(fmResult == FMOD_OK);

	fmResult = m_pSoundsystem->playSound(FMOD_CHANNEL_FREE, m_pVaderSound, true, &m_pVaderChannel);

}