using System;
using System.Net.Sockets;
using Medusa.Network.Service;

namespace Medusa.Network.Message
{
    public class MessageEventArgs : EventArgs
    {
        public MessageEventArgs(IMessage message, TcpClientMessageService service)
        {
            Message = message;
            Service = service;
        }

        public IMessage Message { get; private set; }
        public TcpClientMessageService Service { get; private set; }
    }
}