#pragma once

#include <string>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/syscall.h>

namespace wd
{
#define LOG_MAX_LEN 1024

class Logger
{
public:
	bool init(int intLevel, std::string strLogFilePath="");
	void addLog(int level, const char * module, const char *fmt, ...);
private:
	int	  m_intLogLevel;
	FILE* m_fp;	
};

}