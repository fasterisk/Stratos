#include "RTRS_ObjectManager.h"
#include "RTRS_SimpleTextureShader.h"
#include "RTRS_TextureShader.h"
#include "RTRS_ColorShader.h"
#include "RTRS_EnvironmentMappingShader.h"
#include "RTRS_ParallaxMappingShader.h"
#include "RTRS_EnvironmentMapGenerator.h"
#include "RTRS_ShadowMapGenerator.h"


RTRS::ObjectManager* RTRS::ObjectManager::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::ObjectManager*	RTRS::ObjectManager::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::ObjectManager();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::ObjectManager::ObjectManager()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::ObjectManager::~ObjectManager()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ObjectManager::ItlInitialize()
{
	m_pSkybox = new Skybox();

	m_pKapsel = new RTRS::TexturedModel();
	m_pKapsel->LoadMesh("resources/models/kapsel.obj");
	m_pKapsel->SetTexture(0, "hull15");
	m_pKapsel->SetTexture(1, "hull15");
	m_pKapsel->SetTexture(3, "container14");
	m_pKapsel->SetTexture(2, "container16");
	m_pKapsel->Scale(0.07f);

	m_pEarth = new RTRS::TexturedModel();
	m_pEarth->LoadMesh("resources/models/earth.obj");
	m_pEarth->SetTexture("earth");
	m_pEarth->MoveTo(0, -100, 0);
	m_pEarth->Scale(10.0f);

	m_pMoon = new RTRS::TexturedModel();
	m_pMoon->LoadMesh("resources/models/moon.obj");
	m_pMoon->SetTexture("moon");
	m_pMoon->MoveTo(-20, 0, 0);
	m_pMoon->Scale(0.3f);

	m_pLight1 = new RTRS::IModel();
	m_pLight1->LoadMesh("resources/models/sphere.obj");
	m_pLight1->Scale(0.1f);
	m_pLight1->MoveTo(0, -5, 20);
	m_pLight1->SetColor(glm::vec3(1.0f, 1.0f, 0.0f)); 

	m_pAstronaut = new RTRS::TexturedModel();
	m_pAstronaut->LoadMesh("resources/models/astronaut_v2.obj");
	m_pAstronaut->SetTexture("astronaut");
	m_pAstronaut->SetTexture(0, "default");
	m_pAstronaut->SetTexture(2, "default");
	m_pAstronaut->SetEnvironmentMappedFlag(14, true);
	m_pAstronaut->SetEnvironmentMapPosition(0.0f, 1.04f, 1.39f);
	m_pAstronaut->MoveTo(0.0f, 0.04f, 1.3f);
	m_pAstronaut->Scale(0.035f);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ObjectManager::RenderObjects(glm::mat4 m4ViewProjection, glm::mat4 m4View, glm::vec3 v3CameraPosition)
{
	glDisable(GL_CULL_FACE);
	SimpleTextureShader::GetInstance()->Render(m_pSkybox, m4ViewProjection);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	SimpleTextureShader::GetInstance()->Render(m_pEarth, m4ViewProjection);
	SimpleTextureShader::GetInstance()->Render(m_pMoon, m4ViewProjection);

	ParallaxMappingShader::GetInstance()->Render(m_pAstronaut, ShadowMapGenerator::GetInstance()->GetShadowMap(), ShadowMapGenerator::GetInstance()->GetShadowMatrix(), m4ViewProjection, m4View, m_pLight1->GetPosition(), v3CameraPosition);
	ParallaxMappingShader::GetInstance()->Render(m_pKapsel, ShadowMapGenerator::GetInstance()->GetShadowMap(), ShadowMapGenerator::GetInstance()->GetShadowMatrix(), m4ViewProjection, m4View, m_pLight1->GetPosition(), v3CameraPosition);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ObjectManager::RenderObjectsForShadowMap(glm::mat4 m4ViewProjection)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	ColorShader::GetInstance()->Render(m_pEarth, m4ViewProjection);
	ColorShader::GetInstance()->Render(m_pMoon, m4ViewProjection);

	ColorShader::GetInstance()->Render(m_pAstronaut, m4ViewProjection);
	ColorShader::GetInstance()->Render(m_pKapsel, m4ViewProjection);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ObjectManager::RenderEnvironmentMappedObjects(glm::mat4 m4ViewProjection, glm::mat4 m4View, glm::vec3 v3CameraPosition)
{
	EnvironmentMappingShader::GetInstance()->Render(m_pAstronaut, EnvironmentMapGenerator::GetInstance()->GetCubeMap(), m4ViewProjection, m4View, m_pLight1->GetPosition(), v3CameraPosition);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ObjectManager::GenerateEnvironmentMap()
{
	EnvironmentMapGenerator::GetInstance()->Render(m_pAstronaut->GetEnvironmentMapPosition(), m_pLight1->GetPosition());
}


/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ObjectManager::GenerateShadowMap()
{
	ShadowMapGenerator::GetInstance()->SetViewParameters(m_pLight1->GetPosition(), glm::vec3(0, 0, 0));
	ShadowMapGenerator::GetInstance()->Render();
}

void	MoveLightTo(float fX, float fY, float fZ);

/**************************************************************************************************
 **************************************************************************************************/
glm::vec3	RTRS::ObjectManager::GetLightPosition() const
{
	assert(m_pLight1 != NULL);

	return m_pLight1->GetPosition();
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ObjectManager::MoveLightTo(float fX, float fY, float fZ)
{
	m_pLight1->MoveTo(fX, fY, fZ);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::ObjectManager::MoveSkyboxTo(glm::vec3 v3NewPosition)
{
	assert(m_pSkybox != NULL);

	m_pSkybox->MoveTo(v3NewPosition);
}