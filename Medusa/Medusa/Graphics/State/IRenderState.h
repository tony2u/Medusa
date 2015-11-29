// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Graphics/GraphicsTypes.h"
#include "Core/Pattern/LazyValue.h"
#include "Core/Pattern/IClone.h"
#include "Core/Pattern/ISharable.h"
#include "Graphics/State/RenderStateType.h"
#include "Core/Pattern/Event.h"
MEDUSA_BEGIN;

class IRenderState :public RTTIObject, public IClone<IRenderState>, public ISharableSingleThread
{
	MEDUSA_DECLARE_RTTI_ROOT;

public:
	Event<void(IRenderState&)> OnChanged;
public:
	IRenderState();
	virtual ~IRenderState();
	virtual RenderStateType Type()const = 0;
	virtual intp HashCode() const { return 0; }
	virtual bool Equals(const IRenderState& state)const;

	virtual void Apply()const = 0;

	virtual IRenderState* Clone()const;
	virtual void CopyFrom(const IRenderState& other){}
	virtual void UpdateWorldState(const IRenderState* selfRenderState, const IRenderState* parentRenderState, const Matrix4& selfWorldMatrix);

protected:
	void OnStateChanged();
};

MEDUSA_END;