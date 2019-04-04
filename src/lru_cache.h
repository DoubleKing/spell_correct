/*************************************************************************
	> File Name: Cache.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Mon 18 May 2015 02:18:16 AM PDT
 ************************************************************************/
	
#ifndef __CACHE_H__
#define __CACHE_H__
	 
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <iostream>
#include <map>
#include <time.h>

using namespace std;

namespace wd
{

template<class T1, class T2>
class LRUCache
{
public:
	struct cache_data
	{
		time_t begin_time;
		time_t update_time;
		int expire_time;
		int count;
		T2 data;
	};

	LRUCache();
	~LRUCache();
	bool init(int max_cache_size);
	bool get(const T1& key, T2& data);
	bool set(const T1& key, const T2& data, const int& expire_time = -1);
	bool remove(const T1& key);
	int lru_expire();
	int get_avg_expire_time();

private:
	bool lru_remove();
	static void* expire_thread(void *args)
	{
		LRUCache *p_instance = (LRUCache *)args;
		for(;;)
		{
			sleep(abs(p_instance->get_avg_expire_time()/2));
			p_instance->lru_expire();
		}
		return NULL;
	}

private:
	int m_max_size;
	int m_avg_expire_time;
	map<T1, cache_data> m_cache_map;
	std::mutex m_mutex;
};

template<class T1, class T2>
LRUCache<T1,T2>::LRUCache()
{
	m_max_size = 0;
	m_avg_expire_time = 0;
}

template<class T1, class T2>
LRUCache<T1,T2>::~LRUCache()
{
}

template<class T1, class T2>
bool LRUCache<T1,T2>::init(int max_cache_size)
{
	m_max_size = max_cache_size;
	std::thread thd(expire_thread, this);
	thd.detach();
	return true;
}

template<class T1, class T2>
bool LRUCache<T1,T2>::get(const T1& key, T2& data)
{
	std::lock_guard<std::mutex> guard(m_mutex);

	typename map<T1, cache_data>::iterator it = m_cache_map.find(key);
	if(it == m_cache_map.end())
	{
		return false;
	}
	data = it->second.data;
	it->second.count++;
	it->second.update_time = time(NULL);
	return true;
}

template<class T1, class T2>
bool LRUCache<T1,T2>::set(const T1& key, const T2& data, const int& expire_time)
{
	cache_data new_data;
	new_data.count = 0;
	new_data.expire_time = expire_time;
	new_data.begin_time = time(NULL);
	new_data.update_time = new_data.begin_time;
	new_data.data = data;
	std::lock_guard<std::mutex> guard(m_mutex);
	if(m_cache_map.size() >= m_max_size)
	{
		lru_remove();
	}
	m_cache_map.insert(pair<T1, cache_data>(key, new_data));
	return true;
}

template<class T1, class T2>
bool LRUCache<T1,T2>::remove(const T1& key)
{
	std::lock_guard<std::mutex> guard(m_mutex);
	if(m_cache_map.find(key) != m_cache_map.end())
	{
		m_cache_map.erase(key);
		return true;
	}
	return false;
}

//外部互斥
template<class T1, class T2>
bool LRUCache<T1,T2>::lru_remove()
{
	typename map<T1, cache_data>::iterator lru_it = m_cache_map.begin();
	typename map<T1, cache_data>::iterator it = m_cache_map.begin();
	if(it == m_cache_map.end())
	{
		return false;
	}

	size_t weight = it->second.count + it->second.update_time;
	for(++it; it != m_cache_map.end(); ++it)
	{
		if(it->second.count + it->second.update_time < weight)
		{
			weight = it->second.count + it->second.update_time;
			lru_it = it;
		}
	}
	m_cache_map.erase(lru_it);
	return true;
}

template<class T1, class T2>
int LRUCache<T1,T2>::lru_expire()
{
	int count = 0;
	long long sum = 0;
	std::lock_guard<std::mutex> guard(m_mutex);
	for(typename map<T1, cache_data>::iterator it = m_cache_map.begin();
		it != m_cache_map.end();)
	{
		sum += it->second.expire_time;
		if(it->second.expire_time >= 0
		   && time(NULL) - it->second.update_time >= it->second.expire_time)
		{
			m_cache_map.erase(it++);
			++count;
		}
		else
		{
			++it;
		}
	}

	if(!m_cache_map.empty())
	{
		m_avg_expire_time = sum / m_cache_map.size();
	}

	return count;
}

template<class T1, class T2>
int LRUCache<T1,T2>::get_avg_expire_time()
{
	std::lock_guard<std::mutex> guard(m_mutex);
	int avg_expire_time = m_avg_expire_time;
	return avg_expire_time;
}

}
#endif
