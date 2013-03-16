#ifndef _RTRS_SIMPLETEXTURESHADER_H_
#define _RTRS_SIMPLETEXTURESHADER_H_

#include "RTRS_IShader.h"
#include "RTRS_TexturedModel.h"
#include "RTRS_Skybox.h"

namespace RTRS
{
	class SimpleTextureShader : public IShader
	{
	public:
		static SimpleTextureShader*	GetInstance();

		void	Render(RTRS::TexturedModel* pTexturedModel, glm::mat4 m4ViewProjection);
		void	Render(RTRS::Skybox* pSkybox, glm::mat4 m4ViewProjection);

	protected:

		SimpleTextureShader();
		~SimpleTextureShader();

		void ItlInitialize();

		static SimpleTextureShader*	m_pInstance;

		GLuint	m_glnm4MVPLoc;
		GLuint	m_glntColorTextureLoc;
	};
};

#endif //_RTRS_SIMPLETEXTURESHADER_H_