/**
* CloudServerManager.h : ��������������ͷ�ļ�.���ں���������������ͨ�ŵĹ���
* @author��zhouxicai
* @date��2018.09.05
* @��ע��
* */

#ifndef    __CLOUD_SERVER_MANAGER_H__
#define    __CLOUD_SERVER_MANAGER_H__

//#include <WinSock.h>

#include "../ConstDefines.h"
#include "net_protocol_command.h"
#include "net_protocol_login.h"
#include "CloudSocket.h"
//#include "../../game/GameServer/GamePlayer.h"
//#include "../../game/GameServer/GamePlayerManager.h"

#ifdef __WINDOWS__
    #pragma comment(lib, "ws2_32.lib")
#endif


class CGamePlayer;
class CGamePlayerManager;

class CCloudServerManager
{
public:
	CCloudServerManager();
	~CCloudServerManager(void);

	//��ʼ��������������
	bool    Init(const char *szServerName, const char* szIP, unsigned int uPort);

	//ѭ�������հ�����������
	void    Run();

	//������ֹ֮ͣ��ĺ���
	void    Stop();

	//����ָ����ַ���˿ڵķ�����
	bool    Connect(const char *szServerName, unsigned int uSrcPort, const char* szIP, unsigned int uPort);

	//������ҹ�����
	void    SetPlayerManager(/*pengyuan 2014.8.15 ע�͵�CGamePlayerManager* pPlayerMgr*/);

	//�������ӽ����ɹ�֮�󣬷��͸�������������
	void    OnNewConnection(const char* szHost, unsigned int dwPort, unsigned int dwSessionKey);

	//��������
	void    SendMessage(MSG_HEAD* msgHead, const char* szInfo, int nInfoLength);

protected:
	//�쳣����
	void    ProcessExceptions();

	//��������
	bool    ProcessInputs();

	//�������
	void    ProcessOutputs();

	//���������ӽ���
	bool    AcceptNewConnection();

	//�����յ��ķ�������
	void    ProcessPackets();

	//��������ҵ�¼��Ϣ
	int     ProcessLogin(const char* szBuffer);

	//������һ�����Ϣ
	int     ProcessPlayerBaseInfo(unsigned int dwSessionID, const char* szBuffer);

protected:
	//Ҫ�������ӵķ�����������
	const char*     m_pServerName;

	/*pengyuan 2014.8.15 ע�͵�CGamePlayerManager* m_pPlayerManager;*/

	//��game���������ӵ�socket
	CloudSocket    *m_pSocket;

	fd_set          m_ReadFDs[SELECT_MAX];
	fd_set          m_WriteFDs[SELECT_MAX];
	fd_set          m_ExceptFDs[SELECT_MAX];
	timeval         m_Timeout[SELECT_MAX];

	SOCKET          m_MinFD;
	SOCKET          m_MaxFD;
	int             m_nRecvBeginIndex;
	int             m_nRecvLength;
	char            m_RecvBuff[SERVER_RECV_BUFFER_LENGTH];
	int             m_nSendBeginIndex;
	int             m_nSendLength;
	char            m_SendBuffer[SERVER_SEND_BUFFER_LENGTH];

	//���ӹ����ķ�������socket�����Ϣ
	CloudSocket    *m_pConnectSocket;
	SOCKET          m_Socket;
	bool            isClient;
};


extern CCloudServerManager* g_pServerManager;

#endif
