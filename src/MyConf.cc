/*************************************************************************
	> File Name: MyConf.cc
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Wed 13 May 2015 06:20:30 AM PDT
 ************************************************************************/
#include "MyConf.h"
#include <string>
#include <sstream>

namespace wd
{
MyConf(const string& name)
{
	//读配置文件
	std::string tmp;
	fin_.open(name);
	while(std::getline(fin_,tmp))
	{
		std::istringstream line(tmp);
		std::string nname;
		std::string path;
		line>>nname;
		line>>path;
		map_.insert(std::make_pair(nname,path));
	}
	//读字典文件并放到vec_里
	std::istream dicIn;
	dicIn.open(map_.find("mydict").second);

	while(std::getline(dicIn,tmp));
	{
		std::istringstream line(tmp);
		std::string word;
		int frequence;
		line>>word;
		line>>frequence;
		vec_.insert(std::make_pair(word,frequence));
	}
	//根据vector_建立索引
	int i = 0;
	while (i < vec_.size())
	{
		indexToMap(i,index_);
		i++;
	}


}

void indexToMap(int &i, map<string,set<int> >& map)
{
	std::string str = vec_[i].first;
	for(size_t index = 0; index != vec_[i].first.size())
	{
		if(str[index]>0)
		{
			std::string tmp = str.substr(index,1);
			index_[tmp].insert(i);
			index++;
		}
		else if((str[index]&0xF0)==0xC0 || (str[index]&0xF0)==0xD0)
		{
			std::string tmp = str.substr(index,2);
			index_[tmp].insert(i);
			index++;
		}
		else if((str[index]&0xF0)==0xE0)
		{
			std::string tmp = str.substr(index,3);
			index_[tmp].insert(i);
			index++;
		}
		else
		{
			return ;
		}
	}
}

}
