// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"

MEDUSA_BEGIN;


enum class FlipMask
{
	None = 0,
	X = 1,
	Y = 2,
	Z = 4,
};


enum class Direction
{
	Horizontal = 0,
	Vertical
};

enum class Alignment
{
	LeftTop = 0,
	MiddleTop,
	RightTop,
	LeftCenter,
	MiddleCenter,
	RightCenter,
	LeftBottom,
	MiddleBottom,
	RightBottom
};

enum class DockPoint
{
	None = -1,
	LeftTop = 0,
	MiddleTop,
	RightTop,
	LeftCenter,
	MiddleCenter,
	RightCenter,
	LeftBottom,
	MiddleBottom,
	RightBottom,
	Percent,
};

enum class MarginEdges
{
	None = 0,
	Left = 1,
	Right = 2,
	Horizontal = Left | Right,
	Bottom = 4,
	Top = 8,
	Vertical = Bottom | Top,
};


enum class AnchorPoint
{
	LeftTop = 0,
	MiddleTop,
	RightTop,
	LeftCenter,
	MiddleCenter,
	RightCenter,
	LeftBottom,
	MiddleBottom,
	RightBottom
};



enum class Orientation
{
	Left = 0,
	Right,
	Down,
	Up,
};

//     Describes how content is resized to fill its allocated space.
enum class Stretch
{
	None = 0,
	//     The content is resized to fill the destination dimensions. The aspect ratio
	//     is not preserved.
	Fill = 1,
	//     The content is resized to fit in the destination dimensions while it preserves
	//     its native aspect ratio.
	Uniform = 2,
	//     The content is resized to fill the destination dimensions while it preserves
	//     its native aspect ratio. If the aspect ratio of the destination rectangle
	//     differs from the source, the source content is clipped to fit in the destination
	//     dimensions.
	UniformToFill = 3,

	FillWidth = 4,
	FillHeight = 5,
	Percent = 6,

	ExpandWidth = 7,
	ExpandHeight = 8,

};


enum class SizeToContent
{
	None = 0,
	Width = 1,
	Height = 2,
	WidthAndHeight = 3,
	Mesh = 4,
};


enum class FlowDirection
{
	LeftToRight = 0,
	RightToLeft = 1,
};


enum class MatrixOrder
{
	Append = 0,
	Prepend
};

enum class MatrixFlags
{
	None = 0,
	Affine = 1,
	Is2D = 2,
};



//** Determines whether clip space Z ranges from -1 to 1 (OpenGL) or from 0 to 1 (DirectX)
enum class GraphicsSDK
{
	OpenGL = 0,
	DirectX
};

enum class MatrixMultiplyOperation
{
	Matrix4_Matrix4 = 0,
	Matrix4_Matrix43 = 1,
	Matrix4_Matrix3 = 2,
	Matrix4_Matrix2 = 3,

	Matrix43_Matrix4 = (1 << 8) + 0,
	Matrix43_Matrix43 = (1 << 8) + 1,
	Matrix43_Matrix3 = (1 << 8) + 2,
	Matrix43_Matrix2 = (1 << 8) + 3,

	Matrix3_Matrix4 = (2 << 8) + 0,
	Matrix3_Matrix43 = (2 << 8) + 1,
	Matrix3_Matrix3 = (2 << 8) + 2,
	Matrix3_Matrix2 = (2 << 8) + 3,

	Matrix2_Matrix4 = (3 << 8) + 0,
	Matrix2_Matrix43 = (3 << 8) + 1,
	Matrix2_Matrix3 = (3 << 8) + 2,
	Matrix2_Matrix2 = (3 << 8) + 3,

};

enum class MatrixType
{
	Matrix4 = 0,
	Matrix43 = 1,
	Matrix3 = 2,
	Matrix2 = 3,
};

//x,y,z
enum class RotationType
{
	None = 0,
	X = 1,
	Y = 2,
	XY = 3,
	Z = 4,
	XZ = 5,
	YZ = 6,
	XYZ = 7
};

enum class MoveableChangedFlags
{
	None = 0,
	SizeChanged = 1,
	PositionChanged = 2,
	RotationChanged = 4,
	ScaleChanged = 8,
	SkewChanged = 16,
	AnchorChanged = 32,
	FlipChanged = 64,
	MatrixChanged = 128,
	WorldMatrixChanged = 256,
	InheritChanged = 512
};

enum class MoveableInheritFlags
{
	None = 0,
	IgnoreScale = 1,
	IgnoreRotation = 2,
	IgnoreFlip = 4,

};

enum class OrientationMask
{
	None = 0,
	Up = 1,
	Down = 2,
	Left = 4,
	Right = 8,
	UpAndDown = 3,
	LeftAndRight = 12,
	AllButDown = 13
};


enum class RotateDirection
{
	None = 0,
	CounterClockWise = 1,
	ClockWise = 2,
};

#define MEDUSA_MATRIX_MULTIPLY_DEFAULT_ORDER (MatrixOrder::Append)
#define MEDUSA_MATRIX_TRANSFORM_DEFAULT_ORDER (MatrixOrder::Prepend)

#if MEDUSA_IS_OPENGL==1
#define MEDUSA_IS_RIGHT_HAND	(true)
#define MEDUSA_DEFAULT_GRAPHICS_SDK		(GraphicsSDK::OpenGL)
#else
#define MEDUSA_IS_RIGHT_HAND	(false)
#define MEDUSA_DEFAULT_GRAPHICS_SDK		(GraphicsSDK::DirectX)

#endif



MEDUSA_END;