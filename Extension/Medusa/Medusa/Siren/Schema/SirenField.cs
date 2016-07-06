using System;
using System.IO;
using System.Reflection;
using Medusa.Common;

namespace Medusa.Siren.Schema
{
    public enum SirenPropertyFieldType
    {
        Value,
        String,
        Blob,
        List,
        Dictionary,
        Struct,
        Pointer
    }


    public class SirenField : ICloneable
    {
        public SirenFieldAttribute Attribute { get; set; }
        public string TypeName { get; set; }
        public string KeyTypeName { get; set; }
        public string ValueTypeName { get; set; }

        public string Name { get; set; }
        public string DefaultValueString { get; set; }
        public object DefaultValue { get; set; }
        public uint Index { get; set; }
        public ushort Id { get; private set; }

        public SirenType Type { get; set; }
        public SirenType KeyType { get; set; }
        public SirenType ValueType { get; set; }
        public SirenType ParentType { get; set; }


        public PropertyInfo Info { get; private set; }
        public SirenPropertyFieldType FieldType { get; private set; }
        public SirenTypeId DataType { get; private set; }

        public SirenField()
        {
            Attribute = new SirenFieldAttribute();
        }

        public SirenField(ushort id, SirenTypeId type)
        {
            Id = id;
            DataType = type;
        }

        public SirenField(SirenCustomClass parentSirenClass, PropertyInfo info, SirenFieldAttribute attribute, uint index, ushort id)
        {
            ParentType = parentSirenClass;
            Info = info;
            Name = Info.Name;
            Id = id;
            Attribute = attribute;
            Index = index;
            FieldType = SirenPropertyFieldType.Struct;
            Type = SirenMachine.GetType(info.PropertyType);
            DataType = SirenMachine.GetTypeId(Type.Type);

            if (Type.Type.IsGenericType)
            {
                if (Type.Name.StartsWith("List"))
                {
                    FieldType = SirenPropertyFieldType.List;

                    var valueType = Type.Type.GetGenericArguments()[0];
                    ValueType = SirenMachine.GetType(valueType);

                }
                else if (Type.Name.StartsWith("Dictionary"))
                {
                    FieldType = SirenPropertyFieldType.Dictionary;

                    var keyType = Type.Type.GetGenericArguments()[0];
                    var valueType = Type.Type.GetGenericArguments()[1];
                    KeyType = SirenMachine.GetType(keyType);
                    ValueType = SirenMachine.GetType(valueType);
                }
                else
                {
                    throw  new Exception("Invalid siren field");
                }

                DefaultValueString = String.Empty;
            }
            else
            {
                if (Type.Type.IsPrimitive || Type.Type == typeof(string) || Type.Type == typeof(byte[]))
                {
                    if (Type.Type == typeof(string))
                    {
                        FieldType = SirenPropertyFieldType.String;

                    }
                    else if (Type.Type == typeof(byte[]))
                    {
                        FieldType = SirenPropertyFieldType.Blob;

                    }
                    else
                    {
                        FieldType = SirenPropertyFieldType.Value;
                    }
                }
                else
                {
                    FieldType = SirenPropertyFieldType.Struct;
                    ValueType = SirenMachine.GetType(Type.Type);
                }

                DefaultValueString = String.Empty;
                if (Type.Type.IsValueType)
                {

                    if (Attribute.DefaultValue != null)
                    {
                        if (Type.Type.IsEnum)
                        {
                            DefaultValueString = String.Format("({0}){1}", Type.Name, Convert.ToUInt32(Attribute.DefaultValue));

                        }
                        else
                        {
                            DefaultValueString = Attribute.DefaultValue.ToString();
                        }
                    }
                    //else
                    //{
                    //    if (Type.Type == typeof(bool))
                    //    {
                    //        DefaultValueString = "false";
                    //    }
                    //    else if (Type.Type == typeof(float))
                    //    {
                    //        DefaultValueString = "0.f";
                    //    }
                    //    else if (Type.Type == typeof(double))
                    //    {
                    //        DefaultValueString = "0.0";
                    //    }
                    //    else
                    //    {
                    //        if (Type.Type.IsEnum)
                    //        {
                    //            DefaultValueString = String.Format("({0})0", Type.Name);
                    //        }
                    //        else
                    //        {
                    //            DefaultValueString = "0";
                    //        }
                    //    }
                    //}

                }
            }
        }
        public object Clone()
        {
            SirenField val = (SirenField)MemberwiseClone();
            val.Attribute = Attribute.Clone() as SirenFieldAttribute;
            return val;
        }

        public bool LoadFrom(Stream stream)
        {
            Attribute.LoadFrom(stream);
            Name = stream.ReadString();
            DefaultValueString = stream.ReadString();
            TypeName = stream.ReadString();
            KeyTypeName = stream.ReadString();
            ValueTypeName = stream.ReadString();

            return true;
        }

        public bool SaveTo(Stream stream)
        {
            Attribute.SaveTo(stream);
            stream.WriteString(Name);
            stream.WriteString(DefaultValueString);
            stream.WriteString(TypeName);
            stream.WriteString(KeyTypeName);
            stream.WriteString(ValueTypeName);

            return true;
        }


        public bool Link(SirenAssembly assembly)
        {
            return false;
        }

        public bool HasValue(object obj)
        {
            var val = Info.GetValue(obj, null);
            switch (FieldType)
            {
                case SirenPropertyFieldType.Value:
                    return DefaultValueString != val.ToString();
                case SirenPropertyFieldType.Blob:
                    return (val as byte[]).Length > 0;
                case SirenPropertyFieldType.String:
                    return (val as string).Length > 0;
                case SirenPropertyFieldType.Struct:
                    return val != null;
                case SirenPropertyFieldType.List:
                case SirenPropertyFieldType.Dictionary:
                    int count = (int)val.GetType().GetProperty("Count").GetValue(val, null);
                    return count > 0;

            }

            return true;
        }
        public override string ToString()
        {
            return String.Format("{0} {1}", Type, Name);
        }

        public void SetToDefault(object obj)
        {
            Info.SetValue(obj, Attribute.DefaultValue, null);
        }
    }
}
