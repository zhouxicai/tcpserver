/**
* TimeTool.h : �ṩ�뼶��ʱ�������ͷ�ļ�
* @author��zhouxicai
* @date��2012.8.10
* @��ע��
* */

#ifndef    __TIME_TOOL_H__
#define    __TIME_TOOL_H__

#pragma once

#include "stdafx.h"
#include <ctime>

class CTimeTool
{
public:
	CTimeTool();
	~CTimeTool();

	void    Update();

	unsigned int GetCurrentTime();

	void ConvertTime(unsigned int dwSeconds, struct tm szTime);

	int     GetYear();

	int     GetMonth();

	int     GetDay();

	int     GetHour();

protected:

#ifdef __WINDOWS__
	time_t    currentTime;
	struct tm timeValue;
#endif

#ifdef __LINUX__
	time_t current_time;
	struct tm* nowTime;
#endif

private:
};

#endif