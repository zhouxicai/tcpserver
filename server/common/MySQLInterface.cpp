/**
* MySQLInterface.cpp : MySQL数据库访问的封装，实现文件
* @author：zhouxicai
* @date：2011.10.19
* @备注：
* */

#include "stdafx.h"
#include "MySQLInterface.h"
#include "TimeValue.h"

CMySQLInterface::CMySQLInterface(const char * szHost, const char * szUser, const char * szPassword, unsigned int port)
{
	//数据库连接初始化
	//mysql_init(&m_MySQLHandle);
	m_MySQLHandle =  mysql_init(NULL);

	//初始化ip地址，端口号等信息
	strcpy(m_Host, szHost);
	strcpy(m_User, szUser);
	strcpy(m_Password, szPassword);
	m_Port = port;

	//'mysql_autocommit(m_MySQLHandle, false);
}

CMySQLInterface::~CMySQLInterface(void)
{
}

//连接指定名字的数据库
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

	//pengyuan 2011.10.24 这个语句是设定查询的字符集的，只有加了这个语句，读取的汉字才不会是乱码
	int nRet = mysql_set_character_set(pMySQL, "utf8");
	if (nRet != 0)
	{
	}

	return 1;
}

//执行查询操作
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


//执行插入操作
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

//pengyuan 2012.8.15 定时ping一下mysql，免得长时间无连接，mysql自动关闭连接
int   CMySQLInterface::Ping()
{
	int nRet = mysql_ping(m_MySQLHandle);

	return nRet;
}

