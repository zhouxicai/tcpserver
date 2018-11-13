/**
* ConfigFileManager.h : 配置文件管理器，管理所有的配置文件
* @author：pengyuan
* @date：2014.8.18
* @备注：
* */

#ifndef __CONFIG_FILE_MANAGER__
#define __CONFIG_FILE_MANAGER__

#pragma once


#include    "ItemConfigManager.h"

class CLevelConfigManager;
class CItemConfigManager;
class CDropConfigManager;
class CGeneralConfigManager;

class CConfigFileManager
{
public:
	CConfigFileManager(void);
	~CConfigFileManager(void);

	//根据配置文件读取升级配置
	bool    Init();


	//获取道具配置文件
	CItemConfigManager*     GetItemConfigMgr();

private:

	CItemConfigManager     m_ItemConfigMgr;

};


extern CConfigFileManager *g_pConfigFileMgr;

#endif