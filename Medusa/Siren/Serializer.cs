// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using Siren;
using Siren.Attribute;
using Siren.IO;
using Siren.Protocol;
using Siren.Protocol.Binary;

namespace Siren
{
    /*
     * TODO: ??Linq Expression ?????
     */
    public class Serializer
    {
        public BaseProtocolWriter Writer { get; set; }

        public Serializer(BaseProtocolWriter writer)
        {
            Writer = writer;
        }

        public static ArraySegment<byte> Serialize<TWriter>(object obj)
            where TWriter : BaseProtocolWriter, new()
        {
            var writer = new TWriter();
            Serializer serializer = new Serializer(writer);
            serializer.SerializeHelper(obj, SirenFactory.FindClass(obj.GetType()));
            return writer.ToBuffer();
        }


        public static string SerializeJson(object obj)
        {
            var writer = new Siren.Protocol.Json.JsonWriter();
            Serializer serializer = new Serializer(writer);
            serializer.SerializeHelper(obj, SirenFactory.FindClass(obj.GetType()));
            return writer.FlushToString();
        }


        public void SerializeHelper(object obj, SirenClass sirenClass)
        {
            Type type = obj.GetType();
            if (sirenClass == null)
            {
                if (type.IsValueType)
                {
                    Writer.OnValue(obj);
                }
                else if (type == typeof(string))
                {
                    Writer.OnString(obj as string);
                }
                else if (type == typeof(byte[]))
                {
                    Writer.OnMemoryData(obj as byte[]);
                }
                else
                {
                    Console.WriteLine("Unknown type:{0}", type);
                    Writer.OnError();
                }
            }
            else if(sirenClass.SerializeMethodInfo!=null)
            {
                sirenClass.SerializeMethodInfo.Invoke(obj, new object[] {Writer});
            }
            else
            {
                SerializeStruct(obj, sirenClass);
            }

        }

        public void SerializeStruct(object obj, SirenClass sirenClass)
        {
            Writer.OnStructBegin();
            SerializeBase(obj, sirenClass);
            Writer.OnStructEnd();
        }

        public void SerializeBase(object obj, SirenClass sirenClass)
        {
            if (sirenClass.BaseSirenClass != null)
            {
                SerializeBase(obj, sirenClass.BaseSirenClass);
            }

            foreach (var sirenProperty in sirenClass.Properties)
            {
                if (sirenProperty.Attribute.Modifier == SirenPropertyModifier.Required)
                {
                    if (!sirenProperty.HasValue(obj))
                    {
                        Console.WriteLine("Forget to set {0}.{1}", sirenClass.Name, sirenProperty.Name);
                        Writer.OnError();
                        return;
                    }
                }
                else
                {
                    if (!sirenProperty.HasValue(obj))
                    {
                        //skip
                        return;
                    }
                }

                Writer.OnPropertyBegin(sirenProperty.Name,sirenProperty.Id,sirenProperty.DataType);

                switch (sirenProperty.FieldType)
                {
                    case SirenPropertyFieldType.Value:
                        Writer.OnValue(sirenProperty.Info.GetValue(obj));
                        break;
                    case SirenPropertyFieldType.String:
                        Writer.OnString(sirenProperty.Info.GetValue(obj) as string);
                        break;
                    case SirenPropertyFieldType.Blob:
                        Writer.OnMemoryData(sirenProperty.Info.GetValue(obj) as byte[]);
                        break;
                    case SirenPropertyFieldType.List:
                        {
                            object items = sirenProperty.Info.GetValue(obj);
                            var listType = sirenProperty.Type;
                            int count = Convert.ToInt32(listType.GetProperty("Count").GetValue(items));

                            var itemType = sirenProperty.Type.GenericTypeArguments[0];
                            SirenDataType itemDataType = SirenFactory.GetDataType(itemType);
                            Writer.OnListBegin(itemDataType,count);
                            var itemsProperty = listType.GetProperty("Item");
                            for (int i = 0; i < count; i++)
                            {
                                object listItem = itemsProperty.GetValue(items, new object[] { i });
                                SerializeHelper(listItem, sirenProperty.ValueSirenClass);
                            }
                            Writer.OnListEnd();
                        }

                        break;
                    case SirenPropertyFieldType.Dictionary:
                        {
                            object items = sirenProperty.Info.GetValue(obj);
                            var dictType = sirenProperty.Type;
                            int count = Convert.ToInt32(dictType.GetProperty("Count").GetValue(items));

                            var keyType = sirenProperty.Type.GenericTypeArguments[0];
                            var valueType = sirenProperty.Type.GenericTypeArguments[1];

                            SirenDataType keyDataType = SirenFactory.GetDataType(keyType);
                            SirenDataType valueDataType = SirenFactory.GetDataType(valueType);


                            Writer.OnDictionaryBegin(keyDataType, valueDataType,count);

                            foreach (var o in (items as IEnumerable))
                            {
                                var itemKey = o.GetType().GetProperty("Key").GetValue(o, null);
                                SerializeHelper(itemKey, sirenProperty.KeySirenClass);
                                var itemValue = o.GetType().GetProperty("Value").GetValue(o, null);
                                SerializeHelper(itemValue, sirenProperty.ValueSirenClass);
                            }

                            Writer.OnDictionaryEnd();
                        }
                        break;
                    case SirenPropertyFieldType.Pointer:
                    case SirenPropertyFieldType.Struct:
                        {
                            object val = sirenProperty.Info.GetValue(obj);
                            SerializeHelper(val, sirenProperty.ValueSirenClass);
                        }

                        break;
                }

                Writer.OnPropertyEnd();
            }
        }


    }
}
