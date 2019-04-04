/*************************************************************************
	> File Name: MyConf.cc
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 07:12:12 PM PDT
 ************************************************************************/
#include "Settings.h"
#include "../tools/inifile/inifile.h"
using namespace inifile;
namespace wd
{
int SettingData::LoadSetting(std::string strFilePath)
{
	IniFile inifile;
	inifile.Load(strFilePath);
	inifile.GetStringValueOrDefault("SOCKET","ip", &(m_SocketSetting.m_strIP), "127.0.0.1");
	inifile.GetIntValueOrDefault("SOCKET","port", &(m_SocketSetting.m_intPort), 8089);
	inifile.GetStringValueOrDefault("DATA","path", &(m_strDataPath), "./data/mydic.dat");
	inifile.GetStringValueOrDefault("LOG","path", &(m_strLogPath), "");
	inifile.GetIntValueOrDefault("LOG","level", &(m_intLogLevel), 5);
}
}
