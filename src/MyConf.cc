/*************************************************************************
	> File Name: MyConf.cc
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 07:12:12 PM PDT
 ************************************************************************/
#include "MyConf.h"

namespace wd
{
MyConf::MyConf(const std::string& conf_path)
{
	//读配置文件
	std::string tmp;
	std::ifstream fin;
	fin.open(conf_path);
	while(std::getline(fin,tmp))
	{
		std::istringstream line(tmp);
		std::string nname;
		std::string path;
		line>>nname;
		line>>path;
		conf_.insert(std::make_pair(nname,path));
	}
}
void MyConf::conf_show()
{
	for(const auto w : conf_)
		std::cout << w.first << " "
					<<w.second <<std::endl;
}
}
