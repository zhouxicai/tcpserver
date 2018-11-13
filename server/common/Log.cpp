/*
* Copyright (c) 2008, ZhengXujie
* All rights reserved.
*
* Name   : log.cpp
* Type   : CLog Class File
* Summary: Common Class
*
* Version: 1.0
* Author : Zheng Xujie
* History
* 	2008/06/18 created by zhengxujie
*
*/
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <iostream>

//#include <io.h>
//#include <process.h>

#ifdef _WIN32
#include <io.h>
#include <process.h>
#include <stdio.h>
#include <time.h>
#include <direct.h>
#else
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#endif

#ifdef MULTI_THREAD
#include <pthread.h>
#endif

#include "Log.h"

using namespace std;

CLog::CLog() 
{
	outputflag=0;
	filesplit=0;
	fnchange=false;
}

CLog::CLog(char *filename,int len,int flag,int split) 
{
	outputflag=flag;
	filesplit=split;
	SetLog(filename,len,flag,split);

	//记下当前时间
	time_t t;
	memset(&today, 0, sizeof(today));
#ifdef _WIN32
	today = *localtime(&t);
#else
	struct tm mytm;
	today = *localtime_r(&t, &mytm);
#endif
	
}

CLog::~CLog() 
{
}

inline int  CLog::FormatCurrDate(char *szStr,char *strDay)
{
	if (szStr==NULL)
		return 1;
	time_t t;
	time(&t);

	struct tm *today2;
#ifdef _WIN32
	today2 = localtime(&t);
#else
	struct tm mytm;
	today2 = localtime_r(&t, &mytm);
#endif

	if ((today2->tm_year!=today.tm_year) ||  (today2->tm_mon!=today.tm_mon) ||  (today2->tm_mday!=today.tm_mday))
	{
		if (fd.is_open()) {fd.close();}
	}

		//更新today
		today.tm_year=today2->tm_year;
        today.tm_mon=today2->tm_mon;
		today.tm_mday=today2->tm_mday;
		//printf("today %d %d %d today2 %d %d %d\n",today.tm_year,today.tm_mon,today.tm_mday,today2->tm_year,today2->tm_mon,today2->tm_mday);
		if (filesplit==1)
		{
			strftime(szStr,20,"%H:%M:%S",today2);
		}
		else
		{
			strftime(szStr,20,"%Y-%m-%d %H:%M:%S",today2);
		}
		strftime(strDay,10,"%y%m%d",today2);

	
	return 0;
}

int CLog::SetLog(char *filename,int len,int flag,int split)
{
	if (fd.is_open()) {fnchange=true;}//置上标志，在写日志的时候清理
    outputflag=flag;
    filesplit=split;
		if (len == 0) { len = strlen(filename); }
		//处理下路径问题
		char path[1000];
		memset(path,0,sizeof(path));
		memcpy(path,filename,len);
		char* p = strrchr(path,'/');
		*p=0;
		//判断路径是否存在
		struct stat filestat;
		if (!((stat(path,&filestat) ==0) && (filestat.st_mode & S_IFDIR))) {		
#ifdef _WIN32
			_mkdir(path);
#else
			mkdir(path, S_IRWXU | S_IRGRP | S_IROTH);
#endif
		}

    memset(szFile,0,sizeof(szFile));
    if ((len>=CLOG_FL)||(len<=0))
        return -1;
    else
        strncpy(szFile,filename,sizeof(szFile) -1);
    return 0;
}

int CLog::setOutput(int flag)
{
	outputflag=flag;
	return 0;
}

int CLog::setSplit(int split)
{
	filesplit=split;
	return 0;
}

int CLog::outlog(const char* Format,...)
{
	char szBuf[CLOG_MSGL];
	char szTime[20];
	char szDate[10];
	string fn;

	memset(szBuf,0,sizeof(szBuf));
	memset(szTime,0,sizeof(szTime));
	memset(szDate,0,sizeof(szDate));

	va_list	l_va;
	va_start(l_va,Format);
	vsnprintf(szBuf,sizeof(szBuf),Format,l_va);
	va_end(l_va);

	FormatCurrDate(szTime,szDate);
	if (filesplit==1) 
	{
		fn=(string)szFile;
		fn += ".";
		fn += szDate;
	}
	else
	{
		fn=(string)szFile;
	}

	if (outputflag==0)
	{
		cout<<szTime<<","<<szBuf<<endl;
	}
	else
	{
		//ofstream fd;
		try
		{
			if ((fnchange) && (fd.is_open())) {fd.close();}//如果文件名改变，需要关闭上一个文件
			if (!fd.is_open())
			{fd.open(fn.c_str(),ios::app);}
			fd<<szTime<<","<<szBuf<<endl;
		}
		catch(...)
		{
			cerr<<"open log file exception!"<<endl;
			return -1;
		}
	}
	return 0;
}


int CLog::markoutlog(const char* mark,const char* Format,...)
{
        char szBuf[CLOG_MSGL];
        char szTime[20];
        char szDate[10];
        string fn;

        memset(szBuf,0,sizeof(szBuf));
        memset(szTime,0,sizeof(szTime));
        memset(szDate,0,sizeof(szDate));

        va_list l_va;
        va_start(l_va,Format);
        vsnprintf(szBuf,sizeof(szBuf),Format,l_va);
        va_end(l_va);

        FormatCurrDate(szTime,szDate);
        if (filesplit==1)
        {
                fn=(string)szFile;
                fn += ".";
                fn += szDate;
        }
        else
        {
                fn=(string)szFile;
        }

        if (outputflag==0)
        {
                cout<<szTime<<","<<szBuf<<endl;
        }
        else
        {
               // ofstream fd;
                try
                {
					    if ((fnchange) && (fd.is_open())) {fd.close();}//如果文件名改变，需要关闭上一个文件
                        if (!fd.is_open())
			                {fd.open(fn.c_str(),ios::app);}
                        fd<<szTime<<","<<"["<<mark<<"]"<<szBuf<<endl;
						fd.close();
                }
                catch(...)
                {
                        cerr<<"open log file exception!"<<endl;
                        return -1;
                }
        }
        return 0;
}

int CLog::addlog(const char* Format,...)
{
	char szBuf[CLOG_MSGL];
	char szTime[20];
	char szDate[10];
	string fn;

	memset(szBuf,0,sizeof(szBuf));
	memset(szTime,0,sizeof(szTime));
	memset(szDate,0,sizeof(szDate));

	va_list	l_va;
	va_start(l_va,Format);
	vsnprintf(szBuf,sizeof(szBuf),Format,l_va);
	va_end(l_va);

	FormatCurrDate(szTime,szDate);

	if (filesplit==1) 
	{
		fn=(string)szFile;
		fn += ".";
		fn += szDate;
	}
	else
	{
		fn=(string)szFile;
	}

	if (outputflag==0)
	{
		cout<<szBuf<<endl;
	}
	else
	{
		//ofstream fd;
		try
		{
		  if ((fnchange) && (fd.is_open())) {fd.close();fnchange=false;}//如果文件名改变，需要关闭上一个文件
          if (!fd.is_open())
			  {fd.open(fn.c_str(),ios::app);}
			fd<<szBuf;
		}
		catch(...)
		{
			cerr<<"open log file exception!"<<endl;
			return -1;
		}
	}
	return 0;
}

int CLog::writelogto(const char* path, const char* fname,int flag,int split,const char* Format,...)
{
	int pathlen = 0;
	int fnamelen = 0;
	if (path) { pathlen = strlen(path);}
	if (fname) { fnamelen = strlen(fname);}
	int alllen = pathlen + 2 + fnamelen + fnamelen;
	if (alllen  > CLOG_FL) {
		return -1;
	}

	char path_file_name [CLOG_FL];
	memset(path_file_name, 0, sizeof(path_file_name));
  strcpy(path_file_name, path);
	strcat(path_file_name, "/");
	strcat(path_file_name, fname);
	strcat(path_file_name, "/");
	strcat(path_file_name, fname);
  

	SetLog(path_file_name, alllen, flag, split);

	char szBuf[CLOG_MSGL];
	char szTime[20];
	char szDate[10];
	string fn;

	memset(szBuf,0,sizeof(szBuf));
	memset(szTime,0,sizeof(szTime));
	memset(szDate,0,sizeof(szDate));

	va_list	l_va;
	va_start(l_va,Format);
	vsnprintf(szBuf,sizeof(szBuf),Format,l_va);
	va_end(l_va);

	FormatCurrDate(szTime,szDate);
	if (filesplit==1) 
	{
		fn=(string)szFile;
		fn += ".";
		fn += szDate;
	}
	else
	{
		fn=(string)szFile;
	}

	if (outputflag==0)
	{
		cout<<szTime<<","<<szBuf<<endl;
	}
	else
	{
		//ofstream fd;
		try
		{
			if ((fnchange) && (fd.is_open())) {fd.close();}//如果文件名改变，需要关闭上一个文件
			if (!fd.is_open())
			{fd.open(fn.c_str(),ios::app);}
			fd<<szTime<<","<<szBuf<<endl;
		}
		catch(...)
		{
			cerr<<"open log file exception!"<<endl;
			return -1;
		}
	}
	return 0;
}


