#include "RTRS_TextureManager.h"
#include "RTRS_TexturedModel.h"


/**************************************************************************************************
 **************************************************************************************************/
RTRS::TexturedModel::TexturedModel()
{
	m_pglnColorTextureIDs = NULL;
	m_pglnSpecularTextureIDs = NULL;
	m_pglnNormalTextureIDs = NULL;
	m_pglnBumpTextureIDs = NULL;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::TexturedModel::~TexturedModel()
{
	if(m_pglnColorTextureIDs != NULL)
	{
		delete[] m_pglnColorTextureIDs;
		m_pglnColorTextureIDs = NULL;
	}

	if(m_pglnSpecularTextureIDs != NULL)
	{
		delete[] m_pglnSpecularTextureIDs;
		m_pglnSpecularTextureIDs = NULL;
	}

	if(m_pglnNormalTextureIDs != NULL)
	{
		delete[] m_pglnNormalTextureIDs;
		m_pglnNormalTextureIDs = NULL;
	}

	if(m_pglnBumpTextureIDs != NULL)
	{
		delete[] m_pglnBumpTextureIDs;
		m_pglnBumpTextureIDs = NULL;
	}
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::TexturedModel::ItlInitialize()
{
	if(m_pglnColorTextureIDs != NULL)
	{
		delete[] m_pglnColorTextureIDs;
		m_pglnColorTextureIDs = NULL;
	}

	if(m_pglnSpecularTextureIDs != NULL)
	{
		delete[] m_pglnSpecularTextureIDs;
		m_pglnSpecularTextureIDs = NULL;
	}

	if(m_pglnNormalTextureIDs != NULL)
	{
		delete[] m_pglnNormalTextureIDs;
		m_pglnNormalTextureIDs = NULL;
	}

	if(m_pglnBumpTextureIDs != NULL)
	{
		delete[] m_pglnBumpTextureIDs;
		m_pglnBumpTextureIDs = NULL;
	}


	m_pglnColorTextureIDs = new GLuint[m_vMeshes.size()];
	m_pglnSpecularTextureIDs = new GLuint[m_vMeshes.size()];
	m_pglnNormalTextureIDs = new GLuint[m_vMeshes.size()];
	m_pglnBumpTextureIDs = new GLuint[m_vMeshes.size()];

	for(unsigned int i = 0; i < m_vMeshes.size(); i++)
	{
		m_pglnColorTextureIDs[i] = RTRS::TextureManager::GetInstance()->GetDefaultTexture(TextureManager::TEXTURETYPE::COLOR);
		m_pglnSpecularTextureIDs[i] = RTRS::TextureManager::GetInstance()->GetDefaultTexture(TextureManager::TEXTURETYPE::SPECULAR);
		m_pglnNormalTextureIDs[i] = RTRS::TextureManager::GetInstance()->GetDefaultTexture(TextureManager::TEXTURETYPE::NORMAL);
		m_pglnBumpTextureIDs[i] = RTRS::TextureManager::GetInstance()->GetDefaultTexture(TextureManager::TEXTURETYPE::BUMP);
	}
}

/**************************************************************************************************
 **************************************************************************************************/
bool	RTRS::TexturedModel::SetTexture(unsigned int nMeshID, const char* pcTextureName)
{
	bool bOk = false;
	if(nMeshID < m_vMeshes.size())
	{
		assert(m_pglnColorTextureIDs != NULL);
		m_pglnColorTextureIDs[nMeshID] = RTRS::TextureManager::GetInstance()->GetTextureByName(pcTextureName, TextureManager::TEXTURETYPE::COLOR);
		
		assert(m_pglnNormalTextureIDs != NULL);
		m_pglnNormalTextureIDs[nMeshID] = RTRS::TextureManager::GetInstance()->GetTextureByName(pcTextureName, TextureManager::TEXTURETYPE::NORMAL);

		assert(m_pglnBumpTextureIDs != NULL);
		m_pglnBumpTextureIDs[nMeshID] = RTRS::TextureManager::GetInstance()->GetTextureByName(pcTextureName, TextureManager::TEXTURETYPE::BUMP);
		
		assert(m_pglnSpecularTextureIDs != NULL);
		m_pglnSpecularTextureIDs[nMeshID] = RTRS::TextureManager::GetInstance()->GetTextureByName(pcTextureName, TextureManager::TEXTURETYPE::SPECULAR);
	}

	return bOk;
}

/**************************************************************************************************
 **************************************************************************************************/
bool	RTRS::TexturedModel::SetTexture(const char* pcTextureName)
{
	assert(m_pglnColorTextureIDs != NULL);
	assert(m_pglnNormalTextureIDs != NULL);
	assert(m_pglnBumpTextureIDs != NULL);
	assert(m_pglnSpecularTextureIDs != NULL);
	
	for(unsigned int n = 0; n < m_vMeshes.size(); n++)
	{
		m_pglnColorTextureIDs[n] = RTRS::TextureManager::GetInstance()->GetTextureByName(pcTextureName, TextureManager::TEXTURETYPE::COLOR);
		m_pglnNormalTextureIDs[n] = RTRS::TextureManager::GetInstance()->GetTextureByName(pcTextureName, TextureManager::TEXTURETYPE::NORMAL);
		m_pglnBumpTextureIDs[n] = RTRS::TextureManager::GetInstance()->GetTextureByName(pcTextureName, TextureManager::TEXTURETYPE::BUMP);
		m_pglnSpecularTextureIDs[n] = RTRS::TextureManager::GetInstance()->GetTextureByName(pcTextureName, TextureManager::TEXTURETYPE::SPECULAR);
	}

	return true;
}

/**************************************************************************************************
 **************************************************************************************************/
bool	RTRS::TexturedModel::SetTexture(GLuint glnTextureID)
{
	assert(m_pglnColorTextureIDs != NULL);
	assert(m_pglnNormalTextureIDs != NULL);
	assert(m_pglnBumpTextureIDs != NULL);
	assert(m_pglnSpecularTextureIDs != NULL);
	
	for(unsigned int n = 0; n < m_vMeshes.size(); n++)
	{
		m_pglnColorTextureIDs[n] = glnTextureID;
		m_pglnNormalTextureIDs[n] = glnTextureID;
		m_pglnBumpTextureIDs[n] = glnTextureID;
		m_pglnSpecularTextureIDs[n] = glnTextureID;
	}

	return true;
}

/**************************************************************************************************
 **************************************************************************************************/
bool	RTRS::TexturedModel::SetTexture(GLuint glnTextureID, RTRS::TextureManager::TEXTURETYPE eTextureType)
{
	GLuint* pTextureIDs = NULL;

	switch(eTextureType)
	{
	case TextureManager::TEXTURETYPE::COLOR: pTextureIDs = m_pglnColorTextureIDs; break;
	case TextureManager::TEXTURETYPE::NORMAL: pTextureIDs = m_pglnNormalTextureIDs; break;
	case TextureManager::TEXTURETYPE::BUMP: pTextureIDs = m_pglnBumpTextureIDs; break;
	case TextureManager::TEXTURETYPE::SPECULAR: pTextureIDs = m_pglnSpecularTextureIDs; break;
	default: pTextureIDs = NULL;
	}

	assert(pTextureIDs != NULL);

	for(unsigned int n = 0; n < m_vMeshes.size(); n++)
		pTextureIDs[n] = glnTextureID;

	return true;
}

/**************************************************************************************************
 **************************************************************************************************/
GLuint	RTRS::TexturedModel::GetTextureID(unsigned int nMeshID, RTRS::TextureManager::TEXTURETYPE eTextureType) const
{
	assert(nMeshID < m_vMeshes.size());

	switch(eTextureType)
	{
	case TextureManager::TEXTURETYPE::COLOR: return m_pglnColorTextureIDs[nMeshID];
	case TextureManager::TEXTURETYPE::NORMAL: return m_pglnNormalTextureIDs[nMeshID];
	case TextureManager::TEXTURETYPE::BUMP: return m_pglnBumpTextureIDs[nMeshID];
	case TextureManager::TEXTURETYPE::SPECULAR: return m_pglnSpecularTextureIDs[nMeshID];
	default: return m_pglnColorTextureIDs[nMeshID];
	}
}