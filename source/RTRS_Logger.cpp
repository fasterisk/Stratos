#include "RTRS_Logger.h"

#include <iostream>


/**************************************************************************************************
 **************************************************************************************************/
RTRS::Logger::Logger(const char* pName)
{
	m_pName = pName;
	m_eLevel = LOGGER_LEVEL_DEBUG;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::Logger::~Logger()
{}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::Logger& RTRS::Logger::operator<<(const char* pText)
{
	if(m_eLevel == LOGGER_LEVEL_DEBUG || LOGGER_LEVEL_INFO)
		std::cout << pText;
	else if(m_eLevel == LOGGER_LEVEL_ERROR)
		std::cerr << pText;

	return *this;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::Logger& RTRS::Logger::operator<<(const int iValue)
{
	if(m_eLevel == LOGGER_LEVEL_DEBUG || LOGGER_LEVEL_INFO)
		std::cout << iValue;
	else if(m_eLevel == LOGGER_LEVEL_ERROR)
		std::cerr << iValue;

	return *this;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::Logger& RTRS::Logger::debug()
{
	m_eLevel = LOGGER_LEVEL_DEBUG;
	std::cout << "DEBUG("<< m_pName << "): ";
	return *this;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::Logger& RTRS::Logger::error()
{
	m_eLevel = LOGGER_LEVEL_ERROR;
	std::cerr << "ERROR("<< m_pName << "): ";
	return *this;
}

/**************************************************************************************************
 **************************************************************************************************/
RTRS::Logger& RTRS::Logger::info()
{
	m_eLevel = LOGGER_LEVEL_INFO;
	std::cout << "INFO("<< m_pName << "): ";
	return *this;
}

/**************************************************************************************************
 **************************************************************************************************/
const char* RTRS::Logger::endl()
{
	return "\n";
}