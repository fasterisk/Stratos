#ifndef _RTRS_LOGGER_H_
#define _RTRS_LOGGER_H_

namespace RTRS
{
	class Logger
	{
	public:
		Logger(const char* pName);
		~Logger();

		Logger& operator<<(const char* pText);
		Logger& operator<<(const int iValue);

		Logger& debug();
		Logger& error();
		Logger& info();
		const char* endl();

	private:
		enum TItlLoggerLevel
		{
			LOGGER_LEVEL_DEBUG,
			LOGGER_LEVEL_ERROR,
			LOGGER_LEVEL_INFO
		};

		TItlLoggerLevel m_eLevel;

		const char* m_pName;
	};
};

#endif //_RTRS_LOGGER_H_