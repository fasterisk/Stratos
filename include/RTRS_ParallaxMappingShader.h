#ifndef _RTRS_PARALLAXMAPPINGSHADER_H_
#define _RTRS_PARALLAXMAPPINGSHADER_H_

#include "RTRS_IShader.h"
#include "RTRS_TexturedModel.h"

namespace RTRS
{
	class ParallaxMappingShader : public IShader
	{
	public:
		static ParallaxMappingShader*	GetInstance();

		void	Render(RTRS::TexturedModel* pTexturedModel, GLuint glnShadowMap, glm::mat4 m4Shadow, glm::mat4 m4ViewProjection, glm::mat4 m4View, glm::vec3 v3LightPosition, glm::vec3 v3CameraPosition);

	protected:

		ParallaxMappingShader();
		~ParallaxMappingShader();

		void ItlInitialize();

		static ParallaxMappingShader*	m_pInstance;

		GLuint	m_glnm4MVPLoc;
		GLuint	m_glnm4MVLoc;
		GLuint	m_glnm4VLoc;
		GLuint	m_glnm4ShadowMatrixLoc;

		GLuint	m_glnm3NormalMatrixLoc;

		GLuint	m_glnv3LightPositionLoc;
		GLuint	m_glnv3CameraPositionLoc;

		GLuint	m_glntColorTextureLoc;
		GLuint	m_glntSpecularTextureLoc;
		GLuint	m_glntShadowMapLoc;
		GLuint	m_glntNormalMapLoc;
		GLuint	m_glntBumpMapLoc;
	};
};

#endif //_RTRS_PARALLAXMAPPINGSHADER_H_