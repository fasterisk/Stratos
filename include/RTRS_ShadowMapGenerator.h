#ifndef _RTRS_SHADOWMAPGENERATOR_H_
#define _RTRS_SHADOWMAPGENERATOR_H_

#include "RTRS_IModel.h"

namespace RTRS
{
	class ShadowMapGenerator
	{
	public:
		
		static	ShadowMapGenerator*	GetInstance();

		void	SetViewParameters(glm::vec3 v3LightPosition, glm::vec3 v3LightDirection);

		void	Render();

		glm::mat4	GetShadowMatrix();

		GLuint	GetShadowMap() const { return m_glnShadowMap; }
	protected:

		ShadowMapGenerator();
		~ShadowMapGenerator();

		static ShadowMapGenerator	* m_pInstance;

		void	ItlInitialize();

		GLuint					m_glnShadowMap;

		GLuint					m_glnFrameBuffer;
		GLuint					m_glnDepthBuffer;

		glm::mat4				m_m4ProjectionMatrix;
		glm::mat4				m_m4ViewProjectionMatrix;
		glm::mat4				m_m4Bias;
		glm::mat4				m_m4ShadowMatrix;
	};
};
#endif //_RTRS_SHADOWMAPGENERATOR_H_