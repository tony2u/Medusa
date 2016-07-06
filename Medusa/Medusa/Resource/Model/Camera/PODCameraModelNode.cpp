// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PODCameraModelNode.h"
#include "Resource/Model/Scene/PODModel.h"
#include "Resource/Camera/Camera.h"


MEDUSA_BEGIN;


PODCameraModelNode::PODCameraModelNode(StringRef name)
	:BaseCameraModelNode(name), TargetObjectIndex(0), FOV(0.f), Near(0.f), Far(0.f)
{
}


PODCameraModelNode::~PODCameraModelNode(void)
{
}

Share<Camera> PODCameraModelNode::CreateCamera(const Size2F& winSize) const
{
	Share<Camera> camera = new Camera(mName);
	
	camera->ResetDefault(winSize, false);
	camera->SetFovY(FOV);
	camera->SetNearZ(Near);
	camera->SetFarZ(Far);

	PODModel* model = (PODModel*)mParentModel;

	PODNode* cameraNode = model->GetPODNode(mName);
	Matrix4 cameraMatrix;
	model->TryGetWorldMatrix(cameraNode, 0, cameraMatrix);
	camera->SetEyePosition(cameraMatrix.Translation());

	if (TargetObjectIndex>=0)
	{
		Matrix4 targetMatrix;

		PODNode* targetNode = model->GetPODNode(TargetObjectIndex);
		model->TryGetWorldMatrix(targetNode, 0, targetMatrix);
		camera->SetEyeTarget(targetMatrix.Translation());
		camera->SetCameraUp(Point3F(0.f, 1.f, 0.f));
	}
	else
	{
		// View direction is 0,-1,0,1 transformed by world matrix
		Point4F targetPos(0.f, -1.f, 0.f, 1.f);
		targetPos = cameraMatrix.Transform(targetPos);

		camera->SetEyeTarget(targetPos.TruncateTo3D());

		//TODO: I don't understand code below very much. copy it from PVRSDK. Just keep it and debug it later.
#if MEDUSA_IS_DIRECTX
		/*
	When you rotate the camera from "straight forward" to "straight down", in
	D3D the UP vector will be [0, 0, 1]
	*/
		Point3F up(0.f, 0.f, 1.f);
		up = cameraMatrix.TransformVector(up);
		up.Normalize();
		camera->SetCameraUp(up);

#else
		/*
	When you rotate the camera from "straight forward" to "straight down", in
	OpenGL the UP vector will be [0, 0, -1]
	*/

		//Be
		Point3F up(-cameraMatrix.M13, -cameraMatrix.M23, -cameraMatrix.M33);
		up.Normalize();

		camera->SetCameraUp(up);
#endif
	}

	return camera;
}


MEDUSA_END;