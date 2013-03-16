#include "RTRS_IShader.h"

#include <fstream>

/**************************************************************************************************
 **************************************************************************************************/
RTRS::IShader::IShader()
{
	m_pLogger = new Logger("IShader.cpp");
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::IShader::~IShader()
{}

/**************************************************************************************************
 **************************************************************************************************/
bool RTRS::IShader::ItlLoadShaders(const char* pcVertexShaderFileName, const char* pcFragmentShaderFileName)
{
	m_pLogger->debug() << "Loading: " << pcVertexShaderFileName << m_pLogger->endl();
	std::string sVertexShader = ItlLoadShaderFromFile(pcVertexShaderFileName);
	const char* pcVertexShader = sVertexShader.c_str();

	m_glnVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_glnVertexShader, 1, (const GLchar**)&pcVertexShader, NULL);
	glCompileShader(m_glnVertexShader);
	
	//check for a compilation error
	int iGLEWError;
	glGetShaderiv(m_glnVertexShader, GL_COMPILE_STATUS, &iGLEWError);
	if(iGLEWError == GL_FALSE)
	{
		m_pLogger->error() << "Error at compiling: " << pcVertexShaderFileName << m_pLogger->endl();
		ItlPrintErrorLog(m_glnVertexShader);
		return false;
	}

	//check for an Opengl error
	CheckForOpenGLError();

	m_pLogger->debug() << "Loading: " << pcFragmentShaderFileName << m_pLogger->endl();
	std::string sFragmentShader = ItlLoadShaderFromFile(pcFragmentShaderFileName);
	const char* pcFragmentShader = sFragmentShader.c_str();

	m_glnFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_glnFragmentShader, 1, (const GLchar**)&pcFragmentShader, NULL);
	glCompileShader(m_glnFragmentShader);

	//check for a compilation error
	glGetShaderiv(m_glnFragmentShader, GL_COMPILE_STATUS, &iGLEWError);
	if(iGLEWError == GL_FALSE)
	{
		m_pLogger->error() << "Error at compiling: " << pcVertexShaderFileName << m_pLogger->endl();
		ItlPrintErrorLog(m_glnFragmentShader);
		return false;
	}

	//check for an Opengl error
	CheckForOpenGLError();

	m_glnShaderProgram = glCreateProgram();
	glAttachShader(m_glnShaderProgram, m_glnVertexShader);
	glAttachShader(m_glnShaderProgram, m_glnFragmentShader);
	glLinkProgram(m_glnShaderProgram);

	return true;
}

/**************************************************************************************************
 **************************************************************************************************/
std::string	RTRS::IShader::ItlLoadShaderFromFile(const char* pcShaderFileName)
{
	std::fstream fsShaderFile(pcShaderFileName, std::ios::in);
	std::string sShader;

	if(fsShaderFile.is_open())
	{
		std::stringstream ssBuffer;
		ssBuffer << fsShaderFile.rdbuf();
		sShader = ssBuffer.str();
	}

	return sShader;
}

/**************************************************************************************************
 **************************************************************************************************/
void	RTRS::IShader::ItlPrintErrorLog(GLuint glnShaderObject)
{
	GLint iInfoLogLength = 0;

	if(glIsShader(glnShaderObject))
		glGetShaderiv(glnShaderObject,GL_INFO_LOG_LENGTH,&iInfoLogLength);
	else
		glGetProgramiv(glnShaderObject,GL_INFO_LOG_LENGTH,&iInfoLogLength);

	char* pcInfoLog = (char*)malloc(iInfoLogLength);

	if (glIsShader(glnShaderObject))
		glGetShaderInfoLog(glnShaderObject, iInfoLogLength, NULL, pcInfoLog);
	else
		glGetProgramInfoLog(glnShaderObject, iInfoLogLength, NULL, pcInfoLog);

	if (iInfoLogLength > 0)
	{
		m_pLogger->error() << pcInfoLog << m_pLogger->endl();
	}
	
	free(pcInfoLog);
}