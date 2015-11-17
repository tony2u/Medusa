// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Diagnostics;
using System.IO;
using System.Text;
using Newtonsoft.Json;
using Siren.IO;

namespace Siren.Protocol.Json
{
    public class JsonWriter : BaseProtocolWriter
    {
        private readonly JsonTextWriter mWriter;
        private readonly StringWriter mStringWriter;

        public JsonWriter()
        {
            mStringWriter = new StringWriter();
            mWriter = new JsonTextWriter(mStringWriter);
            mWriter.Formatting=Formatting.Indented;
        }

        public override void OnVersion()
        {

        }

        public override void OnStructBegin()
        {
            mWriter.WriteStartObject();
        }

        public override void OnStructEnd()
        {
            mWriter.WriteEndObject();

        }

        public override void OnListBegin(SirenDataType itemDataType, int count)
        {
            mWriter.WriteStartArray();
        }

        public override void OnListEnd()
        {
            mWriter.WriteEndArray();
        }

        public override void OnDictionaryBegin(SirenDataType keyDataType, SirenDataType valueDataType, int count)
        {
            mWriter.WriteStartArray();
        }

        public override void OnDictionaryEnd()
        {
            mWriter.WriteEndArray();
        }

        public override void OnPropertyBegin(string name, ushort id, SirenDataType dataType)
        {
            mWriter.WritePropertyName(name);
        }

        public override void OnPropertyEnd()
        {

        }

        public override void OnString(string obj)
        {
            mWriter.WriteValue(obj);
        }

        public override void OnMemoryData(byte[] obj)
        {
            var str=Base91.Encode(obj);
            mWriter.WriteValue(str);

        }

        public override void OnError()
        {
        }

        public override ArraySegment<byte> ToBuffer()
        {
            var str = FlushToString();
            var bytes = Encoding.UTF8.GetBytes(str);
            return new ArraySegment<byte>(bytes);
        }

        public override void OnValue<T>(T obj)
        {
            mWriter.WriteValue(obj);
        }

        public string FlushToString()
        {
            mWriter.Flush();
            return mStringWriter.GetStringBuilder().ToString();
        }

        public override void OnProperty(string name, ushort id, object obj, bool withHeader = true)
        {
            OnPropertyBegin(name, id, SirenFactory.GetDataType(obj.GetType()));
            OnValue(obj);
            OnPropertyEnd();
        }

    }
}
