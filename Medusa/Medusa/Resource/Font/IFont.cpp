// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IFont.h"
#include "Resource/Material/IMaterial.h"

MEDUSA_BEGIN;

IFont::IFont(const FontId& fontId)
	:IResource(fontId.ToRef()),mFontId(fontId), mFlags(FontFlags::HasHorizontal)
{
	mPadding=Padding4I::Zero;
	mSpacing=Point2I::Zero;
	mImageSize=Size2U::Zero;
	mChannel=Color4F::Zero;
	mMaxAdvance=Size2U::Zero;
}


IFont::~IFont(void)
{
	SAFE_RELEASE_COLLECTION(mMaterials);
	SAFE_DELETE_DICTIONARY_VALUE(mChars);
	SAFE_DELETE_DICTIONARY_VALUE(mKernings);

}

void IFont::AddChar( FontChar* fontChar )
{
	mChars.Add(fontChar->Id,fontChar);
}

const FontChar* IFont::GetChar(wchar_t c) const
{
	return mChars.TryGetValueWithFailed(c,nullptr);
}

FontChar* IFont::GetChar(wchar_t c)
{
	return mChars.TryGetValueWithFailed(c,nullptr);
}

const FontChar* IFont::TryLoadChar(wchar_t c)
{
	const FontChar* result=GetChar(c);
	RETURN_SELF_IF_NOT_NULL(result);
	return OnLoadChar(c);
}

void IFont::AddKerning( FontKerning* pair )
{
	mKernings.Add(pair->Pair,pair);
}

void IFont::AddMaterial( IMaterial* textureMaterial )
{
	textureMaterial->Retain();
	mMaterials.Add(textureMaterial);
}

void IFont::TryAddMaterial(IMaterial* textureMaterial)
{
	if(!mMaterials.Contains(textureMaterial))
	{
		textureMaterial->Retain();
		mMaterials.Add(textureMaterial);
	}
}


const FontKerning* IFont::GetKerning( int prev,int next ) const
{
	uint64 id=((uint64)prev<<32)|((uint64)next);
	return mKernings.TryGetValueWithFailed(id,nullptr);
}

FontKerning* IFont::GetKerning( int prev,int next )
{
	uint64 id=((uint64)prev<<32)|((uint64)next);
	return mKernings.TryGetValueWithFailed(id,nullptr);
}

const FontKerning* IFont::TryLoadKerning( int prev,int next )
{
	const FontKerning* result=GetKerning(prev,next);
	RETURN_SELF_IF_NOT_NULL(result);
	return OnLoadKerning(prev,next);
}




MEDUSA_END;