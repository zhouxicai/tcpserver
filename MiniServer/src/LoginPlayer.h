/**
* LoginPlayer.h : Login服务器上的玩家实例，处理网络连接等信息
* @author：pengyuan
* @date：2011.10.07
* @备注：
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

	//初始化数据结构
	bool    Init(char* szIPAddress, int port);

	//当选择一个空的player的时候，清除里面的相应数据
	void    Clean();

	//得到CloudSocket对象的指针
	CloudSocket* GetSocket();

	//处理输入，收包数据处理
	bool    ProcessInput();

	//处理输出，发包的数据处理
	bool    ProcessOutput();

	//是否断线了
	bool    IsDisconnect();

	//这个玩家是否没有被占用
	bool    IsEmpty();

	//设置这个玩家是否被占用
	void    SetEmpty(bool bEmpty);

	unsigned int     GetSessionKey();

	//设置会晤号
	void    SetSessionKey(unsigned int dwSessionKey);

	//得到玩家Uin信息
	unsigned int    GetUin();

	//给这个客户端发消息
	void    AddSendMessage(const char* szBuffer, int nLength);

protected:
	void    ProcessPackets();

	//返回的是已经处理的字节数
	int     ProcessLogin(const char* szBuffer);

	//pengyuan 2012.4.16 处理注册消息
	int     ProcessRegister(const char* szBuffer);

	//pengyuan 2014.8.18 处理创建角色消息
	int     ProcessCreateCharacter(const char* szBuffer);


	//从数据库中得到玩家的基本信息
	bool    GetPlayerBaseInfo(unsigned int dwUin, NOTIFY_PLAYER_BASE_INFO& baseInfo);

	//从数据库中得到玩家的道具信息
	bool    GetPlayerItemInfo(unsigned int dwUin);

	//从数据库中得到玩家的将领信息
	bool    GetPlayerGeneralInfo(unsigned int dwUin);

	//玩家道具信息写数据库
	void    WritePlayerItemInfo();

	//新注册的玩家，初始化一系列的数据
	void    InitNewPlayerInfo(unsigned int dwUin, const char* szName);

	//解码装饰信息，从数据库中读取出来的字符，解码成具体的装饰信息
	void    DecodeDecorateInfo(int nDecorateNumber, const char* szDecorateInfo);

	//编码装饰信息，把装饰信息编码，准备存放到数据库中
	void    EncodeDecorateInfo(char* szDecorateInfo);


protected:
	CConnectManager*    m_pConnectManager;

	LoggerPtr logger;                          //pengyuan 2012.4.20 日志类指针

	bool            m_IsEmpty;             //是否未被占用
	bool            m_IsDisconnected;      //连接是否已经断开
	CloudSocket    *m_pSocket;

	int             m_nPlayerID;

	int             m_nSendBeginIndex;
	int             m_nSendLength;
	char            m_SendBuff[SEND_BUFFER_LENGTH];

	int             m_nRecvBeginIndex;
	int             m_nRecvLength;
	char            m_RecvBuff[RECV_BUFFER_LENGTH];
	unsigned int    m_SessionKey;

	//存储玩家的基本信息
	unsigned int    m_dwUin;
	NOTIFY_PLAYER_BASE_INFO m_PlayerBaseInfo;

	//pengyuan 2014.8.20 存储玩家的道具信息
	PLAYER_ITEM_INFO    m_PlayerItemInfo;

	//pengyuan 2014.8.23 存储玩家的主角信息
	SINGLE_EQUIP_INFO   m_szEquipInfos[MAX_EQUIP_COUNT_PER_PLAYER];
	//pengyuan 2014.8.22 存储玩家的将领信息
	GENERAL_INFOS       m_PlayerGeneralInfos;
	
	//pengyuan 2012.6.1 装饰信息存储
	int             m_nDecoNumber;
	MODEL_INFO      m_szDecoInfos[MAX_DECORATE_NUMBER];

};

#endif