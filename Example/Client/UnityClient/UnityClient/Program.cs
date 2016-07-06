using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Medusa.Log;
using Medusa.Network.Message;
using Medusa.Network.Service;
using Medusa.Siren;
using UnityClient.Message;
using UnityClient.Proto;

namespace UnityClient
{
    class Program
    {
        static void Main(string[] args)
        {

            MessageFactory.Register<LoginMessage>();

            Logger.OnInfo += Console.Write;
            Logger.OnError += Console.Write;

            var remoteIp = IPAddress.Parse("127.0.0.1");

            TcpClientMessageService service = new TcpClientMessageService(remoteIp, 9013);

            service.OnConnected += (o, eventArgs) =>
            {
                TcpClientMessageService service2 = o as TcpClientMessageService;
                Logger.InfoLine("Connectd:{0}", service2.RemoteIPEndPoint);

                LoginMessage lognMessage = new LoginMessage
                {
                    Request =
                    {
                        Name = "Hello",
                        Order = 123
                    }
                };

                service2.Write(lognMessage);
            };

            service.OnDisconnected += (o, eventArgs) =>
            {
                TcpClientMessageService service2 = o as TcpClientMessageService;
                Logger.InfoLine("Disconnected:{0}", service2.RemoteIPEndPoint);
            };
            service.OnRead += ServiceOnRead;
            service.OnError += Service_OnError;

            service.BeginConnect();


            Console.Read();
        }


        private static void Service_OnError(object sender, TcpClientExceptionEventArgs e)
        {
            TcpClientMessageService service2 = sender as TcpClientMessageService;
            Logger.Info("Error:{}", e.Exception);
        }

        private static void ServiceOnRead(object sender, TcpClientDataEventArgs<Medusa.Network.NetworkBuffer> e)
        {

        }
    }
}
