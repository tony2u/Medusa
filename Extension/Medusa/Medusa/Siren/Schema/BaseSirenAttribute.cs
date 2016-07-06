using System;
using System.IO;
using Medusa.Common;

namespace Medusa.Siren.Schema
{
    public abstract class BaseSirenAttribute : System.Attribute, ICloneable
    {
        public StringPropertySet KeyValues { get; protected set; }

        protected BaseSirenAttribute()
        {
            KeyValues = new StringPropertySet();
        }

        protected BaseSirenAttribute(string val)
        {
            KeyValues = new StringPropertySet();
            KeyValues.Parse(val);
        }

        protected BaseSirenAttribute(StringPropertySet val)
        {
            KeyValues = new StringPropertySet();
            foreach (var keyValue in val)
            {
                KeyValues.Add(keyValue.Key, keyValue.Value);
            }

        }

        public bool Load(string val)
        {
            KeyValues.Parse(val);
            return OnLoaded();
        }

        public void AddAttribute(string name, string val)
        {
            KeyValues.Set(name, val);
        }

        public abstract object Clone();
        protected virtual bool OnLoaded() { return true; }

        public virtual bool LoadFrom(Stream stream)
        {
            uint count = stream.ReadUInt();
            for (int i = 0; i < count; i++)
            {
                var key = stream.ReadString();
                var val = stream.ReadString();
                KeyValues.Add(key, val);
            }
            return true;
        }

        public virtual bool SaveTo(Stream stream)
        {
            stream.Write((uint)KeyValues.Count);
            foreach (var keyValue in KeyValues)
            {
                stream.WriteString(keyValue.Key);
                stream.WriteString(keyValue.Value);
            }

            return true;
        }
    }
}
