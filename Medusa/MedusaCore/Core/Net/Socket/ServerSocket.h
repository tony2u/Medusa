// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Net/Socket/ISocket.h"
#include "Core/Net/Socket/ClientSocket.h"



MEDUSA_BEGIN;

namespace Socket
{
	class ServerSocket:public ISocket
	{
	public:
		ServerSocket(ushort port, SocketType::SocketType_t socketType=SocketType::TCP)
			:ISocket(socketType)
		{
			//set INADDR_ANY to receive any client
			mAddress.SetAddress(INADDR_ANY);
			mAddress.SetPortID(htons(port));
		}
		virtual ~ServerSocket(void){}

		
		ClientSocket* Accept()
		{
			sockaddr socketAddress;
			int len=sizeof(sockaddr);
			SOCKET clientSocketDescriptor=accept(mSocketDescriptor,&socketAddress,(socklen_t*)&len);

			if (clientSocketDescriptor<=0)	
			{

				//int errorCode= GetError();
				return nullptr;
			}

			return new ClientSocket(clientSocketDescriptor,socketAddress);
		}

		bool Bind()
		{
			int result=::bind(mSocketDescriptor,mAddress.GenearlAddressPtr(),sizeof(sockaddr));
			return result>=0;
		}

		bool Listen(unsigned int inQueueLength=5)
		{
			if (inQueueLength!=0)
			{
				int result=listen(mSocketDescriptor,inQueueLength);
				return result==0;
			}
			return false;
		}
	private:
		void operator=(const ServerSocket&);
		ServerSocket(const ServerSocket&);
	};

}
MEDUSA_END;
