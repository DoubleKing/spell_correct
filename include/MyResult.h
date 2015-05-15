/*************************************************************************
	> File Name: MyResult.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 07:07:18 AM PDT
 ************************************************************************/
#pragma once
#include <string>
namespace wd
{
struct MyResult
{
	std::string word_;
	int dist_;
	int frequence_;
};
class MyCompare
{
public:
	bool operator()(const MyResult &left ,const MyResult& right)
	{
		return left.dist_ < right.dist_;
	}
};
}
