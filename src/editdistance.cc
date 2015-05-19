/*********************************
 *@fileName: editdistance.cc
 *@author  : lemon
 *@email   : haohb13@gmail.com
 *@created : 2015-05-13 20:17:40
**********************************/

#include <iostream>
#include <string>


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


int calcDistance(const std::string &lhs, const std::string &rhs)
{
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


int main(void)
{
	std::string s1 = "我是：中国人";
	std::string s2 = "我是中国人abandon";
	
	std::cout << "s1's size = " << s1.size() << std::endl;
	std::cout << "s1's length = " << length(s1) << std::endl;
	std::cout << "s2's size = " << s2.size() << std::endl;
	std::cout << "s2's length = " << length(s2) << std::endl;
	std::cout << "s1 and s2 's distance = " << calcDistance(s1, s2) << std::endl;
#if 0
	std::string s3 = "hello";
	std::string s4 = "helxly";
	std::cout << "s3 and s4 's distance = " << calcDistance(s3, s4) << std::endl;
#endif

	return 0;
}
