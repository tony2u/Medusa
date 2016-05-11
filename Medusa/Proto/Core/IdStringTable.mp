
class StringId[Embeded,Dir=Core/String/StringTable]
{
    int Id;
    int Check1;
    int Check2;
};

class IdStringTable[Dir=Core/String/StringTable]
{
    Dictionary<StringId, string> Items;
};
