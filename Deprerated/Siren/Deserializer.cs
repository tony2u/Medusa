// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Siren.Attribute;
using Siren.IO;
using Siren.Protocol;

namespace Siren
{
    public class Deserializer
    {
        public BaseProtocolReader Reader { get; set; }

        public Deserializer(BaseProtocolReader reader)
        {
            Reader = reader;
        }

        public static T DeserializeJson<T>(string str)
              where T : class,new()
        {
            var reader = new Siren.Protocol.Json.JsonReader();
            reader.Accept(str);
            Deserializer deserializer = new Deserializer(reader);

            object obj = new T();
            deserializer.DeserializeHelper(typeof(T), ref obj, SirenFactory.FindClass(typeof(T)));
            return (T)obj;


            //JsonSerializerSettings settings = new JsonSerializerSettings
            //{
            //    ContractResolver = Serializer.SirenContractResolver.Instance
            //};
            //return JsonConvert.DeserializeObject<T>(str, settings);
        }

        public static T Deserialize<T, TReader>(ArraySegment<byte> data)
            where T : class,new()
            where TReader : BaseProtocolReader, new()
        {
            var reader = new TReader();
            reader.Accept(data);
            Deserializer deserializer = new Deserializer(reader);

            object obj = new T();
            deserializer.DeserializeHelper(typeof(T), ref obj, SirenFactory.FindClass(typeof(T)));
            return (T)obj;
        }
       


        public void DeserializeHelper(Type type, ref object obj, SirenClass sirenClass)
        {
            if (sirenClass == null)
            {
                if (type.IsValueType)
                {
                    obj = Reader.OnValue(type);
                }
                else if (type == typeof(string))
                {
                    obj = Reader.OnString();

                }
                else if (type == typeof(byte[]))
                {
                    obj = Reader.OnMemoryData();
                }
                else
                {
                    Console.WriteLine("Unknown type:{0}", type);
                    Reader.OnError();
                }
            }
            else if (sirenClass.DeserializeMethodInfo != null)
            {
                sirenClass.DeserializeMethodInfo.Invoke(obj, new object[] { Reader });
            }
            else
            {
                DeserializeStruct(ref obj, sirenClass);
            }

        }

        public void DeserializeStruct(ref object obj, SirenClass sirenClass)
        {
            Reader.OnStructBegin();
            DeserializeBase(ref obj, sirenClass);
            Reader.OnStructEnd();
        }

        public void DeserializeBase(ref object obj, SirenClass sirenClass)
        {
            if (sirenClass.BaseSirenClass != null)
            {
                DeserializeBase(ref obj, sirenClass.BaseSirenClass);
            }

            foreach (var sirenProperty in sirenClass.Properties)
            {
                while (true)
                {
                    if (Reader.IsEnd())
                    {
                        Console.WriteLine("Reach end of file.Cannot find property {0}.{1}", sirenClass.Name, sirenProperty.Name);
                        Reader.OnError();
                        return;
                    }

                    ushort outId;
                    SirenFieldType outDataType;
                    int result = Reader.OnPropertyBegin(sirenProperty.Name, sirenProperty.Id, sirenProperty.DataType, out outId,out outDataType);
                    if (result == 0)
                    {
                        object val = null;

                        switch (sirenProperty.FieldType)
                        {
                            case SirenPropertyFieldType.Value:
                            case SirenPropertyFieldType.String:
                            case SirenPropertyFieldType.Blob:
                                DeserializeHelper(sirenProperty.Type, ref val, sirenProperty.ValueSirenClass);
                                break;
                            case SirenPropertyFieldType.Struct:
                            case SirenPropertyFieldType.Pointer:
                                val = SirenFactory.Create(sirenProperty.Type);
                                DeserializeHelper(sirenProperty.Type, ref val, sirenProperty.ValueSirenClass);
                                break;
                            case SirenPropertyFieldType.List:
                                {
                                    val = SirenFactory.Create(sirenProperty.Type);
                                    SirenFieldType valueDataType;
                                    int count;
                                    Reader.OnListBegin(out valueDataType, out count);//get count and type
                                    var addMethod = sirenProperty.Type.GetMethod("Add");
                                    for (int i = 0; i < count; i++)
                                    {
                                        var listItem = SirenFactory.Create(sirenProperty.ValueType);
                                        DeserializeHelper(sirenProperty.ValueType, ref listItem, sirenProperty.ValueSirenClass);
                                        addMethod.Invoke(val, new[] { listItem });
                                    }
                                    Reader.OnListEnd();
                                }

                                break;
                            case SirenPropertyFieldType.Dictionary:
                                {
                                    val = SirenFactory.Create(sirenProperty.Type);

                                    SirenFieldType keyDataType;
                                    SirenFieldType valueDataType;
                                    int count;
                                    Reader.OnDictionaryBegin(out keyDataType, out valueDataType, out count);//get count and type
                                    var addMethod = sirenProperty.Type.GetMethod("Add");
                                    for (int i = 0; i < count; i++)
                                    {
                                        var dictKey = SirenFactory.Create(sirenProperty.KeyType);
                                        var dictValue = SirenFactory.Create(sirenProperty.ValueType);

                                        DeserializeHelper(sirenProperty.KeyType, ref dictKey, sirenProperty.KeySirenClass);
                                        DeserializeHelper(sirenProperty.ValueType, ref dictValue, sirenProperty.ValueSirenClass);
                                        addMethod.Invoke(val, new[] { dictKey, dictValue });
                                    }

                                    Reader.OnDictionaryEnd();
                                }
                                break;

                        }
                        sirenProperty.Info.SetValue(obj, val);
                        Reader.OnPropertyEnd();
                        break;
                    }
                    else if (result < 0)
                    {
                        //Current filed missed
                        if (sirenProperty.Attribute.Modifier == SirenFieldModifier.Required)
                        {
                            //cannot find this property
                            Console.WriteLine("Cannot find property {0}.{1}", sirenClass.Name, sirenProperty.Name);
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
                        Reader.OnPropertySkip(sirenProperty.DataType);
                        //read next field
                    }
                }


            }
        }



    }
}
