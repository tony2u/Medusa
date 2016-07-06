// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System;
using Medusa.Siren.Schema;

namespace Medusa.Siren.Code
{
    public abstract class BaseProtocolReader
    {
        public abstract void OnVersion();
        public abstract void OnStructBegin();
        public abstract void OnStructEnd();
        public abstract void OnListBegin(out SirenTypeId dataType, out int count);
        public abstract void OnListEnd();
        public abstract void OnDictionaryBegin(out SirenTypeId keyDataType, out SirenTypeId valueDataType, out int count);
        public abstract void OnDictionaryEnd();
        public abstract int OnFieldBegin(string name, ushort id, SirenTypeId dataType, out ushort outId, out SirenTypeId outDataType);
        public abstract void OnFieldEnd();
        public abstract void OnFieldSkip(SirenTypeId dataType);
        public abstract object OnValue(Type type);
        public abstract string OnString();
        public abstract byte[] OnMemoryData();
        public abstract void OnError();
        public abstract void Accept(ArraySegment<byte> data);
        public abstract bool IsEnd();

        public virtual T OnField<T>(string name, ushort id, bool withHeader = true)
        {
            if (withHeader)
            {
                ushort outId;
                SirenTypeId outDataType;
                int r = OnFieldBegin(name, id, SirenMachine.GetTypeId(typeof(T)), out outId, out outDataType);
                if (r == 0)
                {
                    var obj = OnValue(typeof(T));
                    OnFieldEnd();
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
