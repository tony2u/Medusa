// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using System.Collections.Generic;
using Medusa.Core;
using Siren;
using Siren.Attribute;

namespace Medusa.Game
{
    [SirenClass(typeof(MedusaTemplate), @"Game/Network")]
    public enum ServerStatus
    {
        OK = 0,
        Maintain = 1,
        Error = 2
    };

    [SirenClass(typeof(MedusaTemplate), @"Game/Network")]
    public class ServerConfigItem
    {
        [SirenProperty]
        public uint Id { get; set; }

        [SirenProperty]
        public string Name { get; set; }

        [SirenProperty]
        public string Description { get; set; }

        [SirenProperty]
        public ServerStatus Status { get; set; }

        [SirenProperty]
        public Dictionary<uint, ServiceInfo> Services { get; set; }
    }


    [SirenClass(typeof(MedusaTemplate), "Game/Network", SirenGenerateMode.SuppressCompare | SirenGenerateMode.SuppressCopy)]
    public class ServerConfig
    {
        [SirenProperty]
        public Dictionary<uint, ServerConfigItem> Items { get; set; }
    }
}
