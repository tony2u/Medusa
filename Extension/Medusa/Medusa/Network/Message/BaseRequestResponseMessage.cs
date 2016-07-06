using System;
using Medusa.Siren;
using Medusa.Siren.Schema;

namespace Medusa.Network.Message
{
    public abstract class BaseRequestResponseMessage<TRequest, TResponse> : BaseMessage
            where TRequest : class, new()
            where TResponse : class, new()
    {
      
        protected BaseRequestResponseMessage(TRequest request)
            : base(typeof(TRequest))
        {
            Request = request;
            IncreaseSessionId();
        }

        protected BaseRequestResponseMessage()
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
        public TResponse Response { get; set; }

        public override ArraySegment<byte>? SerializeRequest()
        {
            return Serializer.Serialize(Request);
        }

        public override ArraySegment<byte>? SerializeResponse()
        {
            return Serializer.Serialize(Response);
        }

        public override void DeserializeRequest(ArraySegment<byte> val)
        {
            Request = Deserializer.Deserialize<TRequest>(val);
        }

        public override void DeserializeResponse(ArraySegment<byte> val)
        {
            Response = Deserializer.Deserialize<TResponse>(val);
        }
    }
}