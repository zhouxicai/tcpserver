/**
* ConfigFileManager.cpp : �����ļ����������������е������ļ�
* @author��pengyuan
* @date��2014.8.18
* @��ע��
* */


#include "../common/stdafx.h"
#include <iostream>
#include "ConfigFileManager.h"

using namespace std;



CConfigFileManager::CConfigFileManager(void)
{
}


CConfigFileManager::~CConfigFileManager(void)
{
}


bool    CConfigFileManager::Init()
{
	if (!m_ItemConfigMgr.Init("../config/ItemConfig.xml"))
	{
		return false;
	}

	return true;
}



//��ȡ���������ļ�
CItemConfigManager*     CConfigFileManager::GetItemConfigMgr()
{
	return    &m_ItemConfigMgr;
}
