/**
* ItemConfigManager.cpp : ʵ���ļ����������ù�������
* @author��zhouxicai
* @date��2018.09.05
* @��ע��
* */

#include "../common/stdafx.h"
#include <iostream>
#include "ItemConfigManager.h"
#include "../common/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

CItemConfigManager::CItemConfigManager(void)
{
	m_nItemTypeCount  = 0;
}

CItemConfigManager::~CItemConfigManager(void)
{
}


//���������ļ���ȡ��������
bool CItemConfigManager::Init(const char* szConfigName)
{
	cout<<"Read "<<szConfigName<<endl;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(szConfigName);
	m_nItemTypeCount = 0;
	const XMLElement* element = doc.RootElement();
	for (const XMLElement* parent = element->FirstChildElement("ItemConfig");parent;parent = parent->NextSiblingElement())
	{
		const XMLElement *pChild = NULL;
		for (pChild = parent->FirstChildElement("info"); pChild != NULL; pChild = pChild->NextSiblingElement())
		{
			m_szItemCFGInfo[m_nItemTypeCount].dwItemID = atoi(pChild->Attribute("InfoID"));
			m_szItemCFGInfo[m_nItemTypeCount].dwType = atoi(pChild->Attribute("Type"));
			m_szItemCFGInfo[m_nItemTypeCount].dwTypeValue = atoi(pChild->Attribute("Type_Value"));
			m_szItemCFGInfo[m_nItemTypeCount].dwCanSell = atoi(pChild->Attribute("CanSell"));
			m_szItemCFGInfo[m_nItemTypeCount].dwCurrency = atoi(pChild->Attribute("Currency"));
			m_nItemTypeCount++;
		}
	}
	cout<<"Read "<< szConfigName <<" end!"<<endl;

	return true;
}


//���ݵ���IDѰ�Ҹõ��ߵ�������Ϣ
ITEM_CONFIG_INFO* CItemConfigManager::FindItemConfigInfo(unsigned int dwItemID)
{
	for (int i=0; i<min(m_nItemTypeCount, MAX_ITEM_TYPE_COUNT); ++i)
	{
		if (m_szItemCFGInfo[i].dwItemID == dwItemID)
		{
			return &m_szItemCFGInfo[i];
		}
	}

	return NULL;
}
