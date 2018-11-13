/**
* ItemConfigManager.h : 头文件，升级配置文件管理器，管理升级系统配置文件，以及相关级别信息查询等等。
* @author：zhouxicai
* @date：2018.09.05
* @备注：
* */

#ifndef    __ITEM_CONFIG_MANAGER_H__
#define    __ITEM_CONFIG_MANAGER_H__


#pragma once

#include "../../common/ConstDefines.h"

#define    MAX_ITEM_TYPE_COUNT    512    //最大的道具种类数目
#define    MAX_EQUIP_TYPE_COUNT   1024   //最大的装备种类数目

class CItemConfigManager
{
public:
	CItemConfigManager(void);
	~CItemConfigManager(void);

	//根据配置文件读取道具配置
	bool    Init(const char* szConfigName);

	//根据道具ID寻找该道具的配置信息
	ITEM_CONFIG_INFO* FindItemConfigInfo(unsigned int dwItemID);

protected:
	int                 m_nItemTypeCount;
	ITEM_CONFIG_INFO    m_szItemCFGInfo[MAX_ITEM_TYPE_COUNT];
};


#endif