/*************************************************************************
	> File Name: Task.cc
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 07:44:05 AM PDT
 ************************************************************************/
#include <string.h>
#include "Task.h"
namespace wd
{

std::size_t nBytesCode(const char ch)
{
	std::size_t nBytes = 0;
	if(ch & (1 << 7))
	{//对中文进行处理
		if((ch & 0xF0) == 0xC0)
		{//2字节编码
			nBytes += 2;	
		}
		else if((ch & 0xF0) == 0xE0)
		{//3字节编码
			nBytes += 3;
		}
		else if((ch & 0xF0) == 0xF0)
		{//4字节编码
			nBytes += 4;
		}
		else if((ch & 0xFF) == 0xF8)
		{//5字节编码
			nBytes += 5;
		}
		else if((ch & 0xFF) == 0xFE)
		{//6字节编码
			nBytes += 6;
		}
	}
	else{//1字节编码或英文
		nBytes += 1;
	}
	return nBytes;
}


std::size_t length(const std::string &str)
{//获取字符串的长度
	std::size_t ilen = 0;
	std::size_t sz = str.size();
	for(std::size_t idx = 0; idx != sz; ++idx)
	{
		int nBytes = nBytesCode(str[idx]);
		idx += (nBytes - 1);
		++ilen;
	}
	return ilen;
}

int tripleMin(const int &a, const int &b, const int &c)
{
	return (a < b ?	(a < c ? a : c) : (b < c ? b : c));
}




Task::Task(const std::string &expr ,int sockfd ,MyDic &mydic)
	:expr_(expr),
	 sockfd_(sockfd),
	 mydic_(mydic)
	{}

void Task:: execute()
{
	std::cout << "Task::excute()"<<std::endl;
	query_idx_table();
	std::cout << "Task::quer_inx_table()  ended"<<std::endl;
	
	response();
}
void Task::response()
{
	if(!que_res_.empty())
	{
		//std::cout << "Task::response" <<std::endl;
		MyResult tmp = que_res_.top();
		send(sockfd_,tmp.word_.c_str(),tmp.word_.size(),0);
	}
	else
	{
		//std::cout << "Task::response" <<std::endl;
		char buf[]="not found!!";
		send(sockfd_,buf,sizeof(buf),0);
	}
}


int Task::distance( const std::string &rhs)
{
//	std::cout <<"Task::distance()"<<std::endl;
	std::string lhs(expr_);
	std::size_t lhsLen = length(lhs);
	std::size_t rhsLen = length(rhs);
	
	int editDisArray[lhsLen + 1][rhsLen + 1];

	for(std::size_t idx = 0; idx <= lhsLen; ++idx)
	{
		editDisArray[idx][0] = idx;
	}

	for(std::size_t idx = 0; idx <= rhsLen; ++idx)
	{
		editDisArray[0][idx] = idx;
	}
	
	std::string sublhs, subrhs;

	for(std::size_t iIdx = 1, lhsIdx = 0; iIdx <= lhsLen; ++iIdx)
	{
		size_t nBytes = nBytesCode(lhs[lhsIdx]);
		sublhs = lhs.substr(lhsIdx, nBytes);
		lhsIdx += nBytes;

		for(std::size_t jIdx = 1, rhsIdx = 0; jIdx <= rhsLen; ++jIdx)
		{
			nBytes = nBytesCode(rhs[rhsIdx]);
			subrhs = rhs.substr(rhsIdx, nBytes);
			rhsIdx += nBytes;

			if(sublhs == subrhs)
			{
				editDisArray[iIdx][jIdx] = editDisArray[iIdx - 1][jIdx - 1];
			}
			else
			{
				editDisArray[iIdx][jIdx] = tripleMin(
					editDisArray[iIdx][jIdx -1] + 1,
					editDisArray[iIdx - 1][jIdx] + 1,
					editDisArray[iIdx - 1][jIdx - 1] + 1) ;

			}
		}
	}
	return editDisArray[lhsLen][rhsLen];
}

void Task::query_idx_table()
{
	std::cout <<expr_<<"'"<<std::endl;
	std::size_t exprlen = expr_.size();
	
		std::cout <<"exprlen:"<<exprlen<<std::endl;
	std::string subexpr;
	for(std::size_t exprIdx = 0; exprIdx < exprlen ;)
	{
		size_t nBytes = nBytesCode(expr_[exprIdx]);
		std::cout <<"exprIdx:"<<exprIdx<<"  nBytes:"<<nBytes<<std::endl;
		subexpr = expr_.substr(exprIdx,nBytes);
		std::cout << "substr "<<subexpr <<std::endl;
		exprIdx += nBytes;
		satistic(mydic_.index_.find(subexpr)->second);
		std::cout <<"Task::satistic() ended"<<std::endl;
	}
}
void Task::satistic(std::set<int> &iset)
{
	
		std::cout <<"Task::satistic()"<<std::endl;
	for(int idx : iset)
	{
		int dis = distance(mydic_.dic_[idx].first);
		if(dis < 3)
		{
			MyResult myres;
			myres.word_ = mydic_.dic_[idx].first;
			myres.dist_ = dis;
			myres.frequence_ = mydic_.dic_[idx].second;
			myres.show();
			que_res_.push(myres);
		}
	}
}
}
