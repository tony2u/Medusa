// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"

#include "Core/Coder/ICoder.h"

MEDUSA_BEGIN;

class XXTEAEncoder:public ICoder
{
public:
	XXTEAEncoder() = default;
	XXTEAEncoder(const IEventArg& e);
	XXTEAEncoder(const MemoryData& key);
	~XXTEAEncoder();

public:
	virtual CoderType Type()const override { return CoderType::Encoder_XXTEA; }

	using ICoder::Code;
	virtual CoderFlags Flags()const override{ return CoderFlags::Block; }
	virtual size_t GuessResultSize(const IStream& input)const override;
	virtual bool Validate()const override { return mKey.IsValid(); }
	static MemoryUIntData ToUIntArray(const MemoryData& data, bool includeLength);
protected:
	virtual size_t OnCode(const MemoryData& input, MemoryData& output)const override;

private:
	void EncryptHelper(MemoryUIntData& v)const;
private:
	const static size_t mDelta = 0x9E3779B9;
	MemoryUIntData mKey;
};

MEDUSA_END;
