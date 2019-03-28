#include "log.h"

namespace wd
{
bool Logger::init(int intLevel, std::string strLogFilePath)
{
	m_intLogLevel = intLevel;
	if(strLogFilePath.empty())
	{
		m_fp = stdout;
	}
	else
	{
		m_fp = fopen(strLogFilePath.c_str(), "a");
		if (!m_fp)
		{
			m_fp = stdout;
		}
	}
}

void Logger::addLog(int level, const char * module, const char *fmt, ...)
{
    va_list ap;
    char msg[LOG_MAX_LEN];
	char buf[64];

    if ((level&0xff) < m_intLogLevel) return;

    va_start(ap, fmt);
    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    if (!m_fp) return;

    int off;
    struct timeval now_timeval;
	struct tm now_tm;

    gettimeofday(&now_timeval,NULL);
	time_t now_seconds = now_timeval.tv_sec;
	localtime_r(&now_seconds, &now_tm);
    off = strftime(buf,sizeof(buf)," %Y-%m-%d %H:%M:%S.",&now_tm);
    snprintf(buf+off,sizeof(buf)-off,"%03d",(int)now_timeval.tv_usec/1000);

    fprintf(m_fp,"[%s PID=%d Level=%d][%s] [%s]\n",
        buf, (int)syscall(SYS_gettid), level, module, msg);

    fflush(m_fp);
	
}

}