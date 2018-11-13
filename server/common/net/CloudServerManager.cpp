/**
* CloudServerManager.h : ��������������ͷ�ļ�.���ں���������������ͨ�ŵĹ���
* @author��pengyuan
* @date��2011.10.24
* @��ע��
* */

#include "../stdafx.h"

#include <assert.h>
#include <iostream>
#include "CloudServerManager.h"

using namespace std;

extern    CGamePlayerManager* g_pGamePlayerManager;


CCloudServerManager::CCloudServerManager()
{
	m_pSocket = NULL;
	m_pConnectSocket = NULL;
	m_pServerName = NULL;

	m_nRecvBeginIndex = 0;
	m_nRecvLength     = 0;
	memset(m_RecvBuff, 0, SERVER_RECV_BUFFER_LENGTH);
	m_nSendBeginIndex = 0;
	m_nSendLength     = 0;
	memset(m_SendBuffer, 0, SERVER_SEND_BUFFER_LENGTH);

	FD_ZERO( &m_ReadFDs[SELECT_BAK] ) ;
	FD_ZERO( &m_WriteFDs[SELECT_BAK] ) ;
	FD_ZERO( &m_ExceptFDs[SELECT_BAK] ) ;

	m_Timeout[SELECT_BAK].tv_sec = 0;
	m_Timeout[SELECT_BAK].tv_usec = 0;

	m_MinFD = m_MaxFD = INVALID_SOCKET ;
	m_Socket = INVALID_SOCKET;

	isClient = false;
}

CCloudServerManager::~CCloudServerManager()
{

}

//������ҹ�����
void    CCloudServerManager::SetPlayerManager(/*pengyuan 2014.8.15 ע�͵�CGamePlayerManager* pPlayerMgr*/)
{
	//pengyuan 2014.8.15 ע�͵�m_pPlayerManager = pPlayerMgr;
}

//��ʼ��������������
bool    CCloudServerManager::Init(const char *szServerName, const char *szIP, unsigned int uPort)
{
	//���÷�����������
	m_pServerName = szServerName;

	//���Ե�ַ�Ͳ��Զ˿ں�
	m_pSocket = new CloudSocket(szIP, uPort);

	if (!m_pSocket->create())
	{
		throw 1;
	}

	//����Ϊ����ģʽ
	if (!m_pSocket->setReuseAddr())
	{
		throw(1);
	}

	m_pSocket->setNonBlocking() ;

	//�󶨶˿�
	if (!m_pSocket->Bind(uPort))
	{
		throw(1);
	}

	//������Ϣ���д�С
	if (!m_pSocket->Listen(1024))
	{
		throw(1);
	}

	FD_SET(m_pSocket->m_SocketID, &m_ReadFDs[SELECT_BAK]);
	FD_SET(m_pSocket->m_SocketID, &m_WriteFDs[SELECT_BAK]);
	FD_SET(m_pSocket->m_SocketID, &m_ExceptFDs[SELECT_BAK]);

	m_MinFD = m_MaxFD = m_pSocket->m_SocketID;

	m_Timeout[SELECT_BAK].tv_sec = 0;
	m_Timeout[SELECT_BAK].tv_usec = 0;

	return true;
}

//����ָ����ַ���˿ڵķ�����
bool    CCloudServerManager::Connect(const char *szServerName, unsigned int uSrcPort, const char* szIP, unsigned int uPort)
{
	if (!m_pSocket)
	{
		m_pServerName = szServerName;

		//���Ե�ַ�Ͳ��Զ˿ں�
		m_pSocket = new CloudSocket(szIP, uPort);

		if (!m_pSocket->create())
		{
			throw(1);
		}

		//����Ϊ����ģʽ
		/*if (!m_pSocket->setReuseAddr())
		{
			throw(1);
		}*/

		//�󶨶˿�
		if (!m_pSocket->Bind(uSrcPort))
		{
			throw(1);
		}

		if (m_pSocket->Connect(szIP, uPort))
		{
			m_pSocket->setNonBlocking() ;

			//m_pSocket->setLinger(0);

			FD_SET(m_pSocket->m_SocketID, &m_ReadFDs[SELECT_BAK]);
			//FD_SET(m_pSocket->m_SocketID, &m_WriteFDs[SELECT_BAK]);
			//FD_SET(m_pSocket->m_SocketID, &m_ExceptFDs[SELECT_BAK]);

			m_MinFD = m_MaxFD = m_pSocket->m_SocketID;

			m_Timeout[SELECT_BAK].tv_sec = 0;
			m_Timeout[SELECT_BAK].tv_usec = 0;

			isClient = true;

			return true;
		}

	}

	
	return false;
}

//ѭ�������հ�����������
void    CCloudServerManager::Run()
{
	//select
	m_Timeout[SELECT_USE].tv_sec  = m_Timeout[SELECT_BAK].tv_sec;
	m_Timeout[SELECT_USE].tv_usec = m_Timeout[SELECT_BAK].tv_usec;

	m_ReadFDs[SELECT_USE]   = m_ReadFDs[SELECT_BAK];
	m_WriteFDs[SELECT_USE]  = m_WriteFDs[SELECT_BAK];
	m_ExceptFDs[SELECT_USE] = m_ExceptFDs[SELECT_BAK];

	FD_SET(m_pSocket->m_SocketID, &m_ReadFDs[SELECT_USE]);
	//FD_SET(m_pSocket->m_SocketID, &m_WriteFDs[SELECT_USE]);
	//FD_SET(m_pSocket->m_SocketID, &m_ExceptFDs[SELECT_USE]);
	if (m_Socket != INVALID_SOCKET)
	{
		FD_SET(m_Socket, &m_ReadFDs[SELECT_USE]);
		if (m_nSendLength > (int)sizeof(tagMsgHead))
		{
			FD_SET(m_Socket, &m_WriteFDs[SELECT_USE]);
		}
		
		//FD_SET(m_Socket, &m_ExceptFDs[SELECT_USE]);
	}

	int result;
	result = select( (int)m_MaxFD+1 , &m_ReadFDs[SELECT_USE] , &m_WriteFDs[SELECT_USE] , &m_ExceptFDs[SELECT_USE] , &m_Timeout[SELECT_USE] );

	//int nError = WSAGetLastError();
	if (result == SOCKET_ERROR)
	{
		
		assert(false);
	}
	if (result)
	{
		std::cout << m_pServerName<<"  select �¼������"<<result << std::endl;
	}

	//���ߴ���
	ProcessExceptions();

	ProcessInputs();

	ProcessOutputs();
}

//������ֹ֮ͣ��ĺ���
void    CCloudServerManager::Stop()
{

}

//�쳣����
void    CCloudServerManager::ProcessExceptions()
{

}

//��������
bool    CCloudServerManager::ProcessInputs()
{
	//bool ret = false ;

	if (m_MinFD == INVALID_SOCKET && m_MaxFD == INVALID_SOCKET)
	{ 
		return true ;
	}

	//�����ӽ��룺һ���������50�������ӽ���
	if( FD_ISSET(m_pSocket->m_SocketID, &m_ReadFDs[SELECT_USE]) )
	{
		AcceptNewConnection();
	}

	if( FD_ISSET( m_Socket, &m_ReadFDs[SELECT_USE] ) )
	{
		int nReceived = 0;
		if( (m_nRecvLength + 4*1024) >= SERVER_RECV_BUFFER_LENGTH )
		{
			memmove(m_RecvBuff, m_RecvBuff+m_nRecvBeginIndex, m_nRecvBeginIndex);
			m_nRecvLength = m_nRecvBeginIndex;
			m_nRecvBeginIndex = 0;
		}

		nReceived = recv(m_Socket, m_RecvBuff+m_nRecvBeginIndex, SERVER_RECV_BUFFER_LENGTH-m_nRecvBeginIndex, 0);

		if (nReceived <= 0)
		{
			//unsigned int uLastError = WSAGetLastError();
			//LOG4CXX_ERROR(logger, "������������"<<m_pSocket->m_Host<<"��������룺"<<uLastError);
			m_pSocket->Close();
			//Clean();

			return false;
		}

		std::cout << "���շ��������ݴ�С��" << std::endl;

		m_nRecvBeginIndex += nReceived;
		m_nRecvLength += nReceived;

		ProcessPackets();
	}
	
	return true;
}

//�������
void    CCloudServerManager::ProcessOutputs()
{
	//bool ret = false ;

	if (m_MinFD == INVALID_SOCKET && m_MaxFD == INVALID_SOCKET)
	{ 
		return;
	}

	if( FD_ISSET(m_pSocket->m_SocketID, &m_WriteFDs[SELECT_USE]) )
	{
		//m_pSocket->Send("hello,", 6, 0);
	}

	if (FD_ISSET( m_Socket, &m_WriteFDs[SELECT_USE] ))
	{
		while(m_nSendLength > (int)sizeof(tagMsgHead))
		{
			int nRet = send(m_Socket, m_SendBuffer+m_nSendBeginIndex, m_nSendLength, 0);

			m_nSendBeginIndex += nRet;
			m_nSendLength -= nRet;

			if((SERVER_SEND_BUFFER_LENGTH - m_nSendBeginIndex) < MAX_PACKAGE_LENGTH)
			{
				memmove(m_SendBuffer, m_SendBuffer+m_nSendBeginIndex, m_nSendLength);
				m_nSendBeginIndex = 0;
			}
		}
	}
	
}

//���������ӽ���
bool    CCloudServerManager::AcceptNewConnection()
{
	bool ret = false ;

	int fd = INVALID_SOCKET ;

	//���ܿͻ��˽���Socket���
	SOCKADDR_IN socketAddr;
	memset(&socketAddr, 0, sizeof(socketAddr));
	unsigned int addrlen = sizeof(SOCKADDR_IN) ;
	
	SOCKET newSocket = m_pSocket->Accept( (struct sockaddr *)(&socketAddr), &addrlen ) ;
	if( newSocket == INVALID_SOCKET )
		return false ;

	//strncpy( m_pConnectSocket->m_Host, inet_ntoa(m_pConnectSocket->m_SockAddr.sin_addr), IP_SIZE-1 ) ;
	//m_pConnectSocket->m_Port = m_pConnectSocket->m_SockAddr.sin_port;

	fd = (int)newSocket;
	if( fd == INVALID_SOCKET )
	{
		assert(false) ;
		return false;
	}
#ifdef __WINDOWS__
	u_long opCode = 1;
	ret = ioctlsocket( newSocket, FIONBIO, &opCode);
	if( ret == SOCKET_ERROR )
	{
		assert(false) ;
		return false;
	}

	if( m_pConnectSocket->getSockError() )
	{
		assert(false) ;
		return false;
	}
#endif
#ifdef __LINUX__
	int flags = fcntl(newSocket, F_GETFL, 0);
	flags |= O_NONBLOCK;

	fcntl(newSocket, F_SETFL, flags);
#endif

	struct linger ling;
	ling.l_onoff = 0;
	ling.l_linger = 0;
	ret = setsockopt( newSocket , SOL_SOCKET , SO_LINGER , (char*)&ling , sizeof(ling) );
	if( ret == SOCKET_ERROR )
	{	
		assert(false) ;
		return false;
	}

	/*FD_SET(newSocket, &m_ReadFDs[SELECT_USE]);
	FD_SET(newSocket, &m_WriteFDs[SELECT_USE]);
	FD_SET(newSocket, &m_ExceptFDs[SELECT_USE]);*/

	if (newSocket > m_MaxFD)
	{
		m_MaxFD = newSocket;
	}
	if (newSocket < m_MinFD)
	{
		m_MinFD = newSocket;
	}

	m_Timeout[SELECT_BAK].tv_sec = 0;
	m_Timeout[SELECT_BAK].tv_usec = 0;

	m_Socket = newSocket;

	//��ʱ��ӡ������־
	char szInfo[256];
	sprintf(szInfo, "  %s���������ӳɹ���IP��ַ��%s, �˿ںţ�%d", m_pServerName, inet_ntoa(socketAddr.sin_addr), ntohs(socketAddr.sin_port));
	std::cout << szInfo << std::endl;

	return true;
}

//�����յ��ķ�������
void    CCloudServerManager::ProcessPackets()
{
	int nBeginIndex = m_nRecvBeginIndex - m_nRecvLength;
	if (nBeginIndex < 0 )
	{
		return;
	}

	MSG_HEAD msgHead;
	memcpy(&msgHead, m_RecvBuff+nBeginIndex, sizeof(tagMsgHead));
	int nPacketLength = ntohl(msgHead.nPacketLength);

	while(nPacketLength >= m_nRecvLength)
	{
		int    dwUin = ntohl(msgHead.dwUin);
		int    nCommandID = ntohl(msgHead.nCommandID);
		int    nBytesProcessed = 12;

		const char* szBuffer = m_RecvBuff+nBeginIndex+12;

		switch (nCommandID)
		{
		case MSG_ID_NEW_PLAYER_CONNECT:
			nBytesProcessed += ProcessLogin(szBuffer);
			break;
		case MSG_ID_PLAYER_BASE_INFO:
			nBytesProcessed += ProcessPlayerBaseInfo(dwUin, szBuffer);
			break;
		default:break;
		}

		m_nRecvLength -= nBytesProcessed;

		if (m_nRecvLength > (int)sizeof(int))
		{
			nPacketLength = ntohl((u_long)(m_RecvBuff + m_nRecvBeginIndex - m_nRecvLength));
		}
		else
		{
			nPacketLength = -1;
		}
	}
}

//���ﴦ���յ��������Login����Ϣ
int    CCloudServerManager::ProcessLogin(const char *szBuffer)
{
	NEW_LOGIN newLogin;
	int nBytesProcessed = newLogin.Read(szBuffer);

	/*pengyuan 2014.8.15 ע�͵�
	if (m_pPlayerManager)
	{
		m_pPlayerManager->AddPlayer(&newLogin);
	}*/

	return nBytesProcessed;
}

//������һ�����Ϣ
int    CCloudServerManager::ProcessPlayerBaseInfo(unsigned int dwSessionID, const char *szBuffer)
{
	int nBytesProcessed = 0;

	/*pengyuan 2014.8.15 ע�͵�
	if (m_pPlayerManager)
	{
		nBytesProcessed = m_pPlayerManager->ProcessPlayerBaseInfo(dwSessionID, szBuffer);
	}*/

	return nBytesProcessed;
}

//�������ӽ����ɹ�֮�󣬷��͸�������������
void    CCloudServerManager::OnNewConnection(const char* szHost, unsigned int dwPort, unsigned int dwSessionKey)
{
	return;
	if (dwSessionKey == INVALID_SESSION_ID)
	{
		return;
	}

	NEW_LOGIN newLogin;
	newLogin.dwSessionID = dwSessionKey;
	newLogin.byIPLength = strlen(szHost);
	memcpy(newLogin.szHost, szHost, newLogin.byIPLength);
	newLogin.dwPort = dwPort;

	char szSendBuffer[2048];
	memset(szSendBuffer, 0, 2048);
	int nBytesNeeded = newLogin.Write(szSendBuffer);

	MSG_HEAD msgHead;
	msgHead.nPacketLength = sizeof(MSG_HEAD) + nBytesNeeded;
	msgHead.dwUin = 0;
	msgHead.nCommandID = MSG_ID_NEW_PLAYER_CONNECT;
	int nHeadLength = msgHead.Write(m_SendBuffer+m_nSendBeginIndex+m_nSendLength);
	m_nSendLength += nHeadLength;
	memcpy(m_SendBuffer+m_nSendBeginIndex+m_nSendLength, szSendBuffer, nBytesNeeded);
	m_nSendLength += nBytesNeeded;
	
	return;
}

//��������
void     CCloudServerManager::SendMessage(MSG_HEAD* msgHead, const char* szInfo, int nInfoLength)
{
	int nHeadLength = msgHead->Write(m_SendBuffer+m_nSendBeginIndex+m_nSendLength);
	m_nSendLength += nHeadLength;
	memcpy(m_SendBuffer+m_nSendBeginIndex+m_nSendLength, szInfo, nInfoLength);
	m_nSendLength += nInfoLength;
}




