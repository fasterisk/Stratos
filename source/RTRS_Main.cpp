#include "RTRS_Common_includes.h"
#include "RTRS_TextureManager.h"
#include "RTRS_ObjectManager.h"

#include "RTRS_Scene.h"

int main()
{
	RTRS::Logger stLogger("RTRSMain.cpp");
	
	//initialize GLFW
	stLogger.debug() << "Initializing GLFW" << stLogger.endl();
	int iOk = glfwInit();
	assert(iOk != GL_FALSE);

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	
	iOk = glfwOpenWindow(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);
	assert(iOk);

	int iOpenGLMajor = glfwGetWindowParam(GLFW_OPENGL_VERSION_MAJOR);
	int iOpenGLMinor = glfwGetWindowParam(GLFW_OPENGL_VERSION_MINOR);

	std::stringstream ssWindowTitle;
	ssWindowTitle << "STRATOS - OpenGL version " << iOpenGLMajor << "." << iOpenGLMinor;
	glfwSetWindowTitle(ssWindowTitle.str().c_str());

	//initialize GLEW
	stLogger.debug() << "Initializing GLEW" << stLogger.endl();

	glewExperimental = true;

	GLenum gleError = glewInit();
	assert(gleError == GLEW_OK);

	//catch the GL_INVALID_ENUM error that appears at glewInit()
	gleError = glGetError();

	glfwDisable(GLFW_MOUSE_CURSOR);

	//initialize the texturemanager singleton
	RTRS::TextureManager::GetInstance();
	RTRS::ObjectManager::GetInstance();


	RTRS::Scene stScene;

	//the time of the last frame
	double dLastTime = glfwGetTime();

	//LOOP
	while(true)
	{
		double dCurrentTime = glfwGetTime();
		double dDelta = dCurrentTime - dLastTime;
		dLastTime = dCurrentTime;

		if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
			break;

		stScene.Render(dDelta);

		glfwSwapBuffers();
	}

	
}