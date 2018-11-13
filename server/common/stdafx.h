/*
	  ___           ___           ___           ___           ___                       ___           ___
	 /  /\         /__/\         /  /\         /__/\         /__/|        ___          /  /\         /  /\        ___
	/  /::|        \  \:\       /  /::\        \  \:\       |  |:|       /  /\        /  /:/        /  /::\      /  /\
   /  /:/:|         \__\:\     /  /:/\:\        \  \:\      |  |:|      /  /:/       /  /:/        /  /:/\:\    /  /:/
  /  /:/|:|__   ___ /  /::\   /  /:/  \:\   ___  \  \:\   __|__|:|     /__/::\      /  /:/  ___   /  /:/~/::\  /__/::\
 /__/:/ |:| /\ /__/\  /:/\:\ /__/:/ \__\:\ /__/\  \__\:\ /__/::::\____ \__\/\:\__  /__/:/  /  /\ /__/:/ /:/\:\ \__\/\:\__
 \__\/  |:|/:/ \  \:\/:/__\/ \  \:\ /  /:/ \  \:\ /  /:/    ~\~~\::::/    \  \:\/\ \  \:\ /  /:/ \  \:\/:/__\/    \  \:\/\
	 |  |:/:/   \  \::/       \  \:\  /:/   \  \:\  /:/      |~~|:|~~      \__\::/  \  \:\  /:/   \  \::/          \__\::/
	 |  |::/     \  \:\        \  \:\/:/     \  \:\/:/       |  |:|        /__/:/    \  \:\/:/     \  \:\          /__/:/
	 |  |:/       \  \:\        \  \::/       \  \::/        |  |:|        \__\/      \  \::/       \  \:\         \__\/
	 |__|/         \__\/         \__\/         \__\/         |__|/                     \__\/         \__\/
*/
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif					

#if 0
#define __LINUX__
#else
#define __WINDOWS__
#endif
#include <iostream>

#ifdef __WINDOWS__
#include <WinSock.h>
#include <stdio.h>
#include <tchar.h>
#include <yvals.h>
#include <assert.h>
#include "include/mysql.h"
#include "include/mysqld_error.h"
#include "include/errmsg.h"
#endif

#ifdef __LINUX__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include "include/mysql.h"
#include "include/mysqld_error.h"
#include "include/errmsg.h"

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;

#define INVALID_SOCKET              -1                        /*无效socket句柄*/
#define SOCKET_ERROR                -1                        /*socket api的返回值*/
#define S_OK 0
#endif

//#pragma warning(disable:4996 34) // 不显示4996和34号警告信息
//#pragma warning(once:4996) // 4385号警告信息仅报告一次
//#pragma warning(error:164) // 把164号警告信息作为一个错误。

// TODO: reference additional headers your program requires here
