enum ServiceType[Dir=Core/Network/Message/Service]
{
   Mock = 0,
   TcpClient = 1,
   TcpServer=2,
};

class ServiceInfo[Dir=Core/Network/Message/Service]
{
    uint Id;
    string Host;
    ushort Port;
    ServiceType Type;
    string Options;
};
