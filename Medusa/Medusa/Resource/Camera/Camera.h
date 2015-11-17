// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Geometry/Matrix.h"
#include "Core/String/HeapString.h"
#include "Resource/IResource.h"
#include "Core/Geometry/Cube.h"

MEDUSA_BEGIN;

class Camera:public IResource
{
public:
	Camera(const FileIdRef& fileId=FileIdRef::Empty);
	virtual ~Camera(void);
public:
	virtual ResourceType Type()const{return ResourceType::Camera;}
	static ResourceType ClassGetResourceType(){return ResourceType::Camera;}

	virtual bool IsVisible()const{return false;}

	CubeF Frustum() const { return mFrustum; }
	void SetFrustum(CubeF val) { mFrustum = val; }

	void Resize(const Size2F& winSize);

	void ResetDefault(const Size2F& winSize, bool isOrtho=false);
	Point3F EyeDirection()const{return mEyePosition-mEyeTarget;}
	const Point3F& EyePosition() const { return mEyePosition; }
	void SetEyePosition(const Point3F& val);

	const Vector3F& EyeTarget() const { return mEyeTarget; }
	void SetEyeTarget(const Vector3F& val);

	void MoveTo(const Point2F& val);

	void MoveBy(const Point2F& val);
	void MoveByX(float x);
	void MoveByY(float y);


	const Vector3F& CameraUp() const { return mCameraUp; }
	void SetCameraUp(const Vector3F& val);

	void SetOrtho(const Size2F& winSize, float nearZ, float farZ);
	void SetOrthoEx(float left,float right,float bottom,float top,float nearPlane,float farPlane);
	void SetPerspectiveFov(const Size2F& winSize, float yFov, float zNear, float zFar);
	void SetPerspectiveEx(float left,float right,float bottom,float top,float nearPlane,float farPlane);
	void LookAt(const Vector3F& eyes, const Vector3F& target, const Vector3F& up);

	const Matrix& ViewProjectionMatrix() { return mViewProjectionMatrix.Value(); }
	const Matrix& ViewMatrix() { return mViewMatrix.Value(); }

	float FovY() const { return mFovY; }
	void SetFovY(float val);
	float NearZ() const { return mNearZ; }
	void SetNearZ(float val);
	float FarZ() const { return mFarZ; }
	void SetFarZ(float val);
	
protected:
	void OnUpdateViewProjectionMatrix(Matrix& transform,int32 dirtyFlag);
	void OnUpdateViewMatrix(Matrix& transform, int32 dirtyFlag);

protected:
	CubeF mFrustum;
	Point3F mEyePosition;
	
	Vector3F mEyeTarget;
	Vector3F mCameraUp;
	LazyMatrix mViewProjectionMatrix;
	LazyMatrix mViewMatrix;

	bool mIsOrtho;

	float mFovY;
	float mNearZ;
	float mFarZ;

	Size2F mWinSize;
};

MEDUSA_END;
