/*************************************************************************
	> File Name: MyDic.cc
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 07:53:46 PM PDT
 ************************************************************************/
#include "MyDic.h"
extern char g_szWorkPath[];
namespace wd
{
MyDic::MyDic(const MyConf& conf)
{
	std::string dicPath = g_szWorkPath + conf.conf_.find("mydic")->second;

	//std::cout<<dicPath<<std::endl;
	//读字典文件并放到vec_里
	std::string tmp;
	std::ifstream fin;
	fin.open(dicPath);
	while(std::getline(fin,tmp))
	{
		std::istringstream line(tmp);
		std::string word;
		int frequence;
		line>>word;
		line>>frequence;
		dic_.push_back(std::make_pair(word,frequence));
	}
	//根据vector_建立索引
	int i = 0;
	while (i <(int) dic_.size())
	{
		iToIndex(i,index_);
		i++;
	}
}
void MyDic::iToIndex(int &i, std::map<std::string,std::set<int> >& map)
{
	std::string str = dic_[i].first;
	for(size_t index = 0; index != dic_[i].first.size();)
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

void MyDic::show_dic()
{

	for(auto w: dic_)
		std::cout << w.first <<" "
			<< w.second << std::endl;

}
void MyDic::show_index()
{
	for(auto w: index_)
	{
		std::cout << w.first << " {";
		for(auto a : w.second)
			std::cout << a <<",";
		std::cout << "}" <<std::endl;
	}

}
}

