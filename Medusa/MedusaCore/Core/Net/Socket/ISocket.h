// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

#include "Core/Net/Socket/SocketDefines.h"
#include "Core/Net/Socket/AddressInfo.h"
#include "Core/Net/Socket/HostInfo.h"
#include "Core/Net/Socket/ProtocolInfo.h"
#include "Core/Net/Socket/ServiceInfo.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;

namespace Socket
{
	typedef Delegate<bool(const IStream& stream)> ReceiveCompleteChecker;

	class ISocket
	{
	public:
		ISocket(SocketType::SocketType_t socketType)
			:mSocketType(socketType)
		{
			mSocketDescriptor = (SOCKET)(~0);
		}
		static bool InitializeAPI();
		static bool UninitializeAPI();


		bool Initialize();
		bool Uninitialize();
	public:
		SOCKET SocketDescriptor() const { return mSocketDescriptor; }
		void SetSocketDescriptor(SOCKET val) { mSocketDescriptor = val; }
		bool IsValid()const{return mSocketDescriptor!=(~0);}
	public:
		SocketError::SocketError_t Send( const IStream& stream,int inControlFlag=0);
		SocketError::SocketError_t SendTo(const AddressInfo& address, const IStream& stream,int inControlFlag=0);

		SocketError::SocketError_t Receive(IStream& stream,ReceiveCompleteChecker checker,int inControlFlag=0);
		SocketError::SocketError_t ReceiveFrom(const AddressInfo& address,IStream& stream,ReceiveCompleteChecker checker,int inControlFlag=0);

		void Close();
		bool ShutDown(SocketPipeType::SocketPipeType_t inControlFlag=SocketPipeType::ReadWrite);
		static int GetError();

		static bool ParseAddress(StringRef inHostName, ushort port,SocketType::SocketType_t socketType, AddressInfo& outAddress,ProtocolInfo& outProtocolInfo);
	protected:
		const char* GetProtocolName()const;
		static SocketProtocolType::SocketProtocolType_t GetProtocolType(SocketType::SocketType_t socketType);
		bool CreateSocket();
	public:
		AddressInfo& Address() { return mAddress; }
		void SetAddress(const AddressInfo& val) { mAddress = val; }
		ServiceInfo Service() const { return mService; }
		void SetService(const ServiceInfo& val) { mService = val; }

		ProtocolInfo Protocol() const { return mProtocol; }
		void SetProtocol(const ProtocolInfo& val) { mProtocol = val; }

		void SetSendTimeout(int milliSeconds);
		void SetReceiveTimeout(int milliSeconds);

		void SetIsAsync(bool isAsync);
	protected:
		AddressInfo mAddress;				
		ServiceInfo mService;				
		ProtocolInfo mProtocol;			
		
		SocketType::SocketType_t mSocketType;
		SOCKET mSocketDescriptor;					
	};
}
MEDUSA_END;
