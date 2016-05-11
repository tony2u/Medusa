class RandomNameConfigItem[Dir=Core/String/RandomName]
{
    uint Position;
    string Value;
};

class RandomNameConfig[Embeded,SuppressCompare,SuppressCopy,Dir=Core/String/RandomName]
{
    List<RandomNameConfigItem> Items;
};
