// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/LazyValue.h"
#include "Core/Geometry/GeometryDefines.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Point4.h"
#include "MatrixFlags.h"
#include "FlipMask.h"



MEDUSA_BEGIN;


class Matrix
{
public:
	inline Matrix(MatrixFlags flags = MatrixFlags::None) :Flag(flags) {}
	inline Matrix(const float* items, MatrixFlags flags = MatrixFlags::None) 
		: Flag(flags)
	{
		Memory::Copy(M, items, Size);
	}

	//in row-major
	inline Matrix(float m11, float m12, float m13, float m14,
				   float m21, float m22, float m23, float m24,
				   float m31, float m32, float m33, float m34,
				   float m41, float m42, float m43, float m44, MatrixFlags flags = MatrixFlags::None, bool isTransposed = false, bool updateFlag = false);

	inline Matrix(float m11, float m12, float m13,
				  float m21, float m22, float m23,
				  float m31, float m32, float m33,
				  float m41, float m42, float m43, bool updateFlag=false);

	inline Matrix(float m11, float m12, float m13,
				  float m21, float m22, float m23,
				  float m31, float m32, float m33,
				  bool isTransposed = false, bool updateFlag = false);

	inline Matrix(float m11, float m12,
				  float m21, float m22,
				  float m31, float m32);

	explicit Matrix(const Matrix2& m);
	Matrix& operator=(const Matrix2& m);

	explicit Matrix(const Matrix3& m, bool isTransposed = false);
	Matrix& operator=(const Matrix3& m);

	explicit Matrix(const Matrix43& m);
	Matrix& operator=(const Matrix43& m);

	Matrix(const Matrix& m);
	Matrix& operator=(const Matrix& m);

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


	bool operator==(const Matrix& matrix)const;
	bool operator!=(const Matrix& matrix)const;
	bool IsIdentity()const;
	bool IsZero()const;
	bool Is2D()const { return Flag.IsIs2D(); }
	bool IsAffine()const { return Flag.IsAffine(); }

public:
	Point3F Up()const { return Point3F(M21, M22, M23); }
	void SetUp(const Point3F& val) { M21 = val.X; M22 = val.Y; M23 = val.Z; }

	Point3F Down()const { return Point3F(-M21, -M22, -M23); }
	void SetDown(const Point3F& val) { M21 = -val.X; M22 = -val.Y; M23 = -val.Z; }

	Point3F Right()const { return Point3F(M11, M12, M13); }
	void SetRight(const Point3F& val) { M11 = val.X; M12 = val.Y; M13 = val.Z; }

	Point3F Left()const { return Point3F(-M11, -M12, -M13); }
	void SetLeft(const Point3F& val) { M11 = -val.X; M12 = -val.Y; M13 = -val.Z; }

	Point3F Backward()const;
	void SetBackward(const Point3F& val);

	Point3F Forward()const;
	void SetForward(const Point3F& val);

	Point3F Translation()const;
	void SetTranslation(const Point3F& val);

	void DecomposeXYZ(Scale3F& outScale, Rotation3F& outRotation, Point3F& outTranslation)const;
public:
	inline Matrix operator*(const Matrix& matrix)const
	{
		Matrix ret = *this;
		ret.Append(matrix);
		return ret;
	}
	inline Matrix& operator*=(const Matrix& matrix)
	{
		Append(matrix);
		return *this;
	}

	intp HashCode()const;

public:
	Matrix& Multiply(const Matrix& m, MatrixOrder order);
	Matrix& Append(const Matrix& m);
	Matrix& Prepend(const Matrix& m);

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
	Matrix& Inverse();

	Matrix& Transpose();
	Matrix& Translate(const Point3F& point);
	Matrix& Translate(const Point2F& point);

	Matrix& Scale(const Scale3F& scale);
	Matrix& Scale(const Scale2F& scale);

	Matrix& RotateXYZ(const Rotation3F& rotation);
	Matrix& RotateXY(const Rotation2F& rotation);

	Matrix& RotateX(float radian);
	Matrix& RotateY(float radian);
	Matrix& RotateZ(float radian);
	Matrix& RotateEuler(const EulerAngle& angle);
	Matrix& FlipX();
	Matrix& FlipY();
	Matrix& FlipZ();

	Matrix& ResetWorld(const Size3F& size, const Point3F& anchor, const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip = FlipMask::None);
	Matrix& ResetWorld(const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip = FlipMask::None, Point3F flipPivot = Point3F::Zero, const Point3F& pivot = Point3F::Zero);
	Matrix& ResetWorldWithoutAnchor(const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip = FlipMask::None);


	Matrix CreateInverse();
	Matrix CreateTranspose();

	static Matrix CreateTranslate(const Point3F& point);
	static Matrix CreateScale(const Scale3F& scale);
	static Matrix CreateScaleAxis(const Point3F& axis, float scale);
	static Matrix CreateRotateXYZ(const Rotation3F& rotation);
	static Matrix CreateRotateXY(const Rotation2F& rotation);

	static Matrix CreateRotateX(float radian);
	static Matrix CreateRotateY(float radian);
	static Matrix CreateRotateZ(float radian);
	static Matrix CreateRotateAxis(const Point3F& axis, float radian);
	static Matrix CreateFromEuler(const EulerAngle& angle);
	static Matrix CreateFromQuaternion(const Quaternion& q);
	static Matrix CreateProjectToXY();
	static Matrix CreateProjectToXZ();
	static Matrix CreateProjectToYZ();
	static Matrix CreateProjectToPlane(const Point3F& normal);
	static Matrix CreateFlipX();
	static Matrix CreateFlipY();
	static Matrix CreateFlipZ();
	static Matrix CreateFlipByPlane(const Point3F& normal);
	static Matrix CreateFlip(FlipMask flip = FlipMask::None, Point3F flipPivot = Point3F::Zero);

	static Matrix CreateShear(float xy, float xz, float yx, float yz, float zx, float zy);
	static Matrix CreateNormal();
	static Matrix CreateWorld(const Size3F& size, const Point3F& anchor, const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip = FlipMask::None);
	static Matrix CreateWorldWithoutAnchor(const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip = FlipMask::None);
	static Matrix CreateWorld(const Scale3F& scale, const Rotation3F& rotation, const Point3F& translation, FlipMask flip = FlipMask::None, Point3F flipPivot = Point3F::Zero, const Point3F& pivot = Point3F::Zero);



	static Matrix CreateBillboard(const Vector3F& objectPosition, const Vector3F& cameraPosition, const Vector3F& cameraUp, const Vector3F& cameraForward = Vector3F::ForWard, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix CreateConstrainedBillboard(const Vector3F& objectPosition, const Vector3F& cameraPosition, const Vector3F& rotateAxis, const Vector3F& cameraForward = Vector3F::ForWard, const Vector3F& objectForward = Vector3F::ForWard, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);


	static Matrix LookAtLH(const Vector3F& eyes, const Vector3F& target, const Vector3F& up);
	static Matrix LookAtRH(const Vector3F& eyes, const Vector3F& target, const Vector3F& up);
	static Matrix LookAt(const Vector3F& eyes, const Vector3F& target, const Vector3F& up, bool isRightHand = MEDUSA_IS_RIGHT_HAND);

	static Matrix OrthoLH(float width, float height, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix OrthoRH(float width, float height, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix Ortho(float width, float height, float nearPlane, float farPlane, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);

	static Matrix OrthoOffCenterLH(float left, float right, float bottom, float top, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix OrthoOffCenterRH(float left, float right, float bottom, float top, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix OrthoOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);

	static Matrix PerspectiveFOVLH(float fovY, float aspect, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix PerspectiveFOVRH(float fovY, float aspect, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix PerspectiveFOV(float fovY, float aspect, float nearPlane, float farPlane, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);

	static Matrix PerspectiveLH(float width, float height, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix PerspectiveRH(float width, float height, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix Perspective(float width, float height, float nearPlane, float farPlane, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);

	static Matrix PerspectiveOffCenterLH(float left, float right, float bottom, float top, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix PerspectiveOffCenterRH(float left, float right, float bottom, float top, float nearPlane, float farPlane, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);
	static Matrix PerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane, bool isRightHand = MEDUSA_IS_RIGHT_HAND, GraphicsSDK sdk = MEDUSA_DEFAULT_GRAPHICS_SDK);

private:
	//************************************
	// ????:    	AdjointMatrix
	// ????:   	Matrix	
	// ????:		?????????????
	// ????:		
	// ????:		
	//************************************
	Matrix AdjointMatrix();

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

	void UpdateFlag();
#pragma endregion Transform
public:
	const static Matrix Zero;
	const static Matrix Identity;
	const static byte Size = 16;
	const static byte RowSize = 4;
	const static byte ColumnSize = 4;

	union
	{
		float M[Size];

		struct
		{
            union{float M11;float A;}; union{float M12;float B;}; float M13; float M14;
			union{float M21;float C;}; union{float M22;float D;}; float M23; float M24;
			float M31; float M32; float M33; float M34;
			union{float M41;float X;}; union{float M42;float Y;}; union{float M43;float Z;}; float M44;
		};

		
	};

	MatrixFlags Flag;

};

//[PRE_DECLARE_BEGIN]
typedef LazyValue<Matrix> LazyMatrix;
//[PRE_DECLARE_END]
MEDUSA_END;
