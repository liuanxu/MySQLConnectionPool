#pragma once
#include<iostream>
using namespace std;
//存储一些整个项目公共定义的一些内容
#define LOG(str) cout<<__FILE__<<":"<<__TIMESTAMP__<<":"<<str<<endl;	//用来显示日志文件，文件，行号，日期，str