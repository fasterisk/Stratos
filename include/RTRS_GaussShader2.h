#ifndef _RTRS_GAUSSSHADER2_H_
#define _RTRS_GAUSSSHADER2_H_

#include "RTRS_IShader.h"
#include "RTRS_TexturedModel.h"

namespace RTRS
{
	class GaussShader2 : public IShader
	{
	public:
		static GaussShader2*	GetInstance();

		void	Render(RTRS::TexturedModel* pTexturedModel);

	protected:

		GaussShader2();
		~GaussShader2();

		void ItlInitialize();

		static GaussShader2*	m_pInstance;

		GLuint	m_glntColorTextureLoc;
		GLuint	m_glnfPixelOffsetLoc;
	};
};

#endif //_RTRS_GAUSSSHADER2_H_