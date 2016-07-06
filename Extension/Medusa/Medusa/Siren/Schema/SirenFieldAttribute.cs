using System;
using System.IO;
using Medusa.Common;

namespace Medusa.Siren.Schema
{

    public enum SirenFieldGenerateMode
    {
        None = 0,
        Optional = 1,

        ForceKeyToPtr = 2,
        ForceValueToPtr = 4,
        AddDictionaryMethods = 8,

        SuppressMethod = 16,
    }


    [AttributeUsage(AttributeTargets.Property)]
    public class SirenFieldAttribute : BaseSirenAttribute
    {
        public SirenFieldGenerateMode Mode { get; protected set; }
        public object DefaultValue { get; set; }

        public SirenFieldAttribute()
        {
        }
        public SirenFieldAttribute(string val):base(val)
        {
        }
        public SirenFieldAttribute(StringPropertySet val) : base(val)
        {
        }
        public SirenFieldAttribute(SirenFieldGenerateMode mode)
        {
            Mode = mode;
        }

        public override object Clone()
        {
            return new SirenFieldAttribute(Mode);
        }

        public override bool LoadFrom(Stream stream)
        {
            Mode = (SirenFieldGenerateMode)stream.ReadUInt();
            return true;
        }

        public override bool SaveTo(Stream stream)
        {
            stream.Write((uint)Mode);
            return true;
        }
    }
}
