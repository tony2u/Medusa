// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Siren.IO;

namespace Siren.Protocol
{
    public abstract class BaseProtocolReader
    {
        public abstract void OnVersion();
        public abstract void OnStructBegin();
        public abstract void OnStructEnd();
        public abstract void OnListBegin(out SirenFieldType dataType, out int count);
        public abstract void OnListEnd();
        public abstract void OnDictionaryBegin(out SirenFieldType keyDataType, out SirenFieldType valueDataType, out int count);
        public abstract void OnDictionaryEnd();
        public abstract int OnPropertyBegin(string name, ushort id, SirenFieldType dataType, out ushort outId, out SirenFieldType outDataType);
        public abstract void OnPropertyEnd();
        public abstract void OnPropertySkip(SirenFieldType dataType);
        public abstract object OnValue(Type type);
        public abstract string OnString();
        public abstract byte[] OnMemoryData();
        public abstract void OnError();
        public abstract void Accept(ArraySegment<byte> data);
        public abstract bool IsEnd();

        public virtual T OnProperty<T>(string name, ushort id, bool withHeader = true)
        {
            if (withHeader)
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
            else
            {
                return (T)OnValue(typeof(T));
            }
        }
    }
}
