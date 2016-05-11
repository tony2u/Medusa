
  class FuckyStringNode[Embeded,SuppressCompare,SuppressCopy,Dir=Core/String/FuckyString]
  {
       int Char;
       bool IsFucky;
       Dictionary<int, FuckyStringNode> Childs[ForceValueToPtr];
  };

  class FuckyString[Embeded,SuppressCompare,SuppressCopy,Dir=Core/String/FuckyString]
  {
       Dictionary<int, FuckyStringNode> RootNodes;
  };
