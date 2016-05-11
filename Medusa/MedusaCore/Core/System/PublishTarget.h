// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/Collection/Dictionary.h"

#include "PublishVersions.h"
#include "PublishDevices.h"
#include "PublishLanguages.h"

#include "Core/Siren/SirenHeader.h"

MEDUSA_BEGIN;

//sd = 1, //480*320
//hd = 2, //960*640
//hd5 = 4, //1136*640
//ipad = 8, //1024*768
//ipad3 = 16, //2048*1536.



class PublishTarget
{
public:
	struct Schema;
	PublishTarget();

	PublishTarget(PublishVersions targetVersion, PublishDevices targetDevice, PublishLanguages targetLanguage)
		:Version(targetVersion), Device(targetDevice), Language(targetLanguage) {}

	PublishTarget(int tag)
		:Version((tag & 0xFF0000) >> 16), Device((tag & 0x00FF00) >> 8), Language(tag & 0x0000FF) {}

	intp HashCode()const { return Tag(); }
	bool operator<(const PublishTarget& tag)const { return Tag() < tag.Tag(); }
	int Tag()const { return (Version.ToInt() << 16) | (Device.ToInt() << 8) | (Language.ToInt()); }
	void SetTag(int tag) { Version.ForceSet((tag & 0xFF0000) >> 16); Device.ForceSet((tag & 0x00FF00) >> 8); Language.ForceSet(tag & 0x0000FF); }


	/*
	the smaller, the more match
	Int.MinValue: not match
	-1:	super match in anyway
	0:	perfect match
	>0:	diff
	*/
	static int GetDiffScore(PublishVersions fileVersion, PublishVersions targetVersion);
	static int GetDiffScore(PublishDevices fileDevice, PublishDevices targetDevice);
	static int GetDiffScore(PublishLanguages fileLanguage, PublishLanguages targetLanguage);
	int GetDiffScore(const PublishTarget& tag)const;

	bool IsMatch(const PublishTarget& tag)const;

	bool operator==(const PublishTarget& tag)const { return Version == tag.Version&&Device == tag.Device&&Language == tag.Language; }

	static PublishTarget Parse(StringRef fileName);


	PublishVersions Version;
	PublishDevices Device;
	PublishLanguages Language;

	const static PublishTarget MatchAll;

private:
	static Dictionary<StringRef, int> mTagDict;
	static void InitializeDict();
	MEDUSA_DECLARE_STATIC_CONSTRUCTOR();
};

struct PublishTarget::Schema
{
	SIREN_FIELD(0, 0, Optional, PublishTarget, PublishVersions, Version);
	SIREN_FIELD(1, 1, Optional, PublishTarget, PublishDevices, Device);
	SIREN_FIELD(2, 2, Optional, PublishTarget, PublishLanguages, Language);
	SIREN_FIELDS_3(void, PublishTarget);
};


MEDUSA_END;
