/**
* net_protocol_game.h : 游戏服务器的协议定义文件.
* @author：pengyuan
* @date：2011.10.27
* @备注：
* */

#ifndef    __NET_PROTOCOL_GAME_H__
#define    __NET_PROTOCOL_GAME_H__

//#include <WinSock.h>

#include "net_protocol_command.h"
#include "net_protocol_login.h"

//#pragma pack(1)

typedef struct tagRequestGameLogin
{
	unsigned int     dwSessionID;
	unsigned int     dwUin;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwSessionID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwSessionID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwSessionID = ntohl(dwSessionID);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwUin = ntohl(dwUin);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_GAME_LOGIN, *pREQUEST_GAME_LOGIN;


typedef struct tagResponseGameLogin
{
	unsigned char    byResult;
	unsigned int     dwTime;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwTime = htonl(dwTime);
		memcpy(szBuffer+nBytesProcessed, &dwTime, sizeof(int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwTime, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}RESPONSE_GAME_LOGIN, *pRESPONSE_GAME_LOGIN;


//心跳包请求
typedef struct tagRequestGameHeartBeat
{
	unsigned int    dwIndex;

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwIndex = ntohl(dwIndex);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_GAME_HEART_BEAT, *pREQUEST_GAME_HEART_BEAT;


//心跳包回应
typedef struct tagResponseGameHeartBeat
{
	unsigned int    dwIndex;
	unsigned int    dwTime;

	int Write(char* szBuffer)
	{
		int    nBytesProcessed = 0;

		//dwIndex = htonl(dwIndex);
		memcpy(szBuffer+nBytesProcessed, &dwIndex, sizeof(int));
		nBytesProcessed += sizeof(int);

		//dwTime = htonl(dwTime);
		memcpy(szBuffer+nBytesProcessed, &dwTime, sizeof(int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

}RESPONSE_GAME_HEART_BEAT, *pRESPONSE_GAME_HEART_BEAT;


//请求聊天
typedef struct tagRequestChat
{
	int     nChannelID;
	int     nNameLength;
	char    szUserName[16];
	int     nContentLength;
	char    szContent[240];          //目前暂定最大160个汉字

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nChannelID, szBuffer+nBytesProcessed, sizeof(int));
		//nChannelID = ntohl(nChannelID);
		nBytesProcessed += sizeof(int);

		memcpy(&nNameLength, szBuffer+nBytesProcessed, sizeof(int));
		//nNameLength = ntohl(nNameLength);
		nBytesProcessed += sizeof(int);

		memcpy(szUserName, szBuffer+nBytesProcessed, nNameLength);
		nBytesProcessed += nNameLength;

		memcpy(&nContentLength, szBuffer+nBytesProcessed, 4);
		//nContentLength = ntohl(nContentLength);
		nBytesProcessed += sizeof(int);

		memcpy(szContent, szBuffer+nBytesProcessed, nContentLength);
		nBytesProcessed += nContentLength;

		return nBytesProcessed;
	}
}REQUEST_CHAT, *pREQUEST_CHAT;


//通知聊天消息
typedef struct tagNotifyChat
{
	int               nChannelID;
	unsigned char     byNameLength;
	char              szUserName[16];
	unsigned char     byContentLength;
	char              szContent[240];          //目前暂定最大160个汉字

	int Write(char* szBuffer)
	{
		int    nBytesProcessed = 0;

		//nChannelID = htonl(nChannelID);
		memcpy(szBuffer+nBytesProcessed, &nChannelID, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &byNameLength, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, szUserName, byNameLength);
		nBytesProcessed += byNameLength;

		memcpy(szBuffer+nBytesProcessed, &byContentLength, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, szContent, byContentLength);
		nBytesProcessed += byContentLength;

		return nBytesProcessed;
	}
}NOTIFY_CHAT, *pNOTIFY_CHAT;


typedef  NOTIFY_PLAYER_BASE_INFO  NOTIFY_PLAYER_ENTER_GAME;

typedef NOTIFY_PLAYER_BASE_INFO NOTIFY_PLAYER_ENTER_REGION;


//#define    MSG_ID_NOTIFY_PLAYER_LEAVE_REGION               2021         //广播消息，通知新玩家离开同步域
typedef struct tagNotifyPlayerLeaveRegion
{
	unsigned int dwUin;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//dwUin = htonl(dwUin);
		memcpy(szBuffer, &dwUin, sizeof(unsigned int));
		//dwUin = ntohl(dwUin);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}NOTIFY_PLAYER_LEAVE_REGION, *pNOTIFY_PLAYER_LEAVE_REGION;

//#define    MSG_ID_NOTIFY_PLAYER_LOGOUT                     2023         //广播消息，通知有玩家离开游戏
typedef struct tagNotifyPlayerLogout
{
	unsigned int dwUin;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//dwUin = htonl(dwUin);
		memcpy(szBuffer, &dwUin, sizeof(unsigned int));
		//dwUin = ntohl(dwUin);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}NOTIFY_PLAYER_LOGOUT, *pNOTIFY_PLAYER_LOGOUT;

typedef struct tagCloudPoint
{
	tagCloudPoint()
	{
		X = 0;
		Y = 0;
	}

	int X;
	int Y;
}CLOUD_POINT, *pCLOUD_POINT;

typedef struct tagRequestPlayerWalk
{
	unsigned int dwTime;
	char         byPointNumber;
	CLOUD_POINT  points[8];

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwTime, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwTime = ntohl(dwTime);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byPointNumber, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		if (byPointNumber > 8)
		{
			return nBytesProcessed;
		}

		for (int i=0; i<byPointNumber; ++i)
		{
			memcpy(&points[i].X, szBuffer+nBytesProcessed, sizeof(int));
			//points[i].X = ntohl(points[i].X);
			nBytesProcessed += sizeof(int);

			memcpy(&points[i].Y, szBuffer+nBytesProcessed, sizeof(int));
			//points[i].Y = ntohl(points[i].Y);
			nBytesProcessed += sizeof(int);
		}

		return nBytesProcessed;
	}

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwTime, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byPointNumber, sizeof(char));
		nBytesProcessed += sizeof(char);

		if (byPointNumber > 8)
		{
			return nBytesProcessed;
		}

		for (int i=0; i<byPointNumber; ++i)
		{
			memcpy(szBuffer+nBytesProcessed, &points[i].X, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(szBuffer+nBytesProcessed, &points[i].Y, sizeof(int));
			nBytesProcessed += sizeof(int);
		}

		return nBytesProcessed;
	}

}REQUEST_PLAYER_WALK, *pREQUEST_PLAYER_WALK;

typedef struct tagResponsePlayerWalk
{
	unsigned char         byResult;
	unsigned int dwTime;
	char         byPointNumber;
	CLOUD_POINT  points[8];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwTime = htonl(dwTime);
		memcpy(szBuffer+nBytesProcessed, &dwTime, sizeof(unsigned int));
		//dwTime = ntohl(dwTime);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byPointNumber, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byPointNumber; ++i)
		{
			//points[i].X = htonl(points[i].X);
			memcpy(szBuffer+nBytesProcessed, &points[i].X, sizeof(int));
			//points[i].X = ntohl(points[i].X);
			nBytesProcessed += sizeof(int);

			//points[i].Y = htonl(points[i].Y);
			memcpy(szBuffer+nBytesProcessed, &points[i].Y, sizeof(int));
			//points[i].Y = ntohl(points[i].Y);
			nBytesProcessed += sizeof(int);
		}

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwTime, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byPointNumber, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byPointNumber; ++i)
		{
			memcpy(&points[i].X, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&points[i].Y, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);
		}

		return nBytesProcessed;
	}

}RESPONSE_PLAYER_WALK, *pRESPONSE_PLAYER_WALK;

typedef struct tagNotifyPlayerWalk
{
	unsigned int dwUin1;
	unsigned int dwTime;
	char         byPointNumber;
	CLOUD_POINT  points[8];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//dwUin1 = htonl(dwUin1);
		memcpy(szBuffer+nBytesProcessed, &dwUin1, sizeof(unsigned int));
		//dwUin1 = ntohl(dwUin1);
		nBytesProcessed += sizeof(unsigned int);

		//dwTime = htonl(dwTime);
		memcpy(szBuffer+nBytesProcessed, &dwTime, sizeof(unsigned int));
		//dwTime = ntohl(dwTime);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byPointNumber, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byPointNumber; ++i)
		{
			//points[i].X = htonl(points[i].X);
			memcpy(szBuffer+nBytesProcessed, &points[i].X, sizeof(int));
			//points[i].X = ntohl(points[i].X);
			nBytesProcessed += sizeof(int);

			//points[i].Y = htonl(points[i].Y);
			memcpy(szBuffer+nBytesProcessed, &points[i].Y, sizeof(int));
			//points[i].Y = ntohl(points[i].Y);
			nBytesProcessed += sizeof(int);
		}

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwUin1, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwTime, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byPointNumber, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byPointNumber; ++i)
		{
			memcpy(&points[i].X, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&points[i].Y, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);
		}

		return nBytesProcessed;
	}
}NOTIFY_PLAYER_WALK, *pNOTIFY_PLAYER_WALK;

typedef struct tagNotifyNPCInfo
{
	char        byNPCCount;
	int         nNPCIDs[32];
	CLOUD_POINT NPCPoss[32];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer, &byNPCCount, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byNPCCount; ++i)
		{
			//nNPCIDs[i] = htonl(nNPCIDs[i]);
			memcpy(szBuffer+nBytesProcessed, &nNPCIDs[i], sizeof(int));
			//nNPCIDs[i] = ntohl(nNPCIDs[i]);
			nBytesProcessed += sizeof(int);
		}

		for (int i=0; i<byNPCCount; ++i)
		{
			//NPCPoss[i].X = htonl(NPCPoss[i].X);
			memcpy(szBuffer+nBytesProcessed, &NPCPoss[i].X, sizeof(int));
			//NPCPoss[i].X = ntohl(NPCPoss[i].X);
			nBytesProcessed += sizeof(int);

			//NPCPoss[i].Y = htonl(NPCPoss[i].Y);
			memcpy(szBuffer+nBytesProcessed, &NPCPoss[i].Y, sizeof(int));
			nBytesProcessed += sizeof(int);
		}

		return nBytesProcessed;
	}
	
	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byNPCCount, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byNPCCount; ++i)
		{
			memcpy(&nNPCIDs[i], szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);
		}

		for (int i=0; i<byNPCCount; ++i)
		{
			memcpy(&NPCPoss[i].X, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&NPCPoss[i].Y, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);
		}

		return nBytesProcessed;
	}
}NOTIFY_NPC_INFO, *pNOTIFY_NPC_INFO;


typedef struct tagRequestTeleport
{
	unsigned int dwUin1;
	unsigned int dwSrcMapID;
	unsigned int dwDestMapID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwUin1, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwSrcMapID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwDestMapID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwUin1, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwUin1 = ntohl(dwUin1);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwSrcMapID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwSrcMapID = ntohl(dwSrcMapID);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwDestMapID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwDestMapID = ntohl(dwDestMapID);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_TELEPORT, *pREQUEST_TELEPORT;

typedef struct tagResponseTeleport
{
	unsigned char         byResult;
	unsigned int dwDestMapID;
	unsigned int dwInitPosX;
	unsigned int dwInitPosY;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwDestMapID = htonl(dwDestMapID);
		memcpy(szBuffer+nBytesProcessed, &dwDestMapID, sizeof(unsigned int));
		//dwDestMapID = ntohl(dwDestMapID);
		nBytesProcessed += sizeof(unsigned int);

		//dwInitPosX = htonl(dwInitPosX);
		memcpy(szBuffer+nBytesProcessed, &dwInitPosX, sizeof(unsigned int));
		//dwInitPosX = ntohl(dwInitPosX);
		nBytesProcessed += sizeof(unsigned int);

		//dwInitPosY = htonl(dwInitPosY);
		memcpy(szBuffer+nBytesProcessed, &dwInitPosY, sizeof(unsigned int));
		//dwInitPosY = ntohl(dwInitPosY);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwDestMapID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwInitPosX, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwInitPosY, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);


		return nBytesProcessed;
	}

}RESPONSE_TELEPORT, *pRESPONSE_TELEPORT;

typedef struct tagAttribute
{
	int  nAttrName;
	int  nAttrValue;
}ATTRIBUTE, *pATTRIBUTE;

typedef struct tagNotifyAttributeUpdate
{
	unsigned int  dwUin;
	unsigned char byAttrNumber;
	ATTRIBUTE     szAttr[4];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//dwUin = htonl(dwUin);
		memcpy(szBuffer+nBytesProcessed, &dwUin, sizeof(unsigned int));
		//dwUin = ntohl(dwUin);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byAttrNumber, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byAttrNumber; ++i)
		{
			//szAttr[i].nAttrName = htonl(szAttr[i].nAttrName);
			memcpy(szBuffer+nBytesProcessed, &szAttr[i].nAttrName, sizeof(int));
			//szAttr[i].nAttrName = ntohl(szAttr[i].nAttrName);
			nBytesProcessed += sizeof(int);

			//szAttr[i].nAttrValue = htonl(szAttr[i].nAttrValue);
			memcpy(szBuffer+nBytesProcessed, &szAttr[i].nAttrValue, sizeof(int));
			nBytesProcessed += sizeof(int);
		}

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byAttrNumber, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byAttrNumber; ++i)
		{
			memcpy(&szAttr[i].nAttrName, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&szAttr[i].nAttrValue, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);
		}

		return nBytesProcessed;
	}
}NOTIFY_ATTRIBUTE_UPDATE, *pNOTIFY_ATTRIBUTE_UPDATE;

//pengyuan 2012.2.12 关于挑战的协议
typedef struct tagRequestChallenge
{
	unsigned int dwChallengeType;
	unsigned int dwSrcUin;
	unsigned int dwDestUin;

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwChallengeType, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwSrcUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwDestUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwChallengeType, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwChallengeType = ntohl(dwChallengeType);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwSrcUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwSrcUin = ntohl(dwSrcUin);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwDestUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwDestUin = ntohl(dwDestUin);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}REQUEST_CHALLENGE, *pREQUEST_CHALLENGE;


//pengyuan 2012.11.30 关于战斗的协议，新增，原有的结构不适合使用
typedef struct tagRequestBattle
{
	unsigned int dwChallengeType;
	unsigned int dwSrcUin;
	unsigned int dwDestUin;

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwChallengeType, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwSrcUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwDestUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwChallengeType, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwSrcUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwDestUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_BATTLE, *pREQUEST_BATTLE;


typedef struct tagReponseChallenge
{
	unsigned char byResult;
	unsigned int  dwType;
	unsigned int  dwDestUin;
	int           nModelID;
	unsigned int  dwDestHP;                    //pengyuan 2012.9.12 新增战斗时候的对手总血量
	unsigned char byNickNameLength;            //昵称长度
	char          szNickName[16];              //昵称

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwType = htonl(dwType);
		memcpy(szBuffer+nBytesProcessed, &dwType, sizeof(unsigned int));
		//dwType = ntohl(dwType);
		nBytesProcessed += sizeof(unsigned int);

		//dwDestUin = htonl(dwDestUin);
		memcpy(szBuffer+nBytesProcessed, &dwDestUin, sizeof(unsigned int));
		//dwDestUin = ntohl(dwDestUin);
		nBytesProcessed += sizeof(unsigned int);

		//nModelID = htonl(nModelID);
		memcpy(szBuffer+nBytesProcessed, &nModelID, sizeof(int));
		//nModelID = ntohl(nModelID);
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &dwDestHP, sizeof(unsigned int));          //pengyuan 2012.9.12 新增战斗时候的对手总
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byNickNameLength, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, szNickName, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		return nBytesProcessed;
	}
	
		int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwType, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwDestUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&nModelID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&dwDestHP, szBuffer+nBytesProcessed, sizeof(unsigned int)); 
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byNickNameLength, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szNickName, szBuffer+nBytesProcessed, byNickNameLength);
		szNickName[byNickNameLength] = '\0';
		nBytesProcessed += byNickNameLength;

		return nBytesProcessed;
	}

}RESPONSE_CHALLENGE, *pRESPONSE_CHALLENGE;


typedef struct tagBattleOffenderInfo
{
	unsigned char    byIndex;          //站位的索引
	unsigned char    byType;           //表示是人，宠，还是npc
	unsigned int     dwDestUin;
	int              nModelID;
	unsigned int     dwDestHP;         //pengyuan 2012.11.30 新增战斗时候的总血量
	unsigned char    byNickNameLength; //昵称长度
	char             szNickName[16];   //昵称

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer, &byIndex, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byType, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &dwDestUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &nModelID, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &dwDestHP, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byNickNameLength, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, szNickName, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byIndex, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byType, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwDestUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&nModelID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&dwDestHP, szBuffer+nBytesProcessed, sizeof(unsigned int)); 
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byNickNameLength, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szNickName, szBuffer+nBytesProcessed, byNickNameLength);
		szNickName[byNickNameLength] = '\0';
		nBytesProcessed += byNickNameLength;

		return nBytesProcessed;
	}
}BATTLE_OFFENDER_INFO, *pBATTLE_OFFENDER_INFO;


typedef struct tagResponseBattle
{
	unsigned char           byResult;
	unsigned char           byMyCount;
	BATTLE_OFFENDER_INFO    szMyInfos[2];
	unsigned char           byOffenderCount;
	BATTLE_OFFENDER_INFO    szOffenderInfos[4];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byMyCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byMyCount; ++i)
		{
			int nTemp = szMyInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		memcpy(szBuffer+nBytesProcessed, &byOffenderCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byOffenderCount; ++i)
		{
			int nTemp = szOffenderInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byMyCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byMyCount; ++i)
		{
			int nTemp = szMyInfos[i].Read(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		memcpy(&byOffenderCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byOffenderCount; ++i)
		{
			int nTemp = szOffenderInfos[i].Read(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

}RESPONSE_BATTLE, *pRESPONSE_BATTLE;


typedef struct tagRequestRound
{
	unsigned int lastRoundIndex;
	unsigned int lastAttackUin;

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &lastRoundIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &lastAttackUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
	
	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&lastRoundIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//lastRoundIndex = ntohl(lastRoundIndex);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&lastAttackUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//lastAttackUin = ntohl(lastAttackUin);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_ROUND, *pREQUEST_ROUND;

typedef struct tagResponseRound
{
	unsigned int nRoundIndex;
	unsigned int dwAttackerUin;
	unsigned int dwDefenderUin;
	unsigned int dwDamageValue;
	int          nAttackRandType;
	int          nDefendRandType;

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//nRoundIndex = htonl(nRoundIndex);
		memcpy(szBuffer+nBytesProcessed, &nRoundIndex, sizeof(unsigned int));
		//nRoundIndex = ntohl(nRoundIndex);
		nBytesProcessed += sizeof(unsigned int);

		//dwAttackerUin = htonl(dwAttackerUin);
		memcpy(szBuffer+nBytesProcessed, &dwAttackerUin, sizeof(unsigned int));
		//dwAttackerUin = ntohl(dwAttackerUin);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwDefenderUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		//dwDamageValue = htonl(dwDamageValue);
		memcpy(szBuffer+nBytesProcessed, &dwDamageValue, sizeof(unsigned int));
		//dwDamageValue = ntohl(dwDamageValue);
		nBytesProcessed += sizeof(unsigned int);

		//nAttackRandType = htonl(nAttackRandType);
		memcpy(szBuffer+nBytesProcessed, &nAttackRandType, sizeof(int));
		//nAttackRandType = ntohl(nAttackRandType);
		nBytesProcessed += sizeof(int);

		//nDefendRandType = htonl(nDefendRandType);
		memcpy(szBuffer+nBytesProcessed, &nDefendRandType, sizeof(int));
		//nDefendRandType = ntohl(nDefendRandType);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nRoundIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwAttackerUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwDefenderUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwDamageValue, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&nAttackRandType, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nDefendRandType, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

}RESPONSE_ROUND, *pRESPONSE_ROUND;


typedef struct tagRequestBattleRound
{
	unsigned int lastRoundIndex;
	unsigned int lastAttackIndex;

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &lastRoundIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &lastAttackIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&lastRoundIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&lastAttackIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_BATTLE_ROUND, *pREQUEST_BATTLE_ROUND;


typedef struct tagResponseBattleRound
{
	unsigned int nRoundIndex;
	unsigned int dwAttackerIndex;
	unsigned int dwDefenderIndex;
	unsigned int dwDamageValue;
	int          nAttackRandType;
	int          nDefendRandType;

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &nRoundIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwAttackerIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwDefenderIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwDamageValue, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &nAttackRandType, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nDefendRandType, sizeof(int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nRoundIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwAttackerIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwDefenderIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwDamageValue, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&nAttackRandType, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nDefendRandType, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

}RESPONSE_BATTLE_ROUND, *pRESPONSE_BATTLE_ROUND;



typedef struct tagNotifyRoundEnd
{
	unsigned int dwWinnerUin;
	int          nMapID;
	unsigned int dwDingli;

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//dwWinnerUin = htonl(dwWinnerUin);
		memcpy(szBuffer+nBytesProcessed, &dwWinnerUin, sizeof(unsigned int));
		//dwWinnerUin = ntohl(dwWinnerUin);
		nBytesProcessed += sizeof(unsigned int);

		//nMapID = htonl(nMapID);
		memcpy(szBuffer+nBytesProcessed, &nMapID, sizeof(int));
		//nMapID = ntohl(nMapID);
		nBytesProcessed += sizeof(int);

		//dwDingli = htonl(dwDingli);
		memcpy(szBuffer+nBytesProcessed, &dwDingli, sizeof(unsigned int));
		//dwDingli = ntohl(dwDingli);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwWinnerUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&nMapID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&dwDingli, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}NOTIFY_ROUND_END, *pNOTIFY_ROUND_END;

typedef struct tagItemInfo
{
	int    shGridIndex;
	int    shItemID;
	int    shItemCount;
	int    nLevel;
	unsigned char    byExtraCount;
	short    shExtraAttrs[MAX_EXTRA_ATTRS];
	unsigned char    byGemstoneCount;
	short    shGemstones[MAX_GEMSTONE];

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &shGridIndex, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &shItemID, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &shItemCount, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nLevel, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &byExtraCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int j=0;j<byExtraCount;j++)
		{
			memcpy(szBuffer+nBytesProcessed, &shExtraAttrs[j], sizeof(short));
			nBytesProcessed += sizeof(short);
		}

		memcpy(szBuffer+nBytesProcessed, &byGemstoneCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int j=0;j<byGemstoneCount;j++)
		{
			memcpy(szBuffer+nBytesProcessed, &shGemstones[j], sizeof(short));
			nBytesProcessed += sizeof(short);
		}

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&shGridIndex, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&shItemID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&shItemCount, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nLevel, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy( &byExtraCount,szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int j=0;j<byExtraCount;j++)
		{
			memcpy(&shExtraAttrs[j],szBuffer+nBytesProcessed,  sizeof(short));
			nBytesProcessed += sizeof(short);
		}

		memcpy(&byGemstoneCount,szBuffer+nBytesProcessed,  sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int j=0;j<byGemstoneCount;j++)
		{
			memcpy(&shGemstones[j],szBuffer+nBytesProcessed,  sizeof(short));
			nBytesProcessed += sizeof(short);
		}

		return nBytesProcessed;
	}
}ITEM_INFO, *pITEM_INFO;


typedef struct tagNotifyPlayerItemInfo
{
	unsigned char byCount;
	ITEM_INFO     Items[MAX_ITEM_NUMBER];

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer, &byCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byCount; ++i)
		{
			//Items[i].shGridIndex = htonl(Items[i].shGridIndex);
			memcpy(szBuffer+nBytesProcessed, &Items[i].shGridIndex, sizeof(int));
			//Items[i].shGridIndex = ntohl(Items[i].shGridIndex);
			nBytesProcessed += sizeof(int);

			//Items[i].shItemID = htonl(Items[i].shItemID);
			memcpy(szBuffer+nBytesProcessed, &Items[i].shItemID, sizeof(int));
			//Items[i].shItemID = ntohl(Items[i].shItemID);
			nBytesProcessed += sizeof(int);

			//Items[i].shItemCount = htonl(Items[i].shItemCount);
			memcpy(szBuffer+nBytesProcessed, &Items[i].shItemCount, sizeof(int));
			//Items[i].shItemCount = ntohl(Items[i].shItemCount);
			nBytesProcessed += sizeof(int);

			//Items[i].nLevel = htonl(Items[i].nLevel);
			memcpy(szBuffer+nBytesProcessed, &Items[i].nLevel, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(szBuffer+nBytesProcessed, &Items[i].byExtraCount, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<Items[i].byExtraCount;j++)
			{
				memcpy(szBuffer+nBytesProcessed, &Items[i].shExtraAttrs[j], sizeof(short));
				nBytesProcessed += sizeof(short);
			}

			memcpy(szBuffer+nBytesProcessed, &Items[i].byGemstoneCount, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<Items[i].byGemstoneCount;j++)
			{
				memcpy(szBuffer+nBytesProcessed, &Items[i].shGemstones[j], sizeof(short));
				nBytesProcessed += sizeof(short);
			}
		}

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byCount; ++i)
		{
			memcpy(&Items[i].shGridIndex, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&Items[i].shItemID, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&Items[i].shItemCount, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&Items[i].nLevel, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy( &Items[i].byExtraCount,szBuffer+nBytesProcessed, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<Items[i].byExtraCount;j++)
			{
				memcpy(&Items[i].shExtraAttrs[j],szBuffer+nBytesProcessed,  sizeof(short));
				nBytesProcessed += sizeof(short);
			}

			memcpy(&Items[i].byGemstoneCount,szBuffer+nBytesProcessed,  sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<Items[i].byGemstoneCount;j++)
			{
				memcpy(&Items[i].shGemstones[j],szBuffer+nBytesProcessed,  sizeof(short));
				nBytesProcessed += sizeof(short);
			}
		}

		return nBytesProcessed;
	}

}NOTIFY_PLAYER_ITEM_INFO, *pNOTIFY_PLAYER_ITEM_INFO;

typedef struct tagNotifyItemUpdate
{
	unsigned char byCount;
	ITEM_INFO     Items[8];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer, &byCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byCount; ++i)
		{
			//Items[i].shGridIndex = htonl(Items[i].shGridIndex);
			memcpy(szBuffer+nBytesProcessed, &Items[i].shGridIndex, sizeof(int));
			//Items[i].shGridIndex = ntohl(Items[i].shGridIndex);
			nBytesProcessed += sizeof(int);

			//Items[i].shItemID = htonl(Items[i].shItemID);
			memcpy(szBuffer+nBytesProcessed, &Items[i].shItemID, sizeof(int));
			//Items[i].shItemID = ntohl(Items[i].shItemID);
			nBytesProcessed += sizeof(int);

			//Items[i].shItemCount = htonl(Items[i].shItemCount);
			memcpy(szBuffer+nBytesProcessed, &Items[i].shItemCount, sizeof(int));
			//Items[i].shItemCount = ntohl(Items[i].shItemCount);
			nBytesProcessed += sizeof(int);

			//Items[i].nLevel = htonl(Items[i].nLevel);
			memcpy(szBuffer+nBytesProcessed, &Items[i].nLevel, sizeof(int));
			//Items[i].nLevel = ntohl(Items[i].nLevel);
			nBytesProcessed += sizeof(int);

			memcpy(szBuffer+nBytesProcessed, &Items[i].byExtraCount, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<Items[i].byExtraCount;j++)
			{
				memcpy(szBuffer+nBytesProcessed, &Items[i].shExtraAttrs[j], sizeof(short));
				nBytesProcessed += sizeof(short);
			}

			memcpy(szBuffer+nBytesProcessed, &Items[i].byGemstoneCount, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<Items[i].byGemstoneCount;j++)
			{
				memcpy(szBuffer+nBytesProcessed, &Items[i].shGemstones[j], sizeof(short));
				nBytesProcessed += sizeof(short);
			}
		}

		return nBytesProcessed;
	}

	int Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byCount, szBuffer, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byCount; ++i)
		{
			memcpy(&Items[i].shGridIndex, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&Items[i].shItemID, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&Items[i].shItemCount,  szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&Items[i].nLevel, szBuffer+nBytesProcessed,  sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&Items[i].byExtraCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<Items[i].byExtraCount;j++)
			{
				memcpy(&Items[i].shExtraAttrs[j], szBuffer+nBytesProcessed, sizeof(short));
				nBytesProcessed += sizeof(short);
			}

			memcpy(&Items[i].byGemstoneCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<Items[i].byGemstoneCount;j++)
			{
				memcpy(&Items[i].shGemstones[j], szBuffer+nBytesProcessed, sizeof(short));
				nBytesProcessed += sizeof(short);
			}
		}

		return nBytesProcessed;
	}

}NOTIFY_ITEM_UPDATE, *pNOTIFY_ITEM_UPDATE;

typedef struct tagReqeustBuyItem
{
	int shItemID;
	int shItemCount;

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&shItemID, szBuffer+nBytesProcessed, sizeof(int));
		//shItemID = ntohl(shItemID);
		nBytesProcessed += sizeof(int);

		memcpy(&shItemCount, szBuffer+nBytesProcessed, sizeof(int));
		//shItemCount = ntohl(shItemCount);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

	int	Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &shItemID, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &shItemCount, sizeof(int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

}REQUEST_BUY_ITEM, *pREQUEST_BUY_ITEM;


typedef struct tagResponseBuyItem
{
	unsigned char byResult;
	unsigned char byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}

}RESPONSE_BUY_ITEM, *pRESPONSE_BUY_ITEM;


typedef struct tagRequestUseItem
{
	int shGridIndex;
	int shItemID;
	int nLevel;
	int nItemCount;
	unsigned int dwObjectID;//当为宠物使用道具时所需要的道具

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&shGridIndex, szBuffer+nBytesProcessed, sizeof(int));
		//shGridIndex = ntohl(shGridIndex);
		nBytesProcessed += sizeof(int);

		memcpy(&shItemID, szBuffer+nBytesProcessed, sizeof(int));
		//shItemID = ntohl(shItemID);
		nBytesProcessed += sizeof(int);

		memcpy(&nLevel, szBuffer+nBytesProcessed, sizeof(int));
		//nLevel = ntohl(nLevel);
		nBytesProcessed += sizeof(int);

		memcpy(&nItemCount, szBuffer+nBytesProcessed, sizeof(int));
		//nItemCount = ntohl(nItemCount);
		nBytesProcessed += sizeof(int);

		memcpy(&dwObjectID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//nItemCount = ntohl(nItemCount);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

	int  Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &shGridIndex, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &shItemID, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nLevel, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nItemCount, sizeof(int));
		nBytesProcessed += sizeof(int);
		
		memcpy(szBuffer+nBytesProcessed, &dwObjectID, sizeof(unsigned int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

}REQUEST_USE_ITEM, *pREQUEST_USE_ITEM;


typedef struct tagResponseUseItem
{
	unsigned char byResult;
	unsigned char byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_USE_ITEM, *pRESPONSE_USE_ITEM;


typedef struct tagRequestSellItem
{
	int nGridIndex;
	int shItemID;
	int shItemCount;

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nGridIndex, szBuffer+nBytesProcessed, sizeof(int));
		//nGridIndex = ntohl(nGridIndex);
		nBytesProcessed += sizeof(int);

		memcpy(&shItemID, szBuffer+nBytesProcessed, sizeof(int));
		//shItemID = ntohl(shItemID);
		nBytesProcessed += sizeof(int);

		memcpy(&shItemCount, szBuffer+nBytesProcessed, sizeof(int));
		//shItemCount = ntohl(shItemCount);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

	int  Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &nGridIndex, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &shItemID, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &shItemCount, sizeof(int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

}REQUEST_SELL_ITEM, *pREQUEST_SELL_ITEM;


typedef struct tagResponseSellItem
{
	unsigned char byResult;
	unsigned char byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_SELL_ITEM, *pRESPONSE_SELL_ITEM;


typedef struct tagTaskCondition
{
	unsigned char byType;
	unsigned int  dwID;
	unsigned int  dwCount;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byType, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwID = htonl(dwID);
		memcpy(szBuffer+nBytesProcessed, &dwID, sizeof(unsigned int));
		//dwID = ntohl(dwID);
		nBytesProcessed += sizeof(unsigned int);

		//dwCount = htonl(dwCount);
		memcpy(szBuffer+nBytesProcessed, &dwCount, sizeof(unsigned int));
		//dwCount = ntohl(dwCount);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byType, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwID = ntohl(dwID);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwCount, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwCount = ntohl(dwCount);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	//写入DB，不需要进行字节序转化
	int    WriteToDB(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byType, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &dwID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwCount, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	//从DB读取，不需要进行字节序转化
	int    ReadFromDB(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byType, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwCount, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}TASK_CONDITION, *pTASK_CONDITION;


typedef struct tagTaskStatus
{
	unsigned int   dwTaskID;
	unsigned char  byTaskStatus;
	unsigned char  byFinishCount;
	unsigned int   dwFinishTime;
	unsigned char  byConditionCount;
	TASK_CONDITION szConditions[3];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//dwTaskID = htonl(dwTaskID);
		memcpy(szBuffer+nBytesProcessed, &dwTaskID, sizeof(unsigned int));
		//dwTaskID = ntohl(dwTaskID);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byTaskStatus, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byFinishCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwFinishTime = htonl(dwFinishTime);
		memcpy(szBuffer+nBytesProcessed, &dwFinishTime, sizeof(unsigned int));
		//dwFinishTime = ntohl(dwFinishTime);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byConditionCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byConditionCount; ++i)
		{
			int nTemp = szConditions[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwTaskID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwTaskID = ntohl(dwTaskID);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byTaskStatus, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byFinishCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwFinishTime, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwFinishTime = ntohl(dwFinishTime);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byConditionCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byConditionCount; ++i)
		{
			int nTemp = szConditions[i].Read(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

	//写入DB，不需要进行字节序转化
	int    WriteToDB(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwTaskID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byTaskStatus, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byFinishCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &dwFinishTime, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);


		memcpy(szBuffer+nBytesProcessed, &byConditionCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byConditionCount; ++i)
		{
			int nTemp = szConditions[i].WriteToDB(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

	//从DB读取，不需要进行字节序转化
	int    ReadFromDB(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwTaskID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byTaskStatus, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byFinishCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwFinishTime, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byConditionCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byConditionCount; ++i)
		{
			int nTemp = szConditions[i].ReadFromDB(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}
}TASK_STATUS, *pTASK_STATUS;


typedef struct tagNotifyRoleTaskData
{
	unsigned char byTaskCount;
	TASK_STATUS   szTaskStatus[30];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byTaskCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byTaskCount; ++i)
		{
			int nTemp = szTaskStatus[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byTaskCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byTaskCount; ++i)
		{
			int nTemp = szTaskStatus[i].Read(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

}NOTIFY_ROLE_TASK_DATA, *pNOTIFY_ROLE_TASK_DATA;

typedef struct tagFinishTaskInfo
{
	char    szFinishInfo[128];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer, szFinishInfo, 128);
		nBytesProcessed += 128;

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szFinishInfo, szBuffer+nBytesProcessed, 128);
		nBytesProcessed += 128;

		return nBytesProcessed;
	}
}NOTIFY_FINISH_TASK_INFO, *pNOTIFY_FINISH_TASK_INFO;


typedef struct tagNotifyRoleTaskStatus
{
	TASK_STATUS    taskStatus;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		nBytesProcessed += taskStatus.Write(szBuffer+nBytesProcessed);

		return nBytesProcessed;
	}
	/*unsigned int   dwTaskID;
	unsigned char  byTaskStatus;
	unsigned char  byConditionCount;
	TASK_CONDITION szConditions[3];

	int    Write(char* szBuffer)
	{
	int nBytesProcessed = 0;

	dwTaskID = htonl(dwTaskID);
	memcpy(szBuffer+nBytesProcessed, &dwTaskID, sizeof(unsigned int));
	dwTaskID = ntohl(dwTaskID);
	nBytesProcessed += sizeof(unsigned int);

	memcpy(szBuffer+nBytesProcessed, &byTaskStatus, sizeof(unsigned char));
	nBytesProcessed += sizeof(unsigned char);

	memcpy(szBuffer+nBytesProcessed, &byConditionCount, sizeof(unsigned char));
	nBytesProcessed += sizeof(unsigned char);

	for (int i=0; i<byConditionCount; ++i)
	{
	int nTemp = szConditions[i].Write(szBuffer+nBytesProcessed);
	nBytesProcessed += nTemp;
	}

	return nBytesProcessed;
	}*/
}NOTIFY_ROLE_TASK_STATUS, *pNOTIFY_ROLE_TASK_STATUS;

typedef struct tagRequestGetTask
{
	unsigned int dwUin;
	unsigned int dwTaskID;
	unsigned int dwGiveNPC;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwTaskID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwGiveNPC, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwUin = ntohl(dwUin);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwTaskID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwTaskID = ntohl(dwTaskID);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwGiveNPC, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwGiveNPC = ntohl(dwGiveNPC);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_GET_TASK, *pREQUEST_GET_TASK;


typedef struct tagResponseGetTask
{
	unsigned char byResult;
	unsigned int  dwTaskID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwTaskID = htonl(dwTaskID);
		memcpy(szBuffer+nBytesProcessed, &dwTaskID, sizeof(unsigned int));
		//dwTaskID = ntohl(dwTaskID);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwTaskID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}RESPONSE_GET_TASK, *pRESPONSE_GET_TASK;


typedef struct tagRequestFinishTask
{
	unsigned int dwUin;
	unsigned int dwTaskID;
	unsigned int dwReceiveNPC;
	unsigned int dwPointX;
	unsigned int dwPointY;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwTaskID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwReceiveNPC, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwPointX, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwPointY, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwUin = ntohl(dwUin);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwTaskID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwTaskID = ntohl(dwTaskID);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwReceiveNPC, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwReceiveNPC = ntohl(dwReceiveNPC);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwPointX, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwPointX = ntohl(dwPointX);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwPointY, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwPointY = ntohl(dwPointY);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}REQUEST_FINISH_TASK, *pREQUEST_FINISH_TASK;


typedef struct tagResponseFinishTask
{
	unsigned char byResult;
	unsigned int  dwTaskID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwTaskID = htonl(dwTaskID);
		memcpy(szBuffer+nBytesProcessed, &dwTaskID, sizeof(unsigned int));
		//dwTaskID = ntohl(dwTaskID);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwTaskID = htonl(dwTaskID);
		memcpy(&dwTaskID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwTaskID = ntohl(dwTaskID);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}RESPONSE_FINISH_TASK, *pRESPONSE_FINISH_TASK;


typedef struct tagRequestDropTask
{
	unsigned int dwUin;
	unsigned int dwTaskID;

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwUin = ntohl(dwUin);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwTaskID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwTaskID = ntohl(dwTaskID);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int     Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwUin, sizeof(unsigned int));
		//dwUin = ntohl(dwUin);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwTaskID, sizeof(unsigned int));
		//dwTaskID = ntohl(dwTaskID);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_DROP_TASK, *pREQUEST_DROP_TASK;


typedef struct tagResponseDropTask
{
	unsigned char byResult;
	unsigned int  dwTaskID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwTaskID = htonl(dwTaskID);
		memcpy(szBuffer+nBytesProcessed, &dwTaskID, sizeof(unsigned int));
		//dwTaskID = ntohl(dwTaskID);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwTaskID = htonl(dwTaskID);
		memcpy(&dwTaskID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwTaskID = ntohl(dwTaskID);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}RESPONSE_DROP_TASK, *pRESPONSE_DROP_TASK;

typedef struct tagRequestRandomEvents
{
	unsigned int dwUin;
	int          nNickNameLength;
	char         szNickName[32];
	unsigned int dwEventType;
	unsigned int dwEventIndex;

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&nNickNameLength, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&szNickName, szBuffer+nBytesProcessed, nNickNameLength);
		nBytesProcessed += nNickNameLength;
		szNickName[nNickNameLength] = '\0';

		memcpy(&dwEventType, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwEventIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_RANDOM_EVENTS, *pREQUEST_RANDOM_EVENTS;

typedef struct tagResponseRandomEvents
{
	unsigned char byResult;
	unsigned int  dwEventID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwEventID = htonl(dwEventID);
		memcpy(szBuffer+nBytesProcessed, &dwEventID, sizeof(unsigned int));
		//dwEventID = ntohl(dwEventID);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}RESPONSE_RANDOM_EVENTS, *pRESPONSE_RANDOM_EVENTS;

typedef struct tagRequestChallengeInfo
{
	int     nReserved;

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nReserved, szBuffer+nBytesProcessed, sizeof(int));
		//nReserved = ntohl(nReserved);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}
}REQUEST_CHALLENGE_INFO, *pREQUEST_CHALLENGE_INFO;

typedef struct tagRequestChallengeInfos
{
	int     nReserved;

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nReserved, szBuffer+nBytesProcessed, sizeof(int));
		//nReserved = ntohl(nReserved);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}
}REQUEST_CHALLENGE_INFOS, *pREQUEST_CHALLENGE_INFOS;

typedef struct tagResponseChallengeInfo
{
	unsigned int  dwDestUin;           //该玩家的UIN
	int           HeadID;              //头像ID
	int           LV; 		           //等级
	int           Strain; 	           //品种
	int           Fighting; 	       //战斗力
	int           Win; 		           //胜
	int           Lose; 		       //负
	unsigned char byNickNameLength;    //名字长度
	char          szNickName[MAX_NICKNAME_LENGTH];      //名字

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//dwDestUin = htonl(dwDestUin);
		memcpy(szBuffer+nBytesProcessed, &dwDestUin, sizeof(unsigned int));
		//dwDestUin = ntohl(dwDestUin);
		nBytesProcessed += sizeof(unsigned int);

		//HeadID = htonl(HeadID);
		memcpy(szBuffer+nBytesProcessed, &HeadID, sizeof(int));
		//HeadID = ntohl(HeadID);
		nBytesProcessed += sizeof(int);

		//LV = htonl(LV);
		memcpy(szBuffer+nBytesProcessed, &LV, sizeof(int));
		//LV = ntohl(LV);
		nBytesProcessed += sizeof(int);

		//Strain = htonl(Strain);
		memcpy(szBuffer+nBytesProcessed, &Strain, sizeof(int));
		//Strain = ntohl(Strain);
		nBytesProcessed += sizeof(int);

		//Fighting = htonl(Fighting);
		memcpy(szBuffer+nBytesProcessed, &Fighting, sizeof(int));
		//Fighting = ntohl(Fighting);
		nBytesProcessed += sizeof(int);

		//Win = htonl(Win);
		memcpy(szBuffer+nBytesProcessed, &Win, sizeof(int));
		//Win = ntohl(Win);
		nBytesProcessed += sizeof(int);

		//Lose = htonl(Lose);
		memcpy(szBuffer+nBytesProcessed, &Lose, sizeof(int));
		//Lose = ntohl(Lose);
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &byNickNameLength, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, szNickName, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		return nBytesProcessed;
	}
}RESPONSE_CHALLENGE_INFO, *pRESPONSE_CHALLENGE_INFO;

typedef struct tagResponseChallengeInfos
{
	unsigned char           byType;
	unsigned char           byCount;
	RESPONSE_CHALLENGE_INFO szChallengeInfos[6];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byType, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		int nTempBytes = 0;
		for (int i=0; i<byCount; ++i)
		{
			nTempBytes = szChallengeInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTempBytes;
		}

		return nBytesProcessed;
	}

}RESPONSE_CHALLENGE_INFOS, *pRESPONSE_CHALLENGE_INFOS;


typedef struct tagRequestFriendInfo
{
	unsigned int    dwFriendUin;

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwFriendUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwFriendUin = ntohl(dwFriendUin);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}REQUEST_FRIEND_INFO, *pREQUEST_FRIEND_INFO;


typedef struct tagResponseFriendInfo
{
	unsigned int dwUin;                              //玩家Uin
	int          nLevel;                             //玩家等级
	int          nVIP;                               //玩家VIP等级
	char         byNickNameLength;                   //名字长度
	char         szNickName[MAX_NICKNAME_LENGTH];    //名字
	int          nHeadID;                            //玩家头像ID

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//dwUin = htonl(dwUin);
		memcpy(szBuffer+nBytesProcessed, &dwUin, sizeof(unsigned int));
		//dwUin = ntohl(dwUin);
		nBytesProcessed += sizeof(unsigned int);

		//nLevel = htonl(nLevel);
		memcpy(szBuffer+nBytesProcessed, &nLevel, sizeof(int));
		//nLevel = ntohl(nLevel);
		nBytesProcessed += sizeof(int);

		//nVIP = htonl(nVIP);
		memcpy(szBuffer+nBytesProcessed, &nVIP, sizeof(int));
		//nVIP = ntohl(nVIP);
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &byNickNameLength, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, szNickName, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		//nHeadID = htonl(nHeadID);
		memcpy(szBuffer+nBytesProcessed, &nHeadID, sizeof(int));
		//nHeadID = ntohl(nHeadID);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

	int    ReadFromDB(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwUin, szBuffer+nBytesProcessed,sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&nLevel, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nVIP, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&byNickNameLength, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szNickName, szBuffer+nBytesProcessed, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		memcpy(&nHeadID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

	int    WriteToDB(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &nLevel, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nVIP, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &byNickNameLength, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, szNickName, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		memcpy(szBuffer+nBytesProcessed, &nHeadID, sizeof(int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}
}RESPONSE_FRIEND_INFO, *pRESPONSE_FRIEND_INFO;


typedef struct tagResponseFriendInfos
{
	unsigned char           byFriendCount;
	RESPONSE_FRIEND_INFO    szFriendInfos[6];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byFriendCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		int nTemp = 0;
		for (int i=0; i<byFriendCount; ++i)
		{
			nTemp = szFriendInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}
}RESPONSE_FRIEND_INFOS, *pRESPONSE_FRIEND_INFOS;


typedef struct tagNotifyFriendInfos
{
	unsigned char        byFriendCount;
	RESPONSE_FRIEND_INFO szFriends[30];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byFriendCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		int nTemp = 0;
		for (int i=0; i<byFriendCount; ++i)
		{
			nTemp = szFriends[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

}NOTIFY_FRIEND_INFOS, *pNOTIFY_FRIEND_INFOS;


typedef struct tagRequestAddFriend
{
	unsigned int    dwUin;
	char            byNameLength;
	char            szNickName[MAX_NICKNAME_LENGTH];

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byNameLength, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(&szNickName, szBuffer+nBytesProcessed, byNameLength);
		nBytesProcessed += byNameLength;


		return nBytesProcessed;
	}

}REQUEST_ADD_FRIEND, *pREQUEST_ADD_FRIEND;


typedef struct tagResponseAddFriend
{
	unsigned char    byResult;
	unsigned char    byErrorID;
	unsigned int     dwUin;
	unsigned char    byNickNameLength;
	char             szNickName[MAX_NICKNAME_LENGTH];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//dwUin = htonl(dwUin);
		memcpy(szBuffer+nBytesProcessed, &dwUin, sizeof(unsigned int));
		//dwUin = ntohl(dwUin);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byNickNameLength, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &szNickName, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		return nBytesProcessed;
	}
}RESPONSE_ADD_FRIEND, *pRESPONSE_ADD_FRIEND;

//
//typedef struct tagModelInfo
//{
//	unsigned int model_id;
//	int          pos_x;
//	int          pos_y;
//	unsigned int dwValue;
//
//	int    Write(char* szBuffer)
//	{
//		int nBytesProcessed = 0;
//
//		model_id = htonl(model_id);
//		memcpy(szBuffer+nBytesProcessed, &model_id, sizeof(unsigned int));
//		model_id = ntohl(model_id);
//		nBytesProcessed += sizeof(unsigned int);
//
//		pos_x = htonl(pos_x);
//		memcpy(szBuffer+nBytesProcessed, &pos_x, sizeof(int));
//		pos_x = ntohl(pos_x);
//		nBytesProcessed += sizeof(int);
//
//		pos_y = htonl(pos_y);
//		memcpy(szBuffer+nBytesProcessed, &pos_y, sizeof(int));
//		pos_y = ntohl(pos_y);
//		nBytesProcessed += sizeof(int);
//
//		dwValue = htonl(dwValue);
//		memcpy(szBuffer+nBytesProcessed, &dwValue, sizeof(unsigned int));
//		dwValue = ntohl(dwValue);
//		nBytesProcessed += sizeof(unsigned int);
//
//		return nBytesProcessed;
//	}
//}MODEL_INFO, *pMODEL_INFO;
//

typedef struct tagNotifyDecorativeInfos
{
	unsigned int decorative_number;
	MODEL_INFO   deocratives[16];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//decorative_number = htonl(decorative_number);
		memcpy(szBuffer+nBytesProcessed, &decorative_number, sizeof(unsigned int));
		//decorative_number = ntohl(decorative_number);
		nBytesProcessed += sizeof(unsigned int);

		for (unsigned int i=0; i<decorative_number; ++i)
		{
			int nTemp = 0;
			nTemp = deocratives[i].Write(szBuffer+nBytesProcessed);

			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&decorative_number, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		for (unsigned int i=0; i<decorative_number; ++i)
		{
			int nTemp = 0;
			nTemp = deocratives[i].Read(szBuffer+nBytesProcessed);

			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}
}NOTIFY_DECORATIVE_INFOS, *pNOTIFY_DECORATIVE_INFOS;


typedef struct tagRequestFeeding
{
	unsigned int  model_id;
	unsigned int  feed_number;

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&model_id, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//model_id = ntohl(model_id);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&feed_number, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//feed_number = ntohl(feed_number);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}REQUEST_FEEDING, *pREQUEST_FEEDING;


typedef struct tagResponseFeeding
{
	unsigned char  byResult;
	unsigned char  byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_FEEDING, *pRESPONSE_FEEDING;


typedef struct tagRequestCleaning
{
	unsigned int  model_id;
	unsigned int  clean_number;

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&model_id, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//model_id = ntohl(model_id);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&clean_number, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//clean_number = ntohl(clean_number);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}REQUEST_CLEANING, *pREQUEST_CLEANING;


typedef struct tagResponseCleaning
{
	unsigned char  byResult;
	unsigned char  byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_CLEANING, *pRESPONSE_CLEANING;


typedef struct tagRequestPlaying
{
	unsigned int  model_id;
	unsigned int  play_number;

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&model_id, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//model_id = ntohl(model_id);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&play_number, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//play_number = ntohl(play_number);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}REQUEST_PLAYING, *pREQUEST_PLAYING;


typedef struct tagResponsePlaying
{
	unsigned char  byResult;
	unsigned char  byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_PLAYING, *pRESPONSE_PLAYING;


typedef struct tagEquipInfo
{
	int    nEquipID;
	int    nIndex;
	int    nLevel;
	unsigned char    byExtraCount;
	short    shExtraAttrs[MAX_EXTRA_ATTRS];
	unsigned char    byGemstoneCount;
	short    shGemstones[MAX_GEMSTONE];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//nEquipID = htonl(nEquipID);
		memcpy(szBuffer+nBytesProcessed, &nEquipID, sizeof(int));
		//nEquipID = ntohl(nEquipID);
		nBytesProcessed += sizeof(int);

		//nIndex = htonl(nIndex);
		memcpy(szBuffer+nBytesProcessed, &nIndex, sizeof(int));
		//nIndex = ntohl(nIndex);
		nBytesProcessed += sizeof(int);

		//nLevel = htonl(nLevel);
		memcpy(szBuffer+nBytesProcessed, &nLevel, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &byExtraCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int j=0;j<byExtraCount;j++)
		{
			memcpy(szBuffer+nBytesProcessed, &shExtraAttrs[j], sizeof(short));
			nBytesProcessed += sizeof(short);
		}

		memcpy(szBuffer+nBytesProcessed, &byGemstoneCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int j=0;j<byGemstoneCount;j++)
		{
			memcpy(szBuffer+nBytesProcessed, &shGemstones[j], sizeof(short));
			nBytesProcessed += sizeof(short);
		}

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nEquipID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nIndex, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nLevel, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&byExtraCount,szBuffer+nBytesProcessed,  sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int j=0;j<byExtraCount;j++)
		{
			memcpy(&shExtraAttrs[j],szBuffer+nBytesProcessed,  sizeof(short));
			nBytesProcessed += sizeof(short);
		}

		memcpy(&byGemstoneCount,szBuffer+nBytesProcessed,  sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int j=0;j<byGemstoneCount;j++)
		{
			memcpy(&shGemstones[j],szBuffer+nBytesProcessed,  sizeof(short));
			nBytesProcessed += sizeof(short);
		}

		return nBytesProcessed;
	}

	int    ReadFromDB(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nEquipID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nIndex, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nLevel, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&byExtraCount,szBuffer+nBytesProcessed,  sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int j=0;j<byExtraCount;j++)
		{
			memcpy(&shExtraAttrs[j],szBuffer+nBytesProcessed,  sizeof(short));
			nBytesProcessed += sizeof(short);
		}

		memcpy(&byGemstoneCount,szBuffer+nBytesProcessed,  sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int j=0;j<byGemstoneCount;j++)
		{
			memcpy(&shGemstones[j],szBuffer+nBytesProcessed,  sizeof(short));
			nBytesProcessed += sizeof(short);
		}


		return nBytesProcessed;
	}

	int    WriteToDB(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &nEquipID, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nIndex, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nLevel, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &byExtraCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int j=0;j<byExtraCount;j++)
		{
			memcpy(szBuffer+nBytesProcessed, &shExtraAttrs[j], sizeof(short));
			nBytesProcessed += sizeof(short);
		}

		memcpy(szBuffer+nBytesProcessed, &byGemstoneCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int j=0;j<byGemstoneCount;j++)
		{
			memcpy(szBuffer+nBytesProcessed, &shGemstones[j], sizeof(short));
			nBytesProcessed += sizeof(short);
		}

		return nBytesProcessed;
	}
}EQUIP_INFO, *pEQUIP_INFO;


typedef struct tagNotifyEquipInfos 
{
	char       byEquipCount;
	EQUIP_INFO szEquips[6];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byEquipCount, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byEquipCount; ++i)
		{
			memcpy(szBuffer+nBytesProcessed, &szEquips[i].nEquipID, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(szBuffer+nBytesProcessed, &szEquips[i].nIndex, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(szBuffer+nBytesProcessed, &szEquips[i].nLevel, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(szBuffer+nBytesProcessed, &szEquips[i].byExtraCount, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<szEquips[i].byExtraCount;j++)
			{
				memcpy(szBuffer+nBytesProcessed, &szEquips[i].shExtraAttrs[j], sizeof(short));
				nBytesProcessed += sizeof(short);
			}

			memcpy(szBuffer+nBytesProcessed, &szEquips[i].byGemstoneCount, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<szEquips[i].byGemstoneCount;j++)
			{
				memcpy(szBuffer+nBytesProcessed, &szEquips[i].shGemstones[j], sizeof(short));
				nBytesProcessed += sizeof(short);
			}
		}

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byEquipCount, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byEquipCount; ++i)
		{
			memcpy(&szEquips[i].nEquipID, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&szEquips[i].nIndex, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&szEquips[i].nLevel, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy( &szEquips[i].byExtraCount,szBuffer+nBytesProcessed, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<szEquips[i].byExtraCount;j++)
			{
				memcpy(&szEquips[i].shExtraAttrs[j],szBuffer+nBytesProcessed,  sizeof(short));
				nBytesProcessed += sizeof(short);
			}

			memcpy(&szEquips[i].byGemstoneCount,szBuffer+nBytesProcessed,  sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<szEquips[i].byGemstoneCount;j++)
			{
				memcpy(&szEquips[i].shGemstones[j],szBuffer+nBytesProcessed,  sizeof(short));
				nBytesProcessed += sizeof(short);
			}
		}

		return nBytesProcessed;
	}
}NOTIFY_EQUIP_INFOS, *pNOTIFY_EQUIP_INFOS;


typedef struct tagRequestUnEquip
{
	int    nItemID;
	int    nLevel;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nItemID, szBuffer+nBytesProcessed, sizeof(int));
		//nItemID = ntohl(nItemID);
		nBytesProcessed += sizeof(int);

		memcpy(&nLevel, szBuffer+nBytesProcessed, sizeof(int));
		//nLevel = ntohl(nLevel);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &nItemID, sizeof(int));
		//nItemID = ntohl(nItemID);
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nLevel, sizeof(int));
		//nLevel = ntohl(nLevel);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}
}REQUEST_UNEQUIP, *pREQUEST_UNEQUIP;


typedef struct tagResponseUnequip
{
	unsigned char    byResult;
	unsigned char    byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult,szBuffer+nBytesProcessed,  sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byErrorID,szBuffer+nBytesProcessed,  sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}

}RESPONSE_UNEQUIP, *pRESPONSE_UNEQUIP;


typedef struct tagNotifyEquipChange
{
	char       byEquipCount;
	EQUIP_INFO szEquips[6];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byEquipCount, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byEquipCount; ++i)
		{
			memcpy(szBuffer+nBytesProcessed, &szEquips[i].nEquipID, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(szBuffer+nBytesProcessed, &szEquips[i].nIndex, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(szBuffer+nBytesProcessed, &szEquips[i].nLevel, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(szBuffer+nBytesProcessed, &szEquips[i].byExtraCount, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<szEquips[i].byExtraCount;j++)
			{
				memcpy(szBuffer+nBytesProcessed, &szEquips[i].shExtraAttrs[j], sizeof(short));
				nBytesProcessed += sizeof(short);
			}

			memcpy(szBuffer+nBytesProcessed, &szEquips[i].byGemstoneCount, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<szEquips[i].byGemstoneCount;j++)
			{
				memcpy(szBuffer+nBytesProcessed, &szEquips[i].shGemstones[j], sizeof(short));
				nBytesProcessed += sizeof(short);
			}
		}

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byEquipCount,szBuffer+nBytesProcessed,  sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byEquipCount; ++i)
		{
			memcpy(&szEquips[i].nEquipID, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&szEquips[i].nIndex, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&szEquips[i].nLevel, szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);

			memcpy(&szEquips[i].byExtraCount,szBuffer+nBytesProcessed,  sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<szEquips[i].byExtraCount;j++)
			{
				memcpy( &szEquips[i].shExtraAttrs[j],szBuffer+nBytesProcessed, sizeof(short));
				nBytesProcessed += sizeof(short);
			}

			memcpy(&szEquips[i].byGemstoneCount,szBuffer+nBytesProcessed,  sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);

			for (int j=0;j<szEquips[i].byGemstoneCount;j++)
			{
				memcpy(&szEquips[i].shGemstones[j],szBuffer+nBytesProcessed,  sizeof(short));
				nBytesProcessed += sizeof(short);
			}
		}

		return nBytesProcessed;
	}
}NOTIFY_EQUIP_CHANGE, *pNOTIFY_EQUIP_CHANGE;


typedef struct tagRequestVisitHome
{
	unsigned int dwPlayerUin;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwPlayerUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwPlayerUin = ntohl(dwPlayerUin);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}REQUEST_VISIT_HOME, *pREQUEST_VISIT_HOME;


typedef struct tagResponseVisitHome
{
	unsigned char    byResult;
	unsigned char    byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_VISIT_HOME, *pRESPONSE_VISIT_HOME;


//玩家访问别的好友家的协议
typedef  NOTIFY_PLAYER_BASE_INFO  NOTIFY_VISIT_HOME;


typedef struct tagNotifyHomeDecorateInfo
{
	unsigned int               dwPlayerUin;
	NOTIFY_DECORATIVE_INFOS    _decoInfos;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//dwPlayerUin = htonl(dwPlayerUin);
		memcpy(szBuffer+nBytesProcessed, &dwPlayerUin, sizeof(unsigned int));
		//dwPlayerUin = ntohl(dwPlayerUin);
		nBytesProcessed += sizeof(unsigned int);

		int nBytesWritten = _decoInfos.Write(szBuffer+nBytesProcessed);
		nBytesProcessed += nBytesWritten;

		return nBytesProcessed;
	}
}NOTIFY_HOME_DECORATE_INFO, *pNOTIFY_HOME_DECORATE_INFO;


typedef struct tagRequestGoHome
{
	unsigned int    dwPlayerLocation;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwPlayerLocation, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwPlayerLocation = ntohl(dwPlayerLocation);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}REQUEST_GOHOME, *pREQUEST_GOHOME;


typedef struct tagResponseGoHome
{
	unsigned char    byResult;
	unsigned char    byErrorID;
	NOTIFY_DECORATIVE_INFOS decoInfos;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		int nTemp = decoInfos.Write(szBuffer+nBytesProcessed);
		nBytesProcessed += nTemp;

		return nBytesProcessed;
	}
}RESPONSE_GOHOME, *pRESPONSE_GOHOME;


typedef struct tagRequestWalkDog
{
	int    nMapID;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nMapID, szBuffer+nBytesProcessed, sizeof(int));
		//nMapID = ntohl(nMapID);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}
}REQUEST_WALKDOG, *pREQUEST_WALKDOG;


typedef struct tagResponseWalkDog
{
	unsigned char    byResult;
	unsigned char    byErrorID;
	int              nMapID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//nMapID = htonl(nMapID);
		memcpy(szBuffer+nBytesProcessed, &nMapID, sizeof(int));
		//nMapID = ntohl(nMapID);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}
}RESPONSE_WALKDOG, *pRESPONSE_WALKDOG;


typedef struct tagRequestDice
{
	int    nGrid;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nGrid, szBuffer+nBytesProcessed, sizeof(int));
		//nGrid = ntohl(nGrid);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}
}REQUEST_DICE, *pREQUEST_DICE;


typedef struct tagResponseDice
{
	unsigned char    byResult;
	unsigned char    byErrorID;
	unsigned char    byDiceNum;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byDiceNum, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_DICE, *pRESPONSE_DICE;


typedef struct tagRequestDiceReward
{
	int    nGrid;
	unsigned int dwIndex;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nGrid, szBuffer+nBytesProcessed, sizeof(int));
		//nGrid = ntohl(nGrid);
		nBytesProcessed += sizeof(int);

		memcpy(&dwIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwIndex = ntohl(dwIndex);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}REQUEST_DICE_REWARD,*pREQUEST_DICE_REWARD;


typedef struct tagTaskAward
{
	unsigned char byType;
	int           nID;
	int           nCount;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byType, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//nID = htonl(nID);
		memcpy(szBuffer+nBytesProcessed, &nID, sizeof(int));
		//nID = ntohl(nID);
		nBytesProcessed += sizeof(int);

		//nCount = htonl(nCount);
		memcpy(szBuffer+nBytesProcessed, &nCount, sizeof(int));
		//nCount = ntohl(nCount);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}
}TASK_AWARD, *pTASK_AWARD;


typedef struct tagResponseGridReward
{
	unsigned char    byResult;
	unsigned char    byErrorID;
	unsigned char    byRewardCount;
	TASK_AWARD       szTaskAward[3];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byRewardCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byRewardCount; ++i)
		{
			int nTemp = szTaskAward[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}
}RESPONSE_DICE_REWARD, *pRESPONSE_DICE_REWARD;


typedef struct tagRequestRedice
{
	unsigned int dwRediceType;
	unsigned int dwRediceNumber;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwRediceType, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwRediceType = ntohl(dwRediceType);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwRediceNumber, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwRediceNumber = ntohl(dwRediceNumber);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_REDICE, *pREQUEST_REDICE;


typedef struct tagResponseRedice
{
	unsigned char    byResult;
	unsigned char    byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_REDICE, *pRESPONSE_REDICE;


typedef struct tagPVEOwnerInfo
{
	unsigned int   dwMapIndex;
	unsigned int   playerUin;
	unsigned int   dwLv;
	unsigned char  byNameLength;
	char           szName[MAX_NICKNAME_LENGTH];
	unsigned int   dwAttack;
	unsigned int   dwDefense;
	unsigned int   dwFlourish;
	unsigned int   dwTime;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//dwMapIndex = htonl(dwMapIndex);
		memcpy(szBuffer+nBytesProcessed, &dwMapIndex, sizeof(unsigned int));
		//dwMapIndex = ntohl(dwMapIndex);
		nBytesProcessed += sizeof(unsigned int);

		//playerUin = htonl(playerUin);
		memcpy(szBuffer+nBytesProcessed, &playerUin, sizeof(unsigned int));
		//playerUin = ntohl(playerUin);
		nBytesProcessed += sizeof(unsigned int);

		//dwLv = htonl(dwLv);
		memcpy(szBuffer+nBytesProcessed, &dwLv, sizeof(unsigned int));
		//dwLv = ntohl(dwLv);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byNameLength, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, szName, byNameLength);
		nBytesProcessed += byNameLength;

		//dwAttack = htonl(dwAttack);
		memcpy(szBuffer+nBytesProcessed, &dwAttack, sizeof(unsigned int));
		//dwAttack = ntohl(dwAttack);
		nBytesProcessed += sizeof(unsigned int);

		//dwDefense = htonl(dwDefense);
		memcpy(szBuffer+nBytesProcessed, &dwDefense, sizeof(unsigned int));
		//dwDefense = ntohl(dwDefense);
		nBytesProcessed += sizeof(unsigned int);

		//dwFlourish = htonl(dwFlourish);
		memcpy(szBuffer+nBytesProcessed, &dwFlourish, sizeof(unsigned int));
		//dwFlourish = ntohl(dwFlourish);
		nBytesProcessed += sizeof(unsigned int);

		//dwTime = htonl(dwTime);
		memcpy(szBuffer+nBytesProcessed, &dwTime, sizeof(unsigned int));
		//dwTime = ntohl(dwTime);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}PVE_OWNER_INFO, *pPVE_OWNER_INFO;


typedef struct tagRequestPVEMapInfos
{
	unsigned int    dwMapID;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwMapID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwMapID = ntohl(dwMapID);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_PVE_MAP_INFOS, *pREQUEST_PVE_MAP_INFOS;


typedef struct tagResponsePVEMapInfos
{
	unsigned int     dwMapID;
	unsigned char    byPointCount;
	PVE_OWNER_INFO   szMapInfos[16];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//dwMapID = htonl(dwMapID);
		memcpy(szBuffer+nBytesProcessed, &dwMapID, sizeof(unsigned int));
		//dwMapID = ntohl(dwMapID);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byPointCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byPointCount; ++i)
		{
			int nTemp = szMapInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}
}RESPONSE_PVE_MAP_INFOS, *pRESPONSE_PVE_MAP_INFOS;


typedef struct tagRequestOccupyBattle
{
	unsigned int dwMapId;
	unsigned int dwMapIndex;
	unsigned int dwSrcUin;
	unsigned int dwOpponentType;
	unsigned int dwDestUin;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwMapId, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwMapId = ntohl(dwMapId);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwMapIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwMapIndex = ntohl(dwMapIndex);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwSrcUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwSrcUin = ntohl(dwSrcUin);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwOpponentType, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwOpponentType = ntohl(dwOpponentType);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwDestUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwDestUin = ntohl(dwDestUin);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_OCCUPY_BATTLE, *pREQUEST_OCCUPY_BATTLE;


typedef struct tagResponseOccupyBattle
{
	unsigned char byResult;
	unsigned char byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_OCCUPY_BATTLE, *pRESPONSE_OCCUPY_BATTLE;


typedef struct tagNotifyOccupyerChange
{
	unsigned int    dwMapID;
	PVE_OWNER_INFO  szOwnerInfo;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		//dwMapID = htonl(dwMapID);
		memcpy(szBuffer+nBytesProcessed, &dwMapID, sizeof(unsigned int));
		//dwMapID = ntohl(dwMapID);
		nBytesProcessed += sizeof(unsigned int);

		int nTemp = szOwnerInfo.Write(szBuffer+nBytesProcessed);
		nBytesProcessed += nTemp;

		return nBytesProcessed;
	}

}NOTIFY_OCCUPYER_CHANGE, *pNOTIFY_OCCUPYER_CHANGE;


typedef struct tagNotifyBattleResult
{
	unsigned char    byResult;
	unsigned char    byAwardCount;
	TASK_AWARD       szAward[3];	

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byAwardCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byAwardCount; ++i)
		{
			int nTemp = szAward[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}
}NOTIFY_BATTLE_RESULT, *pNOTIFY_BATTLE_RESULT;


typedef struct tagRequestEquipCompound
{
	unsigned int    dwItemID;
	unsigned int    dwGridIndex;
	unsigned int    dwEquipID;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwItemID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwItemID = ntohl(dwItemID);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwGridIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwGridIndex = ntohl(dwGridIndex);
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwEquipID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		//dwEquipID = ntohl(dwEquipID);
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy( szBuffer+nBytesProcessed, &dwItemID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwGridIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwEquipID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_EQUIP_COMPOUND, *pREQUEST_EQUIP_COMPOUND;


typedef struct tagResponseEquipCompound
{
	unsigned char byResult;
	unsigned char byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byErrorID, szBuffer+nBytesProcessed,  sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_EQUIP_COMPOUND, *pRESPONSE_EQUIP_COMPOUND;

typedef struct tagRequestEquipEnforce
{
	int    nEquipID;
	int    nEquipLevel;
	int    nGirdIndex;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nEquipID, szBuffer+nBytesProcessed, sizeof(int));
		//nEquipID = ntohl(nEquipID);
		nBytesProcessed += sizeof(int);

		memcpy(&nEquipLevel, szBuffer+nBytesProcessed, sizeof(int));
		//nEquipLevel = ntohl(nEquipLevel);
		nBytesProcessed += sizeof(int);

		memcpy(&nGirdIndex, szBuffer+nBytesProcessed, sizeof(int));
		//nGirdIndex = ntohl(nGirdIndex);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &nEquipID, sizeof(int));
		//nEquipID = ntohl(nEquipID);
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nEquipLevel, sizeof(int));
		//nEquipLevel = ntohl(nEquipLevel);
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nGirdIndex, sizeof(int));
		//nGirdIndex = ntohl(nGirdIndex);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

}REQUEST_EQUIP_ENFORCE, *pREQUEST_EQUIP_ENFORCE;

typedef struct tagResponseEquipEnforce
{
	unsigned char byResult;
	unsigned char byErrorID;
	int           nEquipId;
	int           nEquipIndex;
	int           nEquipLevel;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		//nEquipId = htonl(nEquipId);
		memcpy(szBuffer+nBytesProcessed, &nEquipId, sizeof(int));
		//nEquipId = ntohl(nEquipId);
		nBytesProcessed += sizeof(int);

		//nEquipIndex = htonl(nEquipIndex);
		memcpy(szBuffer+nBytesProcessed, &nEquipIndex, sizeof(int));
		//nEquipIndex = ntohl(nEquipIndex);
		nBytesProcessed += sizeof(int);

		//nEquipLevel = htonl(nEquipLevel);
		memcpy(szBuffer+nBytesProcessed, &nEquipLevel, sizeof(int));
		//nEquipLevel = ntohl(nEquipLevel);
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byErrorID,szBuffer+nBytesProcessed,  sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&nEquipId, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nEquipIndex, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nEquipLevel, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

}RESPONSE_EQUIP_ENFORCE, *pRESPONSE_EQUIP_ENFORCE;

typedef struct tagRequestAddAttrpoint
{
	int    nAttrPoints[4];

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		for (int i=0; i<4; ++i)
		{
			memcpy(&nAttrPoints[i], szBuffer+nBytesProcessed, sizeof(int));
			nBytesProcessed += sizeof(int);
		}

		return nBytesProcessed;
	}

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		for (int i=0; i<4; ++i)
		{
			memcpy(szBuffer+nBytesProcessed, &nAttrPoints[i], sizeof(int));
			nBytesProcessed += sizeof(int);
		}

		return nBytesProcessed;
	}
}REQUEST_ADD_ATTRPOINT, *pREQUEST_ADD_ATTRPOINT;

typedef struct tagResponseAddAttrpoint
{
	unsigned char byResult;
	unsigned char byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byErrorID, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_ADD_ATTRPOINT, *pRESPONSE_ADD_ATTRPOINT;


typedef struct tagRequestWorkBegin
{
	unsigned int  dwSlaveUin;                        //奴隶Uin
	unsigned int  dwWorkdId;                         //工种

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwSlaveUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwWorkdId, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);
		
		return nBytesProcessed;
	}

}REQUEST_WORK_BEGIN, *pREQUEST_WORK_BEGIN;


typedef struct tagResponseWorkBegin
{
	unsigned char byResult;
	unsigned char byErrorID;
	unsigned int  dwSlaveUin;                        //奴隶Uin
	unsigned int  dwWorkdId;                         //工种

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &dwSlaveUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwWorkdId, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}RESPONSE_WORK_BEGIN, *pRESPONSE_WORK_BEGIN;


typedef struct tagRequestWorkEnd
{
	unsigned int  dwSlaveUin;                        //奴隶Uin
	unsigned int  dwWorkdId;                         //工种

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwSlaveUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwWorkdId, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}REQUEST_WORK_END, *pREQUEST_WORK_END;


typedef struct tagResponseWorkEnd
{
	unsigned char byResult;
	unsigned char byErrorID;
	unsigned int  dwSlaveUin;                        //奴隶Uin
	unsigned int  dwWorkdId;                         //工种

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &dwSlaveUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwWorkdId, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}RESPONSE_WORK_END, *pRESPONSE_WORK_END;

typedef struct tagSlaveInfo
{
	unsigned int  dwUin;                              //玩家Uin
	int           nLevel;                             //玩家等级
	int           nVIP;                               //玩家VIP等级
	char          byNickNameLength;                   //名字长度
	char          szNickName[MAX_NICKNAME_LENGTH];    //名字
	int           nHeadID;                            //玩家头像ID
	unsigned int  dwTime;                             //玩家被抓的时间
	unsigned char bySlaveStatus;                      //奴隶状态
	unsigned char byWorkID;                           //工作类别
	unsigned int  dwWorkBeginTime;                    //奴隶打工开始时间

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &nLevel, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nVIP, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &byNickNameLength, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, szNickName, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		memcpy(szBuffer+nBytesProcessed, &nHeadID, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &dwTime, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &bySlaveStatus, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byWorkID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &dwWorkBeginTime, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&nLevel, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nVIP, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&byNickNameLength, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szNickName, szBuffer+nBytesProcessed, byNickNameLength);
		szNickName[byNickNameLength] = '\0';
		nBytesProcessed += byNickNameLength;

		memcpy(&nHeadID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&dwTime, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&bySlaveStatus, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byWorkID, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwWorkBeginTime, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    ReadFromDB(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwUin, szBuffer+nBytesProcessed,sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&nLevel, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nVIP, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&byNickNameLength, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szNickName, szBuffer+nBytesProcessed, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		memcpy(&nHeadID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&dwTime, szBuffer+nBytesProcessed,sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&bySlaveStatus, szBuffer+nBytesProcessed,sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byWorkID, szBuffer+nBytesProcessed,sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwWorkBeginTime, szBuffer+nBytesProcessed,sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    WriteToDB(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &nLevel, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nVIP, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &byNickNameLength, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, szNickName, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		memcpy(szBuffer+nBytesProcessed, &nHeadID, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &dwTime, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &bySlaveStatus, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byWorkID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &dwWorkBeginTime, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}SLAVE_INFO, *pSLAVE_INFO;


typedef struct tagNotifySlaveInfos
{
	unsigned char bySlaveCount;
	SLAVE_INFO    szSlaveInfos[MAX_SLAVE_COUNT];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &bySlaveCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		int nTemp = 0;
		for (int i=0; i<bySlaveCount; ++i)
		{
			nTemp = szSlaveInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&bySlaveCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		int nTemp = 0;
		for (int i=0; i<bySlaveCount; ++i)
		{
			nTemp = szSlaveInfos[i].Read(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

}NOTIFY_SLAVE_INFOS, *pNOTIFY_SLAVE_INFOS;


typedef struct tagRequestAddSlave
{
	unsigned int    dwSlaveUin;
	unsigned char   byNameLength;
	char            szNickName[MAX_NICKNAME_LENGTH];

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwSlaveUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(int);

		memcpy(&byNameLength, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(&szNickName, szBuffer+nBytesProcessed, byNameLength);
		nBytesProcessed += byNameLength;

		return nBytesProcessed;
	}
}REQUEST_ADD_SLAVE, *pREQUEST_ADD_SLAVE;


typedef struct tagResponseAddSlave
{
	unsigned char byResult;
	unsigned char byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_ADD_SLAVE, *pRESPONSE_ADD_SLAVE;


typedef struct tagRequestDeleteSlave
{
	unsigned int    dwSlaveUin;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwSlaveUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}REQUEST_DELETE_SLAVE, *pREQUEST_DELETE_SLAVE;

//pengyuan 2012.9.4 其实很多这种通用的回复码可以通过typedef来处理
typedef struct tagResponseDeleteSlave
{
	unsigned char byResult;
	unsigned char byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}
}RESPONSE_DELETE_SLAVE, *pRESPONSE_DELETE_SLAVE;


typedef struct tagRequestClearCD
{
	int             nClearType;
	int             nClearID;
	int             nClearArg1;
	int             nClearArg2;
	unsigned int    dwClearTime;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&nClearType, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nClearID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nClearArg1, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nClearArg2, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&dwClearTime, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}REQUEST_CLEAR_CD, *pREQUEST_CLEAR_CD;


typedef struct tagResponseClearCD
{
	unsigned char byResult;
	unsigned char byErrorID;
	int           nClearType;
	int           nClearID;
	int           nClearArg;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &nClearType, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nClearID, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nClearArg, sizeof(int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}
}RESPONSE_CLEAR_CD, *pRESPONSE_CLEAR_CD;


typedef struct tagNotifyHungintEnd
{
	unsigned char byResult;
	unsigned char byErrorID;
	unsigned int  dwMapID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &dwMapID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}
}NOTIFY_HUNTING_END, pNOTIFY_HUNTING_END;


typedef struct tagRequestBeginHunting
{
	unsigned int    dwSrcMapID;
	unsigned int    dwDestMapID;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwSrcMapID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwDestMapID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUESET_BEGIN_HUNTING, *pREQUESET_BEGIN_HUNTING;


typedef struct tagHuntingMonsterInfo
{
	unsigned int dwMonsterID;
	int          nStartX;
	int          nStartY;
	int          nEndX;
	int          nEndY;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwMonsterID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &nStartX, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nStartY, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nEndX, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nEndY, sizeof(int));
		nBytesProcessed += sizeof(int);

		return nBytesProcessed;
	}

}HUNTING_MONSTER_INFO, *pHUNTING_MONSTER_INFO;


typedef struct tagResponseBeginHunting
{
	unsigned char byResult;
	unsigned char byErrorID;
	unsigned int  dwMapID;
	int           nPosX;
	int           nPosY;
	unsigned int  dwMonsterCount;
	HUNTING_MONSTER_INFO szMonsters[MAX_HUNTING_MONSTER_COUNT];
	unsigned int dwEndTime;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &dwMapID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &nPosX, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nPosY, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &dwMonsterCount, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		for (int i=0; i<dwMonsterCount; ++i)
		{
			int nTemp = szMonsters[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		memcpy(szBuffer+nBytesProcessed, &dwEndTime, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}RESPONSE_BEGIN_HUNTING, *pRESPONSE_BEGIN_HUNTING;


typedef struct tagRequestHuntingMonster
{
	unsigned int    dwMonsterID;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwMonsterID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_HUNTING_MONSTER, *pREQUEST_HUNTING_MONSTER;


typedef struct tagResponseHuntingMonster
{
	unsigned char    byResult;
	unsigned char    byErrorID;
	unsigned int     dwMonsterID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &dwMonsterID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}RESPONSE_HUNTING_MONSTER, *pRESPONSE_HUNTING_MONSTER;


//pengyuan 2012.9.27 新增通知系统信息
typedef struct tagNotifySystemInfo
{
	unsigned int  dwInfoType;                 //类型，暂定1为随机事件
	unsigned int  dwInfoTypeID;               //随机事件的id
	unsigned char byNickNameLength;            //昵称长度
	char          szNickName[32];              //昵称

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwInfoType, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwInfoTypeID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byNickNameLength, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, szNickName, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		return nBytesProcessed;
	}

	int    ReadFromDB(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwInfoType, szBuffer+nBytesProcessed,sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwInfoTypeID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byNickNameLength, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szNickName, szBuffer+nBytesProcessed, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		return nBytesProcessed;
	}

	int    WriteToDB(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwInfoType, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwInfoTypeID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byNickNameLength, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, szNickName, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		return nBytesProcessed;
	}

}NOTIFY_SYSTEM_INFO, *pNOTIFY_SYSTEM_INFO;


typedef struct tagNotifySystemInfos
{
	unsigned char   byCount;
	NOTIFY_SYSTEM_INFO    szSystemInfos[10];  //消息最多10条

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byCount; ++i)
		{
			int nTemp = szSystemInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

}NOTIFY_SYSTEM_INFOS, *pNOTIFY_SYSTEM_INFOS;


//pengyuan 2012.11.20 添加宠物相关协议
typedef struct tagPetBaseInfo
{	
	unsigned int     dwPetUin;
	unsigned int     dwPetID;
	unsigned int     dwModelID;
	unsigned int     dwExp;
	unsigned int     dwLevel;
	unsigned int     dwCarryLevel;
	unsigned int     dwAttrPoints;
	unsigned int     dwLiliang;
	unsigned int     dwLingli;
	unsigned int     dwNaili;
	unsigned int     dwMingjie;
	unsigned short   shPhysicsAttack;
	unsigned short   shPhysicsDefense;
	unsigned short   shMagicAttack;
	unsigned short   shMagicDefense;
	unsigned short   shLife;
	unsigned short   shSpeed;
	unsigned char    byStatus;
	unsigned char    bySkillCount;
	unsigned char    bySkills[MAX_PET_SKILL_COUNT];

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwPetUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwPetID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwModelID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwExp, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwLevel, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwCarryLevel, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwAttrPoints, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwLiliang, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwLingli, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwNaili, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwMingjie, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &shPhysicsAttack, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(szBuffer+nBytesProcessed, &shPhysicsDefense, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(szBuffer+nBytesProcessed, &shMagicAttack, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(szBuffer+nBytesProcessed, &shMagicDefense, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(szBuffer+nBytesProcessed, &shLife, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(szBuffer+nBytesProcessed, &shSpeed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(szBuffer+nBytesProcessed, &byStatus, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &bySkillCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<bySkillCount; ++i)
		{
			memcpy(szBuffer+nBytesProcessed, &bySkills[i], sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);
		}

		return nBytesProcessed;
	}

	int Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwPetUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwPetID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwModelID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwExp, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwLevel, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwCarryLevel, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwAttrPoints, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwLiliang, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwLingli, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwNaili, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwMingjie, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&shPhysicsAttack, szBuffer+nBytesProcessed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(&shPhysicsDefense, szBuffer+nBytesProcessed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(&shMagicAttack, szBuffer+nBytesProcessed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(&shMagicDefense, szBuffer+nBytesProcessed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(&shLife, szBuffer+nBytesProcessed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(&shSpeed, szBuffer+nBytesProcessed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(&byStatus, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&bySkillCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<bySkillCount; ++i)
		{
			memcpy(&bySkills[i], szBuffer+nBytesProcessed, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);
		}

		return nBytesProcessed;
	}

	int    WriteToDB(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwPetUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwPetID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwModelID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwExp, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwLevel, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwCarryLevel, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwAttrPoints, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwLiliang, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwLingli, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwNaili, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwMingjie, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &shPhysicsAttack, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(szBuffer+nBytesProcessed, &shPhysicsDefense, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(szBuffer+nBytesProcessed, &shMagicAttack, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(szBuffer+nBytesProcessed, &shMagicDefense, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(szBuffer+nBytesProcessed, &shLife, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(szBuffer+nBytesProcessed, &shSpeed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(szBuffer+nBytesProcessed, &byStatus, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &bySkillCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<bySkillCount; ++i)
		{
			memcpy(szBuffer+nBytesProcessed, &bySkills[i], sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);
		}

		return nBytesProcessed;
	}

	int ReadFromDB(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwPetUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwPetID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwModelID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwExp, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwLevel, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwCarryLevel, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwAttrPoints, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwLiliang, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwLingli, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwNaili, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwMingjie, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&shPhysicsAttack, szBuffer+nBytesProcessed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(&shPhysicsDefense, szBuffer+nBytesProcessed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(&shMagicAttack, szBuffer+nBytesProcessed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(&shMagicDefense, szBuffer+nBytesProcessed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(&shLife, szBuffer+nBytesProcessed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(&shSpeed, szBuffer+nBytesProcessed, sizeof(unsigned short));
		nBytesProcessed += sizeof(unsigned short);

		memcpy(&byStatus, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&bySkillCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<bySkillCount; ++i)
		{
			memcpy(&bySkills[i], szBuffer+nBytesProcessed, sizeof(unsigned char));
			nBytesProcessed += sizeof(unsigned char);
		}

		return nBytesProcessed;
	}

}PET_BASE_INFO, *pPET_BASE_INFO;


typedef struct tagNotifyPetInfos
{
	unsigned char    byPetCount;
	PET_BASE_INFO    szPetInfos[MAX_PET_COUNT];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byPetCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byPetCount; ++i)
		{
			int nTemp = szPetInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byPetCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byPetCount; ++i)
		{
			int nTemp = szPetInfos[i].Read(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

	
	int    WriteToDB(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byPetCount, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byPetCount; ++i)
		{
			int nTemp = szPetInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

	int    ReadFromDB(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byPetCount, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		for (int i=0; i<byPetCount; ++i)
		{
			int nTemp = szPetInfos[i].Read(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

}NOTIFY_PET_INFOS, *pNOTIFY_PET_INFOS;


typedef struct tagNotifyAddPet
{
	unsigned char    byPetIndex;
	PET_BASE_INFO    szPetBaseInfo;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byPetIndex, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		int nTemp = szPetBaseInfo.Write(szBuffer+nBytesProcessed);
		nBytesProcessed += nTemp;

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byPetIndex, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		int nTemp = szPetBaseInfo.Read(szBuffer+nBytesProcessed);
		nBytesProcessed += nTemp;

		return nBytesProcessed;
	}

}NOTIFY_ADD_PET, *pNOTIFY_ADD_PET;

typedef struct tagNotifyUpdatePet
{
	unsigned char    byPetIndex;
	PET_BASE_INFO    szPetBaseInfo;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byPetIndex, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		int nTemp = szPetBaseInfo.Write(szBuffer+nBytesProcessed);
		nBytesProcessed += nTemp;

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byPetIndex, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		int nTemp = szPetBaseInfo.Read(szBuffer+nBytesProcessed);
		nBytesProcessed += nTemp;

		return nBytesProcessed;
	}

}NOTIFY_UPDATE_PET, *pNOTIFY_UPDATE_PET;

typedef struct tagReuqestPetFight
{
	unsigned int    byPetIndex;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byPetIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byPetIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_PET_FIGHT, *pREQUEST_PET_FIGHT;

typedef struct tagResponsePetFight
{
	unsigned char byResult;
	unsigned char byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byErrorID, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}

}RESPONSE_PET_FIGHT, *pRESPONSE_PET_FIGHT;

typedef struct tagReuqestPetUnFight
{
	unsigned int    byPetIndex;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byPetIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byPetIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_PET_UNFIGHT, *pREQUEST_PET_UNFIGHT;

typedef struct tagResponsePetUnFight
{
	unsigned char byResult;
	unsigned char byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byErrorID, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}

}RESPONSE_PET_UNFIGHT, *pRESPONSE_PET_UNFIGHT;

typedef struct tagReuqestPetRelease
{
	unsigned int    byPetIndex;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byPetIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byPetIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_PET_RELEASE, *pREQUEST_PET_RELEASE;

typedef struct tagResponsePetRelease
{
	unsigned char byResult;
	unsigned char byErrorID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byErrorID, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		return nBytesProcessed;
	}

}RESPONSE_PET_RELEASE, *pRESPONSE_PET_RELEASE;

typedef struct tagReuqestEquipPunch
{
	unsigned int    dwItemId;
	unsigned int    dwItemIndex;
	unsigned int    dwPunchIndex;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwItemId, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwItemIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwPunchIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwItemId, szBuffer+nBytesProcessed,  sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwItemIndex,szBuffer+nBytesProcessed,  sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwPunchIndex,szBuffer+nBytesProcessed,  sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_EQUIP_PUNCH, *pREQUEST_EQUIP_PUNCH;


typedef struct tagResponseEquipPunch
{
	unsigned char byResult;
	unsigned char byErrorID;
	unsigned int dwItemID;
	unsigned int dwItemIndex;
	unsigned int dwGemCount;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &dwItemID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwItemIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwGemCount, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byErrorID, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwItemID, szBuffer+nBytesProcessed,  sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwItemIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwGemCount, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}RESPONSE_EQUIP_PUNCH, *pRESPONSE_EQUIP_PUNCH;

typedef struct tagReuqestEquipMosaic
{
	unsigned int    dwItemId;
	unsigned int    dwItemIndex;
	unsigned int    dwGemId;
	unsigned int    dwGemIndex;
	unsigned int    dwPunchIndex;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwItemId, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwItemIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwGemId, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwGemIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwPunchIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwItemId, szBuffer+nBytesProcessed,  sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwItemIndex,szBuffer+nBytesProcessed,  sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwGemId, szBuffer+nBytesProcessed,  sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwGemIndex,szBuffer+nBytesProcessed,  sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwPunchIndex,szBuffer+nBytesProcessed,  sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}REQUEST_EQUIP_MOSAIC, *pREQUEST_EQUIP_MOSAIC;

typedef struct tagResponseEquipMosaic
{
	unsigned char byResult;
	unsigned char byErrorID;
	unsigned int dwItemID;
	unsigned int dwItemIndex;
	unsigned int dwPunchIndex;//空的索引
	unsigned int dwPunchGemId;//空的宝石ID

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &byErrorID, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &dwItemID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwItemIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwPunchIndex, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwPunchGemId, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byResult, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&byErrorID, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&dwItemID, szBuffer+nBytesProcessed,  sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwItemIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwPunchIndex, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwPunchGemId, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		return nBytesProcessed;
	}

}RESPONSE_EQUIP_MOSAIC, *pRESPONSE_EQUIP_MOSAIC;

#endif

