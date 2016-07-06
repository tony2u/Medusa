using System;
using Medusa.Siren;

namespace Medusa.Network.Message
{
    public abstract class BaseRequestMessage<TRequest> : BaseMessage
            where TRequest : class, new()
    {
        protected BaseRequestMessage(TRequest request)
            :base(typeof(TRequest))
        {
            Request = request;
        }
        protected BaseRequestMessage()
            : base(typeof(TRequest))
        {
            Request = new TRequest();
            IncreaseSessionId();
        }

        public void IncreaseSessionId()
        {
            SessionId = ++MessageFactory.SessionId;
        }

        public TRequest Request { get; set; }
        public override ArraySegment<byte>? SerializeRequest()
        {
            return Serializer.Serialize(Request);
        }

        public override void DeserializeRequest(ArraySegment<byte> val)
        {
            Request = Deserializer.Deserialize<TRequest>(val);
        }

    }
}