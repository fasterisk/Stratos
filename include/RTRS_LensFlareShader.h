#ifndef _RTRS_LENSFLARESHADER_H_
#define _RTRS_LENSFLARESHADER_H_

#include "RTRS_IShader.h"
#include "RTRS_TexturedModel.h"

namespace RTRS
{
	class LensFlareShader : public IShader
	{
	public:
		static LensFlareShader*	GetInstance();

		void	Render(RTRS::TexturedModel* pTexturedModel, glm::vec4 v4SunPositionInScreenSpace, glm::vec2 v2LensFlarePositionScreenSpace, float fLensFlareScale, glm::vec4 v4LensFlareColor, GLuint glnLensFlareTexture, GLuint glnDepthTexture);

	protected:

		LensFlareShader();
		~LensFlareShader();

		void ItlInitialize();

		static LensFlareShader*	m_pInstance;

		GLuint	m_glntLensFlareTextureLoc;
		GLuint	m_glntDepthTextureLoc;
		GLuint	m_glnv4SunPositionLoc;
		GLuint	m_glnv4LensFlareColor;
		GLuint	m_glnv2AspectLoc;
		GLuint	m_glnv2LensFlarePosition;
		GLuint	m_glnfLensFlareScale;
	};
};

#endif //_RTRS_LENSFLARESHADER_H_