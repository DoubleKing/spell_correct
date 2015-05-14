/*************************************************************************
	> File Name: MyConf.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Wed 13 May 2015 12:57:59 AM PDT
 ************************************************************************/
#pragma once

#include <map>
#include <vector>
#include <utility>
#include <string>
#include <set>
#include <iostream>
namespace wd
{
class MyConf 
{
public:
	MyConf(const std::string& name);

	void indexToMap(int &i, std::map<std::string ,set<int> > &map_);
	std::map<std::string, std::string> & getMap();
private:
	std::map< std::string, std::string > map_;//存放配置文件内容
	std::vector< std::pair< std::string, int > > vec_;//存放字典文件内容
	std::map< std::string, std::set<int> > index_;//索引
	std::ifstream fin_;
};
}
