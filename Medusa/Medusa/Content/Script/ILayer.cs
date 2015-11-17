// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "INode.cs"
class ILayer:INode
{
    ILayer(const HeapString name)
    {
        mLayer = @Medusa::ILayer(name);
        @mNode = mLayer;
    }

    ~ILayer()
    {

    }
    Medusa::ILayer@ mLayer;

}