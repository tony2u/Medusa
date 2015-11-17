// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Graphics/GraphicsTypes.h"
#include "Rendering/RenderingTypes.h"

MEDUSA_BEGIN;


class BatchGroup
{
public:
	constexpr static uint PriorityBitSize = 8;	//<=32,5bit,id start from 0
	constexpr static uint EffectBitSize = 8;	//id start from 1
	constexpr static uint MaterialBitSize = 16;	//id start from 1
	constexpr static uint StateBitSize = 26;	//id start from 1
	constexpr static uint DrawModeBitSize = 3;	//Count=7,3bit,id start from 0
	constexpr static uint StrategyBitSize = 3;	//Count=7,3bit,id start from 0

	const static uint PriorityMaxId;
	const static uint EffectMaxId;
	const static uint MaterialMaxId;
	const static uint StateMaxId;
	const static uint DrawModeMaxId;
	const static uint StrategyMaxId;

	constexpr static uint StrategyBitStart = 0;
	constexpr static uint DrawModeBitStart = StrategyBitSize;
	constexpr static uint StateBitStart = DrawModeBitStart + DrawModeBitSize;
	constexpr static uint MaterialBitStart = StateBitStart + StateBitSize;
	constexpr static uint EffectBitStart = MaterialBitStart + MaterialBitSize;
	constexpr static uint PriorityBitStart = EffectBitStart + EffectBitSize;


	typedef uint64 IdType;
public:
	BatchGroup(IdType id=0);

	operator IdType()const { return mId; }
	BatchGroup& operator=(IdType v) { mId = v; return *this; }
public:
	static IdType Calculate(uint priority, uint effectId, uint materialId, uint stateTreeNodeId, uint drawMode, uint strategy);
	static IdType Calculate(RenderingPriority priority, const IEffect& effect, const IMaterial& material, const RenderStateTreeLeafNode& stateTreeNode, GraphicsDrawMode drawMode, RenderingStrategy strategy);

	void Update(uint priority, uint effectId, uint materialId, uint stateTreeNodeId, uint drawMode, uint strategy);
	void Update(RenderingPriority priority, const IEffect& effect, const IMaterial& material, const RenderStateTreeLeafNode& stateTreeNode, GraphicsDrawMode drawMode, RenderingStrategy strategy);
private:
	static uint ToDrawModeId(GraphicsDrawMode drawMode);
protected:
	IdType mId;
};

MEDUSA_END;
