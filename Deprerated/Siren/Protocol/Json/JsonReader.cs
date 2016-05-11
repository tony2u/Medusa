// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Siren.IO;
using Siren.Protocol.Binary;

namespace Siren.Protocol.Json
{
    public class JsonReader : BaseProtocolReader
    {
        private JObject mJObject;
        private Stack<JToken> mJsonTokens = new Stack<JToken>();
        private JToken mCurrenToken;
        private Stack<uint> mArrayInices = new Stack<uint>();


        public override void Accept(ArraySegment<byte> data)
        {
            var str = Encoding.UTF8.GetString(data.Array, data.Offset, data.Count);
            mJObject = JObject.Parse(str);

            mCurrenToken = mJObject;
            mJsonTokens.Push(mCurrenToken);
        }

        public void Accept(string str)
        {
            mJObject = JObject.Parse(str);

            mCurrenToken = mJObject;
            mJsonTokens.Push(mCurrenToken);
        }

        public override bool IsEnd()
        {
            return false;
        }

        public override void OnVersion()
        {

        }

        public override void OnStructBegin()
        {

        }

        public override void OnStructEnd()
        {
        }

        public override void OnListBegin(out SirenFieldType dataType, out int count)
        {
            JToken currenToken = CurrentToken();
            count = currenToken.Count();
            mArrayInices.Push(0);
            dataType = SirenFieldType.Bool;
        }

        public override void OnListEnd()
        {
            mArrayInices.Pop();
        }

        public override void OnDictionaryBegin(out SirenFieldType keyDataType, out SirenFieldType valueDataType, out int count)
        {
            JToken currenToken = CurrentToken();
            count = currenToken.Count() / 2;
            mArrayInices.Push(0);
            keyDataType = SirenFieldType.Bool;
            valueDataType = SirenFieldType.Bool;
        }

        public override void OnDictionaryEnd()
        {
            mArrayInices.Pop();
        }

        public override int OnPropertyBegin(string name, ushort id, SirenFieldType dataType, out ushort outId, out SirenFieldType outDataType)
        {
            outId = 0;
            outDataType = SirenFieldType.Struct;
            JToken outToken;
            JToken currenToken = CurrentToken();
            outToken = currenToken[name];
            if (outToken != null)
            {
                mJsonTokens.Push(outToken);
                return 0;
            }
            return -1;

        }

        public override void OnPropertyEnd()
        {
            mJsonTokens.Pop();
        }

        public override void OnPropertySkip(SirenFieldType dataType)
        {
            mJsonTokens.Pop();
        }

        public override object OnValue(Type type)
        {
            JToken currenToken = CurrentToken();
            if (type == typeof(bool))
            {
                return (bool)currenToken;
            }
            else if (type == typeof(char))
            {
                return (char)currenToken;
            }
            else if (type == typeof(short))
            {
                return (short)currenToken;
            }
            else if (type == typeof(int))
            {
                return (int)currenToken;
            }
            else if (type == typeof(Int64))
            {
                return (Int64)currenToken;
            }
            else if (type == typeof(byte))
            {
                return (byte)currenToken;
            }
            else if (type == typeof(ushort))
            {
                return (ushort)currenToken;
            }
            else if (type == typeof(uint))
            {
                return (uint)currenToken;
            }
            else if (type == typeof(UInt64))
            {
                return (UInt64)currenToken;
            }
            else if (type == typeof(float))
            {
                return (float)currenToken;
            }
            else if (type == typeof(double))
            {
                return (double)currenToken;
            }
            else
            {
                if (type.IsEnum)
                {
                    return (uint)currenToken;
                }
                else
                {
                    Console.WriteLine("Invalid value type:{0}", type);
                }
            }

            return null;
        }

        public override string OnString()
        {
            JToken currenToken = CurrentToken();
            return (string)currenToken;

        }

        public override byte[] OnMemoryData()
        {
            JToken currenToken = CurrentToken();
            var str = (string)currenToken;
            var data = Base91.Decode(str);
            return data;
        }

        public JToken CurrentToken()
        {
            JToken currenToken = mJsonTokens.Peek();
            if (mArrayInices.Count <= 0)
            {
                return currenToken;
            }
            uint index = mArrayInices.Pop();
            if (currenToken is JArray)
            {
                currenToken = (currenToken as JArray)[(int)index];
            }
            else
            {
                JToken temp = currenToken.First;
                for (int i = 0; i < index; i++)
                {
                    temp = temp.Next;
                }
                currenToken = temp;
            }


            ++index;
            mArrayInices.Push(index);
            return currenToken;


        }

        public override void OnError()
        {
        }

        public override T OnProperty<T>(string name, ushort id, bool withHeader = true)
        {
            ushort outId;
            SirenFieldType outDataType;
            int r = OnPropertyBegin(name, id, SirenFactory.GetPropertyType(typeof(T)), out outId, out outDataType);
            if (r == 0)
            {
                var obj = OnValue(typeof(T));
                OnPropertyEnd();
                return (T)obj;
            }
            return default(T);
        }

    }
}
