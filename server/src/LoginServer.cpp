/**
* LoginServer.cpp : Login服务器的程序主文件.
* @author：zhouxicai
* @date：2011.09.05
* @备注：
* */

#include <iostream>
#include "../common/stdafx.h"
#include "../common/ConstDefines.h"
#include "../common/net/CloudServerManager.h"
#include "../common/MySQLInterface.h"
#include "../common/TimeValue.h"
#include "../common/Log.h"
#include "ConfigFileManager.h"
//#include "ConnectManager.h"
//#include "MySQLInterface.h"
CLog g_BaseLog;
using namespace std;


//CConnectManager        *g_pConnectManager = NULL;
CCloudServerManager      *g_pConnectManager = NULL;
CMySQLInterface        *g_pMySQLInterface = NULL;
CConfigFileManager     *g_pConfigFileMgr  = NULL;
//CCloudServerManager    *g_pServerManager = NULL;

int Initialize(int iInitMode);

 
#ifdef __WINDOWS__
int _tmain(int argc, _TCHAR* argv[])
{
	/* 日志使用例子
	g_BaseLog.writelogto("./logs", "test", 1, 1, "hello %s", "log");
	*/
	char logs[16];
	memset(logs,0,16);
	strcpy(logs, "./logs/server.log");
	g_BaseLog.SetLog(logs, sizeof(logs), 1, 1);
	g_BaseLog.outlog("Server launch...");
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData ); 

	//初始化数据库，数据库目前暂定的是254 pengyuan 2014.8.13
	//logger->info(("登录服务器连接数据库..."));
	//g_pMySQLInterface = new CMySQLInterface("127.0.0.1", "root", "root");
	//g_pMySQLInterface = new CMySQLInterface("192.168.1.199", "pengyuan", "Jing0812");
	//if (!g_pMySQLInterface->ConnectDB("game_data", logger))
	//{
	//	LOG4CXX_ERROR(logger, "连接数据库失败，请检查数据库");
	//}
/*
	char szCommand[1024];
	memset(szCommand, 0, 1024);
	//尝试插入一个账号
	sprintf(szCommand, "select * from %s where dwUin=1", "base_info");
	MYSQL_RES *pResult;
	g_pMySQLInterface->ExecQuery(szCommand, &pResult);
	memset(szCommand, 0, 1024);
	//pengyuan 2012.1.26这里是插入一条基本记录到base_info表的语句
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

	//初始化连接管理器
	g_pConnectManager = new CCloudServerManager();
	if (!g_pConnectManager)
	{
		g_BaseLog.outlog("分配连接管理器失败");
	}

	if (g_pConnectManager->Init("server","127.0.0.1", 12345) != true)
	{
		g_BaseLog.outlog("初始化连接管理器失败，CConnectManager Init()失败" );
	}

	//初始化配置文件管理器
	g_pConfigFileMgr = new CConfigFileManager();
	if (!g_pConfigFileMgr->Init())
	{
		g_BaseLog.outlog("CConfigFileManager Init()失败" );
	}

	//g_pConnectManager->SetConfigFileMgr(g_pConfigFileMgr);

	//初始化服务器管理器
	/*g_pServerManager = new CCloudServerManager(logger);
	if (!g_pServerManager)
	{
		LOG4CXX_ERROR(logger, "分配服务器管理器失败");
	}
	
	if (g_pServerManager->Init("game", "127.0.0.1", 11000) != S_OK)
	{
		LOG4CXX_ERROR(logger, "初始化服务器管理器失败，CCloudServerManager Init()失败");
	}
	
	g_pConnectManager->SetServerManager(g_pServerManager);*/

	g_BaseLog.outlog("Server launch success.");
	
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
	char logs[16];
	memset(logs, 0, 16);
	strcpy(logs, "./logs/server.log");
	g_BaseLog.SetLog(logs, sizeof(logs), 1, 1);
	g_BaseLog.outlog("Server launch...");

	g_BaseLog.outlog(("Connecting to Database..."));
	//g_pMySQLInterface = new CMySQLInterface("192.168.40.128", "root", "");
	g_pMySQLInterface = new CMySQLInterface("127.0.0.1", "root", "");
	if (!g_pMySQLInterface->ConnectDB("test"))
	{
		std::cout << "Connecting to Database error. Please check database!" << std::endl;
		exit(1);
	}
	std::cout << "Connecting to Database OK..." << std::endl;

	char szCommand[1024];
	memset(szCommand, 0, 1024);
	g_pConnectManager = new CCloudServerManager();
	//g_pConnectManager = new CConnectManager();
	if (!g_pConnectManager)
	{
		std::cout << "new CConnectManager Fail..." << std::endl;
	}

	if (g_pConnectManager->Init("server","127.0.0.1", 12345) != true)
	{
		std::cout << "CConnectManager Init() Fail..." << std::endl;
	}
	std::cout << "CConnectManager Init() OK..." << std::endl;

	g_BaseLog.outlog("Server launch success ...");

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
