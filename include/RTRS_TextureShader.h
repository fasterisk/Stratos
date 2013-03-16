#ifndef _RTRS_TEXTURESHADER_H_
#define _RTRS_TEXTURESHADER_H_

#include "RTRS_IShader.h"
#include "RTRS_TexturedModel.h"

namespace RTRS
{
	class TextureShader : public IShader
	{
	public:
		static TextureShader*	GetInstance();

		void	Render(RTRS::TexturedModel* pTexturedModel, GLuint glnShadowMap, glm::mat4 m4Shadow, glm::mat4 m4ViewProjection, glm::mat4 m4View, glm::vec3 v3LightPosition, glm::vec3 v3CameraPosition);

	protected:

		TextureShader();
		~TextureShader();

		void ItlInitialize();

		static TextureShader*	m_pInstance;

		GLuint	m_glnm4MVPLoc;
		GLuint	m_glnm4MVLoc;
		GLuint	m_glnm4ShadowMatrixLoc;
		GLuint	m_glnm3NormalMatrixLoc;
		GLuint	m_glnv3LightPositionLoc;
		GLuint	m_glnv3CameraPositionLoc;
		GLuint	m_glntColorTextureLoc;
		GLuint	m_glntSpecularTextureLoc;
		GLuint	m_glntShadowMapLoc;
	};
};

#endif //_RTRS_TEXTURESHADER_H_