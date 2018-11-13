/**
* TimeTool.cpp : �ṩ�뼶��ʱ�������ʵ���ļ�
* @author��zhouxicai
* @date��2012.8.10
* @��ע��
* */

#include "stdafx.h"
#include "TimeTool.h"

#include <iostream>
using namespace std;

CTimeTool::CTimeTool()
{

}

CTimeTool::~CTimeTool()
{

}

//��������������ȡϵͳ��ǰʱ�䣬�������һЩʱ����ص��¼�����
void    CTimeTool::Update()
{
#ifdef __WINDOWS__
	time(&currentTime);
	localtime_s(&timeValue, &currentTime);
	//cout<<"��ǰ�����ǣ�"<<timeValue.tm_year<<"��"<<timeValue.tm_mon+1<<"��"<<timeValue.tm_mday<<"��"<<endl;
#endif

#ifdef __LINUX__
	time(&current_time);
	nowTime = localtime(&current_time);

#endif
}

//��������ӿڻ�ȡʱ�䣬������Ҫÿ����Ҫ��ȡʱ���ʱ��Ҫ����һ��ϵͳ����
unsigned int   CTimeTool::GetCurrentTime()
{
#ifdef __WINDOWS__
	return currentTime;
#endif

#ifdef __LINUX__
	return current_time;
#endif
}

#ifdef __WINDOWS__
void CTimeTool::ConvertTime(unsigned int dwSeconds, struct tm szTime)
{
	time_t convertTime = dwSeconds;
	localtime_s(&szTime, &convertTime);

	return;
}

int     CTimeTool::GetYear()
{
	return timeValue.tm_year;
}

int     CTimeTool::GetMonth()
{
	return timeValue.tm_mon;
}

int     CTimeTool::GetDay()
{
	return timeValue.tm_mday;
}

int     CTimeTool::GetHour()
{
	return timeValue.tm_hour;
}
#endif

#ifdef __LINUX__
void CTimeTool::ConvertTime(unsigned int dwSeconds, struct tm szTime)
{
	time_t convertTime = dwSeconds;
	//convertTime.tv_sec = dwSeconds;
	//convertTime.tv_usec = dwSeconds;
	szTime = *localtime(&convertTime);

	return;
}
int     CTimeTool::GetYear()
{
	return nowTime->tm_year;
}

int     CTimeTool::GetMonth()
{
	return nowTime->tm_mon;
}

int     CTimeTool::GetDay()
{
	return nowTime->tm_mday;
}

int     CTimeTool::GetHour()
{
	return nowTime->tm_hour;
}
#endif