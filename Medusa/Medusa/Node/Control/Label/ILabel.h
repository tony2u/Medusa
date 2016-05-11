// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Node/INode.h"
#include "Core/String/HeapString.h"
#include "Geometry/Moveable/DefaultMoveable.h"
#include "Geometry/Color4.h"
#include "Core/String/IStringWrapper.h"

MEDUSA_BEGIN;

class ILabel :public INode, public IWStringWrapper
{
	MEDUSA_DECLARE_RTTI;
public:
	ILabel(StringRef name, IFont* font, Alignment alignment = Alignment::LeftBottom, Size2F restrictSize = Size2F::Zero, bool isMultipleLine = true, bool isStatic = false);
	virtual ~ILabel(void);
	virtual bool Initialize() override;
public:
	IFont* Font() const { return mFont; }
	void SetFont(IFont* val);

	const FontId& GetFontId()const;
	bool SetFontId(const FontId& val);

	Alignment GetAlignment() const { return mAlignment; }
	void SetAlignment(Alignment val);

	const Size2F& RestrictSize() const { return mRestrictSize; }
	void SetRestrictSize(const Size2F& val);

	bool IsMultipleLine() const { return mIsMultipleLine; }
	void EnableMultipleLine(bool val);

	virtual BaseFontMesh* CreateFontMesh(TextureAtlasPage* page, bool isStatic = false) { return nullptr; }

	bool IsStatic() const { return mIsStatic; }
	void SetIsStatic(bool val) { mIsStatic = val; }

	virtual void CommitChanges();	//refresh after text changed outside

	virtual Point2F GetCharPosition(uint charIndex)const = 0;
	virtual Point2F GetCursorPosition(uint charIndex)const = 0;
	virtual uint FindCharIndex(const Point2F& touchPosition, Point2F& outCharPosition)const = 0;
	virtual void UpdateMesh() {}
	virtual void OnStringChanged() override { UpdateMesh(); }
protected:
	virtual void OnUpdateFont() {}

protected:
	IFont* mFont;
	Alignment mAlignment;
	Size2F mRestrictSize;
	bool mIsMultipleLine;

	bool mIsStatic;

};

MEDUSA_END;
