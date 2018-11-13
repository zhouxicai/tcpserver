/**
* MySQLInterface.h : MySQL���ݿ���ʵķ�װ��ͷ�ļ�
* @author��zhouxicai
* @date��2011.10.19
* @��ע��
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

	//����ָ�����ֵ����ݿ�
	int    ConnectDB(const char* szDBName);

	//ִ�в�ѯ����
	int    ExecQuery(const char* szCommand, MYSQL_RES **QueryResult);//�����׳��쳣����

	//ִ�в������
	int    ExecInsert(const char* szCommand);

	MYSQL* GetMySQLHandle();

	//��ʱpingһ��mysql����ó�ʱ�������ӣ�mysql�Զ��ر�����
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