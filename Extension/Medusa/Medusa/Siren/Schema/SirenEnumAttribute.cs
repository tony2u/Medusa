using System;
using System.IO;
using Medusa.Common;

namespace Medusa.Siren.Schema
{

    public enum SirenEnumGenerateMode
    {
        None = 0,
        Generate = 1,
        Suppress = 2,

        CustomEnum = 8,
        CustomFlag = 16,
    }


    [AttributeUsage(AttributeTargets.Enum)]
    public class SirenEnumAttribute : BaseSirenAttribute
    {
        public SirenEnumGenerateMode Mode { get; protected set; }
        public string Dir { get; protected set; }

        public SirenEnumAttribute() 
        {
        }

        public SirenEnumAttribute(StringPropertySet val) : base(val)
        {
        }
        public SirenEnumAttribute(SirenEnumGenerateMode mode, string dir)
        {
            Mode = mode;
            Dir = dir;
        }

        public override object Clone()
        {
            return new SirenEnumAttribute(Mode, Dir);
        }

        public override bool LoadFrom(Stream stream)
        {
            Mode = (SirenEnumGenerateMode)stream.ReadUInt();
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
