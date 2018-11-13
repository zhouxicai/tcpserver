/**
* LoginServer.cpp : Login�������ĳ������ļ�.
* @author��zhouxicai
* @date��2011.09.05
* @��ע��
* */

#include <iostream>
#include "../../common/stdafx.h"
#include "../../common/apache-log4cxx-0.10.0/log4cxx/logger.h"
#include "../../common/apache-log4cxx-0.10.0/log4cxx/propertyconfigurator.h"
#include "../../common/ConstDefines.h"
#include "../../common/net/CloudServerManager.h"
#include "../../common/database/MySQLInterface.h"
#include "../../common/time/TimeValue.h"
#include "ConfigFileManager.h"
//#include "ConnectManager.h"
//#include "MySQLInterface.h"


using namespace std;
using namespace log4cxx;

#ifdef     _DEBUG
    #pragma  comment(lib, "log4cxxd.lib")
#else
    #pragma  comment(lib, "log4cxx.lib")
#endif

//CConnectManager        *g_pConnectManager = NULL;
CCloudServerManager      *g_pConnectManager = NULL;
CMySQLInterface        *g_pMySQLInterface = NULL;
CConfigFileManager     *g_pConfigFileMgr  = NULL;
//CCloudServerManager    *g_pServerManager = NULL;

int Initialize(int iInitMode);

 
#ifdef __WINDOWS__
int _tmain(int argc, _TCHAR* argv[])
{
	//CloudLog("LoginServer��ʼ��...\n");
//#pragma message("����Ӧ�����һ����ȡ�����ļ���ģ��");

	string trace = "";
	string Property = "log4cxx.server.properties";
	log4cxx::PropertyConfigurator::configure(Property);
	LoggerPtr logger = Logger::getLogger(trace);

	LOG4CXX_INFO(logger, "Server launch...");
	/*for(int i = 0; i < 2; i++)
	{
		LOG4CXX_DEBUG(logger, "DEBUG"); 
		LOG4CXX_INFO(logger, "INFO"); 
		LOG4CXX_WARN(logger, "WARN");
		LOG4CXX_ERROR(logger, "ERROR");

	}*/
	//cout<<__DATE__<<"  "<<__TIME__<<"  LoginServer��ʼ��..."<<endl;

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData ); 

	//��ʼ�����ݿ⣬���ݿ�Ŀǰ�ݶ�����254 pengyuan 2014.8.13
	//logger->info(("��¼�������������ݿ�..."));
	//g_pMySQLInterface = new CMySQLInterface("127.0.0.1", "root", "root");
	//g_pMySQLInterface = new CMySQLInterface("192.168.1.199", "pengyuan", "Jing0812");
	//if (!g_pMySQLInterface->ConnectDB("game_data", logger))
	//{
	//	LOG4CXX_ERROR(logger, "�������ݿ�ʧ�ܣ��������ݿ�");
	//}
/*
	char szCommand[1024];
	memset(szCommand, 0, 1024);
	//���Բ���һ���˺�
	sprintf(szCommand, "select * from %s where dwUin=1", "base_info");
	MYSQL_RES *pResult;
	g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	memset(szCommand, 0, 1024);
	//pengyuan 2012.1.26�����ǲ���һ��������¼��base_info������
	sprintf(szCommand, "insert into %s values (%u, %u, %u, %u, '%s',%u, %u, %u,%u, %u, '%s', %u, %u, %u, %u, %u, %u, %u, %u, %u, %u )", 
		"base_info", 1, 2 , 1, 0, "", 1, 1001, 420, 420, 0, "", 0, 0, 100, 100, 100, 100, 100, 100, 100, 100);
	g_pMySQLInterface->ExecInsert(szCommand);*/
	/*memset(szCommand, 0, 1024);
	sprintf(szCommand, "insert into %s values ('%s', '%s', %u)", 
		"account", "wangzhezhi" ,"123456",4);
	g_pMySQLInterface->ExecInsert(szCommand);
	memset(szCommand, 0, 1024);
	sprintf(szCommand, "insert into %s values ('%s', '%s', %u)", 
		"account", "lijian" ,"123456",5);
	g_pMySQLInterface->ExecInsert(szCommand);
	memset(szCommand, 0, 1024);
	sprintf(szCommand, "insert into %s values ('%s', '%s', %u)", 
		"account", "jojo" ,"123456",6);
	g_pMySQLInterface->ExecInsert(szCommand);
	memset(szCommand, 0, 1024);
	sprintf(szCommand, "insert into %s values ('%s', '%s', %u)", 
		"account", "jixiaotian" ,"123456",7);
	g_pMySQLInterface->ExecInsert(szCommand);*/

	//��ʼ�����ӹ�����pengyuan 2014.8.13
	g_pConnectManager = new CCloudServerManager(logger);
	if (!g_pConnectManager)
	{
		LOG4CXX_ERROR(logger, "�������ӹ�����ʧ��");
	}

	//pengyuan 2014.8.13
	if (g_pConnectManager->Init("server","127.0.0.1", 12345) != true)
	{
		LOG4CXX_ERROR(logger, "��ʼ�����ӹ�����ʧ�ܣ�CConnectManager Init()ʧ��");
	}

	//pengyuan 2014.8.18 ��ʼ�������ļ�������
	g_pConfigFileMgr = new CConfigFileManager();
	if (!g_pConfigFileMgr->Init())
	{
		LOG4CXX_ERROR(logger, "CConfigFileManager Init()ʧ��");
	}

	//g_pConnectManager->SetConfigFileMgr(g_pConfigFileMgr);

	//��ʼ��������������
	/*g_pServerManager = new CCloudServerManager(logger);
	if (!g_pServerManager)
	{
		LOG4CXX_ERROR(logger, "���������������ʧ��");
	}
	
	if (g_pServerManager->Init("game", "127.0.0.1", 11000) != S_OK)
	{
		LOG4CXX_ERROR(logger, "��ʼ��������������ʧ�ܣ�CCloudServerManager Init()ʧ��");
	}
	
	g_pConnectManager->SetServerManager(g_pServerManager);*/

	LOG4CXX_INFO(logger, "Server launch success.");
	
	CTimeValue timeValue;
	double fDeltaTime = 0.0f;
	double fServerTime = 0.0f;
	int    nCount = 0;

	while(true)
	{
		timeValue.Begin();
		g_pConnectManager->Run();

		/*Sleep(50);

		fDeltaTime = timeValue.End();
		fServerTime += fDeltaTime;
		if ((fServerTime/60) > nCount)
		{
			LOG4CXX_INFO(logger, "MySQL Ping......");
			g_pMySQLInterface->Ping();
			nCount++;
		}*/

		
	}

	g_pConnectManager->Stop();

	return 0;
}
#endif

#ifdef __LINUX__
int main(int argc, char* argv[])
{
	string trace = "";
	string Property = "log4cxx.server.properties";
	log4cxx::PropertyConfigurator::configure(Property);
	LoggerPtr logger = Logger::getLogger(trace);

	LOG4CXX_INFO(logger, "Server launch...");

	logger->info(("Connecting to Database..."));
	//g_pMySQLInterface = new CMySQLInterface("192.168.40.128", "root", "");
	g_pMySQLInterface = new CMySQLInterface("127.0.0.1", "root", "");
	if (!g_pMySQLInterface->ConnectDB("test", logger))
	{
		LOG4CXX_ERROR(logger, "Connecting to Database error. Please check database!");
		exit(1);
	}
	LOG4CXX_INFO(logger, "Connecting to Database OK...");

	char szCommand[1024];
	memset(szCommand, 0, 1024);
	g_pConnectManager = new CCloudServerManager(logger);
	//g_pConnectManager = new CConnectManager();
	if (!g_pConnectManager)
	{
		LOG4CXX_ERROR(logger, "new CConnectManager Fail...");
	}

	if (g_pConnectManager->Init("server","127.0.0.1", 12345) != true)
	{
		LOG4CXX_ERROR(logger, "CConnectManager Init() Fail...");
	}
	LOG4CXX_INFO(logger, "CConnectManager Init() OK...");

	LOG4CXX_INFO(logger, "Server launch success...");

	CTimeValue timeValue;
	double fDeltaTime = 0.0f;
	double fServerTime = 0.0f;
	int    nCount = 0;

	while(true)
	{
		timeValue.Begin();
		g_pConnectManager->Run();

		usleep(50);

		fDeltaTime = timeValue.End();
		fServerTime += fDeltaTime;
		if ((fServerTime/60) > nCount)
		{
			g_pMySQLInterface->Ping();
			nCount++;
		}
	}

	g_pConnectManager->Stop();

	return 0;
}
#endif

int Initialize(int iInitMode)
{
	return 0;
}
