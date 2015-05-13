/*************************************************************************
	> File Name: NonCopyable.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Fri 08 May 2015 12:44:50 AM PDT
 ************************************************************************/
#pragma once
namespace wd{

class NonCopyable
{
protected:
	NonCopyable(){}
	~NonCopyable(){}
private:
	NonCopyable(const NonCopyable&);
	NonCopyable& operator=( const NonCopyable& );
};

}
