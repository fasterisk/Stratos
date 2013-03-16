#ifndef _RTRS_COLORSHADER_H_
#define _RTRS_COLORSHADER_H_

#include "RTRS_IShader.h"
#include "RTRS_IModel.h"

namespace RTRS
{
	class ColorShader : public IShader
	{
	public:
		static ColorShader*	GetInstance();

		void	Render(RTRS::IModel* pModel, glm::mat4 m4ViewProjection);

	protected:

		ColorShader();
		~ColorShader();

		void ItlInitialize();

		static ColorShader*	m_pInstance;

		GLuint	m_glnm4MVPLoc;
		GLuint	m_glnv3ColorLoc;
	};
};

#endif //_RTRS_COLORSHADER_H_