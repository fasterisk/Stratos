#include "RTRS_TextureManager.h"

RTRS::TextureManager* RTRS::TextureManager::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::TextureManager*	RTRS::TextureManager::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::TextureManager();

	return m_pInstance;
}



/**************************************************************************************************
 **************************************************************************************************/
GLuint	RTRS::TextureManager::GetTextureByName(const char* pcTextureName, TEXTURETYPE eTextureType)
{
	RTRS::TextureMap* pTextureMap = NULL;

	switch(eTextureType)
	{
	case TEXTURETYPE::COLOR: pTextureMap = m_pColorTextureMap; break;
	case TEXTURETYPE::NORMAL: pTextureMap = m_pNormalTextureMap; break;
	case TEXTURETYPE::BUMP: pTextureMap = m_pBumpTextureMap; break;
	case TEXTURETYPE::SPECULAR: pTextureMap = m_pSpecularTextureMap; break;
	}

	assert(pTextureMap != NULL);

	RTRS::TextureMap::iterator iter = pTextureMap->find(pcTextureName);

	if(iter != pTextureMap->end())
		return iter->second;
	else
	{
		return GetDefaultTexture(eTextureType);
	}
}

/**************************************************************************************************
 **************************************************************************************************/
GLuint	RTRS::TextureManager::GetDefaultTexture(TEXTURETYPE eTextureType)
{
	switch(eTextureType)
	{
	case TEXTURETYPE::COLOR: return m_glnDefaultColorTexture;
	case TEXTURETYPE::NORMAL: return m_glnDefaultNormalTexture;
	case TEXTURETYPE::BUMP: return m_glnDefaultBumpTexture;
	case TEXTURETYPE::SPECULAR: return m_glnDefaultSpecularTexture;
	default: return 0;
	}
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::TextureManager::TextureManager()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::TextureManager::~TextureManager()
{
	delete m_pColorTextureMap;
	delete m_pNormalTextureMap;
	delete m_pSpecularTextureMap;
	delete m_pBumpTextureMap;
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::TextureManager::ItlInitialize()
{
	m_pLogger = new Logger("TextureManager.cpp");

	m_pColorTextureMap = new TextureMap();
	m_pNormalTextureMap = new TextureMap();
	m_pSpecularTextureMap = new TextureMap();
	m_pBumpTextureMap = new TextureMap();

	bool bOk = ItlLoadDefaultTexture("resources/textures/defaultcolor.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadDefaultTexture("resources/textures/defaultnormal.tga", TEXTURETYPE::NORMAL);
	assert(bOk == true);
	bOk = ItlLoadDefaultTexture("resources/textures/defaultbump.tga", TEXTURETYPE::BUMP);
	assert(bOk == true);
	bOk = ItlLoadDefaultTexture("resources/textures/defaultspecular.tga", TEXTURETYPE::SPECULAR);
	assert(bOk == true);

	bOk = ItlLoadTexture("skybox_front", "resources/textures/space_skybox/front.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("skybox_back", "resources/textures/space_skybox/back.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("skybox_left", "resources/textures/space_skybox/left.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("skybox_right", "resources/textures/space_skybox/right.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("skybox_top", "resources/textures/space_skybox/top.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("skybox_bottom", "resources/textures/space_skybox/bottom.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("earth", "resources/textures/earth.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("moon", "resources/textures/moon.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("sun", "resources/textures/Sun.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("lensflare1", "resources/textures/lensflare1.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("lensflare2", "resources/textures/lensflare2.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("lensflare3", "resources/textures/lensflare3.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	
	bOk = ItlLoadTexture("astronaut", "resources/textures/astronaut.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("astronaut", "resources/textures/cloth07b.tga", TEXTURETYPE::BUMP);
	assert(bOk == true);
	bOk = ItlLoadTexture("astronaut", "resources/textures/cloth07s.tga", TEXTURETYPE::SPECULAR);
	assert(bOk == true);
	bOk = ItlLoadTexture("astronaut", "resources/textures/cloth07n.tga", TEXTURETYPE::NORMAL);
	assert(bOk == true);

	bOk = ItlLoadTexture("container16", "resources/textures/capsule/container16.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("container16", "resources/textures/capsule/container16b.tga", TEXTURETYPE::BUMP);
	assert(bOk == true);
	bOk = ItlLoadTexture("container16", "resources/textures/capsule/container16s.tga", TEXTURETYPE::SPECULAR);
	assert(bOk == true);
	bOk = ItlLoadTexture("container16", "resources/textures/capsule/container16n.tga", TEXTURETYPE::NORMAL);
	assert(bOk == true);

	bOk = ItlLoadTexture("container14", "resources/textures/capsule/container14.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("container14", "resources/textures/capsule/container14b.tga", TEXTURETYPE::BUMP);
	assert(bOk == true);
	bOk = ItlLoadTexture("container14", "resources/textures/capsule/container14s.tga", TEXTURETYPE::SPECULAR);
	assert(bOk == true);
	bOk = ItlLoadTexture("container14", "resources/textures/capsule/container14n.tga", TEXTURETYPE::NORMAL);
	assert(bOk == true);

	bOk = ItlLoadTexture("hull15", "resources/textures/capsule/hull15.tga", TEXTURETYPE::COLOR);
	assert(bOk == true);
	bOk = ItlLoadTexture("hull15", "resources/textures/capsule/hull15b.tga", TEXTURETYPE::BUMP);
	assert(bOk == true);
	bOk = ItlLoadTexture("hull15", "resources/textures/capsule/hull15s.tga", TEXTURETYPE::SPECULAR);
	assert(bOk == true);
	bOk = ItlLoadTexture("hull15", "resources/textures/capsule/hull15n.tga", TEXTURETYPE::NORMAL);
	assert(bOk == true);
}

/**************************************************************************************************
 **************************************************************************************************/
bool	RTRS::TextureManager::ItlLoadTexture(const char* pcTextureName, const char* pcTexturePath, TEXTURETYPE eTextureType)
{
	bool bOk = true;

	m_pLogger->debug() << "Loading texture: " << pcTexturePath << m_pLogger->endl();

	RTRS::TextureMap* pTextureMap = NULL;

	switch(eTextureType)
	{
	case TEXTURETYPE::COLOR: pTextureMap = m_pColorTextureMap; break;
	case TEXTURETYPE::NORMAL: pTextureMap = m_pNormalTextureMap; break;
	case TEXTURETYPE::BUMP: pTextureMap = m_pBumpTextureMap; break;
	case TEXTURETYPE::SPECULAR: pTextureMap = m_pSpecularTextureMap; break;
	}

	assert(pTextureMap != NULL);

	RTRS::TextureMap::iterator iter = pTextureMap->find(pcTextureName);

	if(iter == pTextureMap->end())
	{
		GLuint nTextureID;
		glGenTextures(1, &nTextureID);
		glBindTexture(GL_TEXTURE_2D, nTextureID);

		if(glfwLoadTexture2D(pcTexturePath, 0))
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			pTextureMap->insert(RTRS::TextureMapPair(pcTextureName, nTextureID));

			bOk = true;
		}
		else
			bOk = false;

		glBindTexture(GL_TEXTURE_2D, 0);
	
		//check for an Opengl error
		CheckForOpenGLError();
	}
	else
	{
		bOk = false;
	}
	return bOk;
}

/**************************************************************************************************
 **************************************************************************************************/
bool	RTRS::TextureManager::ItlLoadDefaultTexture(const char* pcTexturePath, TEXTURETYPE eTextureType)
{
	bool bOk = true;

	switch(eTextureType)
	{
	case TEXTURETYPE::COLOR:
		{
			glGenTextures(1, &m_glnDefaultColorTexture);
			glBindTexture(GL_TEXTURE_2D, m_glnDefaultColorTexture);
			break;
		}
	case TEXTURETYPE::NORMAL:
		{
			glGenTextures(1, &m_glnDefaultNormalTexture);
			glBindTexture(GL_TEXTURE_2D, m_glnDefaultNormalTexture);
			break;
		}
	case TEXTURETYPE::BUMP:
		{
			glGenTextures(1, &m_glnDefaultBumpTexture);
			glBindTexture(GL_TEXTURE_2D, m_glnDefaultBumpTexture);
			break;
		}
	case TEXTURETYPE::SPECULAR:
		{
			glGenTextures(1, &m_glnDefaultSpecularTexture);
			glBindTexture(GL_TEXTURE_2D, m_glnDefaultSpecularTexture);
			break;
		}
	default:
		{
			glGenTextures(1, &m_glnDefaultColorTexture);
			glBindTexture(GL_TEXTURE_2D, m_glnDefaultColorTexture);
			break;
		}
	}
	

	if(glfwLoadTexture2D(pcTexturePath, 0))
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		bOk = true;
	}
	else
		bOk = false;

	glBindTexture(GL_TEXTURE_2D, 0);
	
	//check for an Opengl error

	CheckForOpenGLError();
	return bOk;
}