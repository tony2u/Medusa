// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/Render/Render.h"
#include "Graphics/GraphicsTypes.h"
#include "Core/Pattern/Singleton.h"
#include "Geometry/Color3.h"
#include "Geometry/Point2.h"
#include "Rendering/RenderingTypes.h"
#include "Resource/RenderTarget/IRenderTarget.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/Camera/Camera.h"
#include "Graphics/State/Tree/RenderStateTreeLeafNode.h"

MEDUSA_BEGIN;


class RenderingContext:public Singleton<RenderingContext>
{
	friend class Singleton<RenderingContext>;
private:
	RenderingContext();
	~RenderingContext();
public:
	const Share<IRenderTarget>& RenderTarget() const { return mRenderTarget; }
	Share<BaseProgramRenderPass> ProgramRenderPass()const{return mRenderPass.Cast<Share<BaseProgramRenderPass>>();}
	const Share<IMaterial>& Material() const { return mMaterial; }
	IRenderBatch* Batch() const { return mBatch; }
	const Share<IEffect>& Effect() const { return mEffect; }
	const Share<Camera>& GetCamera() const { return mCamera; }
	const Share<RenderStateTreeLeafNode>& StateNode()const { return mStateNode; }
	GraphicsDrawMode DrawMode() const { return mDrawMode; }



	void SetRenderTargetAndCamera(const Share<IRenderTarget>& val, const Share<Camera>& camera);
	void SetRenderPass(const Share<IRenderPass>& val);
	void SetMaterial(const Share<IMaterial>& val);
	void SetState(const Share<RenderStateTreeLeafNode>& stateNode);
	void SetBatch(IRenderBatch* val);
	void SetEffect(const Share<IEffect>& val);
	void SetDrawMode(GraphicsDrawMode val);


	void ResetRenderTargetAndCamera();
	void ResetRenderPass();
	void ResetMaterial();
	void ResetState();
	void ResetBatch();
	void ResetEffect();
	void ResetDrawMode();


	void ApplyRenderTargetAndCamera(const Share<IRenderTarget>& val, const Share<Camera>& camera);
	void ApplyRenderPass(const Share<IRenderPass>& val);
	void ApplyMaterial(const Share<IMaterial>& val);
	void ApplyState(const Share<RenderStateTreeLeafNode>& stateNode);
	void ApplyDrawMode(GraphicsDrawMode val);
	void ApplyBatch(IRenderBatch* val);

	void RestoreRenderTargetAndCamera();
	void RestoreRenderPass();
	void RestoreMaterial();
	void RestoreState();

	void RestoreDrawMode();
	void RestoreBatch();

	void ValidateBeforeDraw();

	RenderingStep Step() const { return mStep; }
	bool IsRenderTargetStep()const{return mStep==RenderingStep::RenderTarget;}
	bool IsRenderPassStep()const{return mStep==RenderingStep::RenderPass;}
	bool IsMaterialStep()const{return mStep==RenderingStep::Material;}
	bool IsStateStep()const{return mStep==RenderingStep::State;}
	bool IsDrawModeStep()const{return mStep==RenderingStep::DrawMode;}
	bool IsBatchStep()const { return mStep == RenderingStep::Batch; }



	void UpdateShaderUniforms();
private:

	Share<IRenderTarget> mRenderTarget;
	Share<Camera> mCamera;
	Share<IRenderPass> mRenderPass;
	Share<IMaterial> mMaterial;
	IRenderBatch* mBatch;
	Share<IEffect> mEffect;
	Share<RenderStateTreeLeafNode> mStateNode;
	GraphicsDrawMode mDrawMode;
	
	RenderingStep mStep;
	
};


MEDUSA_END;