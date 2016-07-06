using System;
using System.Collections.Generic;
using System.IO;
using Medusa.Common;

namespace Medusa.Siren.Schema
{
    public class SirenCustomEnum : BaseSirenCustomType
    {
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => true;
        public override SirenTypeId Id => SirenTypeId.Enum;
        public SirenEnumAttribute Attribute { get; set; }
        public List<string> FieldNames { get; set; }
        public List<int> FieldValues { get; set; }
        public string UnderlyType { get; set; }

        public SirenCustomEnum(string name = "") : base(name)
        {
            Attribute = new SirenEnumAttribute();
            FieldNames = new List<string>();
            FieldValues = new List<int>();
        }
        public SirenCustomEnum(Type type, SirenEnumAttribute attribute)
        {
            Type = type;
            Attribute = attribute;
        }

        public override object Clone()
        {
            SirenCustomEnum val = new SirenCustomEnum(Name) { Attribute = Attribute.Clone() as SirenEnumAttribute };
            val.FieldNames.AddRange(FieldNames);
            val.FieldValues.AddRange(FieldValues);
            val.UnderlyType = UnderlyType;
            return val;
        }

        public override void AddAttribute(string name, string val)
        {
            Attribute.AddAttribute(name, val);
        }

        public override void SetAttribute(string val)
        {
            Attribute.Load(val);
        }

        public override bool LoadFrom(Stream stream)
        {
            base.LoadFrom(stream);
            Attribute.LoadFrom(stream);
            UnderlyType = stream.ReadString();
            uint count = stream.ReadUInt();
            for (int i = 0; i < count; i++)
            {
                FieldNames.Add(stream.ReadString());
                FieldValues.Add(stream.ReadInt());
            }
            return true;
        }

        public override bool SaveTo(Stream stream)
        {
            base.SaveTo(stream);
            Attribute.SaveTo(stream);
            stream.WriteString(UnderlyType);
            uint count = (uint)FieldNames.Count;
            stream.Write(count);

            for (int i = 0; i < count; i++)
            {
                stream.WriteString(FieldNames[i]);
                stream.Write(FieldValues[i]);
            }

            stream.WriteString(Name);
            return true;
        }

        public bool Initialize()
        {
            return true;
        }
    }
}
