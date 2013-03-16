#ifndef _RTRS_TEXTUREMANAGER_H_
#define _RTRS_TEXTUREMANAGER_H_

#include "RTRS_Common_includes.h"

#include <map>

namespace RTRS
{

	typedef std::map<std::string, GLuint> TextureMap;
	typedef std::pair<std::string, GLuint> TextureMapPair;

	class TextureManager
	{
	public:

		enum TEXTURETYPE {
			COLOR,
			NORMAL,
			SPECULAR,
			BUMP
		};

		static	TextureManager*	GetInstance();

		GLuint	GetTextureByName(const char* pcTextureName, TEXTURETYPE eTextureType);

		GLuint	GetDefaultTexture(TEXTURETYPE eTextureType);
		
	private:
		TextureManager();
		~TextureManager();

		void	ItlInitialize();
		bool	ItlLoadTexture(const char* pcTextureName, const char* pcTexturePath, TEXTURETYPE eTextureType);
		bool	ItlLoadDefaultTexture(const char* pcTexturePath, TEXTURETYPE eTextureType);

		GLuint					m_glnDefaultColorTexture;
		GLuint					m_glnDefaultNormalTexture;
		GLuint					m_glnDefaultSpecularTexture;
		GLuint					m_glnDefaultBumpTexture;

		static TextureManager	* m_pInstance;

		TextureMap*				m_pColorTextureMap;
		TextureMap*				m_pNormalTextureMap;
		TextureMap*				m_pSpecularTextureMap;
		TextureMap*				m_pBumpTextureMap;

		Logger*					m_pLogger;
	};
};

#endif //_RTRS_TEXTUREMANAGER_H_