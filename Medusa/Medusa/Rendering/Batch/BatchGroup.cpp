// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BatchGroup.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/Material/IMaterial.h"
#include "Graphics/State/Tree/RenderStateTree.h"
#include "Graphics/State/Tree/RenderStateTreeLeafNode.h"

#ifdef MEDUSA_SAFE_CHECK
#include "Core/Log/Log.h"
#endif

MEDUSA_BEGIN;

const uint BatchGroup::PriorityMaxId = (1 << 8) - 1;
const uint BatchGroup::EffectMaxId = (1 << 8) - 1;
const uint BatchGroup::MaterialMaxId = (1 << 16) - 1;
const uint BatchGroup::StateMaxId = (1 << 26) - 1;
const uint BatchGroup::DrawModeMaxId = (1 << 3) - 1;
const uint BatchGroup::StrategyMaxId = (1 << 3) - 1;

BatchGroup::BatchGroup(IdType id /*= 0*/) :mId(id)
{

}

BatchGroup::IdType BatchGroup::Calculate(uint priority, uint effectId, uint materialId, uint stateTreeNodeId, uint drawMode, uint strategy)
{
#ifdef MEDUSA_SAFE_CHECK
	Log::AssertFormat(priority <= BatchGroup::PriorityMaxId, "PriorityId:{} > MaxId:{}", priority, BatchGroup::PriorityMaxId);
	Log::AssertFormat(effectId <= EffectMaxId, "EffectId:{} > MaxId:{}", effectId, EffectMaxId);
	Log::AssertFormat(materialId <= MaterialMaxId, "MaterialId:{} > MaxId:{}", materialId, MaterialMaxId);
	Log::AssertFormat(stateTreeNodeId <= StateMaxId, "StateId:{} > MaxId:{}", stateTreeNodeId, StateMaxId);
	Log::AssertFormat(drawMode <= DrawModeMaxId, "DrawModeId:{} > MaxId:{}", drawMode, DrawModeMaxId);
	Log::AssertFormat(strategy <= StrategyMaxId, "StrategyId:{} > MaxId:{}", strategy, StrategyMaxId);


#endif

	IdType id = strategy;
	id |= (IdType)drawMode << DrawModeBitStart;
	id |= (IdType)stateTreeNodeId << StateBitStart;
	id |= (IdType)materialId << MaterialBitStart;
	id |= (IdType)effectId << EffectBitStart;
	id |= (IdType)priority << PriorityBitStart;
	return id;
}


BatchGroup::IdType BatchGroup::Calculate(RenderingPriority priority, const IEffect& effect, const IMaterial& material, const RenderStateTreeLeafNode& stateTreeNode, GraphicsDrawMode drawMode, RenderingStrategy strategy)
{
	uintp stateId = RenderStateTree::Instance().CalcuateId(stateTreeNode);
	return Calculate((uint)priority, effect.Id(), material.Id(), (uint)stateId, ToDrawModeId(drawMode), (uint)strategy);
}

void BatchGroup::Update(RenderingPriority priority, const IEffect& effect, const IMaterial& material, const RenderStateTreeLeafNode& stateTreeNode, GraphicsDrawMode drawMode, RenderingStrategy strategy)
{
	uintp stateId = RenderStateTree::Instance().CalcuateId(stateTreeNode);
	mId = Calculate((uint)priority, effect.Id(), material.Id(), (uint)stateId, ToDrawModeId(drawMode), (uint)strategy);
}

void BatchGroup::Update(uint priority, uint effectId, uint materialId, uint stateTreeNodeId, uint drawMode, uint strategy)
{
	mId = Calculate(priority, effectId, materialId, stateTreeNodeId, drawMode, strategy);
}

uint BatchGroup::ToDrawModeId(GraphicsDrawMode drawMode)
{
	/*enum class GraphicsDrawMode
	{
	Points = GL_POINTS,
	Lines = GL_LINES,
	LineLoop = GL_LINE_LOOP,
	LineStrip = GL_LINE_STRIP,
	Triangles = GL_TRIANGLES,
	TriangleStrip = GL_TRIANGLE_STRIP,
	TriangleFan = GL_TRIANGLE_FAN,
	Count = 7
	};*/

	switch (drawMode)
	{
		case GraphicsDrawMode::Points:
			return 0;
		case GraphicsDrawMode::Lines:
			return 1;
		case GraphicsDrawMode::LineLoop:
			return 2;
		case GraphicsDrawMode::LineStrip:
			return 3;
		case GraphicsDrawMode::Triangles:
			return 4;
		case GraphicsDrawMode::TriangleStrip:
			return 5;
		case GraphicsDrawMode::TriangleFan:
			return 6;
		default:
			return 0;
	}
}

MEDUSA_END;