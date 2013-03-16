#ifndef _RTRS_COMMON_INCLUDES_H_
#define _RTRS_COMMON_INCLUDES_H_

#include <assert.h>
#include <string>
#include <sstream>

#include "GL\glew.h"
#include "GL\glfw.h"
#include "glm/glm.hpp"
#include "RTRS_Logger.h"
#include "fmod/fmod.hpp"

#define PI 3.1415926535897932384626433832795028841971693993751058209749445

#define SCREEN_WIDTH 800//1920//1024
#define SCREEN_HEIGHT 600//1080//768

#undef glGenFramebuffers
#undef glBindFramebuffer
#undef glFramebufferTexture2D
#undef glCheckFramebufferStatus
#define glGenFramebuffers		  ((PFNGLGENFRAMEBUFFERSPROC)		 glfwGetProcAddress("glGenFramebuffers"))
#define glBindFramebuffer		  ((PFNGLBINDFRAMEBUFFERPROC)		 glfwGetProcAddress("glBindFramebuffer"))
#define glFramebufferTexture2D	  ((PFNGLFRAMEBUFFERTEXTURE2DPROC)   glfwGetProcAddress("glFramebufferTexture2D"))
#define glCheckFramebufferStatus  ((PFNGLCHECKFRAMEBUFFERSTATUSPROC) glfwGetProcAddress("glCheckFramebufferStatus"))

static RTRS::Logger g_stLogger("OPENGL");

namespace RTRS
{
	typedef struct {
			glm::vec3 v3Position;
			glm::vec2 v2TexCoords;
	} Vertex;

	static void CheckForOpenGLError()
	{
		GLenum gleError = glGetError();
		if(gleError != 0)
			g_stLogger.error() << "An OpenGL error occurred: " << gleError << g_stLogger.endl();
	}
};

#endif //_RTRS_COMMON_INCLUDES_H_