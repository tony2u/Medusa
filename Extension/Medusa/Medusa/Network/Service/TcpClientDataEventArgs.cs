using System;
using System.Globalization;
using System.Net;
using System.Net.Sockets;
using Medusa.Network.Message;

namespace Medusa.Network.Service
{
    public class TcpClientDataEventArgs<T> : EventArgs
    {
        public TcpClientDataEventArgs(TcpClient client, T data)
        {
            Client = client;
            Data = data;
        }

        public TcpClient Client { get; private set; }
        public T Data { get; private set; }
    }
}