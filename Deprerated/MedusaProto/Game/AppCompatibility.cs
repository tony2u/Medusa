// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

using Siren.Attribute;

namespace Medusa.Game
{
    [SirenClass(typeof(MedusaTemplate), @"Game/Compat")]
    public enum AppInitializeOperation
    {
        None = 0,
        RemoveAllCache = 1
    };

    [SirenClass(typeof(MedusaTemplate), @"Game/Compat")]
    public class AppCompatibility
    {
        [SirenProperty]
        public uint Version { get; set; }
        [SirenProperty]
        public AppInitializeOperation Operation { get; set; }
    }
}
