// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Version.h"
#include "Core/String/StringParser.h"

MEDUSA_BEGIN;


Version::Version(uint major/*=0*/, uint minor/*=0*/, uint build/*=0*/, uint revision/*=0*/)
	:mMajor(major),
	mMinor(minor),
	mBuild(build),
	mRevision(revision)
{

}

Version::Version(const StringRef& versionString)
{
	*this = ParseFrom(versionString);
}

Version::Version(const Version& val)
	:mMajor(val.Major()),
	mMinor(val.Minor()),
	mBuild(val.Build()),
	mRevision(val.Revision())
{

}


Version& Version::operator=(const Version& val)
{
	mMajor = val.Major();
	mMinor = val.Minor();
	mBuild = val.Build();
	mRevision = val.Revision();
	return *this;
}

Version::~Version(void)
{

}

int Version::Compare(const Version& val) const
{
	if (mMajor != val.mMajor)
	{
		return mMajor > val.mMajor ? 1 : -1;
	}

	if (mMinor != val.mMinor)
	{
		return mMinor > val.mMinor ? 1 : -1;
	}

	if (mBuild != val.mBuild)
	{
		return mBuild > val.mBuild ? 1 : -1;
	}

	if (mRevision != val.mRevision)
	{
		return mRevision > val.mRevision ? 1 : -1;
	}

	return 0;
}

HeapString Version::ToString(uint fieldCount/*=4*/) const
{

	switch (fieldCount)
	{
		case 0:
			return HeapString::Empty;
		case 1:
			return StringParser::ToString(mMajor);
		case 2:
		{
			HeapString str;
			str = StringParser::ToString(mMajor);
			str += '.';
			str += StringParser::ToString(mMinor);
			return str;
		}
		break;
		case 3:
		{
			HeapString str;
			str = StringParser::ToString(mMajor);
			str += '.';
			str += StringParser::ToString(mMinor);
			str += '.';
			str += StringParser::ToString(mBuild);
			return str;
		}
		break;
		case 4:
		default:
		{
			HeapString str;
			str = StringParser::ToString(mMajor);
			str += '.';
			str += StringParser::ToString(mMinor);
			str += '.';
			str += StringParser::ToString(mBuild);
			str += '.';
			str += StringParser::ToString(mRevision);
			return str;
		}
		break;
	}
}

Version Version::ParseFrom(const StringRef& versionString)
{
	Version outVersion;
	TryParse(versionString, outVersion);
	return outVersion;
}

bool Version::TryParse(const StringRef& versionString, Version& outVersion)
{
	outVersion = Version::Zero;
	List<HeapString> parts;
	StringParser::Split(versionString, StringRef("."), parts);

	uint length = (uint)parts.Count();
	RETURN_FALSE_IF(length < 2 || length>4);

	long outMajor;
	if (parts[0].TryParseInt(outMajor))
	{
		outVersion.SetMajor((uint)outMajor);
	}
	else
	{
		return false;
	}

	long outMinor;
	if (parts[1].TryParseInt(outMinor))
	{
		outVersion.SetMinor((uint)outMinor);
	}
	else
	{
		return false;
	}

	length -= 2;
	if (length > 0)
	{
		long outBuild;
		if (parts[2].TryParseInt(outBuild))
		{
			outVersion.SetBuild((uint)outBuild);
		}
		else
		{
			return false;
		}

		--length;
		if (length > 0)
		{
			long outRevision;
			if (parts[3].TryParseInt(outRevision))
			{
				outVersion.SetRevision((uint)outRevision);
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}

const Version Version::Zero;


SIREN_METADATA(Version, 7);
SIREN_FIELD_METADATA(0, Version, Major, 5, 0,false);
SIREN_FIELD_METADATA(1, Version, Minor, 5, 0,false);
SIREN_FIELD_METADATA(2, Version, Revision, 8, 0,false);
SIREN_FIELD_METADATA(3, Version, Build, 5, 0,false);



MEDUSA_END;
