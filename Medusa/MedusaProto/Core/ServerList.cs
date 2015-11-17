// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using Siren;
using Siren.Attribute;

namespace Medusa.Core
{
    [SirenClass(typeof(MedusaCoreTemplate), "Core/Config")]
    public enum ServerUsageType
    {
        None = 0,
        Login = 1,
        Game = 2
    };

    [SirenClass(typeof(MedusaCoreTemplate), "Core/Config")]
    public class ServerUsageItem
    {
        [SirenProperty]
        public ServerUsageType Usage { get; set; }
        [SirenProperty]
        public uint ServerId { get; set; }

    }

    [SirenClass(typeof(MedusaCoreTemplate), "Core/Config")]
    public class ServerListItem
    {
        [SirenProperty]
        public List<ServerUsageItem> Usages { get; set; }
        [SirenProperty]
        public uint Id { get; set; }

    }

    [SirenClass(typeof(MedusaCoreTemplate), "Core/Config", SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare | SirenGenerateMode.SuppressCopy)]
    public class ServerList
    {
        [SirenProperty]
        public Dictionary<uint, ServerListItem> Items { get; set; }

    }
}
