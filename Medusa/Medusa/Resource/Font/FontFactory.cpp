// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "FontFactory.h"
#include "Resource/Font/BMPFont.h"
#include "Resource/Font/TTFFont.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/File.h"





MEDUSA_BEGIN;

FontFactory::FontFactory()
{

}

FontFactory::~FontFactory()
{

}
bool FontFactory::Initialize()
{

	return true;
}

bool FontFactory::Uninitialize()
{
	Clear();

	TTFFont::UninitializeLibrary();
	return true;
}
void FontFactory::Clear()
{
	RETURN_IF_EMPTY(mItems);
	SAFE_RELEASE_COLLECTION(mCacheItems);
	SAFE_RELEASE_DICTIONARY_VALUE(mItems);

}


void FontFactory::ReleaseCache()
{
	SAFE_RELEASE_COLLECTION(mCacheItems);
	Shrink();
}


void FontFactory::Shrink()
{
	RETURN_IF_EMPTY(mItems);
	List<FontId, EqualCompare<FontId> > unusedKeys;
	FOR_EACH_COLLECTION(i, mItems)
	{
		const FontId& fileId = i->Key;
		IFont* item = i->Value;
		if (!item->IsShared())
		{
			unusedKeys.Add(fileId);
		}
	}

	RETURN_IF_EMPTY(unusedKeys);
	FOR_EACH_COLLECTION(i, unusedKeys)
	{
		Remove(*i);
	}


}

bool FontFactory::Remove(const FontId& fontId)
{
	IFont* ani = mItems.RemoveOtherKeyWithValueReturned(fontId, fontId.HashCode(), nullptr);
	RETURN_FALSE_IF_NULL(ani);
	ani->Release();
	return true;
}

IFont* FontFactory::Find(const FontId& fontId) const
{
	return mItems.TryGetValueWithFailedByOtherKey(fontId, fontId.HashCode(), nullptr);
}

bool FontFactory::Add(IFont* val, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	RETURN_FALSE_IF_NULL(val);
	switch (shareType)
	{
		case ResourceShareType::Share:

			if (mItems.TryAdd(val->GetFontId(), val))
			{
				val->Retain();
				return true;
			}
			break;
		case ResourceShareType::ShareAndCache:

			if (mItems.TryAdd(val->GetFontId(), val))
			{
				val->Retain();
				mCacheItems.Add(val);
				val->Retain();

				return true;
			}

			break;
		default:
			return true;
	}

	return false;
}


IFont* FontFactory::Create(const FontId& fontId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IFont* resultFont = Find(fontId);
	RETURN_SELF_IF_NOT_NULL(resultFont);

	FileType fileType = FileInfo::ExtractType(fontId.Name);

	switch (fileType)
	{
		case FileType::png:
		{
			resultFont = BMPFont::CreateFromSingleTexture(fontId);
		}
		break;
		case FileType::pvr:
		{
			resultFont = BMPFont::CreateFromPVR(fontId);
		}
		break;
		case FileType::ttf:
		{
			resultFont = TTFFont::CreateFromFile(fontId);
		}
		break;
		case FileType::fnt:
		{

			const IStream* stream = FileSystem::Instance().ReadFile(fontId.ToRef());
			RETURN_NULL_IF_NULL(stream);

			char c1 = (char)stream->ReadChar();
			char c2 = (char)stream->ReadChar();
			char c3 = (char)stream->ReadChar();

			if (c1 == 'B'&&c2 == 'M'&&c3 == 'F')	//this is a binary file
			{
				resultFont = BMPFont::CreateFromBMPBinary(fontId, *stream);
			}
			else
			{
				SAFE_RELEASE(stream);
				stream = FileSystem::Instance().ReadFile(fontId.ToRef(),FileDataType::Text);
				resultFont = BMPFont::CreateFromBMPText(fontId, *stream);
			}

			SAFE_RELEASE(stream);
		}
		break;
		default:
			return nullptr;
			break;
	}

	Add(resultFont, shareType);
	return resultFont;
}

IFont* FontFactory::CreateFromSingleTexture(const FontId& fontId, wchar_t firstChar /*= L'0'*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	{
		IFont* resultFont = Find(fontId);
		RETURN_SELF_IF_NOT_NULL(resultFont);
	}
	
	BMPFont* resultFont = BMPFont::CreateFromSingleTexture(fontId, firstChar);
	Add(resultFont, shareType);
	return resultFont;
}

IFont* FontFactory::CreateFromMemory(const FontId& fontId, const MemoryByteData& data, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	//TODO: load from data

	IFont* resultFont = Find(fontId);
	RETURN_SELF_IF_NOT_NULL(resultFont);

	FileType fileType = FileInfo::ExtractType(fontId.Name);

	switch (fileType)
	{
		case FileType::pvr:
		{
			resultFont = BMPFont::CreateFromPVR(fontId);
		}
		break;
		case FileType::ttf:
		{
			resultFont = TTFFont::CreateFromFile(fontId);
		}
		break;
		case FileType::fnt:
		{
			const IStream* stream = FileSystem::Instance().ReadFile(fontId.ToRef());
			RETURN_NULL_IF_NULL(stream);

			char c1 = (char)stream->ReadChar();
			char c2 = (char)stream->ReadChar();
			char c3 = (char)stream->ReadChar();

			if (c1 == 'B'&&c2 == 'M'&&c3 == 'F')	//this is a binary file
			{
				resultFont = BMPFont::CreateFromBMPBinary(fontId, *stream);
			}
			else
			{
				SAFE_RELEASE(stream);
				stream = FileSystem::Instance().ReadFile(fontId.ToRef(),FileDataType::Text);
				resultFont = BMPFont::CreateFromBMPText(fontId, *stream);
			}

			SAFE_RELEASE(stream);
		}
		break;
		default:
			return nullptr;
			break;
	}

	Add(resultFont, shareType);
	return resultFont;
}



MEDUSA_END;