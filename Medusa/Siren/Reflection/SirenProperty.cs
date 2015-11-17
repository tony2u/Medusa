// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Siren.Attribute;

namespace Siren
{
    public enum SirenPropertyMethodType
    {
        Value,
        List,
        Dictionary,
        Pointer,
        Unsupported
    }

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

    public class SirenProperty
    {
        public Type Type { get { return Info.PropertyType; } }
        public Type KeyType { get; private set; }
        public Type ValueType { get; private set; }

        public string Name { get { return Info.Name; } }

        public SirenClass ParentSirenClass { get; private set; }
        public SirenClass KeySirenClass { get; private set; }
        public SirenClass ValueSirenClass { get; private set; }


        public PropertyInfo Info { get; private set; }
        public SirenPropertyAttribute Attribute { get; private set; }
        public SirenPropertyMethodType MethodType { get; private set; }
        public SirenPropertyFieldType FieldType { get; private set; }
        public SirenDataType DataType { get; private set; }

        public uint Index { get; private set; }
        public ushort Id { get; private set; }
        public string DefaultValueString { get; private set; }

        public SirenProperty(ushort id, SirenDataType type)
        {
            Id = id;
            DataType = type;
        }

        public SirenProperty(SirenClass parentSirenClass, PropertyInfo info, SirenPropertyAttribute attribute, uint index, ushort id)
        {
            ParentSirenClass = parentSirenClass;
            Info = info;
            Id = id;
            Attribute = attribute;
            Index = index;
            FieldType = SirenPropertyFieldType.Struct;
            DataType = SirenFactory.GetDataType(Type);
            MethodType = SirenPropertyMethodType.Unsupported;


            if (Type.IsGenericType)
            {
                if (Type.Name.StartsWith("List"))
                {
                    MethodType = SirenPropertyMethodType.List;
                    FieldType = SirenPropertyFieldType.List;

                    ValueType = Type.GenericTypeArguments[0];
                    ValueSirenClass = SirenFactory.FindClass(ValueType);

                }
                else if (Type.Name.StartsWith("Dictionary"))
                {
                    MethodType = SirenPropertyMethodType.Dictionary;
                    FieldType = SirenPropertyFieldType.Dictionary;

                    KeyType = Type.GenericTypeArguments[0];
                    ValueType = Type.GenericTypeArguments[1];
                    KeySirenClass = SirenFactory.FindClass(KeyType);
                    ValueSirenClass = SirenFactory.FindClass(ValueType);
                }
                else
                {
                    ValueSirenClass = SirenFactory.FindClass(Type);

                    if (Attribute.Modifier == SirenPropertyModifier.Required)
                    {
                        MethodType = SirenPropertyMethodType.Value;
                        FieldType = SirenPropertyFieldType.Struct;
                    }
                    else
                    {
                        MethodType = SirenPropertyMethodType.Pointer;
                        FieldType = SirenPropertyFieldType.Pointer;
                    }

                }

                DefaultValueString = String.Empty;
            }
            else
            {
                if (Type.IsValueType || Type == typeof(string) || Type == typeof(byte[]))
                {
                    MethodType = SirenPropertyMethodType.Value;

                    if (Type == typeof(string))
                    {
                        FieldType = SirenPropertyFieldType.String;

                    }
                    else if (Type == typeof(byte[]))
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
                    if (Attribute.Modifier == SirenPropertyModifier.Required)
                    {
                        MethodType = SirenPropertyMethodType.Value;
                        FieldType = SirenPropertyFieldType.Struct;
                    }
                    else
                    {
                        MethodType = SirenPropertyMethodType.Pointer;
                        FieldType = SirenPropertyFieldType.Pointer;
                    }

                    ValueSirenClass = SirenFactory.FindClass(Type);
                }

                DefaultValueString = String.Empty;
                if (Type.IsValueType)
                {

                    if (Attribute.DefaultValue != null)
                    {
                        if (Type.IsEnum)
                        {
                            DefaultValueString = String.Format("({0}){1}",Type.Name, Convert.ToUInt32(Attribute.DefaultValue));

                        }
                        else
                        {
                            DefaultValueString = Attribute.DefaultValue.ToString();
                        }
                    }
                    else
                    {
                        if (Type == typeof(bool))
                        {
                            DefaultValueString = "false";
                        }
                        else if (Type == typeof(float))
                        {
                            DefaultValueString = "0.f";
                        }
                        else if (Type == typeof(double))
                        {
                            DefaultValueString = "0.0";
                        }
                        else
                        {
                            if (Type.IsEnum)
                            {
                                DefaultValueString = String.Format("({0})0", Type.Name);
                            }
                            else
                            {
                                DefaultValueString = "0";
                            }
                        }
                    }

                }
            }
        }

        public bool HasValue(object obj)
        {
            var val = Info.GetValue(obj);
            switch (FieldType)
            {
                case SirenPropertyFieldType.Value:
                    return DefaultValueString != val.ToString();
                case SirenPropertyFieldType.Blob:
                    return (val as byte[]).Length > 0;
                case SirenPropertyFieldType.String:
                    return (val as string).Length > 0;
                case SirenPropertyFieldType.Struct:
                case SirenPropertyFieldType.Pointer:
                    return val != null;
                case SirenPropertyFieldType.List:
                case SirenPropertyFieldType.Dictionary:
                    int count = (int)val.GetType().GetProperty("Count").GetValue(val);
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
            Info.SetValue(obj, Attribute.DefaultValue);
        }
    }
}
