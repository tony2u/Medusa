// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "INode.cs"
class IScene:INode
{
    IScene(const HeapString name)
    {
        @mScene = @Medusa::IScene(name);
        @mNode = @mScene;
    }

    ~IScene()
    {

    }

    Medusa::IScene@ mScene;

}