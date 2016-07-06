using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using Medusa.Common;

namespace Medusa.Siren.Schema
{
    public class SirenCustomClass : BaseSirenCustomType
    {
        public override bool IsCustomClass => true;
        public override bool IsCustomEnum => false;

        public override SirenTypeId Id => SirenTypeId.Struct;
        public SirenClassAttribute Attribute { get; set; }
        public List<SirenField> Fields { get; private set; }
        public Dictionary<string, SirenField> FieldNameDict { get; private set; }
        public Dictionary<ushort, SirenField> FieldIdDict { get; private set; }

        public Dictionary<string, BaseSirenCustomType> Types { get; set; }

        public string BaseTypeName { get; set; }
        public SirenCustomClass BaseType { get; set; }

        public MethodInfo SerializeMethodInfo { get; private set; }
        public MethodInfo DeserializeMethodInfo { get; private set; }
        public MethodInfo RegisterMethodInfo { get; private set; }

        public SirenCustomClass(Type type, SirenClassAttribute attribute)
        {
            Type = type;
            Attribute = attribute;
            Fields = new List<SirenField>();
            FieldNameDict = new Dictionary<string, SirenField>();
            FieldIdDict = new Dictionary<ushort, SirenField>();
        }

        public SirenCustomClass(string name = "") : base(name)
        {
            Fields = new List<SirenField>();
            FieldNameDict = new Dictionary<string, SirenField>();
            FieldIdDict = new Dictionary<ushort, SirenField>();
        }


        public override object Clone()
        {
            SirenCustomClass val = new SirenCustomClass(Name) { Attribute = Attribute.Clone() as SirenClassAttribute };
            val.BaseTypeName = BaseTypeName;
            val.BaseType = BaseType.Clone() as SirenCustomClass;
            foreach (var baseSirenCustomType in Types)
            {
                val.Types.Add(baseSirenCustomType.Key, baseSirenCustomType.Value.Clone() as BaseSirenCustomType);
            }

            foreach (var sirenField in FieldNameDict)
            {
                val.FieldNameDict.Add(sirenField.Key, sirenField.Value.Clone() as SirenField);
            }
          

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
            BaseTypeName = stream.ReadString();

            //types
            uint typeCount = stream.ReadUInt();
            for (int i = 0; i < typeCount; i++)
            {
                byte isClass = (byte)stream.ReadByte();
                if (isClass == 1)
                {
                    SirenCustomClass type = new SirenCustomClass();
                    type.LoadFrom(stream);
                    type.Parent = this;
                    Types.Add(type.Name, type);
                }
                else
                {
                    SirenCustomEnum type = new SirenCustomEnum();
                    type.LoadFrom(stream);
                    type.Parent = this;
                    Types.Add(type.Name, type);
                }
            }
            //fields
            uint fieldCount = stream.ReadUInt();
            for (int i = 0; i < fieldCount; i++)
            {
                SirenField field = new SirenField();
                field.LoadFrom(stream);
                field.ParentType = this;
                FieldNameDict.Add(field.Name, field);
                field.Index = (ushort)(FieldNameDict.Count - 1);
            }

            return true;
        }

        public override bool SaveTo(Stream stream)
        {
            base.SaveTo(stream);
            Attribute.SaveTo(stream);
            stream.WriteString(BaseTypeName);

            //types
            uint typeCount = (uint)Types.Count;
            stream.Write(typeCount);
            foreach (var baseSirenCustomType in Types)
            {
                byte isClass = baseSirenCustomType.Value.IsCustomClass ? (byte)1 : (byte)0;
                stream.WriteByte(isClass);
                baseSirenCustomType.Value.SaveTo(stream);
            }

            //fields
            uint filedCount = (uint)FieldNameDict.Count;
            stream.Write(filedCount);
            foreach (var sirenField in FieldNameDict)
            {
                sirenField.Value.SaveTo(stream);
            }


            return true;
        }

        public override bool Link(SirenAssembly assembly)
        {
            return false;
        }

        public bool Initialize()
        {
            if (Type.IsEnum)
            {
                return true;
            }

            //get methods
            SerializeMethodInfo = Type.GetMethod("Serialize", BindingFlags.Public | BindingFlags.Instance);
            DeserializeMethodInfo = Type.GetMethod("Deserialize", BindingFlags.Public | BindingFlags.Instance);
            RegisterMethodInfo = Type.GetMethod("Register", BindingFlags.Public | BindingFlags.Instance | BindingFlags.Static);
            if (RegisterMethodInfo != null && !Type.ContainsGenericParameters)
            {
                RegisterMethodInfo.Invoke(null, null);
            }


            //get properties
            uint index = 0;
            ushort id = GetBasePropertyCount();
            var properties = Type.GetProperties(BindingFlags.DeclaredOnly | BindingFlags.Public | BindingFlags.Instance);
            foreach (var propertyInfo in properties)
            {
                var attrs = propertyInfo.GetCustomAttributes(typeof(SirenFieldAttribute), false);
                if (attrs.Length > 0)
                {
                    SirenFieldAttribute propertyAttribute = attrs[0] as SirenFieldAttribute;
                    if (propertyAttribute != null)
                    {
                        SirenField property = new SirenField(this, propertyInfo, propertyAttribute, index++, id++);
                        Fields.Add(property);
                        FieldIdDict.Add(property.Id, property);
                        FieldNameDict.Add(property.Name, property);
                    }
                }

            }

            if (Fields.Count == 0)
            {
                if (Type.BaseType == typeof(object) || Type.BaseType.IsValueType)
                {
                    return false;
                }
            }

            if (!Type.IsValueType&& Type.BaseType != typeof(object) && !Type.BaseType.IsValueType)
            {
                BaseType = SirenMachine.GetClass(Type.BaseType);
                if (BaseType != null)
                {
                    //add base properties
                    foreach (var sirenProperty in BaseType.FieldIdDict)
                    {
                        FieldIdDict.Add(sirenProperty.Key, sirenProperty.Value);
                    }

                    foreach (var sirenProperty in BaseType.FieldNameDict)
                    {
                        FieldNameDict.Add(sirenProperty.Key, sirenProperty.Value);
                    }
                }
            }


            return true;
        }

        public ushort GetBasePropertyCount()
        {
            if (Type.BaseType != typeof(object))
            {
                var baseClass = SirenMachine.FindClass(Type.BaseType);
                if (baseClass != null)
                {
                    return (ushort)(baseClass.GetBasePropertyCount() + (ushort)baseClass.Fields.Count);
                }
            }
            return 0;
        }

        public SirenField FindField(ushort id)
        {
            SirenField outProperty;
            FieldIdDict.TryGetValue(id, out outProperty);
            return outProperty;
        }

        public SirenField FindField(String name)
        {
            SirenField outProperty;
            FieldNameDict.TryGetValue(name, out outProperty);
            return outProperty;
        }
    }
}
