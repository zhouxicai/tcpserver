/**
* MySQLInterface.cpp : MySQL���ݿ���ʵķ�װ��ʵ���ļ�
* @author��zhouxicai
* @date��2011.10.19
* @��ע��
* */

#include "stdafx.h"
#include "MySQLInterface.h"
#include "TimeValue.h"

CMySQLInterface::CMySQLInterface(const char * szHost, const char * szUser, const char * szPassword, unsigned int port)
{
	//���ݿ����ӳ�ʼ��
	//mysql_init(&m_MySQLHandle);
	m_MySQLHandle =  mysql_init(NULL);

	//��ʼ��ip��ַ���˿ںŵ���Ϣ
	strcpy(m_Host, szHost);
	strcpy(m_User, szUser);
	strcpy(m_Password, szPassword);
	m_Port = port;

	//'mysql_autocommit(m_MySQLHandle, false);
}

CMySQLInterface::~CMySQLInterface(void)
{
}

//����ָ�����ֵ����ݿ�
int    CMySQLInterface::ConnectDB(const char *szDBName)
{
	strcpy(m_DBName, szDBName);

	MYSQL* pMySQL;
	unsigned long	lFlags = 0;
	lFlags |= CLIENT_MULTI_STATEMENTS;
	pMySQL = mysql_real_connect( m_MySQLHandle, m_Host, m_User, m_Password, m_DBName, m_Port, NULL, lFlags );
	if (pMySQL == NULL)
	{
		mysql_close(m_MySQLHandle);
		return 0;
	}

	const char* pMySQLStat = mysql_stat(m_MySQLHandle);
	if (pMySQLStat == NULL)
	{
		mysql_close(m_MySQLHandle);
		return 0;
	}

	//pengyuan 2011.10.24 ���������趨��ѯ���ַ����ģ�ֻ�м��������䣬��ȡ�ĺ��ֲŲ���������
	int nRet = mysql_set_character_set(pMySQL, "utf8");
	if (nRet != 0)
	{
	}

	return 1;
}

//ִ�в�ѯ����
int    CMySQLInterface::ExecQuery(const char *szCommand, MYSQL_RES **QueryResult)
{
	CTimeValue cTimeValue;
	cTimeValue.Begin();

	int nRet;
	nRet = mysql_query(m_MySQLHandle, szCommand);

	const char* pError = mysql_error(m_MySQLHandle);

	if (nRet != 0)
	{
		std::cout<<"Query database error: "<<pError<<std::endl;
	}

	int nAffectRows = mysql_affected_rows(m_MySQLHandle);
	if(nAffectRows > 0){
		std::cout << "nAffectRows:"<<nAffectRows << std::endl;
	}	

	*QueryResult = mysql_store_result(m_MySQLHandle);

	double fDeltaTime = cTimeValue.End();
	std::cout << "ExecQuery:"<< szCommand<< " fDeltaTime:"<<fDeltaTime << std::endl;
	return nRet;
}


//ִ�в������
int    CMySQLInterface::ExecInsert(const char *szCommand)
{
	int nRet;
	nRet = mysql_query(m_MySQLHandle, szCommand);

	return nRet;
}


MYSQL* CMySQLInterface::GetMySQLHandle()
{
	return m_MySQLHandle;
}

//pengyuan 2012.8.15 ��ʱpingһ��mysql����ó�ʱ�������ӣ�mysql�Զ��ر�����
int   CMySQLInterface::Ping()
{
	int nRet = mysql_ping(m_MySQLHandle);

	return nRet;
}

