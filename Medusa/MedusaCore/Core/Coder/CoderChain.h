// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Coder/ICoder.h"
#include "Core/Collection/List.h"
#include "Core/Coder/CoderDefines.h"


MEDUSA_BEGIN;

class CoderChain
{
public:
	const static CoderChain Empty;

	CoderChain(CoderList coders, const MemoryData& key);
	CoderChain() {}
	~CoderChain();
	CoderChain(const CoderChain& other);
	CoderChain& operator=(const CoderChain& other);
	CoderChain(CoderChain&& other);
	CoderChain& operator=(CoderChain&& other);

	bool Initialize(CoderList coders, const MemoryData& key);
	bool Uninitialize();

	CoderList Coders() const { return mCoders; }
	void SetCoders(CoderList val);
	bool HasCoders()const { return mCoders != 0; }
	bool Validate()const;

	const MemoryData& Key() const { return mKey; }
	void SetKey(const MemoryData& val);


	size_t Encode(IStream& input, IStream& output)const;
	size_t Encode(const IStream& input, IStream& output)const;

	size_t Encode(const MemoryData& input, MemoryData& output)const;

	size_t Decode(IStream& input, IStream& output)const;
	size_t Decode(const IStream& input, IStream& output)const;
	size_t Decode(const MemoryData& input, MemoryData& output)const;

	static uint64 AddCoders(uint64 coders, CoderType coderType);
	static bool RequireKey(uint64 coders);
protected:
	bool InitializeHelper();

	static size_t OnCode(const List<ICoder*>& coders, IStream& input, IStream& output);
	static size_t OnCode(const List<ICoder*>& coders, const IStream& input, IStream& output);
	static size_t OnCode(const List<ICoder*>& coders, const MemoryData& input, MemoryData& output);
	static size_t OnCode(const List<ICoder*>& coders, MemoryData& input, MemoryData& output);


protected:
	CoderList mCoders = 0;
	MemoryData mKey;

	List<ICoder*> mEncoders;
	List<ICoder*> mDecoders;
};

MEDUSA_END;
