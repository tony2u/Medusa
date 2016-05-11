return
{
    Version = 1,	--  main=1?free=2
    Language = 1,   --  enus=1,zhcn=2
    Device = 2,   --  sd=1,hd=2
	DebugInfo=1,	--Performance=1,GPU=2,Touch=4
	
    IsMockEnabled = false, 
    IsCheatEnabled = false,    
    IsDebugEnabled = true,    
	IsFileUpdateEnabled=false,
	IsEncryptEnabled=false,	
	IsCompressedEnabled=false,	

	MessageVersion=1,	
	LoginServerId=1,		
	
	UpdateServerUrl = "http://static.hhyx.wyximg.com:9999/version1/",  
	UpdateServerConfigName = "Server.bin",   
	
    MessageTimeout = 100000.0,    
    AutoSaveDuration = 5.0,   
	
	MessageRetryTimes=5,	
	MessageRetryInterval=1000,	
	
    HTTPConnectTimeoutSeconds = 5,  
    HTTPReadTimeoutSeconds = 5,   
    HTTPReadLowSpeedLimit = 10,   
    HTTPReadLowSpeedTime = 10,    

    ToastShowTime = 0.5,  

};

