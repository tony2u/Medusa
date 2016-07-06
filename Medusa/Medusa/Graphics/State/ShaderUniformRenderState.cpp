// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/ShaderUniformRenderState.h"
#include "Graphics/Render/Render.h"
#include "Resource/Effect/Shader/Parameter/ShaderUniform.h"
#include "Rendering/RenderingContext.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/ResourceNames.h"

MEDUSA_BEGIN;

ShaderUniformRenderState::ShaderUniformRenderState()
{

}

ShaderUniformRenderState::~ShaderUniformRenderState()
{
	SAFE_DELETE_DICTIONARY_VALUE(mItems);
}

void ShaderUniformRenderState::Apply()const
{
	auto pass = RenderingContext::Instance().ProgramRenderPass();

	for (auto keyValue : mItems)
	{
		auto* uniform = keyValue.Value;
		uniform->Apply(*pass);
	}
}

Share<ShaderUniformRenderState> ShaderUniformRenderState::Clone() const
{
	Share<ShaderUniformRenderState> state = new ShaderUniformRenderState();
	state->CopyFrom(*this);
	return state;
}

void ShaderUniformRenderState::CopyFrom(const IRenderState& other)
{
	MEDUSA_ASSERT(other.Type() == Type(), "Cannot copy render state with different type");
	ShaderUniformRenderState& val = (ShaderUniformRenderState&)other;
	SAFE_DELETE_DICTIONARY_VALUE(mItems);
	for (auto keyValue : val.mItems)
	{
		auto* uniform = keyValue.Value;
		auto* uniformCopy= uniform->Clone();
		Add(uniformCopy);
	}

}

bool ShaderUniformRenderState::Equals(const IRenderState& state) const
{
	RETURN_FALSE_IF_FALSE(IRenderState::Equals(state));
	const ShaderUniformRenderState& val = (const ShaderUniformRenderState&)state;
	RETURN_FALSE_IF_FALSE(mItems.Count() == val.mItems.Count());
	for (auto keyValue : val.mItems)
	{
		auto* uniform = keyValue.Value;
		auto* curUniform = Find(uniform->Name());
		RETURN_FALSE_IF_NULL(curUniform);
		RETURN_FALSE_IF_NOT_EQUAL(*uniform, *curUniform);
	}

	return true;
}

void ShaderUniformRenderState::Add(ShaderUniformValue* uniform)
{
	mItems.Add(uniform->Name(), uniform);
}

ShaderUniformValue* ShaderUniformRenderState::Find(StringRef name) const
{
	return mItems.GetOptional(name, nullptr);
}

ShaderUniformValue* ShaderUniformRenderState::FindOrCreate(StringRef name)
{
	auto* val = Find(name);
	if (val!=nullptr)
	{
		return val;
	}

	val = new ShaderUniformValue(name);
	Add(val);
	return val;
}

intp ShaderUniformRenderState::HashCode() const
{
	intp val = 0;
	for (auto keyValue : mItems)
	{
		auto* uniform = keyValue.Value;
		val ^= uniform->HashCode();
	}
	return val;
}

MEDUSA_END;