/*************************************************************************
	> File Name: testmain.cc
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 07:18:34 PM PDT
 ************************************************************************/
#include "MyConf.h"
#include "MyDic.h"
#include<iostream>

int main()
{
	wd::MyConf conf("./conf/conf.txt");
	//conf.conf_show();
	wd::MyDic dic(conf);
	dic.show_dic();
	dic.show_index();
	return 0;
}
