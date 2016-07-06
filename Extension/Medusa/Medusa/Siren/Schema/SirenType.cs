using System;
using System.IO;
using System.Linq;
using Medusa.Common;

namespace Medusa.Siren.Schema
{
    public abstract class SirenType : ICloneable
    {
        protected string mName;
        public System.Type Type { get; set; }

        public string Name
        {
            get
            {
                if (!string.IsNullOrEmpty(mName))
                {
                    return mName;
                }

                var str = Type.Name;
                if (str.Contains('.'))
                {
                    str = str.Remove(0, str.LastIndexOf('.'));
                }
                return str;
            }
            set { mName = value; }
        }
        public string FullName { get; protected set; }

        public abstract bool IsBuildIn { get; }
        public abstract bool IsTemplate { get; }
        public abstract bool IsCustomClass { get; }
        public abstract bool IsCustomEnum { get; }

        public abstract SirenTypeId Id { get; }

        public virtual bool Link(SirenAssembly assembly)
        {
            return true;
        }

        public virtual bool LoadFrom(Stream stream)
        {
            Name=stream.ReadString();
            return true;
        }

        public virtual bool SaveTo(Stream stream)
        {
            stream.WriteString(Name);
            return true;
        }

        public abstract object Clone();

        protected SirenType(Type type)
        {
            Type = type;
            Name = type.Name;
            FullName = Name;
        }

        protected SirenType(string name)
        {
            Name = name;
            FullName = name;
        }

        public override string ToString()
        {
            return Name;
        }
    }
}
