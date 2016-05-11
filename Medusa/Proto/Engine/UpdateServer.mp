
   enum UpdateServerStatus[Dir=Game/Network]
  {
      OK = 0,
      Maintain = 1,
      Error = 2,
      DontUpgrade = 3
  };

   class UpdatePackageInfo[SirenConfig,Dir=Game/Network]
  {
       string Description;
       string Path;
       string Signature;   //used to check after download from internet
  };

   class UpdateServer[SirenConfig,Dir=Game/Network]
  {
       uint MinAppVersion;
       uint CurFileVersion;
       string Description;
       UpdateServerStatus Status;
       Dictionary<uint, UpdatePackageInfo> Patches;
       Dictionary<uint, UpdatePackageInfo> JumpPatches;
  };
