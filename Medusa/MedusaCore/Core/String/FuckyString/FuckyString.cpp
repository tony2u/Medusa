// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"

//SIREN_BODY_INCLUDE_BEGIN
#include "FuckyString.h"
//SIREN_BODY_INCLUDE_END
#include "Core/Log/Log.h"
#include "Core/IO/FileSystem.h"
#include "Core/Siren/Siren.h"
#include "Core/IO/FileIdRef.h"

MEDUSA_BEGIN;

FuckyString::FuckyString()
{
//SIREN_BODY_CONSTRUCT_BEGIN
//SIREN_BODY_CONSTRUCT_END
}

FuckyString::~FuckyString()
{
//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
	Unload();
}


bool FuckyString::Initialize(const FileIdRef& fileId, uint format /*= 0*/)
{
	MemoryData data = FileSystem::Instance().ReadAllData(fileId);
	return LoadFromData(fileId, data, format);
}

bool FuckyString::LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format/*=0*/)
{
	Unload();
	RETURN_FALSE_IF_FALSE(Siren::DeserializeBinaryTo(data, *this));

	return true;
}

void FuckyString::Unload()
{
	mRootNodes.Clear();
}

bool FuckyString::IsFucky(StringRef str) const
{
	WHeapString tempStr = StringParser::ToW(str);
	return IsFucky(tempStr);
}

bool FuckyString::IsFucky(WStringRef str) const
{
	size_t length = str.Length();
	FOR_EACH_SIZE(i, length)
	{
		wchar_t c = str[i];

		const FuckyStringNode* node = mRootNodes.TryGet(c);
		CONTINUE_IF_NULL(node);

		const Dictionary<int, FuckyStringNode*>* nodes = node->ChildsPtr();
		CONTINUE_IF_NULL(nodes);

		for (size_t j = i + 1; j < length; ++j)
		{
			wchar_t c2 = str[j];

			FuckyStringNode* tempNode = nodes->GetOptional(c2, nullptr);
			BREAK_IF_NULL(tempNode);

			if (tempNode->IsFucky())
			{
				//shorted match
				return true;
			}
			else
			{
				nodes = tempNode->ChildsPtr();
				RETURN_TRUE_IF_NULL(nodes);	//reach the last one
			}
		}
	}

	return false;
}



bool FuckyString::TryClean(WHeapString& str, char replace) const
{
	bool isFucky = false;
	//longest match
	uint length = static_cast<uint>(str.Length());
	FOR_EACH_SIZE(i, length)
	{
		wchar_t c = str[i];
		const FuckyStringNode* node = mRootNodes.TryGet(c);
		CONTINUE_IF_NULL(node);

		const Dictionary<int, FuckyStringNode*>* nodes = node->ChildsPtr();
		CONTINUE_IF_NULL(nodes);

		size_t matchIndex = 0;
		for (size_t j = i + 1; j < length; ++j)
		{
			wchar_t c2 = str[j];
			FuckyStringNode* tempNode = nodes->GetOptional(c2, nullptr);
			BREAK_IF_NULL(node);
			if (tempNode->IsFucky())
			{
				matchIndex = j;
			}
			else
			{
				nodes = tempNode->ChildsPtr();
				if (nodes == nullptr)
				{
					matchIndex = j;
					break;
				}

			}
		}

		if (matchIndex > 0)
		{
			for (size_t k = i; k <= matchIndex; ++k)
			{
				str[k] = replace;
			}

			i = matchIndex;	//will +1 in for later
			isFucky = true;
		}
	}

	return isFucky;
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(FuckyString, 11);
SIREN_FIELD_METADATA_STRUCT(0, FuckyString, RootNodes, 9);
//SIREN_BODY_METADATA_END

MEDUSA_END;