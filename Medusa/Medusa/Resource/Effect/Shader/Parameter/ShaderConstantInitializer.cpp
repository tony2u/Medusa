// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/Shader/Parameter/ShaderConstantInitializer.h"
#include "Resource/Effect/Shader/Parameter/ShaderConstant.h"
#include "Resource/ResourceNames.h"
#include "Rendering/RenderingContext.h"
#include "Rendering/Batch/IRenderBatch.h"
#include "Core/Geometry/Matrix.h"
#include "Core/Geometry/Matrix3.h"
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


ShaderConstantInitializer::ShaderConstantInitializer( void )
{
	Register(RenderingStep::Batch,ShaderConstantNames::WorldViewProjectMatrix,UpdateWorldViewProjectMatrix);
	Register(RenderingStep::RenderPass,ShaderConstantNames::ViewProjectMatrix,UpdateViewProjectMatrix);

	Register(RenderingStep::Batch,ShaderConstantNames::WorldMatrix,UpdateWorldMatrix);
	Register(RenderingStep::Batch,ShaderConstantNames::WorldViewMatrixIT,UpdateWorldViewMatrixIT);

}


ShaderConstantInitializer::~ShaderConstantInitializer( void )
{
	SAFE_DELETE_DICTIONARY_VALUE(mInitializerDict);
}

void ShaderConstantInitializer::Register(RenderingStep step,StringRef name,FuncType func )
{
	
	InitializerType* initializer= mInitializerDict.TryGetValueWithFailed(step,nullptr);
	if (initializer==nullptr)
	{
		initializer=new InitializerType();
		mInitializerDict.Add(step,initializer);
	}

	if(initializer->ContainsKey(name))
	{
		MEDUSA_ASSERT_FAILED("Duplicate register");
	}

	initializer->Add(name,func);
}

bool ShaderConstantInitializer::Update(RenderingStep step, ShaderConstant& uniform)
{
	InitializerType* tempInitializer= mInitializerDict.TryGetValueWithFailed(step,nullptr);
	RETURN_FALSE_IF_NULL(tempInitializer);

	FuncType* func=(tempInitializer)->TryGetValue(uniform.Name());
	if (func==nullptr)
	{
		return false;
	}
	
	return (*func)(uniform);
}

bool ShaderConstantInitializer::UpdateWorldViewProjectMatrix( ShaderConstant& uniform)
{
	BaseProgramRenderPass* effect= RenderingContext::Instance().ProgramRenderPass();
	RETURN_FALSE_IF_NULL(effect);

	IRenderBatch* batch=RenderingContext::Instance().Batch();
	const Matrix& modelMatrix=batch->GetModelMatrix();
	Camera* camera= RenderingContext::Instance().GetCamera();
	if (camera!=nullptr)
	{
		const Matrix& projectionMatrix= camera->ViewProjectionMatrix();
		Matrix pmvMatrix=modelMatrix*projectionMatrix;
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

bool ShaderConstantInitializer::UpdateViewProjectMatrix( ShaderConstant& uniform)
{
	BaseProgramRenderPass* effect= RenderingContext::Instance().ProgramRenderPass();
	RETURN_FALSE_IF_NULL(effect);

	//IRenderBatch* batch=RenderingContext::Instance().GetBatch();
	Camera* camera= RenderingContext::Instance().GetCamera();
	if (camera!=nullptr)
	{
		const Matrix& projectionMatrix= camera->ViewProjectionMatrix();
		uniform.SetMatrix(projectionMatrix);
	}
	else
	{
		Log::Error("No camera for ViewProjectMatrix");
	}

	return true;
}

bool ShaderConstantInitializer::UpdateWorldMatrix( ShaderConstant& uniform )
{
	BaseProgramRenderPass* effect= RenderingContext::Instance().ProgramRenderPass();
	RETURN_FALSE_IF_NULL(effect);

	IRenderBatch* batch=RenderingContext::Instance().Batch();
	const Matrix& modelMatrix=batch->GetModelMatrix();
	uniform.Invalidate();
	uniform.SetMatrix(modelMatrix);

	return true;
}


bool ShaderConstantInitializer::UpdateWorldViewMatrixIT( ShaderConstant& uniform)
{
	IRenderBatch* batch=RenderingContext::Instance().Batch();
	Matrix modelMatrix=batch->GetModelMatrix();
	Camera* camera= RenderingContext::Instance().GetCamera();
	const Matrix& viewMatrix=camera->ViewMatrix();
	Matrix modelViewIT=modelMatrix*viewMatrix;
	modelMatrix.Inverse();
	modelMatrix.Transpose();
	Matrix3 modelViewIT2(modelViewIT);
	uniform.Invalidate();
	uniform.SetMatrix3(modelViewIT2);
	return true;
}


bool ShaderConstantInitializer::UpdateModelEyePosition( ShaderConstant& uniform)
{
	Camera* camera= RenderingContext::Instance().GetCamera();

	Point3F pos= camera->EyePosition();
	IRenderBatch* batch=RenderingContext::Instance().Batch();
	Matrix modelMatrix=batch->GetModelMatrix();
	modelMatrix.Inverse();
	pos= modelMatrix.Transform(pos);
	uniform.Invalidate();
	uniform.Set(pos);

	return true;
}

bool ShaderConstantInitializer::UpdateModelEyeDirection( ShaderConstant& uniform)
{
	Camera* camera= RenderingContext::Instance().GetCamera();
	Point3F direction= camera->EyeDirection();
	IRenderBatch* batch=RenderingContext::Instance().Batch();
	Matrix modelMatrix=batch->GetModelMatrix();
	modelMatrix.Inverse();
	direction= modelMatrix.TransformVector(direction);
	direction.Normalize();
	uniform.Invalidate();
	uniform.Set(direction);
	return true;
}


bool ShaderConstantInitializer::UpdateModelLightDirection( ShaderConstant& uniform)
{
	ILight* light=LightFactory::Instance().GetCurrentLight();
	if (light!=nullptr)
	{
		IRenderBatch* batch=RenderingContext::Instance().Batch();
		Matrix modelMatrix=batch->GetModelMatrix();
		modelMatrix.Inverse();
		Point3F direction=light->Direction();
		direction=modelMatrix.TransformVector(direction);
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


bool ShaderConstantInitializer::UpdateModelLightPosition( ShaderConstant& uniform )
{
	ILight* light=LightFactory::Instance().GetCurrentLight();
	if (light!=nullptr)
	{
		IRenderBatch* batch=RenderingContext::Instance().Batch();
		Matrix modelMatrix=batch->GetModelMatrix();
		modelMatrix.Inverse();
		Point3F position=light->Position();
		position=modelMatrix.Transform(position);
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


bool ShaderConstantInitializer::UpdateWorldEyePosition( ShaderConstant& uniform)
{
	Camera* camera= RenderingContext::Instance().GetCamera();
	Point3F pos= camera->EyePosition();
	uniform.Invalidate();
	uniform.Set(pos);

	return true;
}

bool ShaderConstantInitializer::UpdateWorldEyeDirection( ShaderConstant& uniform)
{
	Camera* camera= RenderingContext::Instance().GetCamera();
	Point3F direction= camera->EyeDirection();
	uniform.Invalidate();
	uniform.Set(direction);
	return true;
}


bool ShaderConstantInitializer::UpdateWorldLightDirection( ShaderConstant& uniform)
{
	ILight* light=LightFactory::Instance().GetCurrentLight();
	if (light!=nullptr)
	{
		//IRenderBatch* batch=RenderingContext::Instance().GetBatch();
		Point3F direction=light->Direction();
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


bool ShaderConstantInitializer::UpdateWorldLightPosition( ShaderConstant& uniform )
{
	ILight* light=LightFactory::Instance().GetCurrentLight();
	if (light!=nullptr)
	{
		//IRenderBatch* batch=RenderingContext::Instance().GetBatch();
		Point3F position=light->Position();
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

bool ShaderConstantInitializer::UpdateLightAmbient( ShaderConstant& uniform )
{
	ILight* light=LightFactory::Instance().GetCurrentLight();
	if (light!=nullptr)
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


bool ShaderConstantInitializer::UpdateLightDiffuse( ShaderConstant& uniform)
{
	ILight* light=LightFactory::Instance().GetCurrentLight();
	if (light!=nullptr)
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

bool ShaderConstantInitializer::UpdateLightSpecular( ShaderConstant& uniform )
{
	ILight* light=LightFactory::Instance().GetCurrentLight();
	if (light!=nullptr)
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

bool ShaderConstantInitializer::UpdateLightViewProjectMatrix( ShaderConstant& uniform)
{
	ILight* light=LightFactory::Instance().GetCurrentLight();

	if (light!=nullptr&&light->LightType()==GraphicsLightType::Spot)
	{
		SpotLight* spotLight=(SpotLight*)light;
		uniform.Invalidate();
		const Matrix& matrix=spotLight->ViewProjectMatrix();
		uniform.SetMatrix(matrix);
		return true;
	}
	else
	{
		MEDUSA_ASSERT_FAILED("No spot light for LightViewProjectMatrix");
		return false;
	}
	
}

bool ShaderConstantInitializer::UpdateLightWorldViewProjectMatrix( ShaderConstant& uniform)
{
	ILight* light=LightFactory::Instance().GetCurrentLight();
	if (light!=nullptr&&light->LightType()==GraphicsLightType::Spot)
	{
		IRenderBatch* batch=RenderingContext::Instance().Batch();
		Matrix modelMatrix=batch->GetModelMatrix();

		SpotLight* spotLight=(SpotLight*)light;
		uniform.Invalidate();
		const Matrix& matrix=spotLight->ViewProjectMatrix();
		modelMatrix*=matrix;
		uniform.SetMatrix(modelMatrix);
		return true;
	}
	else
	{
		MEDUSA_ASSERT_FAILED("No spot light for LightViewProjectMatrix");
		return false;
	}

}

bool ShaderConstantInitializer::UpdateGlobalAmbient( ShaderConstant& uniform)
{
	return true;
}

bool ShaderConstantInitializer::UpdateFogRange( ShaderConstant& uniform )
{
	return true;
}

bool ShaderConstantInitializer::UpdateFogColor( ShaderConstant& uniform )
{
	return true;
}

MEDUSA_END;