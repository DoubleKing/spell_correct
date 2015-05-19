/*************************************************************************
	> File Name: Task.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 06:46:15 AM PDT
 ************************************************************************/
#pragma once

#include <queue>
#include <set>
#include <string>
namespace wd
{
class Cache;
class Mydic;

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
		if(left.dist_ > right.dist_)
			return true
		else if (left.dist_ == right.dist_ && 
				left.frequence_ > right.frequence_)
			return true;
		else if (left.dist_ == right.dist_ && 
				left.frequence_ ==  right.frequence_ &&
				left.word_ > right.word_)
			return true;
		else
			return false;
	}
};
class Task
{
public:
	Task(const std::string &expr ,int sockfd , MyDic &mydic);
	Task(const char*expr, int sockfd , MyDic &mydic);

	void excute(/*MyCache& cache*/);
private:
	void query_idx_table();
	void satistic(set<int>& iset);
	int distance(const std::string& right);
	void response(/*Cache &cache*/);
private:
	std::string expr_;
	int sockfd_;
	MyDic &mydic_;
	std::priority_queue<MyResult, vector<MyResult> ,MyCompare> que_res_;
};
}
