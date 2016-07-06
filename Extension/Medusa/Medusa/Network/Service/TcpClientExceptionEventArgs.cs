using System;
using System.Globalization;
using System.Net;
using System.Net.Sockets;

namespace Medusa.Network.Service
{
    public class TcpClientExceptionEventArgs : EventArgs
    {
        public TcpClientExceptionEventArgs(TcpClient client, Exception innerException)
        {
            Client = client;
            Exception = innerException;
        }

        public TcpClient Client { get; private set; }
        public Exception Exception { get; private set; }
    }
}