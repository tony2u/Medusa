// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TNodeTemplate.h"
#include "Resource/Font/FontId.h"

MEDUSA_BEGIN;

class LabelTemplate :public TNodeTemplate<WHeapString>
{
public:
	LabelTemplate(bool isSingleLine = true);
	virtual ~LabelTemplate(void);

	virtual Size2F Measure(const WHeapString& data, const Size2F& limitSize = Size2F::Zero)const override;
	virtual INode* Load(const WHeapString& data, const Size2F& limitSize = Size2F::Zero, INode* reloadNode = nullptr)const override;

public:
	const FontId& GetFontId() const { return mFontId; }
	FontId& MutableFontId() { return mFontId; }

	Alignment GetAlignment() const { return mAlignment; }
	void SetAlignment(Alignment val) { mAlignment = val; }


	bool IsStatic() const { return mIsStatic; }
	void SetIsStatic(bool val) { mIsStatic = val; }

protected:
	HeapString mFontName;
	FontId mFontId;
	Alignment mAlignment = Alignment::LeftBottom;
	bool mIsSingleLine = true;
	bool mIsStatic = true;

};

MEDUSA_END;
