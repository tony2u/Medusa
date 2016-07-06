// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IFont.h"
#include "Resource/TextureAtlas/TextureAtlasFactory.h"

MEDUSA_BEGIN;

IFont::IFont(const FontId& fontId)
	:IResource(fontId.ToRef()), mFontId(fontId), mFlags(FontFlags::HasHorizontal)
{
	mPadding = Padding4I::Zero;
	mSpacing = Point2I::Zero;
	mImageSize = Size2U::Zero;
	mChannel = Color4F::Zero;
	mMaxAdvance = Size2U::Zero;

	FileId atlasId = fontId;
	if (!fontId.IsBitmap())
	{
		atlasId.Name.Format("{}@{}{}", fontId.Name,mId,FileExtensions::matlas);
	}

	mAtlas = TextureAtlasFactory::Instance().CreateEmpty(atlasId, ResourceShareType::None);		//TODO: expand to single+font id
}


IFont::~IFont(void)
{
	SAFE_DELETE_DICTIONARY_VALUE(mChars);
	SAFE_DELETE_DICTIONARY_VALUE(mKernings);
	
}

void IFont::AddChar(FontChar* fontChar)
{
	mChars.Add(fontChar->Id, fontChar);
}

const FontChar* IFont::GetChar(wchar_t c) const
{
	return mChars.GetOptional(c, nullptr);
}

FontChar* IFont::GetChar(wchar_t c)
{
	return mChars.GetOptional(c, nullptr);
}

const FontChar* IFont::TryLoadChar(wchar_t c)
{
	const FontChar* result = GetChar(c);
	RETURN_SELF_IF_NOT_NULL(result);
	return OnLoadChar(c);
}

void IFont::AddKerning(FontKerning* pair)
{
	mKernings.Add(pair->Pair, pair);
}


const FontKerning* IFont::GetKerning(int prev, int next) const
{
	uint64 id = ((uint64)prev << 32) | ((uint64)next);
	return mKernings.GetOptional(id, nullptr);
}

FontKerning* IFont::GetKerning(int prev, int next)
{
	uint64 id = ((uint64)prev << 32) | ((uint64)next);
	return mKernings.GetOptional(id, nullptr);
}

const FontKerning* IFont::TryLoadKerning(int prev, int next)
{
	const FontKerning* result = GetKerning(prev, next);
	RETURN_SELF_IF_NOT_NULL(result);
	return OnLoadKerning(prev, next);
}


bool IFont::HasSinglePage() const
{
	return mAtlas->PageCount() == 1;
}


void IFont::SetAtlas(const Share<TextureAtlas>& val)
{
	mAtlas = val;
}

//const char* IFont::mASCIIChars = "\"!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþ ";
const char* IFont::mNEHEChars = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ";

MEDUSA_END;

