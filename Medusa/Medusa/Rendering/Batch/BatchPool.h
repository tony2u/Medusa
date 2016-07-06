// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Object/IdSingleObjectPool.h"
#include "Graphics/GraphicsTypes.h"
#include "Rendering/Batch/IRenderBatch.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Collection/LinkedList.h"

MEDUSA_BEGIN;

struct BatchNewerById
{
	static IRenderBatch* New(RenderingStrategy id);
};

class BatchPool 
	:public Singleton<BatchPool>,
	public IdSingleObjectPool < RenderingStrategy, IRenderBatch*, BatchNewerById, SafeEnumHashCoder >,
	public IInitializable
{
	friend class Singleton < BatchPool > ;
	BatchPool() {}
	~BatchPool();

public:
	using IdSingleObjectPool < RenderingStrategy, IRenderBatch*, BatchNewerById, SafeEnumHashCoder >::Create;
	using IdSingleObjectPool < RenderingStrategy, IRenderBatch*, BatchNewerById, SafeEnumHashCoder >::Recycle;

public:
	virtual bool Initialize()override;
	virtual bool Uninitialize() override;
	void Update(float dt);

	IRenderBatch* Create(IRenderable* node);
	void Recycle(IRenderBatch* batch);
protected:
	LinkedList<IRenderBatch*> mRecycledNodes;
	const static uint mRecycleFrameDuration=1;
};

MEDUSA_END;
