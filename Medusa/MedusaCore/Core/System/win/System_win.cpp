// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_WINDOWS

#include "Core/System/System.h"
#include "Core/IO/Directory.h"
#include "Core/String/StringParser.h"
#include "Core/IO/File.h"
#include "Core/IO/Path.h"

MEDUSA_BEGIN;

WHeapString GetSystemFontPath(const WStringRef& faceName)
{
	static const LPWSTR fontRegistryPath = L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts";
	HKEY hKey;
	LONG result;

	// Open Windows font registry key
	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, fontRegistryPath, 0, KEY_READ, &hKey);
	if (result != ERROR_SUCCESS)
	{
		return WHeapString::Empty;
	}

	DWORD maxValueNameSize, maxValueDataSize;
	result = RegQueryInfoKey(hKey, 0, 0, 0, 0, 0, 0, 0, &maxValueNameSize, &maxValueDataSize, 0, 0);
	if (result != ERROR_SUCCESS)
	{
		return WHeapString::Empty;
	}

	DWORD valueIndex = 0;
	LPWSTR valueName = new WCHAR[maxValueNameSize];
	LPBYTE valueData = new BYTE[maxValueDataSize];
	DWORD valueNameSize, valueDataSize, valueType;
	WHeapString resultFontFile;

	// Look for a matching font name
	do
	{

		resultFontFile.Clear();
		valueDataSize = maxValueDataSize;
		valueNameSize = maxValueNameSize;

		result = RegEnumValue(hKey, valueIndex, valueName, &valueNameSize, 0, &valueType, valueData, &valueDataSize);

		valueIndex++;

		if (result != ERROR_SUCCESS || valueType != REG_SZ)
		{
			continue;
		}

		WStringRef wsValueName(valueName, valueNameSize);

		// Found a match
		if (wsValueName.BeginWith(faceName))
		{
			resultFontFile = WStringRef((LPWSTR)valueData, valueDataSize);
			break;
		}

	} while (result != ERROR_NO_MORE_ITEMS);

	delete[] valueName;
	delete[] valueData;

	RegCloseKey(hKey);

	if (resultFontFile.IsEmpty())
	{
		return WHeapString::Empty;
	}

	// Build full font file path
	WHeapString resultPath;
	resultPath.ReserveSize(MAX_PATH);
	uint len = GetWindowsDirectory(resultPath.MutableBuffer(), MAX_PATH);	//add win dir path
	resultPath.ForceSetLength(len);

	resultPath += L"\\Fonts\\";
	resultPath += resultFontFile;
	return resultPath;
}

static MemoryData GetFontDataHelper(const HFONT fontHandle)
{
	//only work with ttf,but not ttc
	MemoryData result;
	HDC hdc = ::CreateCompatibleDC(NULL);
	if (hdc != NULL)
	{
		::SelectObject(hdc, fontHandle);
		const DWORD size = ::GetFontData(hdc, 0, 0, NULL, 0);
		if (size > 0)
		{
			result = MemoryData::Alloc(size);
			if (::GetFontData(hdc, 0, 0, result.MutableData(), size) != size)
			{
				result = MemoryData::Empty;
			}
		}
		::DeleteDC(hdc);
	}
	return result;
}
static int CALLBACK EnumFontFamExProc(ENUMLOGFONTEX* /*lpelfe*/, NEWTEXTMETRICEX* /*lpntme*/, int /*FontType*/, LPARAM lParam)
{
	LPARAM* l = (LPARAM*)lParam;
	*l = TRUE;
	return TRUE;
}

System::System(void)
{
	UpdatePaths();
	mCurrentFontName = "Microsoft YaHei";	//use Yahei in windows, but you can change it
}

void System::UpdatePaths()
{
	if (mWorkingPath.IsEmpty())
	{
		char buffer[512];
		GetCurrentDirectoryA(sizeof(buffer), buffer);
		mWorkingPath = buffer;

		::GetTempPathA(sizeof(buffer) / sizeof(char), buffer);
		mTempPath = buffer;
	}
	else
	{
		mTempPath = mWorkingPath;
	}

	mApplicationPath = mWorkingPath;
	mReadonlyPath = mApplicationPath;
	mWritablePath = mApplicationPath;

	mReadonlyPath = Path::CombineNoChecks(mReadonlyPath, mReadonlySubPath);
	mWritablePath = Path::CombineNoChecks(mWritablePath, mWritableSubPath);
	mTempPath = Path::CombineNoChecks(mTempPath, mTempSubPath);
}


WHeapString System::DefaultFontName()
{
	LOGFONT lf;
	SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &lf, 0);
	return WHeapString(lf.lfFaceName);
}


bool System::ContainsFont(WStringRef fontName)
{
	if (fontName.IsEmpty())
	{
		return false;
	}
	HDC hdc = ::CreateCompatibleDC(NULL);
	// Get the screen DC
	if (hdc == nullptr)
	{
		return false;
	}
	LOGFONT lf = { 0 };
	// Any character set will do
	lf.lfCharSet = DEFAULT_CHARSET;
	// Set the facename to check for
	wcscpy_s(lf.lfFaceName, sizeof(lf.lfFaceName), fontName.c_str());
	LPARAM lParam = 0;
	// Enumerate fonts
	::EnumFontFamiliesEx(hdc, &lf, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)&lParam, 0);
	return lParam ? true : false;
}

MemoryData System::GetFontData(WStringRef fontName /*= WStringRef::Empty*/)
{
	auto path = GetSystemFontPath(fontName);
	auto realPath = StringParser::ToA(path);
	return File::ReadAllData(realPath);
}


MEDUSA_END;
#endif
