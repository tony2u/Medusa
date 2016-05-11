class StringNameItem[Embeded,SuppressCompare,SuppressCopy,Dir=Core/String/StringTable]
{
    Dictionary<uint, string> Items;
};

class StringTable[Embeded,SuppressCompare,SuppressCopy,Dir=Core/String/StringTable]
{
    Dictionary<string, StringNameItem> Items;
};
