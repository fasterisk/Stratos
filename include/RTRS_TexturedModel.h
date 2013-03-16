#ifndef _RTRS_TEXTUREDMODEL_H_
#define _RTRS_TEXTUREDMODEL_H_

#include "RTRS_IModel.h"
#include "RTRS_TextureManager.h"

namespace RTRS
{
	class TexturedModel : public IModel
	{
	public:
		TexturedModel();
		~TexturedModel();

		bool			SetTexture(unsigned int nMeshID, const char* pcTextureName);
		bool			SetTexture(const char* pcTextureName);
		bool			SetTexture(GLuint glnTextureID);
		bool			SetTexture(GLuint glnTextureID, RTRS::TextureManager::TEXTURETYPE eTextureType);
		
		GLuint			GetTextureID(unsigned int nMeshID, RTRS::TextureManager::TEXTURETYPE eTextureType) const;


	protected:
		virtual void		ItlInitialize();

		GLuint*				m_pglnColorTextureIDs;
		GLuint*				m_pglnSpecularTextureIDs;
		GLuint*				m_pglnNormalTextureIDs;
		GLuint*				m_pglnBumpTextureIDs;
	};
};

#endif //_RTRS_TEXTUREDMODEL_H_