/**
* TimeValue.cpp : 用来调试的时间函数
* @author：zhouxicai
* @date：2012.7.1
* @备注：
* */

#include "stdafx.h"
#include "TimeValue.h"

CTimeValue::CTimeValue()
{

}

CTimeValue::~CTimeValue()
{

}

void    CTimeValue::Begin()
{
#ifdef __WINDOWS__
	QueryPerformanceFrequency(&f);  
	dqFreq=(double)f.QuadPart;  
	QueryPerformanceCounter(&time_start);
	time_over = time_start;
	m_fDeltaTime = 0.0f;

#endif

#ifdef __LINUX__
	gettimeofday(&time_start, 0);

#endif
}

double   CTimeValue::End()
{
#ifdef __WINDOWS__
	QueryPerformanceCounter(&time_over);
	m_fDeltaTime = ((time_over.QuadPart-time_start.QuadPart)/dqFreq);
	time_start = time_over;

	return m_fDeltaTime;
#endif

#ifdef __LINUX__
	gettimeofday(&time_over, 0);
	ms = (double)(time_over.tv_sec - time_start.tv_sec);// * 1000 + (double)(time_over.tv_usec - time_start.tv_usec)/1000;
	return ms;
#endif
}
