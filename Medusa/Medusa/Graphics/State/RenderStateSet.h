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

MEDUSA_BEGIN;


class RenderStateSet
{
public:
	RenderStateSet();
	virtual ~RenderStateSet(void);
	RenderStateSet& operator=(const RenderStateSet& val);

	Event<void(IRenderState&)> OnStateChanged;
	Event<void(RenderStateType)> OnStateRemoved;

public:
	void Apply()const;
	void Restore()const;

	bool Equals(const RenderStateSet& states)const;

	IRenderState* GetState(RenderStateType type)const;
	bool TryGetState(RenderStateType type, IRenderState*& outState)const;
public:
	//blend
	bool IsBlendEnabled()const;
	bool EnableBlend(bool val);
	bool SetBlendFunc(GraphicsBlendSrcFunc srcFunc, GraphicsBlendDestFunc destFunc);
	bool RemoveBlend();
	BlendRenderState* BlendState();

	//scissor
	bool HasScissorBox()const;
	bool IsScissorEnabled()const;
	bool SetScissorBox(const Rect2F& val);
	bool EnableScissor(bool val);
	bool RemoveScissor();

	const Rect2F* TryGetScissorBox() const;
	const Rect2F& GetScissorBoxOrEmpty() const;

	void UpdateFromParent(const RenderStateSet& selfRenderState, const RenderStateSet& parentRenderState, const Matrix& selfWorldMatrix, RenderStateType flag);
	void UpdateFromSelf( const RenderStateSet& selfRenderState, const Matrix& selfWorldMatrix, RenderStateType flag);
protected:
	void OnStateChangedEvent(IRenderState& state);
protected:
	LazyStrongPtr<BlendRenderState, DefaultPointerReleaser<BlendRenderState> > mBlendState;	//nullptr means never initialized
	LazyStrongPtr<ScissorRenderState, DefaultPointerReleaser<ScissorRenderState>> mScissorState;	//nullptr means never initialized

};

MEDUSA_END;