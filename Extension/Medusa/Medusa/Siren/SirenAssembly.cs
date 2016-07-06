using System.Collections.Generic;
using Medusa.Siren.Schema;

namespace Medusa.Siren
{
    public class SirenAssembly
    {
        public string Name { get; set; }
        public List<SirenAssembly> ReferenceAssemblies { get; protected set; }
        public Dictionary<string,BaseSirenCustomType> Types { get; protected set; }

        public BaseSirenCustomType FindCustomType(string name)
        {
            BaseSirenCustomType type;
            Types.TryGetValue(name, out type);
            return type;
        }

    }
}
