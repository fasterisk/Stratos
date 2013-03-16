#ifndef _RTRS_POSTPROCESSINGEFFECTS_H_
#define _RTRS_POSTPROCESSINGEFFECTS_H_

#include "RTRS_TexturedModel.h"

namespace RTRS
{
	class PostProcessingEffects {
	public:

		static	PostProcessingEffects*	GetInstance();
		

		void	BeginPreparePostProcessing();
		void	EndPreparePostProcessing();

		void	RenderLensflares(glm::mat4 v4ViewProjection);

		void	RenderBloom();

		void	RenderToScreen();

	private:

		PostProcessingEffects();
		~PostProcessingEffects();

		void	ItlInitialize();

		static PostProcessingEffects	* m_pInstance;

		bool	m_bLensFlareRendered;

		TexturedModel* m_pScreenQuad;

		GLuint	m_glnFrameBuffer;
		//GLuint	m_glnRenderBuffer;

		GLuint	m_glnScreenTexture;
		GLuint	m_glnScreenDepthTexture;

		//bloom
		GLuint	m_glnFrameBufferDownsized;
		GLuint	m_glnRenderBufferDownsized;
		GLuint	m_glnDownSizedTexture;

		GLuint	m_glnFrameBufferBrightPass;
		GLuint	m_glnRenderBufferBrightPass;
		GLuint	m_glnBrightPassTexture;

		GLuint	m_glnFrameBufferGaussPass1;
		GLuint	m_glnRenderBufferGaussPass1;
		GLuint	m_glnGaussPass1Texture;

		GLuint	m_glnFrameBufferGaussPass2;
		GLuint	m_glnRenderBufferGaussPass2;
		GLuint	m_glnGaussPass2Texture;

		GLuint	m_glnFrameBufferBlending;
		GLuint	m_glnRenderBufferBlending;
		GLuint	m_glnBlendingTexture;

		//lens flare
		GLuint	m_glnFrameBufferLensFlare;
		GLuint	m_glnRenderBufferLensFlare;
		GLuint	m_glnLensFlareTexture;

	};
};

#endif //_RTRS_POSTPROCESSINGEFFECTS_H_