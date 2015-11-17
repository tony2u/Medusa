// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"

#include "Core/Coder/ICoder.h"

MEDUSA_BEGIN;

class XXTEADecoder:public ICoder
{
public:
	XXTEADecoder() = default;
	XXTEADecoder(const IEventArg& e);
	XXTEADecoder(const MemoryByteData& key);
	~XXTEADecoder();

public:
	virtual CoderFlags Flags()const override { return CoderFlags::None; }
	using ICoder::Code;
	virtual CoderType Type()const override { return CoderType::Decoder_XXTEA; }
	virtual bool Validate()const override { return mKey.IsValid(); }
	virtual size_t GuessResultSize(const IStream& input)const override;
protected:
	virtual size_t OnCode(const MemoryByteData& input, MemoryByteData& output)const override;
private:
	void DecryptHelper(MemoryUIntData& v)const;
private:
	const static size_t mDelta = 0x9E3779B9;
	MemoryUIntData mKey;
};

MEDUSA_END;
