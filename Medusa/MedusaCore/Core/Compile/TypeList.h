// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"


MEDUSA_BEGIN;
namespace Compile
{
	template <typename THead,typename...Types>
	struct Typelist		//[IGNORE_PRE_DECLARE]	
	{
		typedef THead Head;
		typedef Typelist<Types...> Tail;
		constexpr static size_t Length = 1 + Tail::Length;
	};
	
	template <typename THead>
	struct Typelist<THead>//[IGNORE_PRE_DECLARE]	
	{
		typedef THead Head;
		typedef void Tail;

		constexpr static size_t Length = 1;
	};

	template <>
	struct Typelist<void>//[IGNORE_PRE_DECLARE]	
	{
		typedef void Head;
		typedef void Tail;

		constexpr static size_t Length = 0;
	};


}

MEDUSA_END;