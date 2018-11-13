/**
* LoginPlayer.h : Login�������ϵ����ʵ���������������ӵ���Ϣ
* @author��pengyuan
* @date��2011.10.07
* @��ע��
* */

#ifndef __LOGIN_PLAYER__
#define __LOGIN_PLAYER__

#pragma once

#include <log4cxx/logger.h>

#include "../../common/ConstDefines.h"
//#include "ConnectManager.h"
#include "../../common/net/CloudSocket.h"
#include "../../common/net/net_protocol_command.h"
#include "../../common/net/net_protocol_login.h"

using namespace log4cxx;

class CConnectManager;

class CLoginPlayer
{
public:
	CLoginPlayer(CConnectManager* pConnectManager, LoggerPtr Logger);
	~CLoginPlayer(void);

	//��ʼ�����ݽṹ
	bool    Init(char* szIPAddress, int port);

	//��ѡ��һ���յ�player��ʱ������������Ӧ����
	void    Clean();

	//�õ�CloudSocket�����ָ��
	CloudSocket* GetSocket();

	//�������룬�հ����ݴ���
	bool    ProcessInput();

	//������������������ݴ���
	bool    ProcessOutput();

	//�Ƿ������
	bool    IsDisconnect();

	//�������Ƿ�û�б�ռ��
	bool    IsEmpty();

	//�����������Ƿ�ռ��
	void    SetEmpty(bool bEmpty);

	unsigned int     GetSessionKey();

	//���û����
	void    SetSessionKey(unsigned int dwSessionKey);

	//�õ����Uin��Ϣ
	unsigned int    GetUin();

	//������ͻ��˷���Ϣ
	void    AddSendMessage(const char* szBuffer, int nLength);

protected:
	void    ProcessPackets();

	//���ص����Ѿ�������ֽ���
	int     ProcessLogin(const char* szBuffer);

	//pengyuan 2012.4.16 ����ע����Ϣ
	int     ProcessRegister(const char* szBuffer);

	//pengyuan 2014.8.18 ��������ɫ��Ϣ
	int     ProcessCreateCharacter(const char* szBuffer);


	//�����ݿ��еõ���ҵĻ�����Ϣ
	bool    GetPlayerBaseInfo(unsigned int dwUin, NOTIFY_PLAYER_BASE_INFO& baseInfo);

	//�����ݿ��еõ���ҵĵ�����Ϣ
	bool    GetPlayerItemInfo(unsigned int dwUin);

	//�����ݿ��еõ���ҵĽ�����Ϣ
	bool    GetPlayerGeneralInfo(unsigned int dwUin);

	//��ҵ�����Ϣд���ݿ�
	void    WritePlayerItemInfo();

	//��ע�����ң���ʼ��һϵ�е�����
	void    InitNewPlayerInfo(unsigned int dwUin, const char* szName);

	//����װ����Ϣ�������ݿ��ж�ȡ�������ַ�������ɾ����װ����Ϣ
	void    DecodeDecorateInfo(int nDecorateNumber, const char* szDecorateInfo);

	//����װ����Ϣ����װ����Ϣ���룬׼����ŵ����ݿ���
	void    EncodeDecorateInfo(char* szDecorateInfo);


protected:
	CConnectManager*    m_pConnectManager;

	LoggerPtr logger;                          //pengyuan 2012.4.20 ��־��ָ��

	bool            m_IsEmpty;             //�Ƿ�δ��ռ��
	bool            m_IsDisconnected;      //�����Ƿ��Ѿ��Ͽ�
	CloudSocket    *m_pSocket;

	int             m_nPlayerID;

	int             m_nSendBeginIndex;
	int             m_nSendLength;
	char            m_SendBuff[SEND_BUFFER_LENGTH];

	int             m_nRecvBeginIndex;
	int             m_nRecvLength;
	char            m_RecvBuff[RECV_BUFFER_LENGTH];
	unsigned int    m_SessionKey;

	//�洢��ҵĻ�����Ϣ
	unsigned int    m_dwUin;
	NOTIFY_PLAYER_BASE_INFO m_PlayerBaseInfo;

	//pengyuan 2014.8.20 �洢��ҵĵ�����Ϣ
	PLAYER_ITEM_INFO    m_PlayerItemInfo;

	//pengyuan 2014.8.23 �洢��ҵ�������Ϣ
	SINGLE_EQUIP_INFO   m_szEquipInfos[MAX_EQUIP_COUNT_PER_PLAYER];
	//pengyuan 2014.8.22 �洢��ҵĽ�����Ϣ
	GENERAL_INFOS       m_PlayerGeneralInfos;
	
	//pengyuan 2012.6.1 װ����Ϣ�洢
	int             m_nDecoNumber;
	MODEL_INFO      m_szDecoInfos[MAX_DECORATE_NUMBER];

};

#endif