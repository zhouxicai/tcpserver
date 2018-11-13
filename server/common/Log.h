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
        int outputflag;		// 0 ��׼�����1 ������ļ� szFile
        int filesplit;		// 0 �����ļ���1 ������������ļ���1��һ���ļ����Զ��� szFile �����������".yymmdd"

				struct tm today;
				ofstream fd;

				bool fnchange;//����ļ����Ƿ�ı�
        int  FormatCurrDate(char *szStr,char *strDay);
    public:
        CLog();
        CLog(char *filename,int len,int flag=1, int split=0);		// filename:��־�ļ�����len: filename �ĳ���, flag: 0 ��׼�����1 ������ļ�
        ~CLog();
        int SetLog(char *filename,int len,int flag=1, int split=0);
        int setOutput(int flag);
        int setSplit(int split);
        int outlog(const char* Format, ...);     //nType:1 error,2 warn,3 message
		int markoutlog(const char* mark,const char* Format,...);     //nType:1 error,2 warn,3 message
		int addlog(const char* Format,...);//����־��������ݣ��û��Լ����Ƹ�ʽ
		//д��־��ָ���ļ� flag: 0 ��׼��� 1 ������ļ� ��split: 0 �����ļ���1 ������������ļ���1��һ���ļ����Զ��� szFile �����������".yymmdd"
		int writelogto(const char* path, const char* fname, int flag, int split, const char* Format,...);
};


#endif
