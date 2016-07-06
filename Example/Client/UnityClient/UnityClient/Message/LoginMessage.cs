using System;
using Medusa.Log;
using Medusa.Network;
using Medusa.Network.Message;
using UnityClient.Proto;

namespace UnityClient.Message
{
    [MessageId(1)]
    public class LoginMessage : BaseRequestResponseMessage<LoginRequest, LoginResponse>
    {
        public override void OnRequest()
        {
            base.OnRequest();
            Response = new LoginResponse();
            Response.Error = 23;
            Logger.InfoLine("Send:{0} {1}", Request.Name,Request.Order);
        }

        public override void OnResponse()
        {
            base.OnResponse();
            Logger.InfoLine("Receive:{0}", Response.Error);
        }

       
    }
}