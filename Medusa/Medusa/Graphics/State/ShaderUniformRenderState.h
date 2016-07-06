// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/State/IRenderState.h"
#include "Resource/Effect/Shader/Parameter/ShaderUniformValue.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

class ShaderUniformRenderState :public IRenderState
{
	MEDUSA_RTTI(ShaderUniformRenderState,IRenderState);
public:
	ShaderUniformRenderState();
	virtual ~ShaderUniformRenderState();
	virtual void Apply()const override;

	Share<ShaderUniformRenderState> Clone()const;
	virtual void CopyFrom(const IRenderState& other)override;

	virtual bool Equals(const IRenderState& state)const override;
	virtual RenderStateType Type()const override { return GetTypeIdStatic(); }
	static RenderStateType GetTypeIdStatic() { return RenderStateType::ShaderUniform; }

	void Add(ShaderUniformValue* uniform);
	ShaderUniformValue* Find(StringRef name)const;
	ShaderUniformValue* FindOrCreate(StringRef name);

	virtual intp HashCode() const override;

protected:
	Dictionary<StringRef, ShaderUniformValue*> mItems;
};


MEDUSA_END;