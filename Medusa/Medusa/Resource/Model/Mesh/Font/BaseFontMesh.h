// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Resource/Model/Mesh/IMesh.h"

MEDUSA_BEGIN;

/*
We choose separate buffer instead of interleaved, because we want to update only one component 
*/
class BaseFontMesh:public IMesh
{
public:
	BaseFontMesh(bool isStatic=false);
	virtual ~BaseFontMesh(void);
public:
	virtual void ReserveMesh(uint charCount){}
	virtual void ShrinkMesh(){}

	virtual void AddFontChar(const IFont& font,const FontChar& fontChar,const Point3F& origin){}
	virtual bool HasChars()const{ return false; }

	virtual Point2F GetCharPosition(uint charIndex)const = 0;
	virtual Point2F GetCursorPosition(uint charIndex)const = 0;
	virtual uint FindCharIndex(const Point2F& touchPosition, Point2F& outCharPosition)const = 0;
};

MEDUSA_END;