// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Resource/Effect/Pass/IRenderPass.h"
#include "Graphics/State/ProgramRenderState.h"
#include "Resource/ResourceNames.h"
#include "Core/Collection/Array.h"

MEDUSA_BEGIN;

class BaseProgramRenderPass :public IRenderPass
{
public:
	BaseProgramRenderPass(const FileIdRef& fileId, IShader* vertexShader, IShader* pixelShader, int index = 0);
	virtual ~BaseProgramRenderPass();

	virtual void Apply();
	virtual void Restore();
	virtual bool IsCustom()const { return false; }

	virtual bool Initialize();
	virtual bool Uninitialize();

	uint Program() const { return mProgramState->Program(); }

	bool IsLinked() const { return mProgramState->Program() != 0 && mIsLinked; }
	ShaderUniform* FindUniform(const StringRef& name)const;
	ShaderAttribute* FindAttribute(const StringRef& name)const;
	ShaderAttribute* FindAttributeByIndex(ShaderAttributeIndex index)const;


	IShader* VertexShader() const { return mVertexShader; }
	IShader* PixelShader() const { return mPixelShader; }

	virtual void UpdateShaderUniforms(RenderingStep step);
	virtual void Validate();
	virtual void Invalidate();
private:
	void Link();
	bool TryAddToManagedAttributes(const StringRef& name, ShaderAttribute* val);
protected:
	IShader* mVertexShader = nullptr;
	IShader* mPixelShader = nullptr;
	//render states
	ProgramRenderState* mProgramState = nullptr;

	bool mIsLinked = false;
	Dictionary<HeapString, ShaderUniform*> mUniforms;
	Dictionary<HeapString, ShaderAttribute*> mAttributes;
	Array<ShaderAttribute*, (uint)ShaderAttributeIndex::Count> mManagedAttributes;
};

MEDUSA_END;