// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FileIdRef.h"
#include "Core/IO/Path.h"
#include "Core/IO/FileInfo.h"

MEDUSA_BEGIN;

bool FileIdRef::operator<(const FileIdRef& fileId) const
{
	if (Order < fileId.Order)
	{
		return true;
	}
	else if (Order == fileId.Order)
	{
		return Name < fileId.Name;
	}

	return false;
}

bool FileIdRef::IsPath() const
{
	return Path::IsPath(Name);
}

HeapString FileIdRef::ToString(const PublishTarget& tag /*= PublishTarget::MatchAll*/) const
{
	if (Order==0&& tag == PublishTarget::MatchAll)
	{
		return Name;
	}

	HeapString str;
	intp index=Name.LastIndexOf('.');
	if (index>0)
	{
		str.Append(Name.c_str(), index);
	}
	else
	{
		str.Append(Name);
	}

	if (tag.Version!=PublishVersions::All)
	{
		str += '-';
		str+=tag.Version.ToString();
	}

	if (tag.Device!=PublishDevices::All)
	{
		str += '-';
		str += tag.Device.ToString();
	}

	if (tag.Language !=PublishLanguages::All)
	{
		str += '-';
		str += tag.Language.ToString();
	}

	if (Order!=0)
	{
		str.Append('-');
		str += StringParser::ToString(Order);
	}
	if (index > 0)
	{
		str.Append(Name.c_str() + index);
	}
	return str;
}

FileType FileIdRef::Type() const
{
	return FileInfo::ExtractType(Name);
}

const FileIdRef FileIdRef::Empty;

MEDUSA_END;
