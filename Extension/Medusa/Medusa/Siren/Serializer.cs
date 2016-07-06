// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System;
using System.Collections;
using Medusa.Log;
using Medusa.Siren.Code;
using Medusa.Siren.Code.Binary;
using Medusa.Siren.Schema;

namespace Medusa.Siren
{
    public class Serializer
    {
        public BaseProtocolWriter Writer { get; set; }

        public Serializer(BaseProtocolWriter writer)
        {
            Writer = writer;
        }

        public static ArraySegment<byte> Serialize(object obj)
        {
            var writer = new CompactBinaryWriter();
            Serializer serializer = new Serializer(writer);
            serializer.SerializeHelper(obj, SirenMachine.GetType(obj.GetType()));
            return writer.ToBuffer();
        }

        public void SerializeHelper(object obj, SirenType sirenType)
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
                        Writer.OnString(obj as string);
                        break;
                    case SirenTypeId.Blob:
                        Writer.OnMemoryData(obj as byte[]);
                        break;
                    default:
                        Writer.OnValue(obj);
                        break;

                }
            }
            else
            {
                if (sirenType.IsCustomClass)
                {
                    SirenCustomClass sirenClass=sirenType as SirenCustomClass;
                    if (sirenClass.SerializeMethodInfo != null)
                    {
                        sirenClass.SerializeMethodInfo.Invoke(obj, new object[] { Writer });
                    }
                    else
                    {
                        SerializeStruct(obj, sirenClass);
                    }
                }
                else
                {
                    SerializeEnum(obj,sirenType as SirenCustomEnum);
                }
            }

           
        }

        public void SerializeEnum(object obj, SirenCustomEnum sirenEnum)
        {
            Writer.OnValue(obj);
        }

        public void SerializeStruct(object obj, SirenCustomClass sirenClass)
        {
            Writer.OnStructBegin();
            SerializeBase(obj, sirenClass);
            Writer.OnStructEnd();
        }

        public void SerializeBase(object obj, SirenCustomClass sirenClass)
        {
            if (sirenClass.BaseType != null)
            {
                SerializeBase(obj, sirenClass.BaseType);
            }

            foreach (var sirenField in sirenClass.Fields)
            {
                if (sirenField.Attribute.Mode != SirenFieldGenerateMode.Optional)
                {
                    if (!sirenField.HasValue(obj))
                    {
                        Logger.ErrorLine("Forget to set {0}.{1}", sirenClass.Name, sirenField.Name);
                        Writer.OnError();
                        return;
                    }
                }
                else
                {
                    if (!sirenField.HasValue(obj))
                    {
                        //skip
                        return;
                    }
                }

                Writer.OnFieldBegin(sirenField.Name, sirenField.Id, sirenField.DataType);

                switch (sirenField.FieldType)
                {
                    case SirenPropertyFieldType.Value:
                        Writer.OnValue(sirenField.Info.GetValue(obj, null));
                        break;
                    case SirenPropertyFieldType.String:
                        Writer.OnString(sirenField.Info.GetValue(obj, null) as string);
                        break;
                    case SirenPropertyFieldType.Blob:
                        Writer.OnMemoryData(sirenField.Info.GetValue(obj, null) as byte[]);
                        break;
                    case SirenPropertyFieldType.List:
                        {
                            object items = sirenField.Info.GetValue(obj, null);
                            var listType = sirenField.Type;
                            int count = Convert.ToInt32(listType.Type.GetProperty("Count").GetValue(items, null));

                            var itemType = sirenField.Type.Type.GetGenericArguments()[0];
                            SirenTypeId itemDataType = SirenMachine.GetTypeId(itemType);
                            Writer.OnListBegin(itemDataType, count);
                            var itemsProperty = listType.Type.GetProperty("Item");
                            for (int i = 0; i < count; i++)
                            {
                                object listItem = itemsProperty.GetValue(items, new object[] { i });
                                SerializeHelper(listItem, sirenField.ValueType);
                            }
                            Writer.OnListEnd();
                        }

                        break;
                    case SirenPropertyFieldType.Dictionary:
                        {
                            object items = sirenField.Info.GetValue(obj, null);
                            var dictType = sirenField.Type;
                            int count = Convert.ToInt32(dictType.Type.GetProperty("Count").GetValue(items, null));

                            var keyType = sirenField.Type.Type.GetGenericArguments()[0];
                            var valueType = sirenField.Type.Type.GetGenericArguments()[1];

                            SirenTypeId keyDataType = SirenMachine.GetTypeId(keyType);
                            SirenTypeId valueDataType = SirenMachine.GetTypeId(valueType);


                            Writer.OnDictionaryBegin(keyDataType, valueDataType, count);

                            foreach (var o in (items as IEnumerable))
                            {
                                var itemKey = o.GetType().GetProperty("Key").GetValue(o, null);
                                SerializeHelper(itemKey, sirenField.KeyType);
                                var itemValue = o.GetType().GetProperty("Value").GetValue(o, null);
                                SerializeHelper(itemValue, sirenField.ValueType);
                            }

                            Writer.OnDictionaryEnd();
                        }
                        break;
                    case SirenPropertyFieldType.Struct:
                        {
                            object val = sirenField.Info.GetValue(obj, null);
                            SerializeHelper(val, sirenField.ValueType);
                        }

                        break;
                }

                Writer.OnFieldEnd();
            }
        }


    }
}
