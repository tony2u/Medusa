
  enum EntryOperation:byte[CustomFlag,Dir=Core/IO/Storage]
  {
      None = 0,
      Add = 1,
      Delete = 2,
      Update = 4,
  };

  enum FilePermission[CustomFlag,Dir=Core/IO/Storage]
  {
      None = 0,
      Read = 0x100,  //S_IREAD
      Write = 0x080, //S_IWRITE
      All = Read|Write,
  };


  class DirectoryEntry[Embeded,SuppressCompare,SuppressCopy,Dir=Core/IO/Storage]
  {
       string Name[Optional];
       EntryOperation Operations=0[Optional];   //deleted or not,operation
       List<DirectoryEntry> Dirs[Optional,ForceValueToPtr];   //path id
       List<FileEntry> Files[Optional,ForceValueToPtr];  //name id
  };

  class FileEntry[Embeded,SuppressCompare,SuppressCopy,Dir=Core/IO/Storage]
  {
       string Name[Optional];
       FilePermission Permission=FilePermission::All[Optional];   //0 to not use any coder,max to use default coders
       uint FirstBlockId=0xFFFFFFFF[Optional];
       uint OriginalSize=0[Optional];   //size before coding
       uint Size=0[Optional];

       string Signature[Optional];   //for hash check
       EntryOperation Operations=0[Optional];   //deleted or not,operation
       List<uint> CoderOffsets[Optional];  //coders only apply to current file
  };

   class FileStorage[Embeded,SuppressCompare,SuppressCopy,Dir=Core/IO/Storage]
  {
       DirectoryEntry RootDir;
       Dictionary<string,uint64> CodeRules[Optional];    //file extention-coder list
  };
