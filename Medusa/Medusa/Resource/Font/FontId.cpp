// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "FontId.h"
#include "Core/IO/FileInfo.h"
MEDUSA_BEGIN;

FontId::FontId(const FileIdRef& fileId/*=FileId::Empty*/,uint size/*=12*/)
	:FileId(fileId),
	mSize(size),
	mColor(Color4F::Black),
	mBackgroundColor(Color4F::White),
	mOutlineColor(Color4F::Black),
	mUnderlineColor(Color4F::Black),
	mOverlineColor(Color4F::Black),
	mStrikethroughColor(Color4F::Black),
	mMatrix(Matrix2::Identity)
{
	mIsBitmap=IsBitmapFont(Name);
}
FontId::FontId(const char* name, uint size /*= 12*/)
	:FileId(FileIdRef(name)),
	mSize(size),
	mColor(Color4F::Black),
	mBackgroundColor(Color4F::White),
	mOutlineColor(Color4F::Black),
	mUnderlineColor(Color4F::Black),
	mOverlineColor(Color4F::Black),
	mStrikethroughColor(Color4F::Black),
	mMatrix(Matrix2::Identity)
{
	mIsBitmap = IsBitmapFont(Name);
}


FontId::FontId(const FontId& fontId)
{
	Name = fontId.Name;
	Order = fontId.Order;

	mIsBitmap = fontId.mIsBitmap;
	mDepth = fontId.mDepth;
	mOriginalSize = fontId.mOriginalSize;
	mSize = fontId.mSize;

	mRise = fontId.mRise;
	mSpacing = fontId.mSpacing;
	mGamma = fontId.mGamma;
	mFlags = fontId.mFlags;
	mOutlineType = fontId.mOutlineType;
	mUnderlineTickness = fontId.mUnderlineTickness;
	mOutlineThickness = fontId.mOutlineThickness;

	mColor = fontId.mColor;
	mBackgroundColor = fontId.mBackgroundColor;
	mOutlineColor = fontId.mOutlineColor;
	mUnderlineColor = fontId.mUnderlineColor;
	mOverlineColor = fontId.mOverlineColor;
	mStrikethroughColor = fontId.mStrikethroughColor;
	mLCDFilterType = fontId.mLCDFilterType;
	mMatrix = fontId.mMatrix;
}



FontId& FontId::operator=(const FontId& fontId)
{
	Name = fontId.Name;
	Order = fontId.Order;

	mIsBitmap = fontId.mIsBitmap;
	mDepth = fontId.mDepth;
	mOriginalSize = fontId.mOriginalSize;
	mSize = fontId.mSize;

	mRise = fontId.mRise;
	mSpacing = fontId.mSpacing;
	mGamma = fontId.mGamma;
	mFlags = fontId.mFlags;
	mOutlineType = fontId.mOutlineType;
	mUnderlineTickness = fontId.mUnderlineTickness;
	mOutlineThickness = fontId.mOutlineThickness;

	mColor = fontId.mColor;
	mBackgroundColor = fontId.mBackgroundColor;
	mOutlineColor = fontId.mOutlineColor;
	mUnderlineColor = fontId.mUnderlineColor;
	mOverlineColor = fontId.mOverlineColor;
	mStrikethroughColor = fontId.mStrikethroughColor;
	mLCDFilterType = fontId.mLCDFilterType;
	mMatrix = fontId.mMatrix;

	return *this;
}

bool FontId::IsBitmapFont(const StringRef& name)
{
	FileType fileType = FileInfo::ExtractType(name);
	switch (fileType)
	{
	case FileType::pvr:
	case FileType::fnt:
		return true;
	case FileType::ttf:
	default:
		return false;
		break;
	}
}

intp FontId::HashCode() const
{
	if (mIsBitmap)
	{
		return FileId::HashCode()^mSize;
	}
	else
	{

		intp hashCode=FileId::HashCode();
		hashCode^=(int)mDepth;
		hashCode^=mIsBitmap?1:0;
		hashCode^=mSize;
		hashCode^=mOriginalSize;

		hashCode^=HashUtility::Hash(mRise);
		hashCode^=HashUtility::Hash(mSpacing);
		hashCode^=HashUtility::Hash(mGamma);
		hashCode^=mFlags.ToInt();
		hashCode^=(int)mOutlineType;
		hashCode^=mUnderlineTickness;
		hashCode^=mOutlineThickness;

		hashCode^=mColor.HashCode();
		hashCode^=mBackgroundColor.HashCode();
		hashCode^=mOutlineColor.HashCode();
		hashCode^=mUnderlineColor.HashCode();
		hashCode^=mOverlineColor.HashCode();
		hashCode^=mStrikethroughColor.HashCode();

		hashCode^=(int)mLCDFilterType;
		hashCode^=mMatrix.HashCode();

		return hashCode;
	}

	
}

bool FontId::operator==( const FontId& val ) const
{
	if (mIsBitmap&&val.mIsBitmap)
	{
		return Name==val.Name&&Order==val.Order&&mSize==val.mSize;
	}

	return Name==val.Name&&
		Order==val.Order&&
		mIsBitmap==val.mIsBitmap&&
		mDepth==val.mDepth&&
		mSize==val.mSize&&
		mOriginalSize==val.mOriginalSize&&
		Math::IsEqual(mRise,val.mRise)&&
		Math::IsEqual(mSpacing,val.mSpacing)&&
		Math::IsEqual(mGamma,val.mGamma)&&
		mFlags==val.mFlags&&
		mOutlineType==val.mOutlineType&&
		mUnderlineTickness==val.mUnderlineTickness&&
		mOutlineThickness==val.mOutlineThickness&&
		mColor==val.mColor&&
		mBackgroundColor==val.mBackgroundColor&&
		mOutlineColor==val.mOutlineColor&&
		mUnderlineColor==val.mUnderlineColor&&
		mOverlineColor==val.mOverlineColor&&
		mStrikethroughColor==val.mStrikethroughColor&&
		mLCDFilterType==val.mLCDFilterType&&
		mMatrix==val.mMatrix;
}


const byte FontId::LightLCDFilter[5]={0x00, 0x55, 0x56, 0x55, 0x00};
const byte FontId::DefaultLCDFilter[5]={0x10, 0x40, 0x70, 0x40, 0x10};
const FontId FontId::Default(StringRef::Empty);






MEDUSA_END;