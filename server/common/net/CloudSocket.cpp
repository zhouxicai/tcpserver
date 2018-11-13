#include "../stdafx.h"
//////////////////////////////////////////////////////////////////////
// 
// CloudSocket.cpp
// 
// 
//////////////////////////////////////////////////////////////////////

#include "CloudSocket.h"

CloudSocket::CloudSocket () 
{ 
	m_SocketID = INVALID_SOCKET ;
	memset( &m_SockAddr, 0, sizeof(SOCKADDR_IN) ) ;
	memset( m_Host, 0, IP_SIZE ) ;
	m_Port = 0 ;
}

CloudSocket::CloudSocket ( const char* host , unsigned int port ) 
{ 
	strncpy( m_Host, host, IP_SIZE-1 ) ;
	m_Port = port ;

//	create() ;	
}

CloudSocket::~CloudSocket () 
{ 
	Close() ;
}

#ifdef __WINDOWS__

bool CloudSocket::create( )
{
	m_SocketID = socket(AF_INET, SOCK_STREAM, 0);

	int iError = WSAGetLastError();
	if (iError == INVALID_SOCKET)
	{
		return false;
	}
    
	memset( &m_SockAddr , 0 , sizeof(m_SockAddr) );
	m_SockAddr.sin_addr.s_addr = htonl( INADDR_ANY);
	m_SockAddr.sin_family      = AF_INET;
	m_SockAddr.sin_port        = htons(m_Port);

	if( isValid() )
		return true ;
	else 
		return false ;

	return false ;
}

void CloudSocket::Close () 
{ 
	if( isValid() && !isSockError() ) 
	{
		closesocket( m_SocketID );
	}

	m_SocketID = INVALID_SOCKET ;
	memset( &m_SockAddr, 0, sizeof(SOCKADDR_IN) ) ;
	memset( m_Host, 0, IP_SIZE ) ;
	m_Port = 0 ;
}


unsigned int CloudSocket::available ()const
{ 
	unsigned long argp = 0;
	ioctlsocket(m_SocketID, FIONREAD, &argp);
	return argp;
}

unsigned int CloudSocket::getLinger ()const 
{ 
	struct linger ling;
	unsigned int len = sizeof(ling);

	if(getsockopt( m_SocketID , SOL_SOCKET , SO_LINGER , (char*)&ling , (int*)&len ) == SOCKET_ERROR)
	{
		return SOCKET_ERROR;
	}

	return ling.l_linger;
}


SOCKET CloudSocket::Accept( struct sockaddr* addr, unsigned int* addrlen )
{
	SOCKET client = accept( m_SocketID , addr , (int*)addrlen );

	return client;
}

bool CloudSocket::setNonBlocking (bool on ) 
{ 
	unsigned long argp = ( on == true ) ? 1 : 0;

	int nRet = ioctlsocket( m_SocketID, FIONBIO, &argp);

	if (nRet == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}



unsigned int CloudSocket::getReceiveBufferSize ()const 
{ 
	unsigned int ReceiveBufferSize;
	unsigned int size = sizeof(ReceiveBufferSize);

	getsockopt( m_SocketID , SOL_SOCKET , SO_RCVBUF , (char*)&ReceiveBufferSize, (int*)&size );

	return ReceiveBufferSize;

	return 0 ;
}


unsigned int CloudSocket::getSendBufferSize ()const 
{ 
	unsigned int SendBufferSize;
	unsigned int size = sizeof(SendBufferSize);

	getsockopt( m_SocketID , SOL_SOCKET , SO_SNDBUF , (char*)&SendBufferSize, (int*)&size );

	return SendBufferSize;

	return 0 ;
}

bool CloudSocket::isSockError()const
{
	int error;
	unsigned int len = sizeof(error);

	int Result = getsockopt( m_SocketID , SOL_SOCKET , SO_ERROR , (char*)&error, (int*)&len );

	if( Result == SOCKET_ERROR ) 
		return true;
	else 			  
		return false;

	return false ;
}


bool CloudSocket::isReuseAddr ()const
{
	int reuse;
	unsigned int len = sizeof(reuse);

	getsockopt( m_SocketID , SOL_SOCKET , SO_REUSEADDR , (char*)&reuse , (int*)&len );

	return reuse == 1;

	return 0 ;
}

#endif

#ifdef __LINUX__

bool CloudSocket::create( )
{
	m_SocketID = socket(AF_INET, SOCK_STREAM, 0);

	//int iError = WSAGetLastError();
	if (m_SocketID == INVALID_SOCKET)
	{
		return false;
	}

	memset( &m_SockAddr , 0 , sizeof(m_SockAddr) );
	m_SockAddr.sin_addr.s_addr = htonl( INADDR_ANY);
	m_SockAddr.sin_family      = AF_INET;
	m_SockAddr.sin_port        = htons(m_Port);

	if( isValid() )
		return true ;
	else 
		return false ;

	return false ;
}

void CloudSocket::Close() 
{ 
	if( isValid() && !isSockError() ) 
	{
		close( m_SocketID );
	}

	m_SocketID = INVALID_SOCKET ;
	memset( &m_SockAddr, 0, sizeof(SOCKADDR_IN) ) ;
	memset( m_Host, 0, IP_SIZE ) ;
	m_Port = 0 ;
}


unsigned int CloudSocket::available ()const
{ 
	unsigned long argp = 0;
	ioctl(m_SocketID, FIONREAD, &argp);
	return argp;
}

unsigned int CloudSocket::getLinger ()const 
{ 
	struct linger ling;
	unsigned int len = sizeof(ling);

	if(getsockopt( m_SocketID , SOL_SOCKET , SO_LINGER , (char*)&ling , (socklen_t *)&len ) == SOCKET_ERROR)
	{
		return SOCKET_ERROR;
	}

	return ling.l_linger;
}


SOCKET CloudSocket::Accept( struct sockaddr* addr, unsigned int* addrlen )
{
	SOCKET client = accept( m_SocketID , addr , (socklen_t*)addrlen );

	return client;
}

bool CloudSocket::setNonBlocking (bool on ) 
{ 
	unsigned long argp = ( on == true ) ? 1 : 0;

	//int nRet = ioctlsocket( m_SocketID, FIONBIO, &argp);
	ioctl(m_SocketID, FIONBIO, &argp);
	int flags = fcntl(m_SocketID, F_GETFL, 0);
	if (flags == SOCKET_ERROR)
		return false;
		
	int nRet = fcntl(m_SocketID, F_SETFL, O_NDELAY);

	if (nRet == SOCKET_ERROR)
		return false;

	return true;
}



unsigned int CloudSocket::getReceiveBufferSize ()const 
{ 
	unsigned int ReceiveBufferSize;
	unsigned int size = sizeof(ReceiveBufferSize);

	getsockopt( m_SocketID , SOL_SOCKET , SO_RCVBUF , (char*)&ReceiveBufferSize, (socklen_t*)&size );

	return ReceiveBufferSize;

	return 0 ;
}


unsigned int CloudSocket::getSendBufferSize ()const 
{ 
	unsigned int SendBufferSize;
	unsigned int size = sizeof(SendBufferSize);

	getsockopt( m_SocketID , SOL_SOCKET , SO_SNDBUF , (char*)&SendBufferSize, (socklen_t*)&size );

	return SendBufferSize;

	return 0 ;
}


bool CloudSocket::isSockError()const
{
	int error;
	unsigned int len = sizeof(error);

	int Result = getsockopt( m_SocketID , SOL_SOCKET , SO_ERROR , (char*)&error, (socklen_t*)&len );

	if( Result == SOCKET_ERROR ) 
		return true;
	else 			  
		return false;

	return false ;
}


bool CloudSocket::isReuseAddr ()const
{
	int reuse;
	unsigned int len = sizeof(reuse);

	getsockopt( m_SocketID , SOL_SOCKET , SO_REUSEADDR , (char*)&reuse , (socklen_t*)&len );

	return reuse == 1;

	return 0 ;
}

#endif

// close previous connection and connect to another server socket
bool CloudSocket::reconnect ( const char* host , unsigned int port )
{
	// delete old socket impl object
	Close();

	// create new socket impl object
	strncpy( m_Host, host, IP_SIZE-1 ) ;
	m_Port = port ;

	create() ;

	// try to connect
	return Connect();	

	return false ;
}


	
bool CloudSocket::Connect () 
{ 
	m_SockAddr.sin_addr.s_addr = inet_addr( m_Host );
	
	// set sockaddr's port
	m_SockAddr.sin_port = htons(m_Port);
	
	// try to connect to peer host
	bool result = connect(m_SocketID, (const struct sockaddr *)&m_SockAddr, sizeof(m_SockAddr));
	if( !result)
		return true ;
	else
		return false ;

	return 0 ;
}

bool CloudSocket::Connect (const char* host, unsigned int port) 
{ 
	strncpy( m_Host, host, IP_SIZE-1 ) ;
	m_Port = port ;

	return Connect() ;

	return 0 ;
}

unsigned int CloudSocket::Send (const void* buf, unsigned int len, unsigned int flags) 
{ 
	return send(m_SocketID,(const char *)buf, len, flags);

	return 0 ;
}

unsigned int CloudSocket::receive (void* buf, unsigned int len, unsigned int flags) 
{ 
	return recv(m_SocketID, (char*)buf, len, flags);

	return 0 ;
}




bool CloudSocket::setLinger (unsigned int lingertime) 
{
	struct linger ling;
	
	ling.l_onoff = lingertime > 0 ? 1 : 0;
	ling.l_linger = lingertime;
	
	int nRet = setsockopt( m_SocketID , SOL_SOCKET , SO_LINGER , (char*)&ling , sizeof(ling) );

	if (nRet == SOCKET_ERROR)
	{
		return false;
	}

	return true ;
}

unsigned int CloudSocket::getSockError()const 
{ 
	return isSockError(); 

	return 0 ;
}

bool CloudSocket::isNonBlocking ()const 
{ 
	//return SocketAPI::getsocketnonblocking_ex( m_SocketID );

	return false ;
}


bool CloudSocket::setReceiveBufferSize (unsigned int size)
{ 
	int nRet = setsockopt( m_SocketID , SOL_SOCKET , SO_RCVBUF , (char*)&size, sizeof(unsigned int) );

	if (nRet == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}


bool CloudSocket::setSendBufferSize (unsigned int size)
{ 
	int nRet = setsockopt( m_SocketID , SOL_SOCKET , SO_SNDBUF , (char*)&size, sizeof(unsigned int) );
	if (nRet == SOCKET_ERROR)
	{
		return false ;
	}

	return true;
}

unsigned int CloudSocket::getPort ()const 
{ 
	return m_Port; 
}

unsigned long CloudSocket::getHostIP ()const 
{ 
	return (unsigned long)(m_SockAddr.sin_addr.s_addr);
}

bool CloudSocket::isValid ()const 
{
	return m_SocketID != INVALID_SOCKET; 
}

SOCKET CloudSocket::getSOCKET ()const 
{
	return m_SocketID; 
}


bool CloudSocket::Bind( )
{
	m_SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_SockAddr.sin_port        = htons(m_Port);

	if (bind( m_SocketID , (const struct sockaddr *)&m_SockAddr , sizeof(m_SockAddr) )  == SOCKET_ERROR)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CloudSocket::Bind( unsigned int port )
{
	m_Port = port ;

	m_SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_SockAddr.sin_port        = htons(m_Port);

	if (bind( m_SocketID , (const struct sockaddr *)&m_SockAddr , sizeof(m_SockAddr) ) == SOCKET_ERROR)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CloudSocket::Listen( int backlog )
{
	if (listen( m_SocketID , backlog ) == SOCKET_ERROR)
	{
		return false;
	}
	else
	{
		return true;
	} 
}


bool CloudSocket::setReuseAddr ( bool on )
{
	int opt = (on == true ? 1 : 0);
	
	if (setsockopt( m_SocketID , SOL_SOCKET , SO_REUSEADDR , (char*)&opt , sizeof(opt) ) == SOCKET_ERROR)
	{
		return false;
	}
	
	return true ;
}

