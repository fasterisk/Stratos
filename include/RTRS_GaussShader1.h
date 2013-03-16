#ifndef _RTRS_GAUSSSHADER1_H_
#define _RTRS_GAUSSSHADER1_H_

#include "RTRS_IShader.h"
#include "RTRS_TexturedModel.h"

namespace RTRS
{
	class GaussShader1 : public IShader
	{
	public:
		static GaussShader1*	GetInstance();

		void	Render(RTRS::TexturedModel* pTexturedModel);

	protected:

		GaussShader1();
		~GaussShader1();

		void ItlInitialize();

		static GaussShader1*	m_pInstance;

		GLuint	m_glntColorTextureLoc;
		GLuint	m_glnfPixelOffsetLoc;
	};
};

#endif //_RTRS_GAUSSSHADER1_H_