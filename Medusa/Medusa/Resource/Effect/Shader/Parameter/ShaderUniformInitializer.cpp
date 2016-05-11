// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/Shader/Parameter/ShaderUniformInitializer.h"
#include "Resource/Effect/Shader/Parameter/ShaderUniform.h"
#include "Resource/ResourceNames.h"
#include "Rendering/RenderingContext.h"
#include "Rendering/Batch/IRenderBatch.h"
#include "Geometry/Matrix4.h"
#include "Geometry/Matrix3.h"
#include "Resource/Camera/Camera.h"
#include "Resource/Texture/ITexture.h"
#include "Rendering/Batch/IRenderBatch.h"
#include "Resource/RenderTarget/IRenderTarget.h"
#include "Resource/Material/IMaterial.h"
#include "Rendering/RenderEngine.h"
#include "Resource/Light/SpotLight.h"
#include "Core/Log/Log.h"
#include "Graphics/ResolutionAdapter.h"
#include "Resource/Light/LightFactory.h"

MEDUSA_BEGIN;


ShaderUniformInitializer::ShaderUniformInitializer(void)
{
	Register(RenderingStep::Batch, ShaderUniformNames::WorldViewProjectMatrix, UpdateWorldViewProjectMatrix);
	Register(RenderingStep::RenderPass, ShaderUniformNames::ViewProjectMatrix, UpdateViewProjectMatrix);

	Register(RenderingStep::Batch, ShaderUniformNames::WorldMatrix, UpdateWorldMatrix);
	Register(RenderingStep::Batch, ShaderUniformNames::WorldViewMatrixIT, UpdateWorldViewMatrixIT);

}


ShaderUniformInitializer::~ShaderUniformInitializer(void)
{
	SAFE_DELETE_DICTIONARY_VALUE(mInitializerDict);
}

void ShaderUniformInitializer::Register(RenderingStep step, StringRef name, FuncType func)
{

	InitializerType* initializer = mInitializerDict.GetOptional(step, nullptr);
	if (initializer == nullptr)
	{
		initializer = new InitializerType();
		mInitializerDict.Add(step, initializer);
	}

	if (initializer->ContainsKey(name))
	{
		MEDUSA_ASSERT_FAILED("Duplicate register");
	}

	initializer->Add(name, func);
}

bool ShaderUniformInitializer::Update(RenderingStep step, ShaderUniform& uniform)
{
	InitializerType* tempInitializer = mInitializerDict.GetOptional(step, nullptr);
	RETURN_FALSE_IF_NULL(tempInitializer);

	FuncType* func = (tempInitializer)->TryGet(uniform.Name());
	if (func == nullptr)
	{
		return false;
	}

	return (*func)(uniform);
}

bool ShaderUniformInitializer::UpdateWorldViewProjectMatrix(ShaderUniform& uniform)
{
	BaseProgramRenderPass* effect = RenderingContext::Instance().ProgramRenderPass();
	RETURN_FALSE_IF_NULL(effect);

	IRenderBatch* batch = RenderingContext::Instance().Batch();
	const Matrix4& modelMatrix = batch->GetModelMatrix();
	Camera* camera = RenderingContext::Instance().GetCamera();
	if (camera != nullptr)
	{
		const Matrix4& projectionMatrix = camera->ViewProjectionMatrix();
		Matrix4 pmvMatrix = modelMatrix*projectionMatrix;
		uniform.Invalidate();
		uniform.SetMatrix(pmvMatrix);
	}
	else
	{
		uniform.Invalidate();
		uniform.SetMatrix(modelMatrix);
	}

	return true;
}

bool ShaderUniformInitializer::UpdateViewProjectMatrix(ShaderUniform& uniform)
{
	BaseProgramRenderPass* effect = RenderingContext::Instance().ProgramRenderPass();
	RETURN_FALSE_IF_NULL(effect);

	//IRenderBatch* batch=RenderingContext::Instance().GetBatch();
	Camera* camera = RenderingContext::Instance().GetCamera();
	if (camera != nullptr)
	{
		const Matrix4& projectionMatrix = camera->ViewProjectionMatrix();
		uniform.SetMatrix(projectionMatrix);
	}
	else
	{
		Log::Error("No camera for ViewProjectMatrix");
	}

	return true;
}

bool ShaderUniformInitializer::UpdateWorldMatrix(ShaderUniform& uniform)
{
	BaseProgramRenderPass* effect = RenderingContext::Instance().ProgramRenderPass();
	RETURN_FALSE_IF_NULL(effect);

	IRenderBatch* batch = RenderingContext::Instance().Batch();
	const Matrix4& modelMatrix = batch->GetModelMatrix();
	uniform.Invalidate();
	uniform.SetMatrix(modelMatrix);

	return true;
}


bool ShaderUniformInitializer::UpdateWorldViewMatrixIT(ShaderUniform& uniform)
{
	IRenderBatch* batch = RenderingContext::Instance().Batch();
	Matrix4 modelMatrix = batch->GetModelMatrix();
	Camera* camera = RenderingContext::Instance().GetCamera();
	const Matrix4& viewMatrix = camera->ViewMatrix();
	Matrix4 modelViewIT = modelMatrix*viewMatrix;
	modelMatrix.Inverse();
	modelMatrix.Transpose();
	Matrix3 modelViewIT2(modelViewIT);
	uniform.Invalidate();
	uniform.SetMatrix3(modelViewIT2);
	return true;
}


bool ShaderUniformInitializer::UpdateModelEyePosition(ShaderUniform& uniform)
{
	Camera* camera = RenderingContext::Instance().GetCamera();

	Point3F pos = camera->EyePosition();
	IRenderBatch* batch = RenderingContext::Instance().Batch();
	Matrix4 modelMatrix = batch->GetModelMatrix();
	modelMatrix.Inverse();
	pos = modelMatrix.Transform(pos);
	uniform.Invalidate();
	uniform.Set(pos);

	return true;
}

bool ShaderUniformInitializer::UpdateModelEyeDirection(ShaderUniform& uniform)
{
	Camera* camera = RenderingContext::Instance().GetCamera();
	Point3F direction = camera->EyeDirection();
	IRenderBatch* batch = RenderingContext::Instance().Batch();
	Matrix4 modelMatrix = batch->GetModelMatrix();
	modelMatrix.Inverse();
	direction = modelMatrix.TransformVector(direction);
	direction.Normalize();
	uniform.Invalidate();
	uniform.Set(direction);
	return true;
}


bool ShaderUniformInitializer::UpdateModelLightDirection(ShaderUniform& uniform)
{
	ILight* light = LightFactory::Instance().GetCurrentLight();
	if (light != nullptr)
	{
		IRenderBatch* batch = RenderingContext::Instance().Batch();
		Matrix4 modelMatrix = batch->GetModelMatrix();
		modelMatrix.Inverse();
		Point3F direction = light->Direction();
		direction = modelMatrix.TransformVector(direction);
		direction.Normalize();
		uniform.Invalidate();
		uniform.Set(direction);
		return true;
	}
	else
	{
		MEDUSA_ASSERT_FAILED("No light for ModelLightDirection");
		return false;
	}
}


bool ShaderUniformInitializer::UpdateModelLightPosition(ShaderUniform& uniform)
{
	ILight* light = LightFactory::Instance().GetCurrentLight();
	if (light != nullptr)
	{
		IRenderBatch* batch = RenderingContext::Instance().Batch();
		Matrix4 modelMatrix = batch->GetModelMatrix();
		modelMatrix.Inverse();
		Point3F position = light->Position();
		position = modelMatrix.Transform(position);
		uniform.Invalidate();
		uniform.Set(position);
		return true;
	}
	else
	{
		MEDUSA_ASSERT_FAILED("No light for ModelLightPosition");
		return false;
	}
}


bool ShaderUniformInitializer::UpdateWorldEyePosition(ShaderUniform& uniform)
{
	Camera* camera = RenderingContext::Instance().GetCamera();
	Point3F pos = camera->EyePosition();
	uniform.Invalidate();
	uniform.Set(pos);

	return true;
}

bool ShaderUniformInitializer::UpdateWorldEyeDirection(ShaderUniform& uniform)
{
	Camera* camera = RenderingContext::Instance().GetCamera();
	Point3F direction = camera->EyeDirection();
	uniform.Invalidate();
	uniform.Set(direction);
	return true;
}


bool ShaderUniformInitializer::UpdateWorldLightDirection(ShaderUniform& uniform)
{
	ILight* light = LightFactory::Instance().GetCurrentLight();
	if (light != nullptr)
	{
		//IRenderBatch* batch=RenderingContext::Instance().GetBatch();
		Point3F direction = light->Direction();
		uniform.Invalidate();
		uniform.Set(direction);
		return true;
	}
	else
	{
		MEDUSA_ASSERT_FAILED("No light for WorldLightDirection");
		//lightDirectionUniform->Set(Point3F(0.f,0.f,-1.f));	//default light
		return false;
	}
}


bool ShaderUniformInitializer::UpdateWorldLightPosition(ShaderUniform& uniform)
{
	ILight* light = LightFactory::Instance().GetCurrentLight();
	if (light != nullptr)
	{
		//IRenderBatch* batch=RenderingContext::Instance().GetBatch();
		Point3F position = light->Position();
		uniform.Invalidate();
		uniform.Set(position);
		return true;
	}
	else
	{
		MEDUSA_ASSERT_FAILED("No light for WorldLightPosition");
		return false;
	}
}

bool ShaderUniformInitializer::UpdateLightAmbient(ShaderUniform& uniform)
{
	ILight* light = LightFactory::Instance().GetCurrentLight();
	if (light != nullptr)
	{
		uniform.Invalidate();
		uniform.Set(light->AmbientColor());
		return true;
	}
	else
	{
		MEDUSA_ASSERT_FAILED("No light for LightAmbient");
		return false;
	}
}


bool ShaderUniformInitializer::UpdateLightDiffuse(ShaderUniform& uniform)
{
	ILight* light = LightFactory::Instance().GetCurrentLight();
	if (light != nullptr)
	{
		uniform.Invalidate();
		uniform.Set(light->DiffuseColor());
		return true;
	}
	else
	{
		MEDUSA_ASSERT_FAILED("No light for LightDiffuse");
		return false;
	}
}

bool ShaderUniformInitializer::UpdateLightSpecular(ShaderUniform& uniform)
{
	ILight* light = LightFactory::Instance().GetCurrentLight();
	if (light != nullptr)
	{
		uniform.Invalidate();
		uniform.Set(light->SpecularColor());
		return true;
	}
	else
	{
		MEDUSA_ASSERT_FAILED("No light for LightSpecular");
		return false;
	}
}

bool ShaderUniformInitializer::UpdateLightViewProjectMatrix(ShaderUniform& uniform)
{
	ILight* light = LightFactory::Instance().GetCurrentLight();

	if (light != nullptr&&light->LightType() == GraphicsLightType::Spot)
	{
		SpotLight* spotLight = (SpotLight*)light;
		uniform.Invalidate();
		const Matrix4& matrix = spotLight->ViewProjectMatrix();
		uniform.SetMatrix(matrix);
		return true;
	}
	else
	{
		MEDUSA_ASSERT_FAILED("No spot light for LightViewProjectMatrix");
		return false;
	}

}

bool ShaderUniformInitializer::UpdateLightWorldViewProjectMatrix(ShaderUniform& uniform)
{
	ILight* light = LightFactory::Instance().GetCurrentLight();
	if (light != nullptr&&light->LightType() == GraphicsLightType::Spot)
	{
		IRenderBatch* batch = RenderingContext::Instance().Batch();
		Matrix4 modelMatrix = batch->GetModelMatrix();

		SpotLight* spotLight = (SpotLight*)light;
		uniform.Invalidate();
		const Matrix4& matrix = spotLight->ViewProjectMatrix();
		modelMatrix *= matrix;
		uniform.SetMatrix(modelMatrix);
		return true;
	}
	else
	{
		MEDUSA_ASSERT_FAILED("No spot light for LightViewProjectMatrix");
		return false;
	}

}

bool ShaderUniformInitializer::UpdateGlobalAmbient(ShaderUniform& uniform)
{
	return true;
}

bool ShaderUniformInitializer::UpdateFogRange(ShaderUniform& uniform)
{
	return true;
}

bool ShaderUniformInitializer::UpdateFogColor(ShaderUniform& uniform)
{
	return true;
}

MEDUSA_END;