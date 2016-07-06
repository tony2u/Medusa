// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System;
using Medusa.Log;
using Medusa.Siren.Code;
using Medusa.Siren.Code.Binary;
using Medusa.Siren.Schema;

namespace Medusa.Siren
{
    public class Deserializer
    {
        public BaseProtocolReader Reader { get; set; }

        public Deserializer(BaseProtocolReader reader)
        {
            Reader = reader;
        }


        public static T Deserialize<T>(ArraySegment<byte> data)
            where T : class, new()
        {
            var reader = new CompactBinaryReader();
            reader.Accept(data);
            Deserializer deserializer = new Deserializer(reader);

            object obj = new T();
            deserializer.DeserializeHelper(typeof(T), ref obj, SirenMachine.GetType(typeof(T)));
            return (T)obj;
        }



        public void DeserializeHelper(Type type, ref object obj, SirenType sirenType)
        {
            if (sirenType.IsBuildIn)
            {
                switch (sirenType.Id)
                {
                    case SirenTypeId.List:
                        break;
                    case SirenTypeId.Dictionary:
                        break;
                    case SirenTypeId.String:
                        obj = Reader.OnString();
                        break;
                    case SirenTypeId.Blob:
                        obj = Reader.OnMemoryData();
                        break;
                    default:
                        obj = Reader.OnValue(type);
                        break;

                }
            }
            else
            {
                if (sirenType.IsCustomClass)
                {
                    SirenCustomClass sirenClass = sirenType as SirenCustomClass;
                    if (sirenClass.DeserializeMethodInfo != null)
                    {
                        sirenClass.DeserializeMethodInfo.Invoke(obj, new object[] { Reader });
                    }
                    else
                    {
                        DeserializeStruct(ref obj, sirenClass);
                    }
                }
                else
                {
                    obj = DeserializeEnum(sirenType as SirenCustomEnum);
                }
            }


        }

        public object DeserializeEnum(SirenCustomEnum sirenEnum)
        {
            return Reader.OnValue(sirenEnum.Type);
        }


        public void DeserializeStruct(ref object obj, SirenCustomClass sirenClass)
        {
            Reader.OnStructBegin();
            DeserializeBase(ref obj, sirenClass);
            Reader.OnStructEnd();
        }

        public void DeserializeBase(ref object obj, SirenCustomClass sirenClass)
        {
            if (sirenClass.BaseType != null)
            {
                DeserializeBase(ref obj, sirenClass.BaseType);
            }

            foreach (var sirenProperty in sirenClass.Fields)
            {
                while (true)
                {
                    if (Reader.IsEnd())
                    {
                        Logger.ErrorLine("Reach end of file.Cannot find property {0}.{1}", sirenClass.Name, sirenProperty.Name);
                        Reader.OnError();
                        return;
                    }

                    ushort outId;
                    SirenTypeId outDataType;
                    int result = Reader.OnFieldBegin(sirenProperty.Name, sirenProperty.Id, sirenProperty.DataType, out outId, out outDataType);
                    if (result == 0)
                    {
                        object val = null;

                        switch (sirenProperty.FieldType)
                        {
                            case SirenPropertyFieldType.Value:
                            case SirenPropertyFieldType.String:
                            case SirenPropertyFieldType.Blob:
                                DeserializeHelper(sirenProperty.Type.Type, ref val, sirenProperty.Type);
                                break;
                            case SirenPropertyFieldType.Struct:
                                val = SirenMachine.Create(sirenProperty.Type.Type);
                                DeserializeHelper(sirenProperty.Type.Type, ref val, sirenProperty.Type);
                                break;
                            case SirenPropertyFieldType.List:
                                {
                                    val = SirenMachine.Create(sirenProperty.Type.Type);
                                    SirenTypeId valueDataType;
                                    int count;
                                    Reader.OnListBegin(out valueDataType, out count);//get count and type
                                    var addMethod = sirenProperty.Type.Type.GetMethod("Add");
                                    for (int i = 0; i < count; i++)
                                    {
                                        var listItem = SirenMachine.Create(sirenProperty.ValueType.Type);
                                        DeserializeHelper(sirenProperty.ValueType.Type, ref listItem, sirenProperty.ValueType);
                                        addMethod.Invoke(val, new[] { listItem });
                                    }
                                    Reader.OnListEnd();
                                }

                                break;
                            case SirenPropertyFieldType.Dictionary:
                                {
                                    val = SirenMachine.Create(sirenProperty.Type.Type);

                                    SirenTypeId keyDataType;
                                    SirenTypeId valueDataType;
                                    int count;
                                    Reader.OnDictionaryBegin(out keyDataType, out valueDataType, out count);//get count and type
                                    var addMethod = sirenProperty.Type.Type.GetMethod("Add");
                                    for (int i = 0; i < count; i++)
                                    {
                                        var dictKey = SirenMachine.Create(sirenProperty.KeyType.Type);
                                        var dictValue = SirenMachine.Create(sirenProperty.ValueType.Type);

                                        DeserializeHelper(sirenProperty.KeyType.Type, ref dictKey, sirenProperty.KeyType);
                                        DeserializeHelper(sirenProperty.ValueType.Type, ref dictValue, sirenProperty.ValueType);
                                        addMethod.Invoke(val, new[] { dictKey, dictValue });
                                    }

                                    Reader.OnDictionaryEnd();
                                }
                                break;

                        }

                        if (sirenProperty.DataType==SirenTypeId.Enum)
                        {
                            var enumObj= Enum.ToObject(sirenProperty.Info.PropertyType, val);
                            sirenProperty.Info.SetValue(obj, enumObj, null);
                        }
                        else
                        {
                            sirenProperty.Info.SetValue(obj, val, null);
                        }
                        Reader.OnFieldEnd();
                        break;
                    }
                    else if (result < 0)
                    {
                        //Current filed missed
                        if (sirenProperty.Attribute.Mode != SirenFieldGenerateMode.Optional)
                        {
                            //cannot find this property
                            Logger.ErrorLine("Cannot find property {0}.{1}", sirenClass.Name, sirenProperty.Name);
                            Reader.OnError();
                            return;
                        }
                        else
                        {
                            sirenProperty.SetToDefault(obj);
                            break;
                        }
                    }
                    else
                    {
                        //Read unknown field
                        //skip current field
                        Reader.OnFieldSkip(sirenProperty.DataType);
                        //read next field
                    }
                }


            }
        }



    }
}
