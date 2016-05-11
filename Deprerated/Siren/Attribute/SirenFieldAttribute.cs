// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;

namespace Siren.Attribute
{

    public enum SirenFieldModifier
    {
        Optional = 0,
        Required = 1,
    };


    [AttributeUsage(AttributeTargets.Property)]
    public class SirenFieldAttribute : System.Attribute
    {
        public SirenFieldModifier Modifier { get; set; }
        public string NewName { get; set; }
        public object DefaultValue { get; set; }
        public bool ForceKeyToPtr { get; set; }
        public bool ForceValueToPtr { get; set; }
        public bool AddDictionaryMethods { get; set; }
        public bool SuppressMethod { get; set; }




        public SirenFieldAttribute(SirenFieldModifier modifier = SirenFieldModifier.Required,object defaultValue=null)
        {
            Modifier = modifier;
            DefaultValue = defaultValue;
        }
      
    }
}
