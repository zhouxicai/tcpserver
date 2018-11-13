//
//�ļ����ƣ�	CloudSocket.h
//����������	��װ����Socket�Ĺ��ܣ�ͨ���ӿ�ʵ�����е��������
//				
//


#ifndef __CLOUD_SOCKET_H__
#define __CLOUD_SOCKET_H__
//
//#include "BaseType.h"
//#include "SocketAPI.h"
#include "../stdafx.h"
#pragma comment(lib, "ws2_32.lib")


//�����������
enum
{
	SELECT_BAK = 0,	//��ǰϵͳ��ӵ�е������������
	SELECT_USE = 1,	//����select���õľ������
	SELECT_MAX = 2, //�ṹʹ������
};

//////////////////////////////////////////////////////////////////////////////
// class Socket
//
// TCP Client Socket
//
// 
//
// 
//////////////////////////////////////////////////////////////////////////////

#define IP_SIZE        24

class CloudSocket 
{
//////////////////////////////////////////////////
// constructor/destructor
//////////////////////////////////////////////////
public :
	
	// constructor
	CloudSocket () ;
	CloudSocket (const char* host, unsigned int port) ;
	
	// destructor
	virtual ~CloudSocket () ;

	
//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	bool create() ;
	
	// close connection
	void Close () ;
	
	// try connect to remote host
	bool Connect () ;
	bool Connect (const char* host, unsigned int port) ;

	// close previous connection and connect to another socket
	bool reconnect (const char* host, unsigned int port) ;
	
	// send data to peer
	unsigned int Send (const void* buf, unsigned int len, unsigned int flags = 0) ;
	
	// receive data from peer
	unsigned int receive (void* buf, unsigned int len, unsigned int flags = 0) ;
	
	unsigned int available ()const ;

	SOCKET Accept( struct sockaddr* addr, unsigned int* addrlen ) ;

	bool Bind( ) ;
	bool Bind( unsigned int port ) ;

	bool Listen( int backlog ) ;

//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
 
    // get/set socket's linger status
    unsigned int getLinger ()const ;
    bool setLinger (unsigned int lingertime) ;

	bool isReuseAddr ()const ;
	bool setReuseAddr (bool on = true) ;

	// get is Error
    unsigned int getSockError()const ;
 
    // get/set socket's nonblocking status
    bool isNonBlocking ()const ;
    bool setNonBlocking (bool on = true) ;
 
    // get/set receive buffer size
    unsigned int getReceiveBufferSize ()const ;
    bool setReceiveBufferSize (unsigned int size) ;
 
    // get/set send buffer size
    unsigned int getSendBufferSize ()const ;
    bool setSendBufferSize (unsigned int size) ;
 
	unsigned int getPort ()const ;
	unsigned long getHostIP ()const ;

	// check if socket is valid
	bool isValid ()const ;

	// get socket descriptor
	SOCKET getSOCKET ()const ;

	bool isSockError()const ;

public :

	SOCKET m_SocketID;
	
	// socket address structure
	//SOCKADDR_IN m_SockAddr;
	struct sockaddr_in m_SockAddr;
	
	// peer host
	char m_Host[IP_SIZE];
	
	// peer port
	unsigned int m_Port;


};

#endif
