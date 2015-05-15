/*************************************************************************
	> File Name: Task.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 06:46:15 AM PDT
 ************************************************************************/
#pragma once

#include "MyResult.h"
#include <string>
#include <netinet/in.h>
#include <vector>
#include <queue>

namespace wd
{
class Task
{
public:
	Task(MyConf& conf);
	void excute(MyCache& cache);
	void satistic(set<int>& iset);
	int editdistance(const string& right);
	void get_result();
private:
	std::string express_;
	struct sockaddr_in addr_;
	int fd_;
	std::vector<pair<std::string,int> >* vec_;
	std::map<std::string, set<int> >* index_;
	std::priority_queue<MyResult, vector<MyResult> ,MyCompare> result_;
};
}
