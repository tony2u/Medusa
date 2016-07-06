// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/System/PublishTarget.h"
#include "Core/Math/Math.h"
#include "Core/IO/Path.h"
#include "Core/Log/Log.h"
#include "Core/String/StringParser.h"

MEDUSA_BEGIN;


PublishTarget::PublishTarget() :Version(Math::IntMinValue), Device(Math::IntMinValue), Language(Math::IntMinValue)
{

}

int PublishTarget::GetDiffScore(PublishVersions fileVersion, PublishVersions targetVersion)
{
	if ((fileVersion&targetVersion) == targetVersion || (fileVersion&targetVersion) == fileVersion)
	{
		return (fileVersion^targetVersion).ToInt();
	}
	return Math::IntMinValue;
}

int PublishTarget::GetDiffScore(PublishDevices fileDevice, PublishDevices targetDevice)
{
	if ((fileDevice&targetDevice) == targetDevice || (fileDevice&targetDevice) == fileDevice)
	{
		return (fileDevice^targetDevice).ToInt();
	}
	return Math::IntMinValue;
}

int PublishTarget::GetDiffScore(PublishLanguages fileLanguage, PublishLanguages targetLanguage)
{
	if ((fileLanguage&targetLanguage) == targetLanguage || (fileLanguage&targetLanguage) == fileLanguage)
	{
		return (fileLanguage^targetLanguage).ToInt();
	}
	return Math::IntMinValue;
}


int PublishTarget::GetDiffScore(const PublishTarget& tag) const
{
	int versionDiff = GetDiffScore(Version, tag.Version);
	if (versionDiff<0)
	{
		return Math::IntMinValue;
	}
	int deviceDiff = GetDiffScore(Device, tag.Device);
	if (deviceDiff < 0)
	{
		return Math::IntMinValue;
	}

	int languageDiff = GetDiffScore(Language, tag.Language);
	if (languageDiff < 0)
	{
		return Math::IntMinValue;
	}

	return (versionDiff << 16) | (deviceDiff << 8) | (languageDiff);	//diff
}

bool PublishTarget::IsMatch(const PublishTarget& tag) const
{
	return GetDiffScore(tag) != Math::IntMinValue;
}

PublishTarget PublishTarget::Parse(StringRef fileName)
{
	if (!fileName.Contains('-'))
	{
		return MatchAll;
	}

	HeapString rawName = Path::GetFileNameWithoutExtension(fileName);
	rawName.RemoveBeginExclude('-');
	if (rawName.IsEmpty())
	{
		return MatchAll;
	}


	List<HeapString> outResults;
	StringParser::Split<char>(rawName, "-", outResults);
	if (outResults.IsEmpty())
	{
		return MatchAll;
	}

	int resultTag = 0;
	for (const auto& str : outResults)
	{
		int* tempTag = mTagDict.TryGet(str);
		if (tempTag != nullptr)
		{
			resultTag |= *tempTag;
		}
		else if (!StdString::IsDigit(str.c_str()))
		{
			Log::FormatError("Invalid tag:{}", str.c_str());
		}
	}

	PublishTarget tag = PublishTarget(resultTag);
	if (tag.Version == PublishVersions::None)
	{
		tag.Version = PublishVersions::All;
	}

	if (tag.Device == PublishDevices::None)
	{
		tag.Device = PublishDevices::All;
	}

	if (tag.Language == PublishLanguages::None)
	{
		tag.Language = PublishLanguages::All;
	}

	return tag;
}


void PublishTarget::InitializeDict()
{
	FOR_EACH_SIZE(i, PublishVersions::Size)
	{
		StringRef name = PublishVersions::Names[i];
		mTagDict.Add(name, PublishVersions::Values[i] << 16);
	}

	FOR_EACH_SIZE(i, PublishDevices::Size)
	{
		StringRef name = PublishDevices::Names[i];
		mTagDict.Add(name, PublishDevices::Values[i] << 8);
	}

	FOR_EACH_SIZE(i, PublishLanguages::Size)
	{
		StringRef name = PublishLanguages::Names[i];
		mTagDict.Add(name, PublishLanguages::Values[i] << 16);
	}
}

Dictionary<StringRef, int> PublishTarget::mTagDict;
const PublishTarget PublishTarget::MatchAll(PublishVersions::All, PublishDevices::All, PublishLanguages::All);
MEDUSA_IMPLEMENT_STATIC_CONSTRUCTOR(PublishTarget, InitializeDict);

SIREN_METADATA(PublishTarget, 13);
SIREN_FIELD_METADATA(0, PublishTarget, Version, 7, 0,false);
SIREN_FIELD_METADATA(1, PublishTarget, Device, 6, 0,false);
SIREN_FIELD_METADATA(2, PublishTarget, Language, 8, 0,false);



MEDUSA_END;
