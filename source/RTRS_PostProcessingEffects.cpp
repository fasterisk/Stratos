#include "RTRS_PostProcessingEffects.h"
#include "RTRS_SimpleTextureShader.h"
#include "RTRS_BrightPassShader.h"
#include "RTRS_GaussShader1.h"
#include "RTRS_GaussShader2.h"
#include "RTRS_BlendingShader.h"
#include "RTRS_LensFlareShader.h"
#include "RTRS_ObjectManager.h"

RTRS::PostProcessingEffects* RTRS::PostProcessingEffects::m_pInstance = 0;

/**************************************************************************************************
 **************************************************************************************************/
RTRS::PostProcessingEffects*	RTRS::PostProcessingEffects::GetInstance()
{
	if(m_pInstance == 0)
		m_pInstance = new RTRS::PostProcessingEffects();

	return m_pInstance;
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::PostProcessingEffects::BeginPreparePostProcessing()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBuffer);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	GLenum gleBuffers[] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT };
	glDrawBuffers(2, gleBuffers);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_bLensFlareRendered = false;
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::PostProcessingEffects::EndPreparePostProcessing()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::PostProcessingEffects::RenderLensflares(glm::mat4 m4ViewProjection)
{
	glm::vec3 v3SunPosition = ObjectManager::GetInstance()->GetLightPosition();

	glm::vec4 v4SunPositionScreenSpace = m4ViewProjection * glm::vec4(v3SunPosition.x, v3SunPosition.y, v3SunPosition.z, 1.0f);
	glm::vec4 v4SunPositionScreenSpaceH = v4SunPositionScreenSpace;
	v4SunPositionScreenSpaceH.x /= v4SunPositionScreenSpaceH.w;
	v4SunPositionScreenSpaceH.y /= v4SunPositionScreenSpaceH.w;
	v4SunPositionScreenSpaceH.z /= v4SunPositionScreenSpaceH.w;
	v4SunPositionScreenSpaceH.w = 1.0f;


	if(v4SunPositionScreenSpaceH.x < 1.0f && v4SunPositionScreenSpaceH.x > -1.0f &&
		v4SunPositionScreenSpaceH.y < 1.0f && v4SunPositionScreenSpaceH.y > -1.0f &&
		v4SunPositionScreenSpace.z > 0.0f)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBufferLensFlare);
		glBindRenderbuffer(GL_FRAMEBUFFER, m_glnRenderBufferLensFlare);
		
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLenum gleBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, gleBuffers);

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

		//render scene into lens flare texture
		m_pScreenQuad->SetTexture(m_glnBlendingTexture, TextureManager::TEXTURETYPE::COLOR);

		SimpleTextureShader::GetInstance()->Render(m_pScreenQuad, glm::mat4());

		//render SUN
		glClear(GL_DEPTH_BUFFER_BIT);
		glm::vec2 v2LensFlarePositionScreenSpace = glm::vec2(v4SunPositionScreenSpaceH.x, v4SunPositionScreenSpaceH.y);
		LensFlareShader::GetInstance()->Render(m_pScreenQuad, v4SunPositionScreenSpaceH, v2LensFlarePositionScreenSpace, 1.0f, glm::vec4(1.0f), TextureManager::GetInstance()->GetTextureByName("sun", TextureManager::TEXTURETYPE::COLOR), m_glnScreenDepthTexture);

		//LENS FLARE 1
		glClear(GL_DEPTH_BUFFER_BIT);
		v2LensFlarePositionScreenSpace = glm::vec2(v4SunPositionScreenSpaceH.x*0.5f, v4SunPositionScreenSpaceH.y*0.5f);
		LensFlareShader::GetInstance()->Render(m_pScreenQuad, v4SunPositionScreenSpaceH, v2LensFlarePositionScreenSpace, 0.20f, glm::vec4(0.4f, 0.4f, 0.1f, 1.0f), TextureManager::GetInstance()->GetTextureByName("lensflare1", TextureManager::TEXTURETYPE::COLOR), m_glnScreenDepthTexture);

		//LENS FLARE 2
		glClear(GL_DEPTH_BUFFER_BIT);
		v2LensFlarePositionScreenSpace = glm::vec2(v4SunPositionScreenSpaceH.x*0.3f, v4SunPositionScreenSpaceH.y*0.3f);
		LensFlareShader::GetInstance()->Render(m_pScreenQuad, v4SunPositionScreenSpaceH, v2LensFlarePositionScreenSpace, 0.05f, glm::vec4(0.4f, 0.4f, 0.4f, 1.0f), TextureManager::GetInstance()->GetTextureByName("lensflare2", TextureManager::TEXTURETYPE::COLOR), m_glnScreenDepthTexture);

		//LENS FLARE 3
		glClear(GL_DEPTH_BUFFER_BIT);
		v2LensFlarePositionScreenSpace = glm::vec2(v4SunPositionScreenSpaceH.x*0.2f, v4SunPositionScreenSpaceH.y*0.2f);
		LensFlareShader::GetInstance()->Render(m_pScreenQuad, v4SunPositionScreenSpaceH, v2LensFlarePositionScreenSpace, 0.10f, glm::vec4(0.3f, 0.4f, 0.1f, 1.0f), TextureManager::GetInstance()->GetTextureByName("lensflare3", TextureManager::TEXTURETYPE::COLOR), m_glnScreenDepthTexture);

		//LENS FLARE 4
		glClear(GL_DEPTH_BUFFER_BIT);
		v2LensFlarePositionScreenSpace = glm::vec2(-v4SunPositionScreenSpaceH.x*0.3f, -v4SunPositionScreenSpaceH.y*0.3f);
		LensFlareShader::GetInstance()->Render(m_pScreenQuad, v4SunPositionScreenSpaceH, v2LensFlarePositionScreenSpace, 0.15f, glm::vec4(0.3f, 0.3f, 0.35f, 1.0f), TextureManager::GetInstance()->GetTextureByName("lensflare1", TextureManager::TEXTURETYPE::COLOR), m_glnScreenDepthTexture);
		
		//LENS FLARE 5
		glClear(GL_DEPTH_BUFFER_BIT);
		v2LensFlarePositionScreenSpace = glm::vec2(-v4SunPositionScreenSpaceH.x*0.5f, -v4SunPositionScreenSpaceH.y*0.5f);
		LensFlareShader::GetInstance()->Render(m_pScreenQuad, v4SunPositionScreenSpaceH, v2LensFlarePositionScreenSpace, 0.05f, glm::vec4(0.4f, 0.25f, 0.1f, 1.0f), TextureManager::GetInstance()->GetTextureByName("lensflare2", TextureManager::TEXTURETYPE::COLOR), m_glnScreenDepthTexture);

		//LENS FLARE 6
		glClear(GL_DEPTH_BUFFER_BIT);
		v2LensFlarePositionScreenSpace = glm::vec2(-v4SunPositionScreenSpaceH.x*0.8f, -v4SunPositionScreenSpaceH.y*0.8f);
		LensFlareShader::GetInstance()->Render(m_pScreenQuad, v4SunPositionScreenSpaceH, v2LensFlarePositionScreenSpace, 0.20f, glm::vec4(0.4f, 0.4f, 0.4f, 1.0f), TextureManager::GetInstance()->GetTextureByName("lensflare3", TextureManager::TEXTURETYPE::COLOR), m_glnScreenDepthTexture);

		//LENS FLARE 7
		glClear(GL_DEPTH_BUFFER_BIT);
		v2LensFlarePositionScreenSpace = glm::vec2(-v4SunPositionScreenSpaceH.x, -v4SunPositionScreenSpaceH.y);
		LensFlareShader::GetInstance()->Render(m_pScreenQuad, v4SunPositionScreenSpaceH, v2LensFlarePositionScreenSpace, 0.10f, glm::vec4(0.4f, 0.4f, 0.0f, 1.0f), TextureManager::GetInstance()->GetTextureByName("lensflare2", TextureManager::TEXTURETYPE::COLOR), m_glnScreenDepthTexture);

		//LENS FLARE 8
		glClear(GL_DEPTH_BUFFER_BIT);
		v2LensFlarePositionScreenSpace = glm::vec2(-v4SunPositionScreenSpaceH.x*2.0f, -v4SunPositionScreenSpaceH.y*2.0f);
		LensFlareShader::GetInstance()->Render(m_pScreenQuad, v4SunPositionScreenSpaceH, v2LensFlarePositionScreenSpace, 0.15f, glm::vec4(0.4f, 0.35f, 0.30f, 1.0f), TextureManager::GetInstance()->GetTextureByName("lensflare3", TextureManager::TEXTURETYPE::COLOR), m_glnScreenDepthTexture);

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glDisable(GL_BLEND);

		m_bLensFlareRendered = true;
	}
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::PostProcessingEffects::RenderBloom()
{
	//DOWNSIZE
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBufferDownsized);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glnRenderBufferDownsized);

	glViewport(0, 0, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);

	GLenum gleBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, gleBuffers);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_pScreenQuad->SetTexture(m_glnScreenTexture);

	SimpleTextureShader::GetInstance()->Render(m_pScreenQuad, glm::mat4());

	//BRIGHTPASS
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBufferBrightPass);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glnRenderBufferBrightPass);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_pScreenQuad->SetTexture(m_glnDownSizedTexture);

	BrightPassShader::GetInstance()->Render(m_pScreenQuad);

	//GAUSS PASS X
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBufferGaussPass1);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glnRenderBufferGaussPass1);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_pScreenQuad->SetTexture(m_glnBrightPassTexture);

	GaussShader1::GetInstance()->Render(m_pScreenQuad);

	//GAUSS PASS Y
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBufferGaussPass2);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glnRenderBufferGaussPass2);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_pScreenQuad->SetTexture(m_glnGaussPass1Texture);

	GaussShader2::GetInstance()->Render(m_pScreenQuad);

	//BLENDING
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBufferBlending);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glnFrameBufferBlending);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_pScreenQuad->SetTexture(m_glnScreenTexture, TextureManager::TEXTURETYPE::COLOR);
	m_pScreenQuad->SetTexture(m_glnGaussPass2Texture, TextureManager::TEXTURETYPE::NORMAL);

	BlendingShader::GetInstance()->Render(m_pScreenQuad);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

}


/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::PostProcessingEffects::RenderToScreen()
{
	if(m_bLensFlareRendered)
		m_pScreenQuad->SetTexture(m_glnLensFlareTexture);
	else
		m_pScreenQuad->SetTexture(m_glnBlendingTexture);

	SimpleTextureShader::GetInstance()->Render(m_pScreenQuad, glm::mat4());
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::PostProcessingEffects::PostProcessingEffects()
{
	ItlInitialize();
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::PostProcessingEffects::~PostProcessingEffects()
{
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::PostProcessingEffects::ItlInitialize()
{
	m_pScreenQuad = new TexturedModel();
	m_pScreenQuad->LoadMesh("resources/models/screenquad.obj");
	

	//initialize screen texture and framebuffer (S)
	glGenTextures(1, &m_glnScreenTexture);
	glBindTexture(GL_TEXTURE_2D, m_glnScreenTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);


	glGenTextures(1, &m_glnScreenDepthTexture);
	glBindTexture(GL_TEXTURE_2D, m_glnScreenDepthTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glGenFramebuffers(1, &m_glnFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glnScreenTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_glnScreenDepthTexture, 0);
	
	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//initialize downsized framebuffer and texture (S')
	glGenTextures(1, &m_glnDownSizedTexture);
	glBindTexture(GL_TEXTURE_2D, m_glnDownSizedTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);

	glGenRenderbuffers(1, &m_glnRenderBufferDownsized);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glnRenderBufferDownsized);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);

	glGenFramebuffers(1, &m_glnFrameBufferDownsized);
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBufferDownsized);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glnDownSizedTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_glnRenderBufferDownsized);

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//initialize bright pass framebuffer and texture (B')
	glGenTextures(1, &m_glnBrightPassTexture);
	glBindTexture(GL_TEXTURE_2D, m_glnBrightPassTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);

	glGenRenderbuffers(1, &m_glnRenderBufferBrightPass);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glnRenderBufferBrightPass);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);

	glGenFramebuffers(1, &m_glnFrameBufferBrightPass);
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBufferBrightPass);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glnBrightPassTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_glnRenderBufferBrightPass);

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//initialize gauss pass framebuffer and texture 1
	glGenTextures(1, &m_glnGaussPass1Texture);
	glBindTexture(GL_TEXTURE_2D, m_glnGaussPass1Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);

	glGenRenderbuffers(1, &m_glnRenderBufferGaussPass1);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glnRenderBufferGaussPass1);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);

	glGenFramebuffers(1, &m_glnFrameBufferGaussPass1);
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBufferGaussPass1);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glnGaussPass1Texture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_glnRenderBufferGaussPass1);

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//initialize gauss pass framebuffer and texture 2 (G')
	glGenTextures(1, &m_glnGaussPass2Texture);
	glBindTexture(GL_TEXTURE_2D, m_glnGaussPass2Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);

	glGenRenderbuffers(1, &m_glnRenderBufferGaussPass2);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glnRenderBufferGaussPass2);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);

	glGenFramebuffers(1, &m_glnFrameBufferGaussPass2);
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBufferGaussPass2);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glnGaussPass2Texture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_glnRenderBufferGaussPass2);

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//initialize blending framebuffer and texture
	glGenTextures(1, &m_glnBlendingTexture);
	glBindTexture(GL_TEXTURE_2D, m_glnBlendingTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);

	glGenRenderbuffers(1, &m_glnRenderBufferBlending);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glnRenderBufferBlending);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, SCREEN_WIDTH, SCREEN_HEIGHT);

	glGenFramebuffers(1, &m_glnFrameBufferBlending);
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBufferBlending);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glnBlendingTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_glnRenderBufferBlending);

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//initialize lens flare framebuffer and texture
	glGenTextures(1, &m_glnLensFlareTexture);
	glBindTexture(GL_TEXTURE_2D, m_glnLensFlareTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);

	glGenRenderbuffers(1, &m_glnRenderBufferLensFlare);
	glBindRenderbuffer(GL_RENDERBUFFER, m_glnRenderBufferLensFlare);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, SCREEN_WIDTH, SCREEN_HEIGHT);

	glGenFramebuffers(1, &m_glnFrameBufferLensFlare);
	glBindFramebuffer(GL_FRAMEBUFFER, m_glnFrameBufferLensFlare);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glnLensFlareTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_glnRenderBufferLensFlare);

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}