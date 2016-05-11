// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
using System;
using Siren;
using Siren.Attribute;
namespace Medusa
{
    [SirenClass(typeof(MedusaTemplate), "Geometry", SirenGenerateMode.Suppress, NewHeader = "GeometryDefines")]
    public enum AnchorPoint
    {
        LeftTop = 0,
        MiddleTop,
        RightTop,
        LeftCenter,
        MiddleCenter,
        RightCenter,
        LeftBottom,
        MiddleBottom,
        RightBottom
    };

}
