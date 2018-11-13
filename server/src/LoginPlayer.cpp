/**
* LoginServer.cpp : Login�������ϵ����ʵ���������������ӵ���Ϣ
* @author��pengyuan
* @date��2011.10.07
* @��ע��
* */

#include "../common/stdafx.h"


#include <iostream>
#include "LoginPlayer.h"

//#include <mysql.h>
//#include <mysqld_error.h>
//#include <errmsg.h>
#include "../common/MySQLInterface.h"


using namespace std;

extern CMySQLInterface* g_pMySQLInterface;

CLoginPlayer::CLoginPlayer(CConnectManager* pConnectManager)
{
	m_pConnectManager = pConnectManager;
	m_IsEmpty         = true;
	m_IsDisconnected  = true;
	m_pSocket         = NULL;
	m_nPlayerID       = 0;

	m_nSendBeginIndex = 0;
	m_nSendLength     = 0;
	m_nRecvBeginIndex = 0;
	m_nRecvLength     = 0;

	m_dwUin = INVALID_PLAYER_UIN;

	memset(m_SendBuff, 0, SEND_BUFFER_LENGTH);
	memset(m_RecvBuff, 0, RECV_BUFFER_LENGTH);

	m_pSocket = new CloudSocket();
}

CLoginPlayer::~CLoginPlayer(void)
{
	if (m_pSocket)
	{
		delete m_pSocket;
		m_pSocket = NULL;
	}
}

CloudSocket*    CLoginPlayer::GetSocket()
{
	return m_pSocket;
}

//��ʼ�����ݽṹ
bool    CLoginPlayer::Init(char* szIPAddress, int port)
{
	if (!m_pSocket)
	{
		m_pSocket = new CloudSocket();
	}

	SetEmpty(false);
	m_nDecoNumber     = 0;
	m_IsDisconnected = false;
	m_nSendBeginIndex = 0;
	m_nSendLength     = 0;
	m_nRecvBeginIndex = 0;
	m_nRecvLength     = 0;

	memset(m_SendBuff, 0, SEND_BUFFER_LENGTH);
	memset(m_RecvBuff, 0, RECV_BUFFER_LENGTH);

	m_PlayerItemInfo.shTotalCount = 0;
	m_PlayerGeneralInfos.byGeneralCount = 0;

	memset(m_szEquipInfos, 0, sizeof(SINGLE_EQUIP_INFO)*MAX_EQUIP_COUNT_PER_PLAYER);

	return true;
}

//��ѡ��һ���յ�player��ʱ������������Ӧ����
void    CLoginPlayer::Clean()
{
	if (m_pSocket)
	{
		m_pSocket->Close();
	}

	m_IsEmpty         = true;
	m_IsDisconnected  = true;
	m_nPlayerID       = 0;
	m_nDecoNumber     = 0;

	m_nSendBeginIndex = 0;
	m_nSendLength     = 0;
	m_nRecvBeginIndex = 0;
	m_nRecvLength     = 0;

	memset(m_SendBuff, 0, SEND_BUFFER_LENGTH);
	memset(m_RecvBuff, 0, RECV_BUFFER_LENGTH);

	m_PlayerItemInfo.shTotalCount = 0;
	m_PlayerGeneralInfos.byGeneralCount = 0;

	memset(m_szEquipInfos, 0, sizeof(SINGLE_EQUIP_INFO)*MAX_EQUIP_COUNT_PER_PLAYER);
}

//char* szPolicyContent = "<?xml version=\"1.0\"?>\n<cross-domain-policy>\n<allow-access-from domain=\"*\" to-ports=\"12345\"/>\n</cross-domain-policy>\0";

//�������룬�հ����ݴ���
bool    CLoginPlayer::ProcessInput()
{
	if( IsDisconnect() )
		return true ;

	//uint ret;// = m_pSocketInputStream->Fill( ) ;
	int nReceived = 0;
	if( (m_nRecvLength + 4*1024) >= RECV_BUFFER_LENGTH )
	{
		memmove(m_RecvBuff, m_RecvBuff+m_nRecvBeginIndex, m_nRecvBeginIndex);
		m_nRecvLength = m_nRecvBeginIndex;
		m_nRecvBeginIndex = 0;
	}

	nReceived = m_pSocket->receive(m_RecvBuff+m_nRecvBeginIndex, RECV_BUFFER_LENGTH-m_nRecvBeginIndex);

	if (nReceived <= 0)
	{
		//unsigned int uLastError = WSAGetLastError();

		std::cout<<"  Client Disconnected Actively...Host: "<<m_pSocket->m_Host<<std::endl;

//#pragma message("ע�������ʱ�����Ų�����գ�ֻ�����յ�game���Ķ�����Ϣ֮�����Ų������ ");
		m_pSocket->Close();
		Clean();

		return false;
	}

	std::cout<< "Accept Data Length: "<<nReceived<<"Host: "<<m_pSocket->m_Host<<"Port: "<<m_pSocket->m_Port << std::endl;
	std::cout<< m_RecvBuff << std::endl;

	/*if (nReceived == 23)
	{
		char szPolicy[23];
		memcpy(szPolicy, m_RecvBuff, 22);
		szPolicy[22] = '\0';
		if (!strcmp(szPolicy, "<policy-file-request/>"))
		{
			send(m_pSocket->m_SocketID, szPolicyContent, strlen(szPolicyContent)+1, 0);
			LOG4CXX_INFO(logger,"Send Policy File to "<<"Host: "<<m_pSocket->m_Host<<"Port: "<<m_pSocket->m_Port);

			long SessionKey = htonl(m_SessionKey);
			send(m_pSocket->m_SocketID, (char*)&SessionKey, 4, 0);
			LOG4CXX_INFO(logger,"Server generate session id is: "<<(int)m_SessionKey);
		}
		else
		{
			m_nRecvBeginIndex += nReceived;
			m_nRecvLength += nReceived;

			ProcessPackets();
		}
	}
	else
	{
		m_nRecvBeginIndex += nReceived;
		m_nRecvLength += nReceived;

		ProcessPackets();
	}*/

	m_nRecvBeginIndex += nReceived;
	m_nRecvLength += nReceived;

	ProcessPackets();

	return true ;
}

//������������������ݴ���
bool    CLoginPlayer::ProcessOutput()
{
	if (IsDisconnect())
	{
		return false;
	}

	while(m_nSendLength > (int)sizeof(tagMsgHead))
	{
		int nRet = send(m_pSocket->m_SocketID, m_SendBuff+m_nSendBeginIndex, m_nSendLength, 0);

		//LOG4CXX_INFO(logger, "send output packets to player...socket id: "<<m_pSocket->m_SocketID);
		//LOG4CXX_INFO(logger, m_SendBuff);

		m_nSendBeginIndex += nRet;
		m_nSendLength -= nRet;

		if((SEND_BUFFER_LENGTH - m_nSendBeginIndex) < MAX_PACKAGE_LENGTH)
		{
			memmove(m_SendBuff, m_SendBuff+m_nSendBeginIndex, m_nSendLength);
			m_nSendBeginIndex = 0;
		}
	}

	return true;
}

//�Ƿ������
bool    CLoginPlayer::IsDisconnect()
{
	return m_IsDisconnected;
}

//�������Ƿ�û�б�ռ��
bool    CLoginPlayer::IsEmpty()
{
	return m_IsEmpty;
}

//�����������Ƿ�ռ��
void    CLoginPlayer::SetEmpty(bool bEmpty)
{
	m_IsEmpty = bEmpty;
}

unsigned int    CLoginPlayer::GetSessionKey()
{
	return m_SessionKey;
}

//���û����
void    CLoginPlayer::SetSessionKey(unsigned int dwSessionKey)
{
	m_SessionKey = dwSessionKey;
}


//�õ����Uin��Ϣ
unsigned int    CLoginPlayer::GetUin()
{
	return    m_dwUin;
}


//������ͻ��˷���Ϣ
void    CLoginPlayer::AddSendMessage(const char* szBuffer, int nLength)
{
	memcpy(m_SendBuff+m_nSendBeginIndex+m_nSendLength, szBuffer, nLength);
	m_nSendLength += nLength;
}

void    CLoginPlayer::ProcessPackets()
{
	int nBeginIndex = m_nRecvBeginIndex - m_nRecvLength;
	if ( nBeginIndex < 0 )
	{
		return;
	}

	MSG_HEAD msgHead;
	msgHead.Read(m_RecvBuff+nBeginIndex);
	//memcpy(&msgHead, m_RecvBuff+nBeginIndex, sizeof(tagMsgHead));
	int nPacketLength = msgHead.nPacketLength;
//#pragma message("2012.04.27:������ʱ���ܴ��������Ϊ�ϰ����͵���������ж��������ˡ��޸����ٲ���")
	std::cout << "CLoginPlayer::ProcessPackets() m_nRecvLength: " << m_nRecvLength << " nPacketLength: " << nPacketLength << std::endl;
	//while(nPacketLength >= m_nRecvLength)
	while(nPacketLength <= m_nRecvLength && nPacketLength > 0)
	{
		//int    dwUin = msgHead.dwUin;
		int    nCommandID = msgHead.nCommandID;
		int    nBytesProcessed = PACKET_HEAD_LENGTH;

		std::cout << "Receive Command from Host: " << m_pSocket->m_Host << " Port: " << m_pSocket->m_Port << " Command ID: " << nCommandID << std::endl;

		switch (nCommandID)
		{
		case MSG_ID_REQUEST_LOGIN:
			nBytesProcessed += ProcessLogin(m_RecvBuff+nBeginIndex+PACKET_HEAD_LENGTH);
			break;
		case MSG_ID_REQUEST_REGISTER:
			nBytesProcessed += ProcessRegister(m_RecvBuff+nBeginIndex+PACKET_HEAD_LENGTH);
			break;
		case MSG_ID_REQUEST_CREATE_CHARACTER:
			nBytesProcessed += ProcessCreateCharacter(m_RecvBuff+nBeginIndex+PACKET_HEAD_LENGTH);
			break;
		default:
			std::cout << "Receive Undefined Command ID: " << nCommandID << "From Host: " << m_pSocket->m_Host << " Port: " << m_pSocket->m_Port << std::endl;
			break;
		}

		m_nRecvLength -= nBytesProcessed;
		nBeginIndex += nBytesProcessed;

		if (m_nRecvLength < 0)
		{
			std::cout << "Process Command Error, From IP: "<<m_pSocket->m_Host<<" Port: "<<m_pSocket->m_Port<<" Command ID: "<<nCommandID << std::endl;
		}

		if (m_nRecvLength > (int)sizeof(tagMsgHead))
		{
			memcpy(&msgHead, m_RecvBuff + m_nRecvBeginIndex - m_nRecvLength, sizeof(tagMsgHead));
			nPacketLength = msgHead.nPacketLength;
		}
		else
		{
			nPacketLength = -1;
		}
	}

}

//���ص����Ѿ�������ֽ���
int    CLoginPlayer::ProcessLogin(const char* szBuffer)
{
	std::cout << "Begin Process Login Message..." << std::endl;
	int    nBytesProcessed = 0;

	//int nRet = send(m_pSocket->m_SocketID, "XXOOXXOO\n", 9, 0);
	//LOG4CXX_INFO(logger, "send xoxoxoxxo to client..."<<m_pSocket->m_SocketID);

	REQUEST_LOGIN requestLogin;
	nBytesProcessed = requestLogin.Read(szBuffer);

	//������ҵ���߼��Ĵ�����֤��¼������
	MYSQL_RES *pResult = NULL;
	char szCommand[1024];
	memset(szCommand, 0, 1024);
	sprintf(szCommand, "select * from %s where user_name='%s'", "account", requestLogin.szUserName);
	
	int nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	if (nRet != S_OK)
	{
		std::cout << "Database Query Error Error Code: "<<nRet << std::endl;
		return nBytesProcessed;
	}

	RESPONSE_LOGIN responseLogin;
	char szSendBuffer[4096];
	memset(szSendBuffer, 0, 4096);

	responseLogin.byResult = 1;
	responseLogin.dwSessionID = 0xFFFFFFFF;
	responseLogin.dwUin = INVALID_PLAYER_UIN;
	int nBytesNeeded = 0;//responseLogin.Write(szSendBuffer+PACKET_HEAD_LENGTH);
	MSG_HEAD msgHead;
	/*msgHead.nPacketLength = PACKET_HEAD_LENGTH + nBytesNeeded;
	msgHead.dwUin = m_dwUin;
	msgHead.nCommandID = MSG_ID_RESPONSE_LOGIN;
	nBytesNeeded += PACKET_HEAD_LENGTH;
	AddSendMessage(szSendBuffer, nBytesNeeded);*/

	MYSQL_ROW row;
	const char* pName     = NULL;
	const char* pPassword = NULL;
	unsigned int dwUin    = 0;
	int nRowCount = mysql_num_rows(pResult);
	if (nRowCount == 1)
	{
		row = mysql_fetch_row(pResult);

		if (mysql_num_fields(pResult) < 6)
		{
			mysql_free_result(pResult);
		}
		else
		{
			pName = row[0];
			pPassword = row[1];
			dwUin = atoi(row[2]);

			if (!strcmp(requestLogin.szUserName, pName) && !strcmp(requestLogin.szPassword, pPassword))
			{
				responseLogin.byResult    = S_OK;
				responseLogin.dwSessionID = m_SessionKey;
				responseLogin.dwUin       = dwUin;
				m_dwUin                   = dwUin;
			}
			else
			{
				responseLogin.byResult    = ERROR_MSG_USER_OR_PWD_ERROR;
				responseLogin.dwSessionID = m_SessionKey;
				responseLogin.dwUin       = INVALID_PLAYER_UIN;
			}
			mysql_free_result(pResult);
		}

	}
	else
	{
		mysql_free_result(pResult);
	}

	char szSenderBuffer[2048];
	memset(szSenderBuffer, 0, 2048);
	nBytesNeeded = responseLogin.Write(szSenderBuffer+PACKET_HEAD_LENGTH);

//	MSG_HEAD msgHead;
	msgHead.nPacketLength = PACKET_HEAD_LENGTH + nBytesNeeded;
	msgHead.dwUin = m_dwUin;
	msgHead.nCommandID = MSG_ID_RESPONSE_LOGIN;
	msgHead.Write(szSenderBuffer);
	//nHeadLength = msgHead.Write(m_SendBuff+m_nSendBeginIndex+m_nSendLength);
	nBytesNeeded += PACKET_HEAD_LENGTH;

	AddSendMessage(szSenderBuffer, nBytesNeeded);
	/*memcpy(m_SendBuff+m_nSendBeginIndex+m_nSendLength, szSenderBuffer, nBytesNeeded);
	m_nSendLength += nBytesNeeded;*/

	if (responseLogin.dwUin != INVALID_PLAYER_UIN)
	{
		//NOTIFY_PLAYER_BASE_INFO playerBaseInfo;
		memset(szSendBuffer, 0, 4096);

		if (GetPlayerBaseInfo(m_dwUin, m_PlayerBaseInfo))
		{
			nBytesNeeded =  m_PlayerBaseInfo.Write(szSendBuffer + PACKET_HEAD_LENGTH);

			MSG_HEAD msgHead;
			msgHead.nPacketLength = PACKET_HEAD_LENGTH + nBytesNeeded;
			msgHead.dwUin = m_dwUin;
			msgHead.nCommandID = MSG_ID_NOTIFY_PLAYER_BASEINFO;
			msgHead.Write(szSendBuffer);
			nBytesNeeded += PACKET_HEAD_LENGTH;
			AddSendMessage(szSendBuffer, nBytesNeeded);

			std::cout << szSendBuffer << std::endl;

		}

		//pengyuan 2014.8.20 ��ȡ��ҵı�����Ϣ
		memset(szSendBuffer, 0, 4096);
		if(GetPlayerItemInfo(m_dwUin))
		{
			nBytesNeeded =  m_PlayerItemInfo.Write(szSendBuffer + PACKET_HEAD_LENGTH);

			MSG_HEAD msgHead;
			msgHead.nPacketLength = PACKET_HEAD_LENGTH + nBytesNeeded;
			msgHead.dwUin = m_dwUin;
			msgHead.nCommandID = MSG_ID_NOTIFY_PLAYER_ITEM_INFO;
			msgHead.Write(szSendBuffer);
			nBytesNeeded += PACKET_HEAD_LENGTH;
			AddSendMessage(szSendBuffer, nBytesNeeded);
		}

		//pengyuan 2014.8.22 ��ȡ��ҵĽ�����Ϣ
		memset(szSendBuffer, 0, 4096);
		if (GetPlayerGeneralInfo(m_dwUin))
		{
			nBytesNeeded =  m_PlayerGeneralInfos.Write(szSendBuffer + PACKET_HEAD_LENGTH);

			MSG_HEAD msgHead;
			msgHead.nPacketLength = PACKET_HEAD_LENGTH + nBytesNeeded;
			msgHead.dwUin = m_dwUin;
			msgHead.nCommandID = MSG_ID_NOTIFY_PLAYER_GENERAL_INFOS;
			msgHead.Write(szSendBuffer);
			nBytesNeeded += PACKET_HEAD_LENGTH;
			AddSendMessage(szSendBuffer, nBytesNeeded);
		}
	}

	std::cout << "Login Message Process End..." << std::endl;

	return nBytesProcessed;
}

//pengyuan 2012.4.16 ����ע����Ϣ
int     CLoginPlayer::ProcessRegister(const char* szBuffer)
{
	int    nBytesProcessed = 0;

	REQUEST_REGISTER requestRegister;
	nBytesProcessed = requestRegister.Read(szBuffer);

	RESPONSE_REGISTER responseRegister;
	responseRegister.byResult = ERROR_MSG_USER_EXIST;
	responseRegister.dwSessionID = 0xffffffff;
	responseRegister.dwUin = 0xffffffff;

	//������ҵ���߼��Ĵ���
	char szCommand[1024];
	memset(szCommand, 0, 1024);
	sprintf(szCommand, "select * from %s where user_name='%s'", "account", requestRegister.szUserName);
	MYSQL_RES *pResult = NULL;
	int nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);

	if (nRet != S_OK)
	{
		std::cout << "Database Query account error, user_name="<<requestRegister.szUserName << std::endl;
	}

	int nRows = mysql_num_rows(pResult);

	if (nRows == 0)
	{
		responseRegister.byResult = S_OK;
		//���￪ʼ��������ݲ��ҳ�ʼ�����ݿ�,��Ҫ�������ű�account, base_info, item_info, task_info
		//INSERT INTO `account` VALUES ('wangzhezhi','123456',5);
		memset(szCommand, 0, 1024);
		unsigned int dwMaxUin=0;
		sprintf(szCommand, "select * from account where dwUin=(select MAX(dwUin) from account);");
		MYSQL_RES *pResult = NULL;
		int nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
		if (nRet != S_OK)
		{
			std::cout << "Database query Max Uin error..." << std::endl;
		}

		MYSQL_ROW maxRow;
		int nMaxRow = mysql_num_rows(pResult);
		if (nMaxRow == 1)
		{
			maxRow = mysql_fetch_row(pResult);
			dwMaxUin = atoi(maxRow[2])+1;
		}
		else
		{
			dwMaxUin = 1;
		}

		memset(szCommand, 0, 1024);
		sprintf(szCommand, "INSERT INTO %s VALUES (\'%s\',\'%s\', %u, %u, %u, \'%s\');", "account", requestRegister.szUserName, requestRegister.szPassword, dwMaxUin, 0, 0, "");
		pResult = NULL;
		nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
		if (nRet != S_OK)
		{
			std::cout << "insert new user into account table error, player_name="<<requestRegister.szUserName<<" ErrorID: "<<nRet << std::endl;
		}
		else
		{
			//����ɹ�����ʼ���������Ϣ�����ݽṹ
			m_nPlayerID = dwMaxUin;
			InitNewPlayerInfo(m_nPlayerID, requestRegister.szUserName);

			responseRegister.byResult    = S_OK;
			responseRegister.dwSessionID = m_SessionKey;
			responseRegister.dwUin       = dwMaxUin;
			/*memset(szCommand, 0, 1024);
			sprintf(szCommand, "select * from %s where user_name='%s'", "account", requestRegister.szUserName);
			MYSQL_RES *pResult = NULL;
			int nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);

			MYSQL_ROW row;
			int nRowCount = mysql_num_rows(pResult);
			if (nRowCount == 1)
			{
				row = mysql_fetch_row(pResult);
				if (mysql_num_fields(pResult) < 3)
				{
					mysql_free_result(pResult);
					return false;
				}
				else
				{
					m_nPlayerID = atoi(row[2]);
					InitNewPlayerInfo(m_nPlayerID, requestRegister.szUserName);
				}
			}*/
		}
	}

	char szSendBuffer[128];
	memset(szSendBuffer, 0, 128);
	int nBytesNeeded = responseRegister.Write(szSendBuffer+PACKET_HEAD_LENGTH);

	MSG_HEAD msgHead;
	msgHead.nPacketLength = PACKET_HEAD_LENGTH + nBytesNeeded;
	msgHead.dwUin = m_dwUin;
	msgHead.nCommandID = MSG_ID_RESPONSE_REGISTER;
	msgHead.Write(szSendBuffer);
	nBytesNeeded += PACKET_HEAD_LENGTH;
	AddSendMessage(szSendBuffer, nBytesNeeded);

	return nBytesProcessed;
}


//pengyuan 2014.8.18 ��������ɫ��Ϣ
int     CLoginPlayer::ProcessCreateCharacter(const char* szBuffer)
{
	int    nBytesProcessed = 0;

	REQUEST_CREATE_CHARACTER requestCreateCharacter;
	nBytesProcessed = requestCreateCharacter.Read(szBuffer);

	RESPONSE_CREATE_CHARACTER responseCreateCharacter;
	responseCreateCharacter.byResult = S_OK;

	char szCommand[1024];

	memset(szCommand, 0, 1024);
	sprintf(szCommand, "select * from %s where nick_name='%s'", "base_info", requestCreateCharacter.szNickName);
	MYSQL_RES *pResult = NULL;
	int nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	if (nRet == S_OK)//��ȷ���ǳ��Ƿ�����
	{
		//MYSQL_ROW row;
		int nRowCount = mysql_num_rows(pResult);
		if (nRowCount == 1)
		{
			responseCreateCharacter.byResult = ERROR_MSG_USER_EXIST;
			mysql_free_result(pResult);
		}
		else
		{
			memset(szCommand, 0, 1024);
			sprintf(szCommand, "select * from %s where dwUin=%u", "base_info", requestCreateCharacter.dwUin);
			MYSQL_RES *pResult = NULL;
			int nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
			if (nRet != S_OK)
			{
				responseCreateCharacter.byResult = ERROR_MSG_QUERY_FAIL;  //��ѯʧ��;
				mysql_free_result(pResult);
			}
			else
			{
				MYSQL_ROW row;
				int nRowCount = mysql_num_rows(pResult);
				if (nRowCount == 1)
				{
					row = mysql_fetch_row(pResult);

					if (mysql_num_fields(pResult) < 9)
					{
						mysql_free_result(pResult);
						responseCreateCharacter.byResult = ERROR_MSG_USER_NOTEXIST;
					}
					else//�������ݿ�д��
					{
						mysql_free_result(pResult);

						sprintf(szCommand, "update %s set career=%u, nick_name='%s' where dwUin=%u", "base_info", requestCreateCharacter.byCareerID, requestCreateCharacter.szNickName, requestCreateCharacter.dwUin);

						int nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
						if (nRet){
							std::cout << "nRet:" << nRet << std::endl;
						}
						responseCreateCharacter.byResult = S_OK;
					}
				}
				else
				{
					responseCreateCharacter.byResult = ERROR_MSG_USER_NOTEXIST;
					mysql_free_result(pResult);
				}
			}	
		}
	}


	char szSendBuffer[128];
	memset(szSendBuffer, 0, 128);
	int nBytesNeeded = responseCreateCharacter.Write(szSendBuffer+PACKET_HEAD_LENGTH);

	MSG_HEAD msgHead;
	msgHead.nPacketLength = PACKET_HEAD_LENGTH + nBytesNeeded;
	msgHead.dwUin = m_dwUin;
	msgHead.nCommandID = MSG_ID_RESPONSE_CREATE_CHARACTER;
	msgHead.Write(szSendBuffer);
	nBytesNeeded += PACKET_HEAD_LENGTH;
	AddSendMessage(szSendBuffer, nBytesNeeded);


	return nBytesProcessed;
}


//�����ݿ��еõ���ҵĻ�����Ϣ
bool    CLoginPlayer::GetPlayerBaseInfo(unsigned int dwUin, NOTIFY_PLAYER_BASE_INFO &baseInfo)
{
	char szCommand[1024];
	memset(szCommand, 0, 1024);
	sprintf(szCommand, "select * from %s where dwUin=%u", "base_info", dwUin);
	MYSQL_RES *pResult = NULL;
	int nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	if (nRet != S_OK)
	{
		return false;
	}

	MYSQL_ROW row;
	int nRowCount = mysql_num_rows(pResult);
	if (nRowCount == 1)
	{
		row = mysql_fetch_row(pResult);

		if (mysql_num_fields(pResult) < 9)
		{
			mysql_free_result(pResult);
			return false;
		}
		else
		{
			//��ȡ��һ�����Ϣ����
			baseInfo.dwUin = atoi(row[0]);
			baseInfo.dwSilver = atoi(row[1]);
			baseInfo.dwYuanbao = atoi(row[2]);
			baseInfo.dwCareer = atoi(row[3]);
			baseInfo.dwLevel = atoi(row[4]);
			baseInfo.byNickNameLength = strlen(row[5]);
			memcpy(baseInfo.szNickName, row[5], baseInfo.byNickNameLength);
			baseInfo.szNickName[baseInfo.byNickNameLength] = '\0';
			baseInfo.dwExperience = atoi(row[6]);
			baseInfo.dwPotentialPoint = atoi(row[7]);
			baseInfo.dwSkillPoint = atoi(row[8]);
			/*baseInfo.dwUin = atoi(row[0]);
			baseInfo.dwHomeLevel = atoi(row[1]);
			baseInfo.byHomeNameLength = strlen(row[2]);
			memcpy(baseInfo.szHomeName, row[2], baseInfo.byHomeNameLength);
			baseInfo.szHomeName[baseInfo.byHomeNameLength] = '\0';
			baseInfo.nModelID = atoi(row[3]);
			baseInfo.nLevel = atoi(row[4]);
			baseInfo.nCareer = atoi(row[5]);
			baseInfo.byNickNameLength = strlen(row[6]);
			memcpy(baseInfo.szNickName, row[6], baseInfo.byNickNameLength);
			baseInfo.szNickName[baseInfo.byNickNameLength] = '\0';
			baseInfo.byGender = atoi(row[7]);
			baseInfo.nMapID = atoi(row[8]);
			baseInfo.nMapPosX = atoi(row[9]);
			baseInfo.nMapPosY = atoi(row[10]);
			baseInfo.byTitleLength = strlen(row[11]);
			memcpy(baseInfo.szTitle, row[11], baseInfo.byTitleLength);
			baseInfo.szTitle[baseInfo.byTitleLength] = '\0';
			baseInfo.nHonorPoint = atoi(row[12]);
			baseInfo.dwExperience = atoi(row[13]);
			baseInfo.dwGold = atoi(row[14]);
			baseInfo.dwYuanbao = atoi(row[15]);
			baseInfo.dwHungry = atoi(row[16]);
			baseInfo.dwClean = atoi(row[17]);
			baseInfo.dwMood = atoi(row[18]);
			baseInfo.dwEnergy = atoi(row[19]);
			baseInfo.dwHP = atoi(row[20]);
			baseInfo.dwAttack = atoi(row[21]);
			baseInfo.dwDefense = atoi(row[22]);
			baseInfo.dwAgile = atoi(row[23]);
			baseInfo.dwIntelligence = atoi(row[24]);
			baseInfo.dwStrength = atoi(row[25]);
			baseInfo.dwDoubleHit = atoi(row[26]);
			baseInfo.dwToughness = atoi(row[27]);
			baseInfo.dwHit = atoi(row[28]);
			baseInfo.dwRunaround = atoi(row[29]);
			baseInfo.nFlourish = atoi(row[30]);
			baseInfo.dwAttrPoint = atoi(row[31]);*/

			mysql_free_result(pResult);
			return true;
		}

	}
	else
	{
		mysql_free_result(pResult);
		return false;
	}

	return false;
}


//�����ݿ��еõ���ҵĵ�����Ϣ
bool    CLoginPlayer::GetPlayerItemInfo(unsigned int dwUin)
{
	m_PlayerItemInfo.shTotalCount = 0;

	char szCommand[1024];
	memset(szCommand, 0, 1024);
	sprintf(szCommand, "select * from %s where dwUin=%u", "item_info", dwUin);
	MYSQL_RES *pResult = NULL;
	int nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	if (nRet != S_OK)
	{
		return false;
	}

	MYSQL_ROW row;
	int nRowCount = mysql_num_rows(pResult);

	if (nRowCount == 1)
	{
		row = mysql_fetch_row(pResult);

		if (mysql_num_fields(pResult) < 3)
		{
			mysql_free_result(pResult);
			return false;
		}
		else
		{
			//��ȡ��һ�����Ϣ����
			m_PlayerItemInfo.shTotalCount = atoi(row[1]);

			char* pData;
			char szItemBuffer[8192];
			memset(szItemBuffer, 0, 8192);
			unsigned   long   *nFieldLength = mysql_fetch_lengths(pResult);
			int nDataLen = (int)nFieldLength[2];

			if (row[2])
			{
				pData = (char*)row[2];
				memset(szItemBuffer, 0, 8192);
				mysql_real_escape_string(g_pMySQLInterface->GetMySQLHandle(), szItemBuffer, pData, nDataLen);

				int nOffset = 0;

				for (int i=0; i<m_PlayerItemInfo.shTotalCount; ++i)
				{
					int nReadedBytes = m_PlayerItemInfo.szItemInfo[i].Read(pData+nOffset);
					nOffset += nReadedBytes;
				}
			}
			
			mysql_free_result(pResult);
			return true;
		}

	}
	else
	{
		mysql_free_result(pResult);
		return false;
	}

	return false;
}


//�����ݿ��еõ���ҵĽ�����Ϣ
bool    CLoginPlayer::GetPlayerGeneralInfo(unsigned int dwUin)
{
	m_PlayerGeneralInfos.byGeneralCount = 0;

	char szCommand[1024];
	memset(szCommand, 0, 1024);
	sprintf(szCommand, "select * from %s where dwUin=%u", "general_info", dwUin);
	MYSQL_RES *pResult = NULL;
	int nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	if (nRet != S_OK)
	{
		return false;
	}

	MYSQL_ROW row;
	int nRowCount = mysql_num_rows(pResult);

	if (nRowCount == 1)
	{
		row = mysql_fetch_row(pResult);

		if (mysql_num_fields(pResult) < 3)
		{
			mysql_free_result(pResult);
			return false;
		}
		else
		{
			//��ȡ���ӵ�еĽ�����Ŀ
			m_PlayerGeneralInfos.byGeneralCount = atoi(row[1]);

			char* pData;
			char szGeneralBuffer[8192];
			memset(szGeneralBuffer, 0, 8192);
			unsigned   long   *nFieldLength = mysql_fetch_lengths(pResult);
			int nDataLen = (int)nFieldLength[2];

			if (row[2])
			{
				pData = (char*)row[2];
				memset(szGeneralBuffer, 0, 8192);
				mysql_real_escape_string(g_pMySQLInterface->GetMySQLHandle(), szGeneralBuffer, pData, nDataLen);

				int nOffset = 0;

				for (int i=0; i<m_PlayerGeneralInfos.byGeneralCount; ++i)
				{
					int nReadedBytes = m_PlayerGeneralInfos.szGeneralInfos[i].Read(pData+nOffset);
					nOffset += nReadedBytes;
				}
			}

			mysql_free_result(pResult);
			return true;
		}

	}
	else
	{
		mysql_free_result(pResult);
		return false;
	}

	return false;
}


//��ҵ�����Ϣд���ݿ�
void    CLoginPlayer::WritePlayerItemInfo()
{
	char szBuffer[4096];
	memset(szBuffer, 0, 4096);

	char szEscapedBuffer[8192];
	memset(szEscapedBuffer, 0, 8192);

	int nBytesProcessed = 0;//m_PlayerItemInfo.Write(szBuffer);
	
	for (int i=0; i<m_PlayerItemInfo.shTotalCount; ++i)
	{
		int nTemp = m_PlayerItemInfo.szItemInfo[i].Write(szBuffer+nBytesProcessed);
		nBytesProcessed += nTemp;
	}

	mysql_real_escape_string(g_pMySQLInterface->GetMySQLHandle(), szEscapedBuffer, szBuffer, 4096);

	char szCommand[9216];
	memset(szCommand, 0, 9216);
	sprintf(szCommand, "update %s set item_number=%u, item_infos='%s' where dwUin=%u", "item_info", m_PlayerItemInfo.shTotalCount, szEscapedBuffer, GetUin());

	MYSQL_RES* pResult;
	int nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);

	if (nRet != 0)
	{
		std::cout << "udpate database error!" << std::endl;
	}
}

//��ע�����ң���ʼ��һϵ�е�����
void    CLoginPlayer::InitNewPlayerInfo(unsigned int dwUin, const char* szName)
{
	//�����ݿ��в�ѯ��Uin��Ȼ����г�ʼ����һϵ�й���
	//��base_info���в�������
	char szCommand[9216];
	memset(szCommand, 0, 9216);
	//sprintf(szCommand, "INSERT INTO base_info VALUES (%u,1,'unknown',2,1,0,'%s',1,1001,428,422,'',0,0,12000,10000,60,60,60,100,100,25,4,5,5,60,5,100,100,5, 0, 0);",  dwUin, szName);
	sprintf(szCommand, "INSERT INTO base_info VALUES (%u,0,0,0,1,'%s',0,0,0);",  dwUin, szName);
	MYSQL_RES *pResult = NULL;
	int nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	if (nRet != S_OK)
	{
		std::cout << "InitNewPlayerInfo Uin=" << dwUin << " insert into base_info table error, error id=" << nRet << std::endl;
	}

	//��ӵ���
	//AddDecorate(1, 669, 307);
	//AddDecorate(101, 480, 153);
	//AddDecorate(201, 480, 453);
	char szTempBuffer[512];
	memset(szTempBuffer, 0, 512);
	//EncodeDecorateInfo(szTempBuffer);
	char szItemInfo[4096];
	memset(szItemInfo, 0, 4096);
	char szItemBuffer[8192];
	memset(szItemBuffer, 0, 8192);
	char szEquipInfo[256];
	memset(szEquipInfo, 0, 256);
	char szEquipBuffer[512];
	memset(szEquipBuffer, 0, 512);

	mysql_real_escape_string(g_pMySQLInterface->GetMySQLHandle(), szItemBuffer, szItemInfo, 4096);
	mysql_real_escape_string(g_pMySQLInterface->GetMySQLHandle(), szEquipBuffer, szEquipInfo, 256);

	//�����߱��в�������
	memset(szCommand, 0, 9216);
	//sprintf(szCommand, "INSERT INTO item_info VALUES (%u, 0, '%s', 0, '%s', 0, '%s');", dwUin, szItemBuffer, szTempBuffer, szEquipBuffer);
	sprintf(szCommand, "INSERT INTO item_info VALUES (%u, 0, '%s');", dwUin, szItemBuffer);
	pResult = NULL;
	nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	if (nRet != S_OK)
	{
		std::cout << "InitNewPlayerInfo Uin=" << dwUin << " insert into item_info table error, error id=" << nRet<<std::endl;
	}

	//pengyuan 2014.8.22��������в�������
	memset(szCommand, 0, 9216);
	m_PlayerGeneralInfos.byGeneralCount = 0;

	memset(szItemInfo, 0, 4096);
	memset(szItemBuffer, 0, 8192);

	int nBytesProcessed = 0;
	for (int i=0; i<m_PlayerGeneralInfos.byGeneralCount; ++i)
	{
		int nTemp = m_PlayerGeneralInfos.szGeneralInfos[i].Write(szItemInfo+nBytesProcessed);
		nBytesProcessed += nTemp;
	}
	//m_PlayerGeneralInfos.Write(szItemInfo);
	mysql_real_escape_string(g_pMySQLInterface->GetMySQLHandle(), szItemBuffer, szItemInfo, 4096);
	
	sprintf(szCommand, "INSERT INTO general_info VALUES (%u, %u, '%s');", dwUin, m_PlayerGeneralInfos.byGeneralCount, szItemBuffer);
	pResult = NULL;
	nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	if (nRet != S_OK)
	{
		std::cout << "InitNewPlayerInfo Uin=" << dwUin << " insert into item_info table error, error id=" << nRet << std::endl;
	}

	//��������в�������
	/*memset(szCommand, 0, 5120);
	char szTaskBuffer[1952];
	memset(szTaskBuffer, 0, 1952);
	char szEscapedBuffer[3904];
	memset(szEscapedBuffer, 0, 3904);
	mysql_real_escape_string(g_pMySQLInterface->GetMySQLHandle(), szEscapedBuffer, szTaskBuffer, 1952);
	sprintf(szCommand, "INSERT INTO task_info VALUES (%u, '', '', 0, '%s');", dwUin, szEscapedBuffer);
	pResult = NULL;
	nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	if (nRet != S_OK)
	{
		LOG4CXX_ERROR(logger, "InitNewPlayerInfo Uin="<<dwUin<<" insert into task_info table error, error id="<<nRet);
	}*/

	//�����ѱ��в�������
	/*memset(szCommand, 0, 5120);
	char szFriendInfo[512];
	memset(szFriendInfo, 0, 512);
	memset(szEscapedBuffer, 0, 1024);
	mysql_real_escape_string(g_pMySQLInterface->GetMySQLHandle(), szEscapedBuffer, szFriendInfo, 512);
	sprintf(szCommand, "INSERT INTO friend_info VALUES (%u, 0,'%s', 0, '%s', 0, 0, '%s');", dwUin, szEscapedBuffer,szEscapedBuffer,szEscapedBuffer);
	pResult = NULL;
	nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	if (nRet != S_OK)
	{
		LOG4CXX_ERROR(logger, "InitNewPlayerInfo Uin="<<dwUin<<" insert into friend_info table error, error id="<<nRet);
	}*/

	//��������в�������
	/*memset(szCommand, 0, 5120);
	char szPetInfo[256];
	memset(szPetInfo, 0, 256);
	memset(szEscapedBuffer, 0, 1024);
	mysql_real_escape_string(g_pMySQLInterface->GetMySQLHandle(), szEscapedBuffer, szPetInfo, 256);
	sprintf(szCommand, "INSERT INTO pet_info VALUES (%u, %u,'%s');", dwUin, 0, szEscapedBuffer);
	pResult = NULL;
	nRet = g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	if (nRet != S_OK)
	{
		LOG4CXX_ERROR(logger, "InitNewPlayerInfo Uin="<<dwUin<<" insert into pet_info table error, error id="<<nRet);
	}*/
}



//����װ����Ϣ�������ݿ��ж�ȡ�������ַ�������ɾ����װ����Ϣ
void    CLoginPlayer::DecodeDecorateInfo(int nDecorateNumber, const char* szDecorateInfo)
{
	if (nDecorateNumber < 0 || nDecorateNumber > MAX_DECORATE_NUMBER)
	{
		m_nDecoNumber = 0;
		return;
	}

	m_nDecoNumber = nDecorateNumber;

	char *pDecorate = const_cast<char*>(szDecorateInfo);
	char szTemp[5];
	for (int i=0; i<m_nDecoNumber; ++i)
	{
		memset(szTemp, 0, 5);
		memcpy(szTemp, pDecorate, 4);
		sscanf(szTemp, "%x", &m_szDecoInfos[i].model_id);
		pDecorate += 4;

		memset(szTemp, 0, 5);
		memcpy(szTemp, pDecorate, 4);
		sscanf(szTemp, "%x", &m_szDecoInfos[i].pos_x);
		pDecorate += 4;

		memset(szTemp, 0, 5);
		memcpy(szTemp, pDecorate, 4);
		sscanf(szTemp, "%x", &m_szDecoInfos[i].pos_y);
		pDecorate += 4;

		memset(szTemp, 0, 5);
		memcpy(szTemp, pDecorate, 4);
		sscanf(szTemp, "%x", &m_szDecoInfos[i].dwValue);
		pDecorate += 4;
	}
}

//����װ����Ϣ����װ����Ϣ���룬׼����ŵ����ݿ���
void    CLoginPlayer::EncodeDecorateInfo(char* szDecorateInfo)
{
	memset(szDecorateInfo, 0, 512);

	char* pBuffer = szDecorateInfo;
	for (int i=0; i<m_nDecoNumber; ++i)
	{
		sprintf(pBuffer, "%4x%4x%4x%4x", m_szDecoInfos[i].model_id, m_szDecoInfos[i].pos_x, m_szDecoInfos[i].pos_y, m_szDecoInfos[i].dwValue);
		pBuffer += 16;
	}
}


