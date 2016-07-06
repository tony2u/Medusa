using System;
using Medusa.Network.Service;

namespace Medusa.Network.Message
{
    public interface IMessage
    {
        uint FromService { get; set; }
        uint ToService { get; set; }
        uint Version { get; set; }
        uint Id { get; set; }
        uint SessionId { get; set; }
        uint ConnectionId { get; set; }

        bool IsRequest { get; }
        void OnSend(TcpClientMessageService service);

        void OnRequest(TcpClientMessageService service);
        void OnResponse(TcpClientMessageService service);

        ArraySegment<byte>? SerializeRequest();
        ArraySegment<byte>? SerializeResponse();


        void DeserializeRequest(ArraySegment<byte> val);
        void DeserializeResponse(ArraySegment<byte> val);

        event EventHandler<MessageEventArgs> OnRequestEvent;
        event EventHandler<MessageEventArgs> OnResponseEvent;
        event EventHandler<MessageEventArgs> OnSendEvent;

    }
}