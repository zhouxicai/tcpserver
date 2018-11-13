/**
* net_protocol_login.h : ��¼��������Э�鶨���ļ�.
* @author��pengyuan
* @date��2011.10.22
* @��ע��
* */

#ifndef    __NET_PROTOCOL_LOGIN_H__
#define    __NET_PROTOCOL_LOGIN_H__

#include "../stdafx.h"
#include "../constDefines.h"
#include "net_protocol_command.h"
#include <string.h>
//#include <WinSock.h>

typedef struct tagMsgHead
{
	int              nPacketLength;
	unsigned int     dwUin;
	int              nCommandID;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];
		memset(szInt,0,10);

		//itoa(nPacketLength, szInt, 10);
		sprintf(szInt, "%08x", nPacketLength);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		//itoa(dwUin, szInt, 10);
		sprintf(szInt, "%08x", dwUin);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		//itoa(nCommandID, szInt, 10);
		sprintf(szInt, "%08x", nCommandID);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &nPacketLength);
		//memcpy(&nPacketLength, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += 8;

		//nPacketLength = atoi((const char*)&nPacketLength);

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwUin);
		//memcpy(&dwUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += 8;

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &nCommandID);
		//memcpy(&nCommandID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += 8;

		//nCommandID = atoi((const char*)&nCommandID);

		return nBytesProcessed;
	}
}MSG_HEAD, *pMSG_HEAD;

typedef struct tagNewLogin
{
	unsigned int    dwSessionID;
	unsigned int    dwPort;
	unsigned char   byIPLength;
	char            szHost[24];

	tagNewLogin()
	{
		dwSessionID = INVALID_SESSION_ID;
		dwPort      = 0;
		byIPLength  = 0;
		memset(szHost, 0, 24);
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&dwSessionID, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwPort, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byIPLength, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szHost, szBuffer+nBytesProcessed, byIPLength);
		szHost[byIPLength] = '\0';
		nBytesProcessed += byIPLength;

		return nBytesProcessed;
	}

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &dwSessionID, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwPort, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byIPLength, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, szHost, byIPLength);
		nBytesProcessed += byIPLength;

		return nBytesProcessed;
	}

}NEW_LOGIN, *pNEW_LOGIN;

typedef struct tagRequestLogin
{
	int     nNameLength;
	char    szUserName[16];
	int     nPasswordLength;
	char    szPassword[16];

	tagRequestLogin()
	{
		nNameLength = 0;
		memset(szUserName, 0, 16);
		
		nPasswordLength = 0;
		memset(szPassword, 0, 16);
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &nNameLength);
		//memcpy(&nNameLength, szBuffer, 4);
		//nNameLength = atoi((const char*)&nNameLength);
		nBytesProcessed += 8;

		memcpy(szUserName, szBuffer+nBytesProcessed, nNameLength);
		szUserName[nNameLength] = '\0';
		nBytesProcessed += nNameLength;

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &nPasswordLength);
		//memcpy(&nPasswordLength, szBuffer+nBytesProcessed, 4);
		//nPasswordLength = atoi((const char*)&nPasswordLength);
		nBytesProcessed += 8;

		memcpy(szPassword, szBuffer+nBytesProcessed, nPasswordLength);
		szPassword[nPasswordLength] = '\0';
		nBytesProcessed += nPasswordLength;

		return nBytesProcessed;
	}

	int     Write()
	{
		return 0;
	}
}REQUEST_LOGIN, *pREQUEST_LOGIN;

typedef struct tagResponseLogin
{
	char            byResult;
	unsigned int    dwSessionID;
	unsigned int    dwUin;

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];
		memset(szInt,0,10);

		//sprintf(szInt, "%c", byResult);
		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(char));
		nBytesProcessed += sizeof(char);

		memset(szInt,0,10);
		//itoa(dwSessionID, szInt, 10);
		sprintf(szInt, "%08x", dwSessionID);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		//itoa(dwUin, szInt, 10);
		sprintf(szInt, "%08x", dwUin);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		szBuffer[nBytesProcessed] = '\n';
		nBytesProcessed += 1;

		return nBytesProcessed;
	}
}RESPONSE_LOGIN, *pRESPONSE_LOGIN;

//���������Ϣ
typedef struct tagNotifyPlayerBaseInfo
{
	unsigned int    dwUin;
	unsigned int    dwSilver;
	unsigned int    dwYuanbao;
	unsigned int    dwCareer;
	unsigned int    dwLevel;
	unsigned char   byNickNameLength;
	char            szNickName[16];
	unsigned int    dwExperience;
	unsigned int    dwPotentialPoint;
	unsigned int    dwSkillPoint;

	//unsigned int   dwUin;                      //Ψһ��ʶ
	//unsigned int   dwHomeLevel;                //���ѵȼ�
	//unsigned char  byHomeNameLength;           //�������ֳ���
	//char           szHomeName[32];             //������
	//int            nModelID;                   //ģ��ID
	//unsigned char  nLevel;                     //�ȼ�
	//char   nCareer;                    //ְҵ
	//char   byNickNameLength;           //�ǳƳ���
	//char   szNickName[16];             //�ǳ�
	//char   byGender;                   //�Ա�
	//int    nMapID;                     //��ͼID
	//float    nMapPosX;                 //��ͼλ��X
	//float    nMapPosY;                 //��ͼλ��Y
	//char   byTitleLength;              //�ƺų���
	//char   szTitle[12];                //�ƺ�
	//int    nHonorPoint;                //������
	//unsigned int dwExperience;         //����
	//unsigned int dwGold;               //���
	//unsigned int dwYuanbao;            //Ԫ��
	//unsigned int dwHungry;             //����ֵ
	//unsigned int dwClean;              //���ֵ
	//unsigned int dwMood;               //����ֵ
	//unsigned int dwEnergy;             //����ֵ
	//unsigned int dwHP;                 //����ֵ
	//unsigned int dwAttack;             //����
	//unsigned int dwDefense;            //����
	//unsigned int dwAgile;              //����
	//unsigned int dwIntelligence;       //����
	//unsigned int dwStrength;           //����
	//unsigned int dwDoubleHit;          //����
	//unsigned int dwToughness;          //����
	//unsigned int dwHit;                //����
	//unsigned int dwRunaround;          //����
	//int          nFlourish;            //���ٶ�
	//unsigned int dwAttrPoint;          //���Ե�

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		/*memcpy(&dwUin, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwHomeLevel, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&byHomeNameLength, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szHomeName, szBuffer+nBytesProcessed, byHomeNameLength);
		nBytesProcessed += byHomeNameLength;

		memcpy(&nModelID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nLevel, szBuffer+nBytesProcessed, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(&nCareer, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(&byNickNameLength, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szNickName, szBuffer+nBytesProcessed, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		memcpy(&byGender, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(&nMapID, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nMapPosX, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&nMapPosY, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&byTitleLength, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szTitle, szBuffer+nBytesProcessed, byTitleLength);
		nBytesProcessed += byTitleLength;

		memcpy(&nHonorPoint, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&dwExperience, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwGold, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwYuanbao, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwHungry, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwClean, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwMood, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwEnergy, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwHP, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwAttack, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwDefense, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwAgile, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwIntelligence, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwStrength, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwDoubleHit, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwToughness, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwHit, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&dwRunaround, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(&nFlourish, szBuffer+nBytesProcessed, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(&dwAttrPoint, szBuffer+nBytesProcessed, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);*/

		return nBytesProcessed;
	}

	int Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];
		memset(szInt,0,10);

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwUin);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwSilver);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwYuanbao);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwCareer);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwLevel);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memcpy(szBuffer+nBytesProcessed, &byNickNameLength, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, szNickName, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwExperience);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwPotentialPoint);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwSkillPoint);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		szBuffer[nBytesProcessed] = '\n';
		nBytesProcessed += 1;

		return nBytesProcessed;

		/*memcpy(szBuffer+nBytesProcessed, &dwUin, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwHomeLevel, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &byHomeNameLength, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, szHomeName, byHomeNameLength);
		nBytesProcessed += byHomeNameLength;

		memcpy(szBuffer+nBytesProcessed, &nModelID, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &nLevel, sizeof(unsigned char));
		nBytesProcessed += sizeof(unsigned char);

		memcpy(szBuffer+nBytesProcessed, &nCareer, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, &byNickNameLength, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, szNickName, byNickNameLength);
		nBytesProcessed += byNickNameLength;

		memcpy(szBuffer+nBytesProcessed, &byGender, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, &nMapID, sizeof(int));
		nBytesProcessed += sizeof(int);

		int nTemp;
		nTemp = nMapPosX;
		memcpy(szBuffer+nBytesProcessed, &nTemp, sizeof(int));
		nBytesProcessed += sizeof(int);

		nTemp = nMapPosY;
		memcpy(szBuffer+nBytesProcessed, &nTemp, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &byTitleLength, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, szTitle, byTitleLength);
		nBytesProcessed += byTitleLength;

		memcpy(szBuffer+nBytesProcessed, &nHonorPoint, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &dwExperience, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwGold, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwYuanbao, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwHungry, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwClean, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwMood, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwEnergy, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwHP, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwAttack, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwDefense, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwAgile, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwIntelligence, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwStrength, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwDoubleHit, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwToughness, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwHit, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &dwRunaround, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);

		memcpy(szBuffer+nBytesProcessed, &nFlourish, sizeof(int));
		nBytesProcessed += sizeof(int);

		memcpy(szBuffer+nBytesProcessed, &dwAttrPoint, sizeof(unsigned int));
		nBytesProcessed += sizeof(unsigned int);*/
	}
}NOTIFY_PLAYER_BASE_INFO, *pNOTIFY_PLAYER_BASE_INFO;


typedef struct tagRequestRegister
{
	int     nNameLength;
	char    szUserName[16];
	int     nPasswordLength;
	char    szPassword[16];

	tagRequestRegister()
	{
		nNameLength = 0;
		memset(szUserName, 0, 16);

		nPasswordLength = 0;
		memset(szPassword, 0, 16);
	}

	int     Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &nNameLength);
		nBytesProcessed += 8;

		memcpy(szUserName, szBuffer+nBytesProcessed, nNameLength);
		nBytesProcessed += nNameLength;

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &nPasswordLength);
		nBytesProcessed += 8;

		memcpy(szPassword, szBuffer+nBytesProcessed, nPasswordLength);
		nBytesProcessed += nPasswordLength;

		return nBytesProcessed;
	}

	int     Write()
	{
		return 0;
	}
}REQUEST_REGISTER, *pREQUEST_REGISTER;


typedef struct tagResponseRegister
{
	unsigned char    byResult;
	unsigned int     dwSessionID;
	unsigned int     dwUin;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];
		memset(szInt,0,10);

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(char));
		nBytesProcessed += sizeof(char);

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwSessionID);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwUin);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		szBuffer[nBytesProcessed] = '\n';
		nBytesProcessed += 1;

		return nBytesProcessed;
	}
}RESPONSE_REGISTER, *pRESPONSE_REGISTER;


//������ɫЭ��
typedef struct tagRequestCreateCharacter
{
	unsigned int     dwUin;
	unsigned char    byCareerID;   
	unsigned char    byGenderID;

	unsigned int     byNickNameLen;              
	char             szNickName[16];


	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwUin);
		nBytesProcessed += 8;

		memcpy(&byCareerID, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(&byGenderID, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &byNickNameLen);
		nBytesProcessed += 8;
		
		memcpy(szNickName, szBuffer+nBytesProcessed, byNickNameLen);
		szNickName[byNickNameLen] = '\0';
		nBytesProcessed += byNickNameLen;

		return nBytesProcessed;
	}
}REQUEST_CREATE_CHARACTER, *pREQUEST_CREATE_CHARACTER;


//�ظ�������ɫЭ��
typedef struct tagResponseCreateCharacter
{
	unsigned char    byResult;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(char));
		nBytesProcessed += sizeof(char);

		szBuffer[nBytesProcessed] = '\n';
		nBytesProcessed += 1;

		return nBytesProcessed;
	}


}RESPONSE_CREATE_CHARACTER, *PRESPONSE_CREATE_CHARACTER;



typedef struct tagItemGridInfo
{
	unsigned int    dwItemID;
	unsigned short  shCount;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];
		memset(szInt,0,10);

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwItemID);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		sprintf(szInt, "%04x", shCount);
		memcpy(szBuffer+nBytesProcessed, szInt, 4);
		nBytesProcessed += 4;

		/* ITEM_GRID_INFO��ΪǶ��Э��ʹ��,���Խ�β����Ҫ���,ͬʱ��Ҫע��������ܵ�������!!!
		szBuffer[nBytesProcessed] = '\n';
		nBytesProcessed += 1;*/

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwItemID);
		nBytesProcessed += 8;

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 4);
		sscanf(szInt, "%hx", &shCount);
		nBytesProcessed += 4;

		return nBytesProcessed;
	}
}ITEM_GRID_INFO, *pITEM_GRID_INFO;


//�������ĵ��߸���Ϣ
typedef struct tagSingleItemGridInfo
{
	unsigned short  shGridIndex;
	unsigned int    dwItemID;
	unsigned short  shCount;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt,0,10);
		sprintf(szInt, "%04x", shGridIndex);
		memcpy(szBuffer+nBytesProcessed, szInt, 4);
		nBytesProcessed += 4;

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwItemID);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		sprintf(szInt, "%04x", shCount);
		memcpy(szBuffer+nBytesProcessed, szInt, 4);
		nBytesProcessed += 4;

		/* ITEM_GRID_INFO��ΪǶ��Э��ʹ��,���Խ�β����Ҫ���,ͬʱ��Ҫע��������ܵ�������!!!
		szBuffer[nBytesProcessed] = '\n';
		nBytesProcessed += 1;*/

		return nBytesProcessed;
	}

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 4);
		sscanf(szInt, "%hx", &shGridIndex);
		nBytesProcessed += 4;

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwItemID);
		nBytesProcessed += 8;

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 4);
		sscanf(szInt, "%hx", &shCount);
		nBytesProcessed += 4;

		return nBytesProcessed;
	}
}SINGLE_ITEM_GRID_INFO, *pSINGLE_ITEM_GRID_INFO;


typedef struct tagPlayerItemInfo
{
	unsigned short    shTotalCount;
	ITEM_GRID_INFO    szItemInfo[MAX_ITEM_COUNT];

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 4);
		sscanf(szInt, "%hx", &shTotalCount);
		nBytesProcessed += 4;

		for (int i=0; i<shTotalCount; ++i)
		{
			int nTemp = 0;
			nTemp += szItemInfo[i].Read(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}


	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt,0,10);
		sprintf(szInt, "%04x", shTotalCount);
		memcpy(szBuffer+nBytesProcessed, szInt, 4);
		nBytesProcessed += 4;

		for (int i=0; i<shTotalCount; ++i)
		{
			int nTemp = 0;
			nTemp = szItemInfo[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		szBuffer[nBytesProcessed] = '\n';
		nBytesProcessed += 1;

		return nBytesProcessed;
	}

}PLAYER_ITEM_INFO, *pPLAYER_ITEM_INFO;


#define    MAX_ITEM_CHANGE_COUNT          8

typedef struct tagNotifyItemChange
{
	unsigned char           byItemCount;
	SINGLE_ITEM_GRID_INFO   szItemInfos[MAX_ITEM_CHANGE_COUNT];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byItemCount, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byItemCount; ++i)
		{
			int nTemp = szItemInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		szBuffer[nBytesProcessed] = '\n';
		nBytesProcessed += 1;

		return nBytesProcessed;

	}
}NOTIFY_ITEM_CHANGE,*pNOTIFY_ITEM_CHANGE;


//�����˳�����Э��
typedef struct tagRequestExitDuplicate
{
	unsigned int     dwUin;
	unsigned int     dwDupID;   
	unsigned char    byBattleResult;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwUin);
		nBytesProcessed += 8;

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwDupID);
		nBytesProcessed += 8;

		memcpy(&byBattleResult, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		return nBytesProcessed;
	}
}REQUEST_EXIT_DUPLICATE, *pREQUEST_EXIT_DUPLICATE;


typedef struct tagGeneralLevelChange
{
	unsigned char    byIndex;             //�����ڿͻ��˴�ŵ�30����������������ţ���Ч����Ϊ255��
	unsigned char    byLevel;
	unsigned int     dwGeneralExp;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memcpy(szBuffer+nBytesProcessed, &byIndex, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, &byLevel, sizeof(char));
		nBytesProcessed += sizeof(char);

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwGeneralExp);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		return nBytesProcessed;
	}
}GENERAL_LEVEL_CHANGE, *pGENERAL_LEVEL_CHANGE;

//��Ӧ�˳�����Э��
typedef struct tagResponseExitDuplicate
{
	unsigned int     dwLevel;
	unsigned int     dwCurrentExp;   
	unsigned int     dwTili;
	//��ӽ����õľ���,��������,�������id����Ŀ
	//unsigned int     dwGeneralExp;
	GENERAL_LEVEL_CHANGE  szGeneralLevelChange[4];
	unsigned int     dwSilver;
	unsigned char    byItemCount;
	SINGLE_ITEM_GRID_INFO   szItemInfos[MAX_ITEM_CHANGE_COUNT];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];
		memset(szInt,0,10);

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwLevel);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwCurrentExp);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwTili);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		/*memset(szInt,0,10);
		sprintf(szInt, "%08x", dwGeneralExp);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;*/

		for (int i=0; i<4; ++i)
		{
			int nTemp = szGeneralLevelChange[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwSilver);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memcpy(szBuffer+nBytesProcessed, &byItemCount, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byItemCount; ++i)
		{
			int nTemp = szItemInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		szBuffer[nBytesProcessed] = '\n';
		nBytesProcessed += 1;

		return nBytesProcessed;
	}

}RESPONSE_EXIT_DUPLICATE, *pRESPONSE_EXIT_DUPLICATE;


typedef struct tagSingleEquipInfo
{
	unsigned int    dwEquipID;
	unsigned char   byEquipLevel;         //�����ȼ�
	unsigned int    dwEquipExperience;    //װ����ʣ��ľ���

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];
		memset(szInt,0,10);

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwEquipID);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memcpy(szBuffer+nBytesProcessed, &byEquipLevel, sizeof(char));
		nBytesProcessed += sizeof(char);

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwEquipExperience);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		return nBytesProcessed;
	}


	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwEquipID);
		nBytesProcessed += 8;

		memcpy(&byEquipLevel, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwEquipExperience);
		nBytesProcessed += 8;

		return nBytesProcessed;
	}

}SINGLE_EQUIP_INFO, *pSINGLE_EQUIP_INFO;


typedef struct tagSingleSkillInfo
{
	unsigned int    dwSkillID;
	unsigned char   bySkillPhase;          //���ܵĽ׶�
	unsigned char   bySkillLevel;          //���ܵĵȼ�

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];
		memset(szInt,0,10);

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwSkillID);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memcpy(szBuffer+nBytesProcessed, &bySkillPhase, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, &bySkillLevel, sizeof(char));
		nBytesProcessed += sizeof(char);

		return nBytesProcessed;
	}


	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwSkillID);
		nBytesProcessed += 8;

		memcpy(&bySkillPhase, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(&bySkillLevel, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		return nBytesProcessed;
	}

}SINGLE_SKILL_INFO, *pSINGLE_SKILL_INFO;


//�������Ϣ�洢������洢����һ���������Ϣ
typedef struct tagSingleGeneralInfo
{
	unsigned int    dwGeneralID;
	unsigned char   byGeneralLevel;
	unsigned int    dwExperience;
	unsigned char   byGeneralStar;
	unsigned char   byShangzhen;                                 //0Ϊû����1Ϊ����
	unsigned char   byGeneralPosition;                           //����λ��
	SINGLE_EQUIP_INFO szEquipInfos[MAX_EQUIP_COUNT_PER_PLAYER];
	SINGLE_SKILL_INFO szSkillInfos[MAX_SKILL_COUNT_PER_PLAYER];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];
		memset(szInt,0,10);

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwGeneralID);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memcpy(szBuffer+nBytesProcessed, &byGeneralLevel, sizeof(char));
		nBytesProcessed += sizeof(char);

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwExperience);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memcpy(szBuffer+nBytesProcessed, &byGeneralStar, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, &byShangzhen, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, &byGeneralPosition, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<MAX_EQUIP_COUNT_PER_PLAYER; ++i)
		{
			int nTemp = szEquipInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		for (int i=0; i<MAX_SKILL_COUNT_PER_PLAYER; ++i)
		{
			int nTemp = szSkillInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}


	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwGeneralID);
		nBytesProcessed += 8;

		memcpy(&byGeneralLevel, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwExperience);
		nBytesProcessed += 8;

		memcpy(&byGeneralStar, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(&byShangzhen, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(&byGeneralPosition, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<MAX_EQUIP_COUNT_PER_PLAYER; ++i)
		{
			int nTemp = szEquipInfos[i].Read(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		for (int i=0; i<MAX_SKILL_COUNT_PER_PLAYER; ++i)
		{
			int nTemp = szSkillInfos[i].Read(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

}SINGLE_GENERAL_INFO, *pSINGLE_GENERAL_INFO;


typedef struct tagGeneralInfos
{
	unsigned char   byGeneralCount;
	SINGLE_GENERAL_INFO  szGeneralInfos[MAX_GENERAL_COUNT_PER_PLAYER];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byGeneralCount, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byGeneralCount; ++i)
		{
			int nTemp = szGeneralInfos[i].Write(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		szBuffer[nBytesProcessed] = '\n';
		nBytesProcessed += 1;

		return nBytesProcessed;
	}


	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(&byGeneralCount, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byGeneralCount; ++i)
		{
			int nTemp = szGeneralInfos[i].Read(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}
}GENERAL_INFOS, *pGENERAL_INFOS;


typedef struct tagSingleGeneralPosition
{
	unsigned int    dwGeneralID;
	unsigned char   byGeneralPosition;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];
		memset(szInt,0,10);

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwGeneralID);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memcpy(szBuffer+nBytesProcessed, &byGeneralPosition, sizeof(char));
		nBytesProcessed += sizeof(char);

		return nBytesProcessed;
	}


	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwGeneralID);
		nBytesProcessed += 8;

		memcpy(&byGeneralPosition, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		return nBytesProcessed;
	}

}SINGLE_GENERAL_POSITION, *pSINGLE_GENERAL_POSITION;


typedef struct tagRequestGeneralPosition
{
	SINGLE_GENERAL_POSITION    szGeneralPositions[MAX_GENERAL_IN_BATTLE];

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		for (int i=0; i<MAX_GENERAL_IN_BATTLE; ++i)
		{
			int nTemp = szGeneralPositions[i].Read(szBuffer+nBytesProcessed);
			nBytesProcessed += nTemp;
		}

		return nBytesProcessed;
	}

}REQUEST_GENERAL_POSITION, *pREQUEST_GENERAL_POSITION;


typedef struct tagResponseGeneralPosition
{
	unsigned char    byResult;

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(char));
		nBytesProcessed += sizeof(char);

		szBuffer[nBytesProcessed] = '\n';
		nBytesProcessed += 1;

		return nBytesProcessed;
	}
}RESPONSE_GENERAL_POSITION, *pRESPONSE_GENERAL_POSITION;


typedef struct tagRequestGeneralEquipChange
{
	unsigned char    byGeneralIndex;
	unsigned char    byEquipLocation;
	unsigned int     dwEquipID;

	int    Read(const char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];

		memcpy(&byGeneralIndex, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(&byEquipLocation, szBuffer+nBytesProcessed, sizeof(char));
		nBytesProcessed += sizeof(char);

		memset(szInt, 0, 10);
		memcpy(szInt, szBuffer+nBytesProcessed, 8);
		sscanf(szInt, "%x", &dwEquipID);
		nBytesProcessed += 8;

		return nBytesProcessed;
	}

}REQUEST_GENERAL_EQUIP_CHANGE, *pREQUEST_GENERAL_EQUIP_CHANGE;


typedef struct tagResponseGeneralEquipChange
{
	unsigned char    byResult;
	unsigned char    byGeneralIndex;
	unsigned char    byEquipLocation;
	unsigned int     dwEquipID;
	unsigned char           byItemCount;
	SINGLE_ITEM_GRID_INFO   szItemInfos[MAX_ITEM_CHANGE_COUNT];

	int    Write(char* szBuffer)
	{
		int nBytesProcessed = 0;

		char szInt[10];
		memset(szInt,0,10);

		memcpy(szBuffer+nBytesProcessed, &byResult, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, &byGeneralIndex, sizeof(char));
		nBytesProcessed += sizeof(char);

		memcpy(szBuffer+nBytesProcessed, &byEquipLocation, sizeof(char));
		nBytesProcessed += sizeof(char);

		memset(szInt,0,10);
		sprintf(szInt, "%08x", dwEquipID);
		memcpy(szBuffer+nBytesProcessed, szInt, 8);
		nBytesProcessed += 8;

		memcpy(szBuffer+nBytesProcessed, &byItemCount, sizeof(char));
		nBytesProcessed += sizeof(char);

		for (int i=0; i<byItemCount; ++i)
		{
			int nTemp = szItemInfos[i].Write(szBuffer + nBytesProcessed);
			nBytesProcessed += nTemp;
		}
		
		szBuffer[nBytesProcessed] = '\n';

		return nBytesProcessed;
	}
}RESPONSE_GENERAL_EQUIP_CHANGE, *pRESPONSE_GENERAL_EQUIP_CHANGE;

#endif



