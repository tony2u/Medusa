// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/Render/Render.h"
#include "Core/Pattern/Singleton.h"

MEDUSA_BEGIN;
/*
nodes->get model->get meshes->pack to batch mesh

render tree for opaque objects
render list from transparent objects


Changes:
Node:	priority	=>	remove & add
		strategy	=>	remove & add
		matrixVersion		=>	update
		remove & add node	=> remove & add

Model:	matrixVersion		=>	update
		remove & add mesh			=> remove & add
Mesh:	matrixVersion		=>	update
		effect			=>	remove & add
		material		=>	remove & add
		version			=>	update
		vertexCount		=>	update
		indexCount		=>	update
		components		=>	update

Culling: remove & add

How can model and mesh changes be found?
1.Merge model and mesh to node
2.callback
3,loop to check

*/


class RenderEngine :public Singleton<RenderEngine>
{
	friend class Singleton<RenderEngine>;
	RenderEngine();
	~RenderEngine();
public:
	bool InitializeBeforeWindow(bool disableThreading = false);
	bool UninitializeBeforeWindow();

	bool Initialize();

	bool InitializeAfterWindow(bool disableThreading = false);
	bool UninitializeAfterWindow();

	void Clear();
	void Draw(float dt);
	void Update(float dt);

	bool IsFrameDirty() const { return mIsFrameDirty; }
	void SetFrameDirty() { mIsFrameDirty = true; }
protected:
	bool mIsFrameDirty;
	
};


MEDUSA_END;