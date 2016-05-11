enum AppInitializeOperation[Dir=Application/Compat]
{
   None = 0,
   RemoveAllCache = 1
};

class AppCompatibility[Dir=Application/Compat]
{
    uint Version;
    AppInitializeOperation Operation;
};
