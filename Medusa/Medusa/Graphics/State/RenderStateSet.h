// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Graphics/GraphicsTypes.h"
#include "Core/Pattern/Ptr/LazyStrongPtr.h"
#include "Core/Pattern/LazyValue.h"
#include "Graphics/State/RenderStateType.h"
#include "Core/Pattern/Event.h"
#include "Core/Collection/Array.h"
#include "Core/Pattern/INonCopyable.h"

MEDUSA_BEGIN;


class RenderStateSet:public INonCopyable<RenderStateSet>
{
public:
	RenderStateSet();
	virtual ~RenderStateSet(void);

	Event<void(IRenderState&)> OnStateChanged;
	Event<void(IRenderState&)> OnStateAdded;
	Event<void(RenderStateType)> OnStateRemoved;

public:
	void Apply()const;
	void Restore()const;

	bool Equals(const RenderStateSet& states)const;
public:
	IRenderState* GetState(RenderStateType type)const;
	IRenderState* AllocState(RenderStateType type);
	IRenderState* RemoveState(RenderStateType type);

	template<typename T>
	T* GetState()const
	{
		return (T*)GetState(T::GetTypeIdStatic());
	}

	template<typename T>
	T* AllocState()
	{
		return (T*)AllocState(T::GetTypeIdStatic());
	}

	template<typename T>
	T* RemoveState()
	{
		return (T*)RemoveState(T::GetTypeIdStatic());
	}
public:

	void UpdateFromParent(const RenderStateSet& selfRenderState, const RenderStateSet& parentRenderState, const Matrix4& selfWorldMatrix, RenderStateType flag);
	void UpdateFromSelf(const RenderStateSet& selfRenderState, const Matrix4& selfWorldMatrix, RenderStateType flag);
public:
	//blend
	bool IsBlendEnabled()const;
	void EnableBlend(bool val);
	void SetBlendFunc(GraphicsBlendSrcFunc srcFunc, GraphicsBlendDestFunc destFunc);
	BlendRenderState* RemoveBlend();

	//scissor
	bool HasScissorBox()const;
	bool IsScissorEnabled()const;
	void SetScissorBox(const Rect2F& val);
	void EnableScissor(bool val);
	ScissorRenderState* RemoveScissor();

	const Rect2F* TryGetScissorBox() const;
	const Rect2F& GetScissorBoxOrEmpty() const;

	//rasterizer

protected:
	void OnStateChangedEvent(IRenderState& state);
protected:
	Array<IRenderState*, (uint32)RenderStateType::Count> mItems;

};

MEDUSA_END;