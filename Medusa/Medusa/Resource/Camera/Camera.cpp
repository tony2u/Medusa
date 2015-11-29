// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Camera.h"
#include "Graphics/Render/Render.h"
#include "Rendering/RenderingContext.h"
#include "Core/Pattern/AutoIncreaseId.h"


MEDUSA_BEGIN;

Camera::Camera(const FileIdRef& fileId/*=FileId::Empty*/)
	:IResource(fileId),
	mEyeTarget(Vector3F::Zero),
	mCameraUp(Vector3F::Zero),
	mViewProjectionMatrix(Matrix4::Identity)
{
	mId = AutoIncreaseId<Camera>::New();

	mViewProjectionMatrix.SetUpdateDelegate(Bind(&Camera::OnUpdateViewProjectionMatrix,this));
	mViewMatrix.SetUpdateDelegate(Bind(&Camera::OnUpdateViewMatrix,this));

	mIsOrtho=false;
}

Camera::~Camera(void)
{
}

void Camera::Resize(const Size2F& winSize)
{
	ResetDefault(winSize, mIsOrtho);
}

void Camera::ResetDefault(const Size2F& winSize, bool isOrtho /*= false*/)
{
	mWinSize = winSize;
	mIsOrtho = isOrtho;
	float zEye = winSize.Height / 1.1566f;//this magic number will show the picture "pixel-to-pixel" on the screen
	mEyePosition = Point3F(winSize.Width / 2.f, winSize.Height / 2.f, zEye);
	mEyeTarget = Vector3F(winSize.Width / 2.f, winSize.Height / 2.f, 0.f);
	mCameraUp=Vector3F(0.f,1.f,0.f);

	if (mIsOrtho)
	{
		SetOrtho(mWinSize, 0.f, 2048.f);
	}
	else
	{
		mFovY = Math::ToRadian(60.f);
		mNearZ = 0.1f;
		mFarZ = zEye * 2;
		SetPerspectiveFov(mWinSize,mFovY, mNearZ, mFarZ);
	}
	LookAt(mEyePosition,mEyeTarget,mCameraUp);
}


void Camera::SetPerspectiveFov(const Size2F& winSize, float yFov, float zNear, float zFar)
{
	mWinSize = winSize;

	float aspect = (float)winSize.Width / (float)winSize.Height;

	yFov*=0.5f;
	float ySize = zNear * Math::Tan(yFov);

	return SetPerspectiveEx(-ySize*aspect,ySize*aspect,-ySize,ySize,zNear,zFar);
}


void Camera::SetPerspectiveEx( float left,float right,float bottom,float top,float nearPlane,float farPlane )
{
	mFrustum.Origin.X=left;
	mFrustum.Origin.Y=bottom;
	mFrustum.Origin.Z=nearPlane;

	mFrustum.Size.Depth=farPlane-nearPlane;
	mFrustum.Size.Width=right-left;
	mFrustum.Size.Height=top-bottom;
	mIsOrtho=false;
	mViewProjectionMatrix.SetDirty();
}

void Camera::LookAt( const Vector3F& eyes, const Vector3F& target, const Vector3F& up )
{
	mEyePosition=eyes;
	mEyeTarget=target;
	mCameraUp=up;

	mViewProjectionMatrix.SetDirty();
	mViewMatrix.SetDirty();
}


void Camera::SetEyePosition(const Point3F& val)
{
	mEyePosition = val; 
	mViewMatrix.SetDirty();
	mViewProjectionMatrix.SetDirty();
}

void Camera::SetEyeTarget(const Vector3F& val)
{
	mEyeTarget = val; 
	mViewMatrix.SetDirty(); 
	mViewProjectionMatrix.SetDirty();
}

void Camera::MoveTo(const Point2F& val)
{
	mEyePosition.X = val.X;
	mEyePosition.Y = val.Y;

	mEyeTarget.X = val.X;
	mEyeTarget.Y = val.Y;

	mViewMatrix.SetDirty();
	mViewProjectionMatrix.SetDirty();
}

void Camera::MoveBy(const Point2F& val)
{
	mEyePosition.X += val.X;
	mEyePosition.Y += val.Y;

	mEyeTarget.X += val.X;
	mEyeTarget.Y += val.Y;

	mViewMatrix.SetDirty();
	mViewProjectionMatrix.SetDirty();
}

void Camera::MoveByY(float y)
{
	mEyePosition.Y += y;
	mEyeTarget.Y += y;

	mViewMatrix.SetDirty();
	mViewProjectionMatrix.SetDirty();
}

void Camera::MoveByX(float x)
{
	mEyePosition.X += x;
	mEyeTarget.X += x;

	mViewMatrix.SetDirty();
	mViewProjectionMatrix.SetDirty();
}

void Camera::SetCameraUp(const Vector3F& val)
{
	mCameraUp = val; 
	mViewMatrix.SetDirty(); 
	mViewProjectionMatrix.SetDirty();
}


void Camera::SetOrtho(const Size2F& winSize, float nearZ, float farZ)
{
	mWinSize = winSize;
	mNearZ = nearZ;
	mFarZ = farZ;
	return SetOrthoEx(-winSize.Width / 2, winSize.Width / 2, -winSize.Height / 2, winSize.Height / 2, mNearZ, mFarZ);
}

void Camera::SetOrthoEx( float left,float right,float bottom,float top,float nearPlane,float farPlane )
{
	mFrustum.Origin.X=left;
	mFrustum.Origin.Y=bottom;
	mFrustum.Origin.Z=nearPlane;

	mFrustum.Size.Depth=farPlane-nearPlane;
	mFrustum.Size.Width=right-left;
	mFrustum.Size.Height=top-bottom;
	mIsOrtho=true;
	mViewProjectionMatrix.SetDirty();

}

void Camera::SetNearZ(float val)
{
	RETURN_IF_EQUAL(mNearZ, val);
	mNearZ = val; 

	if (mIsOrtho)
	{
		SetOrtho(mWinSize,mNearZ, mFarZ);
	}
	else
	{
		SetPerspectiveFov(mWinSize,mFovY, mNearZ, mFarZ);
	}
}

void Camera::SetFarZ(float val)
{
	RETURN_IF_EQUAL(mFarZ, val);
	mFarZ = val; 
	if (mIsOrtho)
	{
		SetOrtho(mWinSize,mNearZ, mFarZ);
	}
	else
	{
		SetPerspectiveFov(mWinSize,mFovY, mNearZ, mFarZ);
	}
}

void Camera::SetFovY(float val)
{
	mFovY = val;
	SetPerspectiveFov(mWinSize,mFovY, mNearZ, mFarZ);
}


void Camera::OnUpdateViewProjectionMatrix(Matrix4& transform, int32 dirtyFlag)
{
	if (mIsOrtho)
	{
		transform = Matrix4::OrthoOffCenter(mFrustum.Left(), mFrustum.Right(), mFrustum.Bottom(), mFrustum.Top(), mFrustum.Near(), mFrustum.Far());
	}
	else
	{
		transform = Matrix4::PerspectiveOffCenter(mFrustum.Left(), mFrustum.Right(), mFrustum.Bottom(), mFrustum.Top(), mFrustum.Near(), mFrustum.Far());
	}

	const Matrix4& viewMatrix = mViewMatrix.Value();
	transform = viewMatrix*transform;
}


void Camera::OnUpdateViewMatrix(Matrix4& transform, int32 dirtyFlag)
{
	transform = Matrix4::LookAt(mEyePosition, mEyeTarget, mCameraUp);
}


MEDUSA_END;
