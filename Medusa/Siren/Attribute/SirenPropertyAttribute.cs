// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;

namespace Siren.Attribute
{

    public enum SirenPropertyModifier
    {
        Optional = 0,
        Required = 1,
    };


    [AttributeUsage(AttributeTargets.Property)]
    public class SirenPropertyAttribute : System.Attribute
    {
        public SirenPropertyModifier Modifier { get; set; }
        public string NewName { get; set; }
        public object DefaultValue { get; set; }
        public bool ForceKeyToPtr { get; set; }
        public bool ForceValueToPtr { get; set; }
        public bool AddDictionaryMethods { get; set; }
        public bool SuppressMethod { get; set; }




        public SirenPropertyAttribute(SirenPropertyModifier modifier = SirenPropertyModifier.Required,object defaultValue=null)
        {
            Modifier = modifier;
            DefaultValue = defaultValue;
        }
      
    }
}
