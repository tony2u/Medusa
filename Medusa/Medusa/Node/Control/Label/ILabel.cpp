// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ILabel.h"
#include "Resource/Font/IFont.h"
#include "Resource/Font/FontFactory.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;


ILabel::ILabel(StringRef name, const Share<IFont>& font, Alignment alignment/*=Alignment::LeftBottom*/, Size2F restrictSize/*=Size2F::Zero*/, bool isMultipleLine/*=true*/, bool isStatic/*=false*/)
	:INode(name),mFont(font),mAlignment(alignment),mRestrictSize(restrictSize),mIsMultipleLine(isMultipleLine),mIsStatic(isStatic)
{
	
}


ILabel::ILabel(const StringRef& name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:INode(name,e),mRestrictSize(Size2F::Zero)
{

}

ILabel::~ILabel(void)
{
	

}

bool ILabel::Initialize()
{
	return true;
}



void ILabel::SetRestrictSize(const Size2F& val)
{
	RETURN_IF_EQUAL(mRestrictSize,val);
	mRestrictSize=val;
	UpdateMesh();

}

void ILabel::EnableMultipleLine(bool val)
{
	RETURN_IF_EQUAL(mIsMultipleLine,val);
	mIsMultipleLine = val;
	UpdateMesh();
}

void ILabel::SetFont(const Share<IFont>& val)
{
	RETURN_IF_EQUAL(mFont,val);
	mFont = val;
	OnUpdateFont();
	UpdateMesh();

}


void ILabel::SetAlignment(Alignment val)
{
	RETURN_IF_EQUAL(mAlignment, val);
	mAlignment = val;
	UpdateMesh();

}


const FontId& ILabel::GetFontId() const
{
	if (mFont != nullptr)
	{
		return mFont->GetFontId();
	}
	return FontId::Empty;
}

bool ILabel::SetFontId(const FontId& val)
{
	if (mFont != nullptr)
	{
		RETURN_FALSE_IF_EQUAL(mFont->GetFontId(), val);
	}

	mFont = FontFactory::Instance().Create(val);
	
	OnUpdateFont();
	UpdateMesh();
	return true;
}

void ILabel::CommitChanges()
{
	UpdateMesh();
}

MEDUSA_END;
