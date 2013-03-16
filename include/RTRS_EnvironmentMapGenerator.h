#ifndef _RTRS_ENVIRONMENTMAPGENERATOR_H_
#define _RTRS_ENVIRONMENTMAPGENERATOR_H_

#include "RTRS_IModel.h"

namespace RTRS
{
	class EnvironmentMapGenerator
	{
	public:
		static	EnvironmentMapGenerator*	GetInstance();

		void	Render(glm::vec3 v3CameraPosition, glm::vec3 v3LightPosition);

		GLuint	GetCubeMap() const { return m_glnCubeColorMap; }
	protected:
		EnvironmentMapGenerator();
		~EnvironmentMapGenerator();

		void	ItlInitialize();

		static EnvironmentMapGenerator	* m_pInstance;

		GLuint					m_glnCubeColorMap;
		GLuint					m_glnCubeDepthMap;
		GLuint					m_glnFrameBuffer;
		GLuint					m_glnDepthBuffer;
	};
};
#endif //_RTRS_ENVIRONMENTMAPGENERATOR_H_