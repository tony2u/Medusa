// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System.Collections.Generic;
using Siren;
using Siren.Attribute;

namespace Medusa.Game
{
    [SirenClass(typeof(MedusaTemplate), @"Game/Drop", SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare)]
    public class DropPoolItem
    {
        [SirenProperty]
        public uint Id { get; set; }    //often be item Id,and could be inner drop id too

        [SirenProperty(SirenPropertyModifier.Optional, 0)]
        public int Type { get; set; }  //type ==-1 means another drop id,then Count means times to execuate dropping

        [SirenProperty(SirenPropertyModifier.Optional, 1)]
        public int Count { get; set; }

    }

    [SirenClass(typeof(MedusaTemplate), @"Game/Drop",SirenGenerateMode.Embeded)]
    public class DropPoolRandomItem : DropPoolItem
    {
        [SirenProperty(SirenPropertyModifier.Optional, 1)]
        public uint Probability { get; set; }  
    }


    [SirenClass(typeof(MedusaTemplate), @"Game/Drop")]
    public class DropPoolGroup
    {
        [SirenProperty(SirenPropertyModifier.Optional)]
        public bool PreventDuplicate { get; set; }

        [SirenProperty(SirenPropertyModifier.Optional,1)]
        public uint MinTimes { get; set; } 

        [SirenProperty(SirenPropertyModifier.Optional, 1)]
        public uint MaxTimes { get; set; } 

        [SirenProperty]
        public List<DropPoolRandomItem> Items { get; set; }

    }

    [SirenClass(typeof(MedusaTemplate), @"Game/Drop")]
    public class DropPoolConditionItem
    {
        [SirenProperty]
        public uint PredicateId { get; set; }   //serach predicate in another table, then invoke it with void* passed in param

        [SirenProperty]
        public DropPoolItem Item { get; set; } 


    }

    [SirenClass(typeof(MedusaTemplate), @"Game/Drop", SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare)]
    public class DropPoolItemLimit
    {
        [SirenProperty]
        public uint ItemId { get; set; }  

        [SirenProperty(SirenPropertyModifier.Optional, 0)]
        public int Type { get; set; } 

        [SirenProperty]
        public int MinCount { get; set; } //auto add when not enough

        [SirenProperty]
        public int MaxCount { get; set; } //exceed will be ignored, when 0, means no drop

    }


    [SirenClass(typeof(MedusaTemplate), @"Game/Drop", SirenGenerateMode.Embeded)]
    public class DropPool
    {
        [SirenProperty(SirenPropertyModifier.Optional)]
        public List<DropPoolItem> FixedItems { get; set; }

        [SirenProperty(SirenPropertyModifier.Optional)]
        public List<DropPoolGroup> RandomGroups { get; set; }

        
        [SirenProperty(SirenPropertyModifier.Optional)]
        public List<DropPoolConditionItem> ConditionItems { get; set; }

        //global limit
        [SirenProperty(SirenPropertyModifier.Optional)]
        public List<DropPoolItemLimit> ItemLimits { get; set; }
    }

    [SirenClass(typeof(MedusaTemplate), @"Game/Drop", SirenGenerateMode.SirenConfig | SirenGenerateMode.Embeded | SirenGenerateMode.SuppressCompare | SirenGenerateMode.SuppressCopy)]
    public class DropPoolConfig
    {
        [SirenProperty(AddDictionaryMethods = true)]
        public Dictionary<uint, DropPool> Items { get; set; }

    }
}
