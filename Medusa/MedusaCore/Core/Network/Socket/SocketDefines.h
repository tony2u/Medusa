// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_WINDOWS
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"wsock32.lib")		//add socket lib, or it'll be failed
#endif

MEDUSA_BEGIN;

enum class SocketAddressFamily :ushort
{
	IP = AF_INET,
	IP6 = AF_INET6,
	Unix = AF_UNIX
};


enum class SocketType
{
	TCP = SOCK_STREAM,
	UDP = SOCK_DGRAM
};


enum class SocketProtocolType
{
	TCP = IPPROTO_TCP,
	UDP = IPPROTO_UDP
};




#ifdef MEDUSA_WINDOWS

/*
* Windows Sockets errors redefined as regular Berkeley error constants.
* These are commented out in Windows NT to avoid conflicts with errno.h.
* Use the WSA constants instead.
*/
#if 1
#undef  EWOULDBLOCK            
#undef EINPROGRESS            
#undef EALREADY               
#undef ENOTSOCK               
#undef EDESTADDRREQ           
#undef EMSGSIZE               
#undef EPROTOTYPE             
#undef ENOPROTOOPT            
#undef EPROTONOSUPPORT        
#undef ESOCKTNOSUPPORT        
#undef EOPNOTSUPP             
#undef EPFNOSUPPORT           
#undef EAFNOSUPPORT           
#undef EADDRINUSE             
#undef EADDRNOTAVAIL          
#undef ENETDOWN               
#undef ENETUNREACH            
#undef ENETRESET              
#undef ECONNABORTED           
#undef ECONNRESET             
#undef ENOBUFS                
#undef EISCONN                
#undef ENOTCONN               
#undef ESHUTDOWN              
#undef ETOOMANYREFS           
#undef ETIMEDOUT              
#undef ECONNREFUSED           
#undef ELOOP                  
#undef ENAMETOOLONG           
#undef EHOSTDOWN              
#undef EHOSTUNREACH           
#undef ENOTEMPTY              
#undef EPROCLIM               
#undef EUSERS                 
#undef EDQUOT                 
#undef ESTALE                 
#undef EREMOTE                

//////////////////////////////////////////////////////////////////////////
#define EWOULDBLOCK             WSAEWOULDBLOCK
#define EINPROGRESS             WSAEINPROGRESS
#define EALREADY                WSAEALREADY
#define ENOTSOCK                WSAENOTSOCK
#define EDESTADDRREQ            WSAEDESTADDRREQ
#define EMSGSIZE                WSAEMSGSIZE
#define EPROTOTYPE              WSAEPROTOTYPE
#define ENOPROTOOPT             WSAENOPROTOOPT
#define EPROTONOSUPPORT         WSAEPROTONOSUPPORT
#define ESOCKTNOSUPPORT         WSAESOCKTNOSUPPORT
#define EOPNOTSUPP              WSAEOPNOTSUPP
#define EPFNOSUPPORT            WSAEPFNOSUPPORT
#define EAFNOSUPPORT            WSAEAFNOSUPPORT
#define EADDRINUSE              WSAEADDRINUSE
#define EADDRNOTAVAIL           WSAEADDRNOTAVAIL
#define ENETDOWN                WSAENETDOWN
#define ENETUNREACH             WSAENETUNREACH
#define ENETRESET               WSAENETRESET
#define ECONNABORTED            WSAECONNABORTED
#define ECONNRESET              WSAECONNRESET
#define ENOBUFS                 WSAENOBUFS
#define EISCONN                 WSAEISCONN
#define ENOTCONN                WSAENOTCONN
#define ESHUTDOWN               WSAESHUTDOWN
#define ETOOMANYREFS            WSAETOOMANYREFS
#define ETIMEDOUT               WSAETIMEDOUT
#define ECONNREFUSED            WSAECONNREFUSED
#define ELOOP                   WSAELOOP
#define ENAMETOOLONG            WSAENAMETOOLONG
#define EHOSTDOWN               WSAEHOSTDOWN
#define EHOSTUNREACH            WSAEHOSTUNREACH
#define ENOTEMPTY               WSAENOTEMPTY
#define EPROCLIM                WSAEPROCLIM
#define EUSERS                  WSAEUSERS
#define EDQUOT                  WSAEDQUOT
#define ESTALE                  WSAESTALE
#define EREMOTE                 WSAEREMOTE

#endif

#endif

MEDUSA_END;