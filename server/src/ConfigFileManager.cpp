/**
* ConfigFileManager.cpp : 配置文件管理器，管理所有的配置文件
* @author：pengyuan
* @date：2014.8.18
* @备注：
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



//获取道具配置文件
CItemConfigManager*     CConfigFileManager::GetItemConfigMgr()
{
	return    &m_ItemConfigMgr;
}
