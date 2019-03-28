/*************************************************************************
	> File Name: Cache.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Mon 18 May 2015 02:18:16 AM PDT
 ************************************************************************/
#pragma once

#include "MutexLock.h"
#include <map>
#include <string>

namespace wd
{
class Cache
{
public:
	Cache(const int num = 100);
	Cache(const Cache &cache);

	void map_to_cache(std::string &key, std::string &value);
	std::string query_cache(const std::string &word);
	void write_to_file(std::ofstream &fout);
	void read_from_file(const std::string &filename);
	void add_elements(const Cache &cache);
private:
	std::unorder_map<std::string, std::string> cachemap_;
	MutexLock mutex_;
};
}
