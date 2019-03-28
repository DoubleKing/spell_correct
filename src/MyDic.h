/*************************************************************************
	> File Name: MyDic.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 07:42:48 PM PDT
 ************************************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>

namespace wd
{
struct MyDic
{
	MyDic(const std::string& strFilePath);
	void iToIndex(int &i , std::map<std::string, std::set<int> > &map);
	void show_dic();
	void show_index();

	std::vector<std::pair<std::string ,int> > dic_;//词典
	std::map<std::string ,std::set<int> > index_;//索引

};
}

