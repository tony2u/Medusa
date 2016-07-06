// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System;
using Medusa.Siren.Schema;

namespace Medusa.Siren.Code
{
    public abstract class BaseProtocolWriter
    {
        public abstract void OnVersion();
        public abstract void OnStructBegin();
        public abstract void OnStructEnd();
        public abstract void OnListBegin(SirenTypeId itemDataType, int count);
        public abstract void OnListEnd();
        public abstract void OnDictionaryBegin(SirenTypeId keyDataType, SirenTypeId valueDataType, int count);
        public abstract void OnDictionaryEnd();
        public abstract void OnFieldBegin(string name, ushort id, SirenTypeId dataType);
        public abstract void OnFieldEnd();
        public abstract void OnValue<T>(T obj);
        public abstract void OnString(string obj);
        public abstract void OnMemoryData(byte[] obj);
        public abstract void OnError();

        public abstract ArraySegment<byte> ToBuffer();

        public virtual void OnField(string name, ushort id, object obj, bool withHeader = true)
        {
            if (withHeader)
            {
                OnFieldBegin(name, id, SirenMachine.GetTypeId(obj.GetType()));
                OnValue(obj);
                OnFieldEnd();
            }
            else
            {
                OnValue(obj);
            }
        }

    }
}
