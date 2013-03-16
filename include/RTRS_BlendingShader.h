#ifndef _RTRS_BLENDINGSHADER_H_
#define _RTRS_BLENDINGSHADER_H_

#include "RTRS_IShader.h"
#include "RTRS_TexturedModel.h"

namespace RTRS
{
	class BlendingShader : public IShader
	{
	public:
		static BlendingShader*	GetInstance();

		void	Render(RTRS::TexturedModel* pTexturedModel);

	protected:

		BlendingShader();
		~BlendingShader();

		void ItlInitialize();

		static BlendingShader*	m_pInstance;

		GLuint	m_glntColorTexture1Loc;
		GLuint	m_glntColorTexture2Loc;
	};
};

#endif //_RTRS_BLENDINGSHADER_H_