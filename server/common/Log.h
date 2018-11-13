/*
* Copyright (c) 2008, ZhengXujie
* All rights reserved.
*
* Name   : log.h
* Type   : CLog Header File
* Summary: Common Class
*
* Version: 1.0
* Author : Zheng Xujie
* History
* 	2008/06/18 created by zhengxujie
*
*/
#include <fstream>
#ifndef __CLOG_H
#define __CLOG_H


#define CLOG_FL   255
#define CLOG_MSGL 102400
#define MULTI_THREAD

#ifdef MULTI_THREAD

#endif

using namespace std;
class CLog
{
    private:
        char szFile[CLOG_FL];
        int outputflag;		// 0 标准输出，1 输出到文件 szFile
        int filesplit;		// 0 单个文件，1 按照日期输出文件，1天一个文件（自动在 szFile 后面加上日期".yymmdd"

				struct tm today;
				ofstream fd;

				bool fnchange;//标记文件名是否改变
        int  FormatCurrDate(char *szStr,char *strDay);
    public:
        CLog();
        CLog(char *filename,int len,int flag=1, int split=0);		// filename:日志文件名，len: filename 的长度, flag: 0 标准输出，1 输出到文件
        ~CLog();
        int SetLog(char *filename,int len,int flag=1, int split=0);
        int setOutput(int flag);
        int setSplit(int split);
        int outlog(const char* Format, ...);     //nType:1 error,2 warn,3 message
		int markoutlog(const char* mark,const char* Format,...);     //nType:1 error,2 warn,3 message
		int addlog(const char* Format,...);//往日志里添加数据，用户自己控制格式
		//写日志到指定文件 flag: 0 标准输出 1 输出到文件 ；split: 0 单个文件，1 按照日期输出文件，1天一个文件（自动在 szFile 后面加上日期".yymmdd"
		int writelogto(const char* path, const char* fname, int flag, int split, const char* Format,...);
};


#endif
