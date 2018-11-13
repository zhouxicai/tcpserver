/**
* TimeValue.h : 用来调试的时间函数，现在windows平台和linux平台返回的计数单位都是秒
* @author：zhouxicai
* @date：2012.7.1
* @备注：
* */

#ifndef    __TIME_VALUE_H__
#define    __TIME_VALUE_H__

#pragma once

#include "stdafx.h"
#include <ctime>

class CTimeValue
{
public:
	CTimeValue();
	~CTimeValue();

	void    Begin();

	double   End();

protected:

#ifdef __WINDOWS__
	_LARGE_INTEGER time_start;    /*开始时间*/ 
	_LARGE_INTEGER time_over;        /*结束时间*/ 
	double dqFreq;                /*计时器频率*/ 
	LARGE_INTEGER f;            /*计时器频率*/ 
	double m_fDeltaTime; 
#endif

#ifdef __LINUX__
	struct timeval time_start;
	struct timeval time_over;
	double ms;
#endif

private:
};

#endif