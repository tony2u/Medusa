// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), "Core/Config")]
    public enum ServerStatus
    {
        OK = 0,
        Maintain = 1,
        Error = 2
    };

    [SirenClass(typeof(MedusaCoreTemplate), "Core/Config")]
    public enum ServerType
    {
        Tcp = 0,
        Mock = 1
    };

    [SirenClass(typeof(MedusaCoreTemplate), "Core/Config")]
    public class ServerConfigItem
    {
        [SirenProperty]
        public uint Id { get; set; }
        [SirenProperty]
        public string Address { get; set; }
        [SirenProperty]
        public uint Port { get; set; }

        [SirenProperty]
        public ServerStatus Status { get; set; }
        [SirenProperty]
        public ServerType Type { get; set; }
    }

    [SirenClass(typeof(MedusaCoreTemplate), "Core/Config", SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare | SirenGenerateMode.SuppressCopy)]
    public class ServerConfig
    {
        [SirenProperty]
        public Dictionary<uint,ServerConfigItem> Items { get; set; }
    }
}
