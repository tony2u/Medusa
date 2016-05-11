enum ServerStatus[Dir=Core/Network/Message/Service]
{
    OK = 0,
    Maintain = 1,
    Error = 2
};

class ServerConfigItem[Dir=Core/Network/Message/Service]
{
     uint Id;
     string Name;
     string Description;
     ServerStatus Status;
     Dictionary<uint, ServiceInfo> Services;
};

class ServerConfig[SuppressCompare,SuppressCopy,Dir=Core/Network/Message/Service]
{
     Dictionary<uint, ServerConfigItem> Items;
};
