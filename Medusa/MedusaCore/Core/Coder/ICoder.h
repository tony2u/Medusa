// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/Coder/CoderType.h"
#include "Core/IO/Stream/StreamDefines.h"
#include "CoderDefines.h"
MEDUSA_BEGIN;



class ICoder
{
public:
	ICoder(const IEventArg& e) {}
	ICoder() = default;
	virtual ~ICoder() {}

	virtual CoderType Type()const = 0;
	virtual CoderFlags Flags()const { return CoderFlags::None; }
	virtual size_t GuessResultSize(const IStream& input)const { return 0; }	//0 means not support guessing
	virtual bool Validate()const { return true; }

	size_t Code(const MemoryByteData& input, MemoryByteData& output)const;
	size_t Code(IStream& input, IStream& output)const;
	size_t Code(const IStream& input, IStream& output)const;

public:
	MemoryByteData Code(MemoryByteData& input)const;
	MemoryByteData Code(const MemoryByteData& input)const;

	MemoryByteData Code(const StringRef& input)const;
	MemoryByteData Code(HeapString& input)const;

protected:
	virtual size_t OnCode(const MemoryByteData& input, MemoryByteData& output)const { return 0; }
	virtual size_t OnCode(const IStream& input, IStream& output)const { return 0; }


};


MEDUSA_END;