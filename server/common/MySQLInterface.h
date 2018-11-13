/**
* MySQLInterface.h : MySQL数据库访问的封装，头文件
* @author：zhouxicai
* @date：2011.10.19
* @备注：
* */

#ifndef __MYSQL_INTERFACE_H__
#define __MYSQL_INTERFACE_H__

#pragma once

//#include <WinSock.h>
//#include <mysql.h>
//#include "stdafx"
#include "../../include/mysql.h"
#include "../../include/mysqld_error.h"
#include "../../include/errmsg.h"

#ifdef __WINDOWS__
    #pragma comment(lib, "../../libs/libmysql.lib")
#endif


class CMySQLInterface
{
public:
	CMySQLInterface(const char * szHost, const char * szUser, const char * szPassword, unsigned int port=3306);
	~CMySQLInterface(void);

	//连接指定名字的数据库
	int    ConnectDB(const char* szDBName);

	//执行查询操作
	int    ExecQuery(const char* szCommand, MYSQL_RES **QueryResult);//错误抛出异常测试

	//执行插入操作
	int    ExecInsert(const char* szCommand);

	MYSQL* GetMySQLHandle();

	//定时ping一下mysql，免得长时间无连接，mysql自动关闭连接
	int    Ping();

protected:
	MYSQL*	m_MySQLHandle; 
	char    m_DBName[24];
	char    m_Host[24];
	char    m_User[24];
	char    m_Password[24];
	unsigned int m_Port;
};

extern CMySQLInterface* g_pMySQLInterface;

#endif