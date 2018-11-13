/**
* TimeValue.h : �������Ե�ʱ�亯��������windowsƽ̨��linuxƽ̨���صļ�����λ������
* @author��zhouxicai
* @date��2012.7.1
* @��ע��
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
	_LARGE_INTEGER time_start;    /*��ʼʱ��*/ 
	_LARGE_INTEGER time_over;        /*����ʱ��*/ 
	double dqFreq;                /*��ʱ��Ƶ��*/ 
	LARGE_INTEGER f;            /*��ʱ��Ƶ��*/ 
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