using System;
using Medusa.Network.Service;
using Medusa.Siren.Schema;

namespace Medusa.Network.Message
{
    public abstract class BaseMessage : IMessage
    {
        protected BaseMessage(Type requestType)
        {
            var attr2 = requestType.GetCustomAttributes(typeof(SirenClassAttribute), false);
            if (attr2.Length > 0)
            {
                var idAttr = attr2[0] as SirenClassAttribute;
                var idStr = idAttr.KeyValues["Id"];
                Id = Convert.ToUInt32(idStr);
            }

        }
        protected BaseMessage()
        {
            Id = 0;

        }

        public uint FromService { get; set; }
        public uint ToService { get; set; }
        public uint Version { get; set; }
        public uint Id { get; set; }
        public uint SessionId { get; set; }
        public uint ConnectionId { get; set; }

        public bool IsRequest => Id != 0 || (Id == 0 && SessionId == 0);

        public virtual void OnSend(TcpClientMessageService service)
        {
            OnSendEvent?.Invoke(this, new MessageEventArgs(this, service));
        }


        public virtual void OnRequest(TcpClientMessageService service)
        {
            OnRequestEvent?.Invoke(this, new MessageEventArgs(this, service));
        }

        public virtual void OnResponse(TcpClientMessageService service)
        {
            OnResponseEvent?.Invoke(this, new MessageEventArgs(this, service));
        }

        public virtual ArraySegment<byte>? SerializeRequest()
        {
            return null;
        }
        public virtual ArraySegment<byte>? SerializeResponse()
        {
            return null;
        }

        public virtual void DeserializeRequest(ArraySegment<byte> val)
        {

        }

        public virtual void DeserializeResponse(ArraySegment<byte> val)
        {
        }

        public event EventHandler<MessageEventArgs> OnRequestEvent;
        public event EventHandler<MessageEventArgs> OnResponseEvent;
        public event EventHandler<MessageEventArgs> OnSendEvent;

    }
}