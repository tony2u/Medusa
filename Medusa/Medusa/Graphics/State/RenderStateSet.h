// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Graphics/GraphicsTypes.h"
#include "Core/Pattern/LazyStrongPtr.h"
#include "Core/Pattern/LazyValue.h"
#include "Graphics/State/RenderStateType.h"
#include "Core/Pattern/Event.h"
#include "Core/Collection/Array.h"
#include "Core/Pattern/INonCopyable.h"
#include "Graphics/State/IRenderState.h"
#include "Core/Pattern/Share.h"
#include "Graphics/State/ScissorRenderState.h"
#include "Graphics/State/BlendRenderState.h"

MEDUSA_BEGIN;


class RenderStateSet:public INonCopyable
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
	Share<IRenderState> GetState(RenderStateType type)const;
	Share<IRenderState> AllocState(RenderStateType type);
	Share<IRenderState> RemoveState(RenderStateType type);

	template<typename T>
	Share<T> GetState()const
	{
		return GetState(T::GetTypeIdStatic()).CastPtr<T>();
	}

	template<typename T>
	Share<T> AllocState()
	{
		return AllocState(T::GetTypeIdStatic()).CastPtr<T>();
	}

	template<typename T>
	Share<T> RemoveState()
	{
		return RemoveState(T::GetTypeIdStatic()).CastPtr<T>();
	}
public:

	void UpdateFromParent(const RenderStateSet& selfRenderState, const RenderStateSet& parentRenderState, const Matrix4& selfWorldMatrix, RenderStateType flag);
	void UpdateFromSelf(const RenderStateSet& selfRenderState, const Matrix4& selfWorldMatrix, RenderStateType flag);
public:
	//blend
	bool IsBlendEnabled()const;
	void EnableBlend(bool val);
	void SetBlendFunc(GraphicsBlendSrcFunc srcFunc, GraphicsBlendDestFunc destFunc);
	Share<BlendRenderState> RemoveBlend();

	//scissor
	bool HasScissorBox()const;
	bool IsScissorEnabled()const;
	void SetScissorBox(const Rect2F& val);
	void EnableScissor(bool val);
	Share<ScissorRenderState> RemoveScissor();

	const Rect2F* TryGetScissorBox() const;
	const Rect2F& GetScissorBoxOrEmpty() const;

	//rasterizer

	//shader uniform
	ShaderUniformValue* FindOrCreateUniform(StringRef name);
protected:
	void OnStateChangedEvent(IRenderState& state);
protected:
	Array<Share<IRenderState>, (uint32)RenderStateType::Count> mItems;

};

MEDUSA_END;