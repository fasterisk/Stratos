#ifndef _RTRS_ISHADER_H_
#define _RTRS_ISHADER_H_

#include "RTRS_Common_includes.h"
#include "RTRS_IModel.h"
#include <map>

namespace RTRS
{
	class IShader
	{
	public:

		IShader();
		~IShader();

	protected:

		bool	ItlLoadShaders(const char* pcVertexShaderFileName, const char* pcFragmentShaderFileName);
		
		std::string	ItlLoadShaderFromFile(const char* pcShaderFileName);
		
		void		ItlPrintErrorLog(GLuint glnShaderObject);

		Logger*		m_pLogger;

		GLuint		m_glnVertexShader;
		GLuint		m_glnFragmentShader;
		GLuint		m_glnShaderProgram;
	};
};

#endif //_RTRS_ISHADER_H_