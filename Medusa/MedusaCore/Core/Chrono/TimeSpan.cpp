// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Chrono/TimeSpan.h"
#include "Core/String/StringParser.h"
#include "Core/String/Format/Format.h"

MEDUSA_BEGIN;

HeapString TimeSpan::ToString() const
{
	return String::Format("{} {}:{}:{}", Days(), Hours(), Minutes(), Seconds());
}

HeapString TimeSpan::ToShortString() const
{
	return String::Format("{}:{}:{}", (int)TotalHours().count(), Minutes(), Seconds());
}
HeapString TimeSpan::ToTotalSecondsString() const
{
	return String::Format("{}", TotalSeconds().count());
}



MEDUSA_END;