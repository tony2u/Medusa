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
class ShaderConstantInitializer:public Singleton<ShaderConstantInitializer>
{
	friend class Singleton<ShaderConstantInitializer>;
	typedef Delegate<bool(ShaderConstant& uniform)> FuncType;
	typedef Dictionary<StringRef,FuncType> InitializerType;
	typedef Dictionary<RenderingStep, InitializerType*, SafeEnumHashCoder<RenderingStep>> InitializerDict;
protected:
	ShaderConstantInitializer(void);
	~ShaderConstantInitializer(void);
public:
	void Register(RenderingStep step,StringRef name,FuncType func);
	bool Update(RenderingStep step,ShaderConstant& uniform);

private:
	static bool UpdateWorldViewProjectMatrix(ShaderConstant& uniform);
	static bool UpdateViewProjectMatrix(ShaderConstant& uniform);

	static bool UpdateWorldMatrix(ShaderConstant& uniform);
	static bool UpdateWorldViewMatrixIT(ShaderConstant& uniform);

	static bool UpdateModelEyePosition(ShaderConstant& uniform);
	static bool UpdateModelEyeDirection(ShaderConstant& uniform);
	static bool UpdateModelLightDirection(ShaderConstant& uniform);
	static bool UpdateModelLightPosition(ShaderConstant& uniform);

	static bool UpdateWorldEyePosition(ShaderConstant& uniform);
	static bool UpdateWorldEyeDirection(ShaderConstant& uniform);
	static bool UpdateWorldLightDirection(ShaderConstant& uniform);
	static bool UpdateWorldLightPosition(ShaderConstant& uniform);


	static bool UpdateLightAmbient(ShaderConstant& uniform);
	static bool UpdateLightDiffuse(ShaderConstant& uniform);
	static bool UpdateLightSpecular(ShaderConstant& uniform);
	static bool UpdateLightViewProjectMatrix(ShaderConstant& uniform);
	static bool UpdateLightWorldViewProjectMatrix(ShaderConstant& uniform);





	static bool UpdateGlobalAmbient(ShaderConstant& uniform);
	static bool UpdateFogRange(ShaderConstant& uniform);
	static bool UpdateFogColor(ShaderConstant& uniform);








private:
	InitializerDict mInitializerDict;
};
MEDUSA_END;