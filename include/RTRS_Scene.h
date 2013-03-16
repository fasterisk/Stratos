#ifndef _RTRS_SCENE_H_
#define _RTRS_SCENE_H_

#include "RTRS_Common_includes.h"
#include "RTRS_Camera.h"

namespace RTRS
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Render(double dDeltaTime);

	private:
		void ItlInitialize();

		double		m_dTime;
		glm::ivec2	m_v2MousePosition;

		Camera*		m_pMovingCamera;
		Camera*		m_pAstronautCamera;

		Camera*		m_pCurrentCamera;
		
		Logger*		m_pLogger;

		int			m_iSpaceButtonBefore;
		int			m_iF1ButtonBefore;

		bool		m_bInputLocked;

		//Sound
		FMOD::System*	m_pSoundsystem;

		FMOD::Sound*	m_pBackgroundSound;
		FMOD::Sound*	m_pVaderSound;

		FMOD::Channel*	m_pBackgroundChannel;
		FMOD::Channel*	m_pVaderChannel;

	};
};

#endif //_RTRS_SCENE_H_