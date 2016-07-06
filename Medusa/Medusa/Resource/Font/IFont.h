// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Font/FontChar.h"
#include "Resource/Font/FontId.h"
#include "Core/Collection/Dictionary.h"
#include "Resource/IResource.h"
#include "Geometry/Padding4.h"
#include "Geometry/Point2.h"
#include "Geometry/Size2.h"
#include "Geometry/Color4.h"
#include "FontDefines.h"

MEDUSA_BEGIN;



class IFont :public IResource
{
public:
	IFont(const FontId& fontId);
	virtual ~IFont(void);
public:
	virtual ResourceType Type()const { return ResourceType::Font; }
	static ResourceType ClassGetResourceType() { return ResourceType::Font; }

	virtual bool IsBitmap()const = 0;

	StringRef FamilyName() const { return mFamilyName; }
	void SetFamilyName(const StringRef& val) { mFamilyName = val; }

	StringRef StyleName() const { return mStyleName; }
	void SetStyleName(const StringRef& val) { mStyleName = val; }

	void AddChar(FontChar* fontChar);
	void AddKerning(FontKerning* pair);
	const FontChar* GetChar(wchar_t c)const;
	FontChar* GetChar(wchar_t c);

	const FontChar* TryLoadChar(wchar_t c);

	const FontId& GetFontId() const { return mFontId; }
	FontId& MutableFontId() { return mFontId; }

	void SetFontId(const FontId& val) { mFontId = val; OnUpdateFontId(); }

	uint Size() const { return mFontId.Size(); }

	uintp LineHeight() const { return mLineHeight; }
	void SetLineHeight(uintp val) { mLineHeight = val; }

	uint TotalCharCount() const { return mTotalCharCount; }
	void SetTotalCharCount(uint val) { mTotalCharCount = val; }

	uint KerningPairsCount() const { return static_cast<uint>(mKernings.Count()); }

	intp Ascender() const { return mAscender; }
	void SetAscender(intp val) { mAscender = val; }

	intp Descender() const { return mDescender; }
	void SetDescender(intp val) { mDescender = val; }

	uint SpaceWidth() const { return mSpaceFontChar->HAdvance; }
	const FontChar* SpaceFontChar() const { return mSpaceFontChar; }
	void SetSpaceFontChar(const FontChar* val) { mSpaceFontChar = val; }


	const FontKerning* GetKerning(int prev, int next)const;
	FontKerning* GetKerning(int prev, int next);
	const FontKerning* TryLoadKerning(int prev, int next);

	bool HasKerning()const { return MEDUSA_FLAG_HAS(mFlags, FontFlags::HasKerning); }

	bool HasSinglePage()const;
	virtual bool IsFixed()const { return true; }

	bool IsBold() const { return MEDUSA_FLAG_HAS(mFlags, FontFlags::IsBold); }
	void SetIsBold(bool val) { MEDUSA_FLAG_ENABLE(mFlags, FontFlags::IsBold, val); }

	bool IsItalic() const { return MEDUSA_FLAG_HAS(mFlags, FontFlags::IsItalic); }
	void SetIsItalic(bool val) { MEDUSA_FLAG_ENABLE(mFlags, FontFlags::IsItalic, val); }

	bool IsPacked() const { return mIsPacked; }
	void SetIsPacked(bool val) { mIsPacked = val; }

	void SetOutlineThickness(uint val) { mFontId.SetOutlineThickness(val); }

	const Padding4I& Padding() const { return mPadding; }
	void SetPadding(const Padding4I& val) { mPadding = val; }

	Point2I Spacing() const { return mSpacing; }
	void SetSpacing(Point2I val) { mSpacing = val; }

	const Size2U& ImageSize() const { return mImageSize; }
	void SetImageSize(Size2U val) { mImageSize = val; }

	Color4F Channel() const { return mChannel; }
	void SetChannel(Color4F val) { mChannel = val; }

	FontFlags Flags() const { return mFlags; }
	void SetFlags(FontFlags val) { mFlags = val; }
	uint OriginalSize() const { return mOriginalSize; }
	void SetOriginalSize(uint val) { mOriginalSize = val; }

	const Share<TextureAtlas>& Atlas() const { return mAtlas; }
	void SetAtlas(const Share<TextureAtlas>& val);

	virtual uint Preload(const WStringRef& str) { return 0; }
protected:
	virtual const FontChar* OnLoadChar(wchar_t c) { return nullptr; }
	virtual const FontKerning* OnLoadKerning(int prev, int next) { return nullptr; }
	virtual bool OnUpdateFontId() { return true; }
protected:
	FontId mFontId;
	uint mTotalCharCount = 0;
	HeapString mFamilyName;
	HeapString mStyleName;
	FontFlags mFlags;
	uint mOriginalSize = 0;


	Padding4I mPadding;	//	The padding for each character (up, right, down, left).
	Point2I mSpacing;	//	The spacing for each character (horizontal, vertical).
	Size2U mImageSize;

	bool mIsPacked = false;	//Set to 1 if the monochrome characters have been packed into each of the texture channels. In this case alphaChnl describes what is stored in each channel.
	Color4F mChannel;	//Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one.

	//layout
	uintp mLineHeight = 0;
	intp mAscender = 0;	//height above base line
	intp mDescender = 0;	//height below base line
	Size2U mMaxAdvance;

	intp mUnderlinePosition = 0;
	uintp mUnderlineTickness = 0;

	//contents
	Share<TextureAtlas> mAtlas;

	Dictionary<wchar_t, FontChar*> mChars;
	Dictionary<uint64, FontKerning*> mKernings;

	const FontChar* mSpaceFontChar = nullptr;

	//const static char* mASCIIChars;
	const static char* mNEHEChars;

};

MEDUSA_END;