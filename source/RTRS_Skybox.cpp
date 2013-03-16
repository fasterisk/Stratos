#include "RTRS_TextureManager.h"

#include "RTRS_Skybox.h"


/**************************************************************************************************
 **************************************************************************************************/
RTRS::Skybox::Skybox()
{
	m_nFrontTexture		= 0;
	m_nBackTexture		= 0;
	m_nLeftTexture		= 0;
	m_nRightTexture		= 0;
	m_nTopTexture		= 0;
	m_nBottomTexture	= 0;

	LoadMesh("resources/models/skybox.obj");
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::Skybox::~Skybox()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Skybox::ItlInitialize()
{
	m_nFrontTexture		= RTRS::TextureManager::GetInstance()->GetTextureByName("skybox_front", TextureManager::TEXTURETYPE::COLOR);
	m_nBackTexture		= RTRS::TextureManager::GetInstance()->GetTextureByName("skybox_back", TextureManager::TEXTURETYPE::COLOR);
	m_nLeftTexture		= RTRS::TextureManager::GetInstance()->GetTextureByName("skybox_front", TextureManager::TEXTURETYPE::COLOR);
	m_nRightTexture		= RTRS::TextureManager::GetInstance()->GetTextureByName("skybox_front", TextureManager::TEXTURETYPE::COLOR);
	m_nTopTexture		= RTRS::TextureManager::GetInstance()->GetTextureByName("skybox_top", TextureManager::TEXTURETYPE::COLOR);
	m_nBottomTexture	= RTRS::TextureManager::GetInstance()->GetTextureByName("skybox_bottom", TextureManager::TEXTURETYPE::COLOR);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::Skybox::SetTextures(const char* pcFront,
								  const char* pcBack,
								  const char* pcLeft, 
								  const char* pcRight, 
								  const char* pcTop, 
								  const char* pcBottom)
{
	m_nFrontTexture		= RTRS::TextureManager::GetInstance()->GetTextureByName(pcFront, TextureManager::TEXTURETYPE::COLOR);
	m_nBackTexture		= RTRS::TextureManager::GetInstance()->GetTextureByName(pcBack, TextureManager::TEXTURETYPE::COLOR);
	m_nLeftTexture		= RTRS::TextureManager::GetInstance()->GetTextureByName(pcLeft, TextureManager::TEXTURETYPE::COLOR);
	m_nRightTexture		= RTRS::TextureManager::GetInstance()->GetTextureByName(pcRight, TextureManager::TEXTURETYPE::COLOR);
	m_nTopTexture		= RTRS::TextureManager::GetInstance()->GetTextureByName(pcTop, TextureManager::TEXTURETYPE::COLOR);
	m_nBottomTexture	= RTRS::TextureManager::GetInstance()->GetTextureByName(pcBottom, TextureManager::TEXTURETYPE::COLOR);
}

/**************************************************************************************************
 **************************************************************************************************/
GLuint	RTRS::Skybox::GetTextureID(TextureIndex eIndex)
{
	switch(eIndex)
	{
	case TextureIndex::FRONT: return m_nFrontTexture;
	case TextureIndex::BACK: return m_nBackTexture;
	case TextureIndex::LEFT: return m_nLeftTexture;
	case TextureIndex::RIGHT: return m_nRightTexture;
	case TextureIndex::TOP: return m_nTopTexture;
	case TextureIndex::BOTTOM: return m_nBottomTexture;
	default: return m_nFrontTexture;
	}
}