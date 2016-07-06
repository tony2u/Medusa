using System;
using System.IO;
using Medusa.Common;

namespace Medusa.Siren.Schema
{
    public enum SirenClassGenerateMode
    {
        None = 0,
        Generate = 1,
        Suppress = 2,
        Embeded = 4 | Generate,

        SuppressCompare = 8,
        SuppressCopy = 16,

        SirenConfig = 32 | SuppressCompare | SuppressCopy,

    }

    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct)]
    public class SirenClassAttribute : BaseSirenAttribute
    {
        public SirenClassGenerateMode Mode { get; protected set; }
        public string Dir { get; protected set; }

        public SirenClassAttribute()
        {
        }

        public SirenClassAttribute(string val):base(val)
        {
        }

        public SirenClassAttribute(StringPropertySet val) : base(val)
        {
        }
        public SirenClassAttribute(SirenClassGenerateMode mode, string dir)
        {
            Mode = mode;
            Dir = dir;
        }


        public override object Clone()
        {
            return new SirenClassAttribute(Mode,Dir);
        }

        public override bool LoadFrom(Stream stream)
        {
            Mode = (SirenClassGenerateMode)stream.ReadUInt();
            Dir = stream.ReadString();
            return true;
        }

        public override bool SaveTo(Stream stream)
        {
            stream.Write((uint)Mode);
            stream.WriteString(Dir);
            return true;
        }
    }
}
