// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Siren/SirenHeader.h"

//SIREN_HEADER_INCLUDE_BEGIN
#include "Node/Input/Gesture/Stroke/SingleStrokeTemplate.h"
#include "Core/Siren/ISirenConfig.h"
//SIREN_HEADER_INCLUDE_END
#include "StrokeTypes.h"

MEDUSA_BEGIN;

class SingleStrokeLibrary : public ISirenConfig<SingleStrokeLibrary>
{
public:
	// How many points do we use to represent a gesture
	// Best results between 32-256
	constexpr static size_t StrokePointCount = 128;
	// Before matching, we stretch the symbol across a square
	// That way we don't have to worry about the symbol the user drew
	//  being smaller or larger than the one in the template
	constexpr static float SquareSize = 250.f;
	// 1/2 max distance across a square, which is the maximum distance
	//  a point can be from the center of the gesture
	//mSquareDiagonalHalf = 0.5 * sqrt((250.0 * 250.0) + (250.0 * 250.0));
	constexpr static float mSquareDiagonalHalf = 176.7766952966369f;

	constexpr static float mAnglePrecision = 2.f;
	// A magic number used in pre-processing the symbols
	constexpr static float mGoldenRatio = 0.6180339887498948f;	//use golden search to best match
public:
	struct Schema;
	SingleStrokeLibrary();
	~SingleStrokeLibrary();
public:
	bool IsIgnoreRotation()const { return mIgnoreRotation; }
	void EnableIgnoreRotation(bool val) { mIgnoreRotation = val; }

	void Add(SingleStrokeTemplate* val);
public:
	const SingleStrokeTemplate* Recognize(float& outScore, SingleStrokeTemplate& val, SingleStrokeRecognizeAlgorithm algorithm = SingleStrokeRecognizeAlgorithm::Protractor)const;
protected:
	float AngleRange()const { return mIgnoreRotation ? 45.f : 15.f; }
	double DistanceAtAngle(const PointPath2F& from, const PointPath2F& to, float rotation)const;
	double DistanceAtBestAngle(const PointPath2F& from, const PointPath2F& to)const;
	double OptimalCosineDistance(const PointPath2F& from, const PointPath2F& to)const; // for Protractor
	virtual bool OnLoaded() override;

	//SIREN_HEADER_METHOD_BEGIN
public:
	SIREN_METHOD_LIST(SingleStrokeTemplate*, Templates);
	//SIREN_HEADER_METHOD_END
protected:
	//SIREN_HEADER_FIELD_BEGIN
protected:
	List<SingleStrokeTemplate*> mTemplates;
	//SIREN_HEADER_FIELD_END

	// Before matching, we rotate the symbol the user drew so that the 
	//  start point is at degree 0 (right side of symbol). That's how 
	//  the templates are rotated so it makes matching easier
	// Note: this assumes we want symbols to be rotation-invariant, 
	//  which we might not want. Using this, we can't tell the difference
	//  between squares and diamonds (which is just a rotated square)
	bool mIgnoreRotation = false;

};

//SIREN_HEADER_SCHEMA_BEGIN
struct SingleStrokeLibrary::Schema
{
	SIREN_FIELD_LIST(0, 0, Required, SingleStrokeLibrary, SingleStrokeTemplate*, mTemplates);
	SIREN_FIELDS_1(void, SingleStrokeLibrary);
};
//SIREN_HEADER_SCHEMA_END

MEDUSA_END;