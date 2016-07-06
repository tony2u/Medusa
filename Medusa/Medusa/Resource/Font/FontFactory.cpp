// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "FontFactory.h"
#include "Resource/Font/BMPFont.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/File.h"
#include "Core/IO/Path.h"
#include "Core/System/System.h"

#ifdef MEDUSA_FREETYPE
#include "Resource/Font/TTFFont.h"
#endif
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

#ifdef MEDUSA_FREETYPE
	TTFFont::UninitializeLibrary();
#endif
	return true;
}
void FontFactory::Clear()
{
	RETURN_IF_EMPTY(mItems);
	mCacheItems.Clear();
	mItems.Clear();
	
	

}


void FontFactory::ReleaseCache()
{
	mCacheItems.Clear();
	Shrink();
}


void FontFactory::Shrink()
{
	RETURN_IF_EMPTY(mItems);
	List<FontId, EqualCompare > unusedKeys;
	for (auto& i : mItems)
	{
		const FontId& fileId = i.Key;
		auto& item = i.Value;
		if (!item->IsShared())
		{
			unusedKeys.Add(fileId);
		}
	}

	RETURN_IF_EMPTY(unusedKeys);
	for (auto i : unusedKeys)
	{
		Remove(i);
	}


}

bool FontFactory::Remove(const FontId& fontId)
{
	return mItems.RemoveOtherKey(fontId, fontId.HashCode());
}

Share<IFont> FontFactory::Find(const FontId& fontId) const
{
	return mItems.GetOptionalByOtherKey(fontId, fontId.HashCode(), nullptr);
}

bool FontFactory::Add(const Share<IFont>& val, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	RETURN_FALSE_IF_NULL(val);
	switch (shareType)
	{
	case ResourceShareType::Share:

		if (mItems.TryAdd(val->GetFontId(), val))
		{
			return true;
		}
		break;
	case ResourceShareType::ShareAndCache:

		if (mItems.TryAdd(val->GetFontId(), val))
		{
			mCacheItems.Add(val);
			return true;
		}

		break;
	default:
		return true;
	}

	return false;
}


Share<IFont> FontFactory::Create(const FontId& fontId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<IFont> resultFont = nullptr;
	if (shareType != ResourceShareType::None)
	{
		resultFont = Find(fontId);
		RETURN_SELF_IF_NOT_NULL(resultFont);
	}

	if (Path::HasExtension(fontId.Name))
	{

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
#ifdef MEDUSA_FREETYPE
		case FileType::ttf:
		case FileType::ttc:
		{
			resultFont = TTFFont::CreateFromFile(fontId);
		}
		break;
#endif
		case FileType::fnt:
		{

			auto stream = FileSystem::Instance().Read(fontId.ToRef());
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
			
				stream = FileSystem::Instance().Read(fontId.ToRef(), FileDataType::Text);
				resultFont = BMPFont::CreateFromBMPText(fontId, *stream);
			}

		}
		break;
		default:
			return nullptr;
			break;
		}
	}
	else
	{
		WHeapString fontName = StringParser::ToW(fontId.Name);
#ifdef MEDUSA_FREETYPE
		//system font
		auto data= System::Instance().GetFontData(fontName);
		if (!data.IsNull())
		{
			resultFont = TTFFont::CreateFromData(fontId,data);
		}
		else
		{
			Log::FormatError(L"Cannot open system font:{}", fontName);
		}
#else
		Log::FormatError(L"Cannot open system font:{} without freetype support", fontName);
#endif
	}

	Add(resultFont, shareType);
	return resultFont;
}

Share<IFont> FontFactory::CreateFromSingleTexture(const FontId& fontId, wchar_t firstChar /*= L'0'*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{

	if (shareType != ResourceShareType::None)
	{
		auto resultFont = Find(fontId);
		RETURN_SELF_IF_NOT_NULL(resultFont);
	}

	auto resultFont = BMPFont::CreateFromSingleTexture(fontId, firstChar);
	Add(resultFont, shareType);
	return resultFont;
}

Share<IFont> FontFactory::CreateFromMemory(const FontId& fontId, const MemoryData& data, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	//TODO: load from data
	Share<IFont> resultFont;
	if (shareType != ResourceShareType::None)
	{
		resultFont = Find(fontId);
		RETURN_SELF_IF_NOT_NULL(resultFont);
	}

	FileType fileType = FileInfo::ExtractType(fontId.Name);

	switch (fileType)
	{
	case FileType::pvr:
	{
		resultFont = BMPFont::CreateFromPVR(fontId);
	}
	break;
#ifdef MEDUSA_FREETYPE
	case FileType::ttf:
	{
		resultFont = TTFFont::CreateFromFile(fontId);
	}
	break;
#endif
	case FileType::fnt:
	{
		auto stream = FileSystem::Instance().Read(fontId.ToRef());
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
			stream = FileSystem::Instance().Read(fontId.ToRef(), FileDataType::Text);
			resultFont = BMPFont::CreateFromBMPText(fontId, *stream);
		}
	}
	break;
	default:
		return nullptr;
		break;
	}

	Add(resultFont, shareType);
	return resultFont;
}


bool FontFactory::Exists(const StringRef& fontName) const
{
	return Exists(FileIdRef(fontName));
}

StringRef FontFactory::ExistsOr(const StringRef& fontName, const StringRef& optional) const
{
	if (Exists(fontName))
	{
		return fontName;
	}
	return optional;
}

StringRef FontFactory::ExistsOrDefault(const StringRef& fontName) const
{
	if (Exists(fontName))
	{
		return fontName;
	}
	return System::Instance().CurrentFontName();
}

FileIdRef FontFactory::ExistsOrDefault(const FileIdRef& fileId) const
{
	if (Exists(fileId))
	{
		return fileId;
	}
	return System::Instance().CurrentFontName();
}

bool FontFactory::Exists(const FileIdRef& fontName) const
{
	if (fontName.Order != 0)
	{
		return FileSystem::Instance().Exists(fontName);
	}
	if (Path::HasExtension(fontName.Name))	//.ttf,.ttc,.fnt
	{
		return FileSystem::Instance().Exists(fontName);
	}
	else
	{
		//check system font
		WHeapString str = StringParser::ToW(fontName.Name);
		return System::Instance().ContainsFont(str);
	}
}

FileIdRef FontFactory::ExistsOr(const FileIdRef& fileId, const FileIdRef& optional) const
{
	if (Exists(fileId))
	{
		return fileId;
	}
	return optional;
}


MEDUSA_END;

