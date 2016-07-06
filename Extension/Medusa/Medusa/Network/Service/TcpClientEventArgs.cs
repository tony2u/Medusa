using System;
using System.Globalization;
using System.Net;
using System.Net.Sockets;

namespace Medusa.Network.Service
{
    public class TcpClientEventArgs : EventArgs
    {
        public TcpClientEventArgs(TcpClient client)
        {
            Client = client;
        }

        public TcpClient Client { get; private set; }
    }
}