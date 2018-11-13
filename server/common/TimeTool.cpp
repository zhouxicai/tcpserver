/**
* TimeTool.cpp : 提供秒级的时间计数，实现文件
* @author：zhouxicai
* @date：2012.8.10
* @备注：
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

//在这个函数里面获取系统当前时间，方便进行一些时间相关的事件处理
void    CTimeTool::Update()
{
#ifdef __WINDOWS__
	time(&currentTime);
	localtime_s(&timeValue, &currentTime);
	//cout<<"当前日期是："<<timeValue.tm_year<<"年"<<timeValue.tm_mon+1<<"月"<<timeValue.tm_mday<<"日"<<endl;
#endif

#ifdef __LINUX__
	time(&current_time);
	nowTime = localtime(&current_time);

#endif
}

//调用这个接口获取时间，而不需要每次需要获取时间的时候都要进行一次系统调用
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