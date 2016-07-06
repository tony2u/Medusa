// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Geometry/PointPath2.h"
//SIREN_HEADER_INCLUDE_END
#include "Geometry/Line2.h"
MEDUSA_BEGIN;

class SingleStrokeTemplate
{
public:
	struct Schema;
	SingleStrokeTemplate();
	~SingleStrokeTemplate();
//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_STRING(HeapString, Name);
	SIREN_METHOD(PointPath2F, Path);
//SIREN_HEADER_METHOD_END
public:
	Point2F StartUnitVector() const { return mStartUnitVector; }
	void SetStartUnitVector(Point2F val) { mStartUnitVector = val; }

	const PointPath2F& Vectors() const { return mVectors; }
	PointPath2F& MutableVectors() { return mVectors; }
	void Add(Point2F val) { mPath.Add(val); }
	void AddRange(const List<Point2F>& items) { mPath.AddRange(items); }
	void AddLine(const Line2F& line, uint sampleCount);
	void AddLine(const Point2F& from,const Point2F& to, uint sampleCount);
	void AddLine(float fromX,float fromY,float toX,float toY, uint sampleCount);

	void BeginAdd(float fromX, float fromY);
	void AddTo(float toX, float toY, uint sampleCount);
	Point2F CurrentAdd()const { return mCurrentAddPoint; }

	void Clear();
public:
	void Normalize(size_t strokePointCount, float squareSize, bool ignoreRotation);
	void CalculateVectors();
//SIREN_HEADER_FIELD_BEGIN
protected:
	HeapString mName;
	PointPath2F mPath;
//SIREN_HEADER_FIELD_END

	Point2F mStartUnitVector;
	PointPath2F mVectors;
	Point2F mCurrentAddPoint;	//temp point for add
};

//SIREN_HEADER_SCHEMA_BEGIN
struct SingleStrokeTemplate::Schema
{
	SIREN_FIELD(0, 0, Required, SingleStrokeTemplate, HeapString, mName);
	SIREN_FIELD(1, 1, Required, SingleStrokeTemplate, PointPath2F, mPath);
	SIREN_FIELDS_2(void,SingleStrokeTemplate);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;