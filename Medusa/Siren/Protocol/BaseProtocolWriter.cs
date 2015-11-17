// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Siren.IO;

namespace Siren.Protocol
{
    public abstract class BaseProtocolWriter
    {
        public abstract void OnVersion();
        public abstract void OnStructBegin();
        public abstract void OnStructEnd();
        public abstract void OnListBegin(SirenDataType itemDataType, int count);
        public abstract void OnListEnd();
        public abstract void OnDictionaryBegin(SirenDataType keyDataType, SirenDataType valueDataType, int count);
        public abstract void OnDictionaryEnd();
        public abstract void OnPropertyBegin(string name, ushort id, SirenDataType dataType);
        public abstract void OnPropertyEnd();
        public abstract void OnValue<T>(T obj);
        public abstract void OnString(string obj);
        public abstract void OnMemoryData(byte[] obj);
        public abstract void OnError();

        public abstract ArraySegment<byte> ToBuffer();

        public virtual void OnProperty(string name, ushort id, object obj, bool withHeader = true)
        {
            if (withHeader)
            {
                OnPropertyBegin(name, id, SirenFactory.GetDataType(obj.GetType()));
                OnValue(obj);
                OnPropertyEnd();
            }
            else
            {
                OnValue(obj);
            }
        }

    }
}
