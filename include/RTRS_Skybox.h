#ifndef _RTRS_SKYBOX_H_
#define _RTRS_SKYBOX_H_

#include "RTRS_IModel.h"

namespace RTRS
{
	class Skybox : public IModel
	{
	public:
		enum TextureIndex
		{
			BOTTOM,
			TOP,
			RIGHT,
			LEFT,
			BACK,
			FRONT
		};

		Skybox();
		~Skybox();

		void			SetTextures(const char* pcFront, 
									const char* pcBack, 
									const char* pcLeft, 
									const char* pcRight, 
									const char* pcTop, 
									const char* pcBottom);

		GLuint			GetTextureID(TextureIndex eIndex);

	protected:
		virtual void	ItlInitialize();

		GLuint	m_nFrontTexture;
		GLuint	m_nBackTexture;
		GLuint	m_nLeftTexture;
		GLuint	m_nRightTexture;
		GLuint	m_nTopTexture;
		GLuint	m_nBottomTexture;
	};
};

#endif //_RTRS_SKYBOX_H_