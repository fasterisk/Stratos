#ifndef _RTRS_OBJECTMANAGER_H_
#define _RTRS_OBJECTMANAGER_H_

#include "RTRS_Common_includes.h"
#include "RTRS_Skybox.h"
#include "RTRS_TexturedModel.h"

namespace RTRS
{
	class ObjectManager
	{
	public:

		static	ObjectManager*	GetInstance();

		void	RenderObjects(glm::mat4 m4ViewProjection, glm::mat4 m4View, glm::vec3 v3CameraPosition);
		void	RenderEnvironmentMappedObjects(glm::mat4 m4ViewProjection, glm::mat4 m4View, glm::vec3 v3CameraPosition);
		void	GenerateEnvironmentMap();
		void	GenerateShadowMap();
		void	RenderObjectsForShadowMap(glm::mat4 m4ViewProjection);

		void	MoveLightTo(float fX, float fY, float fZ);

		glm::vec3	GetLightPosition() const;
		void		MoveSkyboxTo(glm::vec3 v3NewPosition);

	private:

		ObjectManager();
		~ObjectManager();

		void	ItlInitialize();

		static ObjectManager	* m_pInstance;

		Skybox*						m_pSkybox;

		TexturedModel*				m_pAstronaut;
		TexturedModel*				m_pKapsel;
		TexturedModel*				m_pEarth;
		TexturedModel*				m_pMoon;

		IModel*						m_pLight1;

	};
};

#endif //_RTRS_OBJECTMANAGER_H_