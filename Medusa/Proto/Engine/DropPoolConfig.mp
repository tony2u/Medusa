
class DropPoolItem[Embeded,SuppressCompare,Dir=Game/Drop]
{
     uint Id;    //often be item Id,and could be inner drop id too
     int Type=0[Optional];  //type ==-1 means another drop id,then Count means times to execuate dropping
     int Count=1[Optional];
};

class DropPoolRandomItem : DropPoolItem[Embeded,Dir=Game/Drop]
{
     uint Probability=1[Optional];
};


class DropPoolGroup[Dir=Game/Drop]
{
     bool PreventDuplicate[Optional];
     uint MinTimes=1[Optional];
     uint MaxTimes=1[Optional];
     List<DropPoolRandomItem> Items;
};

class DropPoolConditionItem[Dir=Game/Drop]
{
     uint PredicateId;   //serach predicate in another table, then invoke it with void* passed in param
     DropPoolItem Item;
};

class DropPoolItemLimit[Embeded,SuppressCompare,Dir=Game/Drop]
{
     uint ItemId;
     int Type=0[Optional];
     int MinCount; //auto add when not enough
     int MaxCount; //exceed will be ignored, when 0, means no drop
};


class DropPool[Embeded,Dir=Game/Drop]
{
     List<DropPoolItem> FixedItems[Optional];
     List<DropPoolGroup> RandomGroups[Optional];
     List<DropPoolConditionItem> ConditionItems[Optional];
    //global limit
     List<DropPoolItemLimit> ItemLimits[Optional];
};

class DropPoolConfig[SirenConfig,Embeded,SuppressCompare,SuppressCopy,Dir=Game/Drop]
{
     Dictionary<uint, DropPool> Items[AddDictionaryMethods];
};
