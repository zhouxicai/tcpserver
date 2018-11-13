/**
* ItemConfigManager.h : ͷ�ļ������������ļ�����������������ϵͳ�����ļ����Լ���ؼ�����Ϣ��ѯ�ȵȡ�
* @author��zhouxicai
* @date��2018.09.05
* @��ע��
* */

#ifndef    __ITEM_CONFIG_MANAGER_H__
#define    __ITEM_CONFIG_MANAGER_H__


#pragma once

#include "../../common/ConstDefines.h"

#define    MAX_ITEM_TYPE_COUNT    512    //���ĵ���������Ŀ
#define    MAX_EQUIP_TYPE_COUNT   1024   //����װ��������Ŀ

class CItemConfigManager
{
public:
	CItemConfigManager(void);
	~CItemConfigManager(void);

	//���������ļ���ȡ��������
	bool    Init(const char* szConfigName);

	//���ݵ���IDѰ�Ҹõ��ߵ�������Ϣ
	ITEM_CONFIG_INFO* FindItemConfigInfo(unsigned int dwItemID);

protected:
	int                 m_nItemTypeCount;
	ITEM_CONFIG_INFO    m_szItemCFGInfo[MAX_ITEM_TYPE_COUNT];
};


#endif