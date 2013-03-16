#ifndef _RTRS_BRIGHTPASSSHADER_H_
#define _RTRS_BRIGHTPASSSHADER_H_

#include "RTRS_IShader.h"
#include "RTRS_TexturedModel.h"

namespace RTRS
{
	class BrightPassShader : public IShader
	{
	public:
		static BrightPassShader*	GetInstance();

		void	Render(RTRS::TexturedModel* pTexturedModel);

	protected:

		BrightPassShader();
		~BrightPassShader();

		void ItlInitialize();

		static BrightPassShader*	m_pInstance;

		GLuint	m_glntColorTextureLoc;
	};
};

#endif //_RTRS_BRIGHTPASSSHADER_H_