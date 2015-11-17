// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/LazyValue.h"
#include "FlipMask.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Point4.h"
#include "GeometryDefines.h"

MEDUSA_BEGIN;

/*
Store in row or column major depends on MEDUSA_IS_OPENGL
BUT all calculation should use row-major as to be standard
SO all vectors should be looked as row-vector

OpenGL
[11,12,13,14]	[x]				[1,0,0,tx]
[21,22,23,24]	[y]		like 	[0,1,0,ty]
[31,32,33,34]	[z]				[0,0,1,tz]
[41,42,43,44]	[w]				[0,0,0,1]

v'=T*R*S*v, Prepend

DirectX
[x,y,z,w]	[11,12,13,14]			[1,0,0,0]
[21,22,23,24]	like 	[0,1,0,0]
[31,32,33,34]			[0,0,1,0]
[41,42,43,44]			[tx,ty,tz,1]
v'=v*S*R*T	Append

But because OpenGL store the matrix in column order, so OpenGL and DirectX will have the same items order!

(T*R*S)-t?????S-t*R-t*T-t ,???????????????????S*R*T??,??OpenGL????????????????????,????????????(S*R*T)-t,???????T-t*R-t*S-t,
??????????????????????S,R,T?????????????,????????SRT?????????????-t,??????????????????
*/

class Matrix4
{
public:
	inline Matrix4(void) {}
	inline Matrix4(const float* items)
	{
		Memory::Copy(M, items, Size);
	}
	//No need this because C++ will produce default copy-assignment for us
	//inline Matrix4(const Matrix4& matrix);
	//inline Matrix4& operator=(const Matrix4& matrix);

	//in row-major
	inline Matrix4(float m11, float m12, float m13, float m14,
				   float m21, float m22, float m23, float m24,
				   float m31, float m32, float m33, float m34,
				   float m41, float m42, float m43, float m44, bool isTransposed = false)
	{
		if (isTransposed)
		{
			M11 = m11; M21 = m12; M31 = m13; M41 = m14;
			M12 = m21; M22 = m22; M32 = m23; M42 = m24;
			M13 = m31; M23 = m32; M33 = m33; M43 = m34;
			M14 = m41; M24 = m42; M34 = m43; M44 = m44;
		}
		else
		{
			M11 = m11; M12 = m12; M13 = m13; M14 = m14;
			M21 = m21; M22 = m22; M23 = m23; M24 = m24;
			M31 = m31; M32 = m32; M33 = m33; M34 = m34;
			M41 = m41; M42 = m42; M43 = m43; M44 = m44;
		}

	}

	explicit Matrix4(const Matrix43& m, bool isTransposed = false);
	Matrix4& operator=(const Matrix43& m);

	explicit Matrix4(const Matrix3& m, bool isTransposed = false);
	Matrix4& operator=(const Matrix3& m);

	explicit Matrix4(const Matrix& m, bool isTransposed = false);
	Matrix4& operator=(const Matrix& m);

	float* Items() { return M; }
	const float* const Items()const { return M; }

	float& operator[](byte index) { return M[index]; }
	const float& operator[](byte index)const { return M[index]; }

	inline float& operator()(byte row, byte column) { return M[row*ColumnSize + column]; }
	inline const float& operator()(byte row, byte column)const { return M[row*ColumnSize + column]; }

	Point4F Row(byte row)const { return Point4F(M + ColumnSize*row); }
	void SetRow(byte row, const Point4F& val);

	Point4F Column(byte column);
	void SetColumn(byte column, const Point4F& val);


	bool operator==(const Matrix4& matrix)const;
	bool operator!=(const Matrix4& matrix)const;
	bool IsIdentity()const;
	bool IsZero()const;

public:
	Point3F Up()const { return Point3F(M21, M22, M23); }
	void SetUp(const Point3F& val) { M21 = val.X; M22 = val.Y; M23 = val.Z; }

	Point3F Down()const { return Point3F(-M21, -M22, -M23); }
	void SetDown(const Point3F& val) { M21 = -val.X; M22 = -val.Y; M23 = -val.Z; }

	Point3F Right()const { return Point3F(M11, M12, M13); }
	void SetRight(const Point3F& val) { M11 = val.X; M12 = val.Y; M13 = val.Z; }

	Point3F Left()const { return Point3F(-M11, -M12, -M13); }
	void SetLeft(const Point3F& val) { M11 = -val.X; M12 = -val.Y; M13 = -val.Z; }

	Point3F Backward()const { return Point3F(M31, M32, M33); }
	void SetBackward(const Point3F& val) { M31 = val.X; M32 = val.Y; M33 = val.Z; }

	Point3F Forward()const { return Point3F(-M31, -M32, -M33); }
	void SetForward(const Point3F& val) { M31 = -val.X; M32 = -val.Y; M33 = -val.Z; }

	Point3F Translation()const { return Point3F(M41, M42, M43); }
	void SetTranslation(const Point3F& val) { M41 = val.X; M42 = val.Y; M43 = val.Z; }

	void DecomposeXYZ(Scale3F& outScale, Rotation3F& outRotation, Point3F& outTranslation)const;
public:
	inline Matrix4 operator*(const Matrix4& matrix)const
	{
		Matrix4 ret = *this;
		ret.Append(matrix);
		return ret;
	}
	inline Matrix4& operator*=(const Matrix4& matrix)
	{
		Append(matrix);
		return *this;
	}

	intp HashCode()const
	{
		return HashUtility::Hash(M);
	}

public:
	Matrix4& Multiply(const Matrix4& m, MatrixOrder order);
	Matrix4& Append(const Matrix4& m);
	Matrix4& Prepend(const Matrix4& m);

	inline void LoadIdentity() { *this = Identity; }
	inline void LoadZero() { *this = Zero; }
	HeapString ToString()const;
	float Determinant()const;

	Vector3F TransformVector(const Vector3F& point)const;
	Point2F Transform(const Point2F& point)const;
	Point3F Transform(const Point3F& point)const;
	Point4F Transform(const Point4F& point)const;
	Rect2F Transform(const Rect2F& rect)const;
	CubeF Transform(const CubeF& cube)const;



	Scale3F GetScale()const;
	Rotation3F GetRotationXYZ()const;

#pragma region Transform
	Matrix4& Inverse();
	Matrix4& Inverse43();

	Matrix4& Transpose();
	Matrix4& Translate(const Point3F& point);
	Matrix4& Scale(const Scale3F& scale);
	Matrix4& RotateXYZ(const Rotation3F& rotation);
	Matrix4& RotateX(float radian);
	Matrix4& RotateY(float radian);
	Matrix4& RotateZ(float radian);
	Matrix4& RotateEuler(const EulerAngle& angle);
	Matrix4& FlipX();
	Matrix4& FlipY();
	Matrix4& FlipZ();

	Matrix4& ResetWorld(const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip = FlipMask::None, Point3F flipPivot = Point3F::Zero, const Point3F& pivot = Point3F::Zero);
	Matrix4& ResetWorld(const Size3F& size, const Point3F& anchor, const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip = FlipMask::None);

	Matrix4 CreateInverse();
	Matrix43 CreateInverse43();

	//************************************
	// ????:    	InverseMatrixByGauss
	// ????:   	Matrix44	
	// ????:		????-????????
	// ????:		
	// ????:		
	//************************************
	Matrix4 CreateInverseByGauss();
	Matrix4 CreateTranspose();


	static Matrix4 CreateTranslate(const Point3F& point);
	static Matrix4 CreateScale(const Scale3F& scale);
	static Matrix4 CreateScaleAxis(const Point3F& axis, float scale);
	static Matrix4 CreateRotateXYZ(const Rotation3F& rotation);
	static Matrix4 CreateRotateX(float radian);
	static Matrix4 CreateRotateY(float radian);
	static Matrix4 CreateRotateZ(float radian);
	static Matrix4 CreateRotateAxis(const Point3F& axis, float radian);
	static Matrix4 CreateFromEuler(const EulerAngle& angle);
	static Matrix4 CreateFromQuaternion(const Quaternion& q);
	static Matrix4 CreateProjectToXY();
	static Matrix4 CreateProjectToXZ();
	static Matrix4 CreateProjectToYZ();
	static Matrix4 CreateProjectToPlane(const Point3F& normal);
	static Matrix4 CreateFlipX();
	static Matrix4 CreateFlipY();
	static Matrix4 CreateFlipZ();
	static Matrix4 CreateFlipByPlane(const Point3F& normal);
	static Matrix4 CreateFlip(FlipMask flip = FlipMask::None, Point3F flipPivot = Point3F::Zero);

	static Matrix4 CreateShear(float xy, float xz, float yx, float yz, float zx, float zy);
	static Matrix4 CreateNormal();
	static Matrix4 CreateWorld(const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip = FlipMask::None, Point3F flipPivot = Point3F::Zero, const Point3F& pivot = Point3F::Zero);
	static Matrix4 CreateWorld(const Size3F& size, const Point3F& anchor, const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip = FlipMask::None);



	static Matrix4 CreateBillboard(const Vector3F& objectPosition, const Vector3F& cameraPosition, const Vector3F& cameraUp, const Vector3F& cameraForward = Vector3F::ForWard, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix4 CreateConstrainedBillboard(const Vector3F& objectPosition, const Vector3F& cameraPosition, const Vector3F& rotateAxis, const Vector3F& cameraForward = Vector3F::ForWard, const Vector3F& objectForward = Vector3F::ForWard, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);


	static Matrix4 LookAtLH(const Vector3F& eyes, const Vector3F& target, const Vector3F& up);
	static Matrix4 LookAtRH(const Vector3F& eyes, const Vector3F& target, const Vector3F& up);
	static Matrix4 LookAt(const Vector3F& eyes, const Vector3F& target, const Vector3F& up, bool isRightHand = MEDUSA_IS_RIGHT_HAND);

	static Matrix4 OrthoLH(float width, float height, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix4 OrthoRH(float width, float height, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix4 Ortho(float width, float height, float nearPlane, float farPlane, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);

	static Matrix4 OrthoOffCenterLH(float left, float right, float bottom, float top, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix4 OrthoOffCenterRH(float left, float right, float bottom, float top, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix4 OrthoOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);

	static Matrix4 PerspectiveFOVLH(float fovY, float aspect, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix4 PerspectiveFOVRH(float fovY, float aspect, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix4 PerspectiveFOV(float fovY, float aspect, float nearPlane, float farPlane, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);

	static Matrix4 PerspectiveLH(float width, float height, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix4 PerspectiveRH(float width, float height, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix4 Perspective(float width, float height, float nearPlane, float farPlane, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);

	static Matrix4 PerspectiveOffCenterLH(float left, float right, float bottom, float top, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix4 PerspectiveOffCenterRH(float left, float right, float bottom, float top, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix4 PerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);

private:
	//************************************
	// ????:    	AdjointMatrix
	// ????:   	Matrix4	
	// ????:		?????????????
	// ????:		
	// ????:		
	//************************************
	Matrix4 AdjointMatrix();

	//************************************
	// ????:    	SubDeterminant
	// ????:   	float	
	// ????: 	byte row		
	// ????: 	byte column		
	// ????:		????????????????
	// ????:		
	// ????:		
	//************************************
	float SubDeterminant(byte row, byte column);

#pragma endregion Transform
public:
	const static Matrix4 Zero;
	const static Matrix4 Identity;
	const static byte Size = 16;
	const static byte RowSize = 4;
	const static byte ColumnSize = 4;

	union
	{
		float M[Size];
		struct
		{
			union { float M11; float A; }; union { float M12; float B; }; float M13; float M14;
			union { float M21; float C; }; union { float M22; float D; }; float M23; float M24;
			float M31; float M32; float M33; float M34;
			union { float M41; float X; }; union { float M42; float Y; }; union { float M43; float Z; }; float M44;
		};
	};

};

//[PRE_DECLARE_BEGIN]
typedef LazyValue<Matrix4> LazyMatrix4;
//[PRE_DECLARE_END]
MEDUSA_END;
