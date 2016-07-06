// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/Siren/Siren.h"

MEDUSA_BEGIN;

class Version
{
public:
	struct Schema;
	const static Version Zero;
public:
	Version(uint major = 0, uint minor = 0, uint build = 0, uint revision = 0);
	Version(const StringRef& versionString);

	Version(const Version& val);
	Version& operator=(const Version& val);
	~Version(void);

	int Compare(const Version& val)const;

	bool operator==(const Version& val)const { return Compare(val) == 0; }
	bool operator!=(const Version& val)const { return !operator==(val); }
	bool operator>(const Version& val)const { return Compare(val) > 0; }
	bool operator<(const Version& val)const { return Compare(val) < 0; }
	bool operator>=(const Version& val)const { return Compare(val) >= 0; }
	bool operator<=(const Version& val)const { return Compare(val) <= 0; }


	intp HashCode()const { return mMajor^mMinor^mRevision^mBuild; }
	HeapString ToString(uint fieldCount = 4)const;

public:
	static Version ParseFrom(const StringRef& versionString);
	static bool TryParse(const StringRef& versionString, Version& outVersion);

public:
	uint Major() const { return mMajor; }
	uint& MutableMajor() { return mMajor; }
	void SetMajor(uint val) { mMajor = val; }

	uint Minor() const { return mMinor; }
	uint& MutableMinor() { return mMinor; }
	void SetMinor(uint val) { mMinor = val; }

	uint Revision() const { return mRevision; }
	uint& MutableRevision() { return mRevision; }
	void SetRevision(uint val) { mRevision = val; }

	uint Build() const { return mBuild; }
	uint& MutableBuild() { return mBuild; }
	void SetBuild(uint val) { mBuild = val; }
protected:
	uint mMajor;
	uint mMinor;
	uint mBuild;
	uint mRevision;
};


struct Version::Schema
{
	SIREN_FIELD(0, 0, Required, Version, uint, mMajor);
	SIREN_FIELD(1, 1, Required, Version, uint, mMinor);
	SIREN_FIELD(2, 2, Optional, Version, uint, mRevision);
	SIREN_FIELD(3, 3, Optional, Version, uint, mBuild);
	SIREN_FIELDS_4(void, Version);
};


MEDUSA_END;
