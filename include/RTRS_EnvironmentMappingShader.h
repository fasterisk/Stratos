#ifndef _RTRS_ENVIRONMENTMAPPINGSHADER_H_
#define _RTRS_ENVIRONMENTMAPPINGSHADER_H_

#include "RTRS_IShader.h"
#include "RTRS_IModel.h"

namespace RTRS
{
	class EnvironmentMappingShader : public IShader
	{
	public:
		static EnvironmentMappingShader*	GetInstance();

		void	Render(RTRS::IModel* pModel, GLuint glnCubeMapTexture, glm::mat4 m4ViewProjection, glm::mat4 m4View, glm::vec3 v3LightPosition, glm::vec3 v3CameraPosition);

	protected:

		EnvironmentMappingShader();
		~EnvironmentMappingShader();

		void ItlInitialize();

		static EnvironmentMappingShader*	m_pInstance;

		GLuint	m_glnm4MVPLoc;
		GLuint	m_glnm4MVLoc;
		GLuint	m_glnm4MLoc;
		GLuint	m_glnm3NormalMatrixLoc;
		GLuint	m_glnv3LightPosLoc;
		GLuint	m_glnv3TransformedLightPosLoc;
		GLuint	m_glnv3CameraPosLoc;
		GLuint	m_glnv3TransformedCameraPosLoc;
		GLuint	m_glntCubeMapTextureLoc;
	};
};

#endif //_RTRS_ENVIRONMENTMAPPINGSHADER_H_