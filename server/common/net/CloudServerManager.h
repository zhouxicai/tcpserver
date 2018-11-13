/**
* CloudServerManager.h : 服务器管理器的头文件.用于和其他服务器进行通信的功能
* @author：zhouxicai
* @date：2018.09.05
* @备注：
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

	//初始化服务器管理器
	bool    Init(const char *szServerName, const char* szIP, unsigned int uPort);

	//循环调用收包，发包处理
	void    Run();

	//服务器停止之后的后处理
	void    Stop();

	//连接指定地址，端口的服务器
	bool    Connect(const char *szServerName, unsigned int uSrcPort, const char* szIP, unsigned int uPort);

	//设置玩家管理器
	void    SetPlayerManager(/*pengyuan 2014.8.15 注释掉CGamePlayerManager* pPlayerMgr*/);

	//在新连接建立成功之后，发送给服务器管理器
	void    OnNewConnection(const char* szHost, unsigned int dwPort, unsigned int dwSessionKey);

	//发送数据
	void    SendMessage(MSG_HEAD* msgHead, const char* szInfo, int nInfoLength);

protected:
	//异常处理
	void    ProcessExceptions();

	//处理输入
	bool    ProcessInputs();

	//处理输出
	void    ProcessOutputs();

	//接受新连接接入
	bool    AcceptNewConnection();

	//处理收到的服务器包
	void    ProcessPackets();

	//处理新玩家登录消息
	int     ProcessLogin(const char* szBuffer);

	//处理玩家基本信息
	int     ProcessPlayerBaseInfo(unsigned int dwSessionID, const char* szBuffer);

protected:
	//要接受连接的服务器的名字
	const char*     m_pServerName;

	/*pengyuan 2014.8.15 注释掉CGamePlayerManager* m_pPlayerManager;*/

	//与game服务器连接的socket
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

	//连接过来的服务器的socket相关信息
	CloudSocket    *m_pConnectSocket;
	SOCKET          m_Socket;
	bool            isClient;
};


extern CCloudServerManager* g_pServerManager;

#endif
