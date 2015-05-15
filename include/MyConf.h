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
struct MyConf
{
	std::map<std::string, std::string> conf_;
	MyConf(const std::string& conf_path);
	void conf_show();
};
}
