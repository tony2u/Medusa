// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/Delegate.h"
#include "Graphics/GraphicsTypes.h"
#include "Rendering/RenderingTypes.h"

MEDUSA_BEGIN;
class ShaderUniformInitializer :public Singleton<ShaderUniformInitializer>
{
	friend class Singleton<ShaderUniformInitializer>;
	typedef Delegate<bool(ShaderUniform& uniform)> FuncType;
	typedef Dictionary<StringRef, FuncType> InitializerType;
	typedef Dictionary<RenderingStep, InitializerType*, SafeEnumHashCoder<RenderingStep>> InitializerDict;
protected:
	ShaderUniformInitializer(void);
	~ShaderUniformInitializer(void);
public:
	void Register(RenderingStep step, StringRef name, FuncType func);
	bool Update(RenderingStep step, ShaderUniform& uniform);

private:
	static bool UpdateWorldViewProjectMatrix(ShaderUniform& uniform);
	static bool UpdateViewProjectMatrix(ShaderUniform& uniform);

	static bool UpdateWorldMatrix(ShaderUniform& uniform);
	static bool UpdateWorldViewMatrixIT(ShaderUniform& uniform);

	static bool UpdateModelEyePosition(ShaderUniform& uniform);
	static bool UpdateModelEyeDirection(ShaderUniform& uniform);
	static bool UpdateModelLightDirection(ShaderUniform& uniform);
	static bool UpdateModelLightPosition(ShaderUniform& uniform);

	static bool UpdateWorldEyePosition(ShaderUniform& uniform);
	static bool UpdateWorldEyeDirection(ShaderUniform& uniform);
	static bool UpdateWorldLightDirection(ShaderUniform& uniform);
	static bool UpdateWorldLightPosition(ShaderUniform& uniform);


	static bool UpdateLightAmbient(ShaderUniform& uniform);
	static bool UpdateLightDiffuse(ShaderUniform& uniform);
	static bool UpdateLightSpecular(ShaderUniform& uniform);
	static bool UpdateLightViewProjectMatrix(ShaderUniform& uniform);
	static bool UpdateLightWorldViewProjectMatrix(ShaderUniform& uniform);


	static bool UpdateGlobalAmbient(ShaderUniform& uniform);
	static bool UpdateFogRange(ShaderUniform& uniform);
	static bool UpdateFogColor(ShaderUniform& uniform);


private:
	InitializerDict mInitializerDict;
};
MEDUSA_END;