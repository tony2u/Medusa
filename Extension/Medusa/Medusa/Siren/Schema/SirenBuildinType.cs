using System;
using System.IO;

namespace Medusa.Siren.Schema
{
    public abstract class SirenBuildinType : SirenType
    {
        protected SirenBuildinType(Type type) : base(type)
        {
        }

        protected SirenBuildinType(string name)
            : base(name)
        {

        }

        public override bool IsBuildIn => true;
        public override bool LoadFrom(Stream stream) { return true; }
        public override bool SaveTo(Stream stream) { return true; }
    }

    public class SirenBuildinBool : SirenBuildinType
    {
        public SirenBuildinBool(string name) : base(name)
        {
            Type = typeof (bool);
        }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.Bool;
        public override object Clone() { return this; }
    }

    public class SirenBuildinInt8 : SirenBuildinType
    {
        public SirenBuildinInt8(string name) : base(name) { Type = typeof(char); }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.Int8;
        public override object Clone() { return this; }
    }

    public class SirenBuildinUInt8 : SirenBuildinType
    {
        public SirenBuildinUInt8(string name) : base(name) { Type = typeof(byte); }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.UInt8;
        public override object Clone() { return this; }
    }

    public class SirenBuildinInt16 : SirenBuildinType
    {
        public SirenBuildinInt16(string name) : base(name) { Type = typeof(Int16); }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.Int16;
        public override object Clone() { return this; }
    }

    public class SirenBuildinUInt16 : SirenBuildinType
    {
        public SirenBuildinUInt16(string name) : base(name) { Type = typeof(UInt16); }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.UInt16;
        public override object Clone() { return this; }
    }

    public class SirenBuildinInt32 : SirenBuildinType
    {
        public SirenBuildinInt32(string name) : base(name) { Type = typeof(Int32); }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.Int32;
        public override object Clone() { return this; }
    }

    public class SirenBuildinUInt32 : SirenBuildinType
    {
        public SirenBuildinUInt32(string name) : base(name) { Type = typeof(UInt32); }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.UInt32;
        public override object Clone() { return this; }
    }
    public class SirenBuildinInt64 : SirenBuildinType
    {
        public SirenBuildinInt64(string name) : base(name) { Type = typeof(Int64); }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.Int64;
        public override object Clone() { return this; }
    }
    public class SirenBuildinUInt64 : SirenBuildinType
    {
        public SirenBuildinUInt64(string name) : base(name) { Type = typeof(UInt64); }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.UInt64;
        public override object Clone() { return this; }
    }
    public class SirenBuildinFloat : SirenBuildinType
    {
        public SirenBuildinFloat(string name) : base(name) { Type = typeof(float); }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.Float;
        public override object Clone() { return this; }
    }
    public class SirenBuildinDouble : SirenBuildinType
    {
        public SirenBuildinDouble(string name) : base(name) { Type = typeof(double); }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.Double;
        public override object Clone() { return this; }
    }
    public class SirenBuildinString : SirenBuildinType
    {
        public SirenBuildinString(string name) : base(name) { Type = typeof(string); }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.String;
        public override object Clone() { return this; }
    }
    public class SirenBuildinBlob : SirenBuildinType
    {
        public SirenBuildinBlob(string name) : base(name) { Type = typeof(byte[]); }
        public override bool IsTemplate => false;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.Blob;
        public override object Clone() { return this; }
    }

    public class SirenBuildinList : SirenBuildinType
    {
        public SirenBuildinList(string name) : base(name) { }

        public SirenBuildinList(Type type) : base(type)
        {
        }

        public override bool IsTemplate => true;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.List;
        public override object Clone() { return this; }
    }

    public class SirenBuildinDictionary : SirenBuildinType
    {
        public SirenBuildinDictionary(string name) : base(name) { }

        public SirenBuildinDictionary(Type type) : base(type)
        {
        }

        public override bool IsTemplate => true;
        public override bool IsCustomClass => false;
        public override bool IsCustomEnum => false;
        public override SirenTypeId Id => SirenTypeId.Dictionary;
        public override object Clone() { return this; }
    }
}
