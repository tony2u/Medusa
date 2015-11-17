// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/Render/Render.h"
#include "Graphics/GraphicsTypes.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Geometry/Color3.h"
#include "Core/Geometry/Point2.h"
#include "Rendering/RenderingTypes.h"

MEDUSA_BEGIN;


class RenderingContext:public Singleton<RenderingContext>
{
	friend class Singleton<RenderingContext>;
private:
	RenderingContext();
	~RenderingContext();
public:
	IRenderTarget* RenderTarget() const { return mRenderTarget; }
	BaseProgramRenderPass* ProgramRenderPass()const{return (BaseProgramRenderPass*)mRenderPass;}
	const IMaterial* Material() const { return mMaterial; }
	IRenderBatch* Batch() const { return mBatch; }
	const IEffect* Effect() const { return mEffect; }
	Camera* GetCamera() const { return mCamera; }
	RenderStateTreeLeafNode* StateNode()const { return mStateNode; }
	GraphicsDrawMode DrawMode() const { return mDrawMode; }



	void SetRenderTargetAndCamera(IRenderTarget* val,Camera* camera);
	void SetRenderPass(IRenderPass* val);
	void SetMaterial(const IMaterial* val);
	void SetState(RenderStateTreeLeafNode* stateNode);
	void SetBatch(IRenderBatch* val);
	void SetEffect(const IEffect* val);
	void SetDrawMode(GraphicsDrawMode val);


	void ResetRenderTargetAndCamera();
	void ResetRenderPass();
	void ResetMaterial();
	void ResetState();
	void ResetBatch();
	void ResetEffect();
	void ResetDrawMode();


	void ApplyRenderTargetAndCamera(IRenderTarget* val,Camera* camera);
	void ApplyRenderPass(IRenderPass* val);
	void ApplyMaterial(const IMaterial* val);
	void ApplyState(RenderStateTreeLeafNode* stateNode);
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



	void UpdateShaderVariables();
private:
	IRenderTarget* mRenderTarget;
	Camera* mCamera;
	IRenderPass* mRenderPass;
	const IMaterial* mMaterial;
	IRenderBatch* mBatch;
	const IEffect* mEffect;
	RenderStateTreeLeafNode* mStateNode;
	GraphicsDrawMode mDrawMode;
	
	RenderingStep mStep;
	
};


MEDUSA_END;