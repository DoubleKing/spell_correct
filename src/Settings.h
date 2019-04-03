/*************************************************************************
	> File Name: MyConf.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 07:06:59 PM PDT
 ************************************************************************/
#pragma once

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

namespace wd
{
struct SocketSetting
{
	std::string	m_strIP;
	int			m_intPort;
};
class SettingData
{
public:
	SocketSetting	m_SocketSetting;
	std::string		m_strDataPath;
	std::string		m_strLogPath;
	int				m_intLogLevel;	
public:
	//SettingData(std::string strFilePat);
	int LoadSetting(std::string strFilePath);
};
}
