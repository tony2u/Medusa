enum PublishVersions[CustomFlag,Suppress,Dir=Core/System]
{
    none = 0,
    main = 1,
    free = 2,
    all = main|free,
};

enum PublishDevices[CustomFlag,Suppress,Dir=Core/System]
{
    none = 0,
    sd = 1, //480*320
    hd = 2, //960*640
    hd5 = 4, //1136*640
    ipad = 8, //1024*768
    ipad3 = 16, //2048*1536.
    all = sd|hd|hd5|ipad|ipad3,
};


enum PublishLanguages[CustomFlag,Suppress,Dir=Core/System]
{
    none = 0,
    enus = 1,
    zhcn = 2,
    all = enus|zhcn,
};


enum PublishPlatform[Dir=Core/System]
{
    Win = 1,
    IOS = 2,
    Android = 4,
    WindowsPhone = 8,
    all = Win|IOS|Android|WindowsPhone,
};

class PublishTarget[Suppress,Dir=Core/System]
{
     PublishVersions Version[Optional];
     PublishDevices Device[Optional];
     PublishLanguages Language[Optional];
};
