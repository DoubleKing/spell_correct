/*************************************************************************
	> File Name: MyDic.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 07:42:48 PM PDT
 ************************************************************************/
#pragma once
#include "MyConf.h"
#include <set>
#include <map>
#include <iostream>
#include <vector>
namespace wd
{
class MyDic
{
public:
	MyDic(const wd::MyConf& conf);
	void iToIndex(int &i , std::map<std::string, std::set<int> > &map);
	void show_dic();
	void show_index();
private:
	std::vector<std::pair<std::string ,int> > dic_;//词典
	std::map<std::string ,std::set<int> > index_;//索引

};
}

