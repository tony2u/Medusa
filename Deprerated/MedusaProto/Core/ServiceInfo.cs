// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System.Collections.Generic;
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), @"Core/Network/Message/Service")]
    public enum ServiceType
    {
        Mock = 0,
        TcpClient = 1,
        TcpServer=2,

    };


    [SirenClass(typeof(MedusaCoreTemplate), @"Core/Network/Message/Service")]
    public class ServiceInfo
    {
        [SirenProperty]
        public uint Id { get; set; }

        [SirenProperty]
        public string Host { get; set; }

        [SirenProperty]
        public ushort Port { get; set; }

        [SirenProperty]
        public ServiceType Type { get; set; }
    }


}
