// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;

namespace Siren.Attribute
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct | AttributeTargets.Enum)]
    public class SirenClassAttribute : System.Attribute
    {
        public Type Template { get; set; }
        public string Directory { get; set; }
        public SirenGenerateMode Mode { get; set; }
        public string NewHeader { get; set; }
        public string EnumUnderType { get; set; }


        public bool IsEmbeded
        {
            get { return Mode.HasFlag(SirenGenerateMode.Embeded); }
        }

        public SirenClassAttribute(Type template, string directory, SirenGenerateMode mode = SirenGenerateMode.Generate)
        {
            Template = template;
            Directory = directory;
            Mode = mode;

            if (!Mode.HasFlag(SirenGenerateMode.Embeded)&& !Mode.HasFlag(SirenGenerateMode.Generate) &&!Mode.HasFlag(SirenGenerateMode.Suppress))
            {
                Mode |= SirenGenerateMode.Generate;
            }
        }
    }

}
