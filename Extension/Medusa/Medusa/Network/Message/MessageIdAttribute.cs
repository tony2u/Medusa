// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System;

namespace Medusa.Network.Message
{
    [AttributeUsage(AttributeTargets.Class)]
    public class MessageIdAttribute : System.Attribute
    {
        public uint Id { get; set; }

        public MessageIdAttribute(uint id)
        {
            Id = id;
        }
    }

}
