/**
* ConfigFileManager.h : �����ļ����������������е������ļ�
* @author��pengyuan
* @date��2014.8.18
* @��ע��
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

	//���������ļ���ȡ��������
	bool    Init();


	//��ȡ���������ļ�
	CItemConfigManager*     GetItemConfigMgr();

private:

	CItemConfigManager     m_ItemConfigMgr;

};


extern CConfigFileManager *g_pConfigFileMgr;

#endif