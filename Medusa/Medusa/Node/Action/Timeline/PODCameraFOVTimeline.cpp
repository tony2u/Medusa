// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Action/Timeline/PODCameraFOVTimeline.h"
#include "Node/INode.h"
#include "Resource/Timeline/PODCameraFOVTimelineModel.h"
#include "Resource/Camera/CameraFactory.h"

MEDUSA_BEGIN;


PODCameraFOVTimeline::PODCameraFOVTimeline(const Share<PODCameraFOVTimelineModel>& model, bool isRepeatForever, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, isRepeatForever, beforeDelay, repeatDuration, afterDelay, name)
{
	mCamera = nullptr;

}

PODCameraFOVTimeline::PODCameraFOVTimeline(const Share<PODCameraFOVTimelineModel>& model, intp repeatCount, float beforeDelay /*= 0.f*/, float repeatDuration /*= 0.f*/, float afterDelay /*= 0.f*/, const StringRef& name /*= StringRef::Empty*/)
	: ITimeline(model, repeatCount, beforeDelay, repeatDuration, afterDelay, name)
{
	mCamera = nullptr;

}


PODCameraFOVTimeline::~PODCameraFOVTimeline()
{
	
}

bool PODCameraFOVTimeline::Start()
{
	RETURN_FALSE_IF_FALSE((ITimeline::Start()));

	auto ani = mModel.CastPtr<PODCameraFOVTimelineModel>();
	StringRef cameraName=ani->CameraName();
	StringRef targetName=ani->TargetNodeName();

	mCamera=CameraFactory::Instance().Find(cameraName);
	RETURN_FALSE_IF_NULL(mCamera);

	return true;
}

bool PODCameraFOVTimeline::OnUpdate(float prevElapsed,float dt, float blend /*= 1.f*/)
{
	uint outPrevFrameIndex;
	uint outNextFrameIndex;
	float outPercent;
	mModel->TryGetFrame(mElapsed, outPrevFrameIndex, outNextFrameIndex, outPercent);

	auto ani = mModel.CastPtr<PODCameraFOVTimelineModel>();
	

	float prevFov = ani->GetFov(outPrevFrameIndex);
	float nextFov = ani->GetFov(outNextFrameIndex);
	float fov = Math::LinearInterpolate(prevFov, nextFov, outPercent);
	mCamera->SetFovY(fov);


//	if (mCameraState!=nullptr)
//	{
//		const Matrix4& matrix= mCameraState->GetWorldMatrix();
//		// View position is 0,0,0,1 transformed by world matrix
//		mCamera->SetEyePosition(matrix.Translation());
//
//		if (mCameraTargetState!=nullptr)
//		{
//			const Matrix4& targetMatrix= mCameraTargetState->GetWorldMatrix();
//			mCamera->SetEyeTarget(targetMatrix.Translation());
//
//			mCamera->SetCameraUp(Point3F(0.f,1.f,0.f));
//		}
//		else
//		{
//			// View direction is 0,-1,0,1 transformed by world matrix
//			Point4F targetPos(0.f,-1.f,0.f,1.f);
//			targetPos=matrix.TransformPoint(targetPos);
//			
//			mCamera->SetEyeTarget(targetPos.TruncateTo3D());
//
//			//TODO: I don't understand code below very much. copy it from PVRSDK. Just keep it and debug it later.
//#if MEDUSA_IS_DIRECTX
//			/*
//		When you rotate the camera from "straight forward" to "straight down", in
//		D3D the UP vector will be [0, 0, 1]
//	*/
//			Point3F up(0.f,0.f,1.f);
//			up=matrix.TransformVector(up);
//			up.Normalize();
//			mCamera->SetCameraUp(up);
//
//#else
//			/*
//		When you rotate the camera from "straight forward" to "straight down", in
//		OpenGL the UP vector will be [0, 0, -1]
//	*/
//			Point3F up(0.f,0.f,-1.f);
//			up=matrix.TransformVector(up);
//			up.Normalize();
//
//			mCamera->SetCameraUp(up);
//#endif
//		}
//	}
//
	return true;
}

MEDUSA_END;
