// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FileIdRef.h"
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

HeapString FileIdRef::ToString(const PublishTarget& tag /*= PublishTarget::MatchAll*/) const
{
	if (Order==0&& tag == PublishTarget::MatchAll)
	{
		return Name;
	}

	HeapString str;
	intp index=Name.LastIndexOf('.');
	str.Append(Name.c_str(), index);

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
	
	str.Append(Name.c_str() + index);
	return str;
}

const FileIdRef FileIdRef::Empty;

MEDUSA_END;
