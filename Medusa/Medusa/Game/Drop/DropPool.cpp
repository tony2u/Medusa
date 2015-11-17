// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "DropPool.h"
//SIREN_BODY_INCLUDE_END

#include "Core/Math/Random/Random.h"
#include "Core/Math/Random/RandomAlgorithm.h"
#include "Core/Pattern/Predicate/PredicateConfig.h"
#include "Core/Log/Log.h"
#include "DropPoolConfig.h"

MEDUSA_BEGIN;

DropPool::DropPool()
{
	//SIREN_BODY_CONSTRUCT_BEGIN
//SIREN_BODY_CONSTRUCT_END
}

bool DropPool::Generate(const DropPoolConfig& config, List<DropPoolItem>& outItems,void* userData/*=nullptr*/ ) const
{
	// add fixed items
	outItems.AddRange(mFixedItems);

	//rand items
	if (!mRandomGroups.IsEmpty())
	{
		List<size_t> outIndices;
		for (const DropPoolGroup& group : mRandomGroups)
		{
			uintp minCount = group.MinTimes();
			uintp maxCount = group.MaxTimes();
			uintp itemCount = group.ItemsCount();
			if (minCount < itemCount)
			{
				minCount = itemCount;
			}
			if (maxCount < itemCount)
			{
				maxCount = itemCount;
			}

			uint count = (int)Random::Global().Next((int)minCount, (int)maxCount);
			RandomAlgorithm::SelectIndices<DropPoolRandomItem, DropPoolRandomItemProbalityFunc>(outIndices, count, Random::Global(), group.Items(), !group.PreventDuplicate());
			for (size_t seletedIndex : outIndices)
			{
				const DropPoolRandomItem& randomItem = group.Items()[seletedIndex];
				intp index = outItems.IndexOfOther(randomItem);
				if (index < 0)
				{
					DropPoolItem& newItem = outItems.NewAdd();
					newItem = randomItem;	//copy base part
				}
				else
				{
					DropPoolItem& resultItem = outItems[index];
					resultItem.SetCount(resultItem.Count() + randomItem.Count());
				}
			}
		}
	}

	//conditional items
	if (!mConditionItems.IsEmpty())
	{
		for (const DropPoolConditionItem& conditionItem : mConditionItems)
		{
			IPredicate* predicate = PredicateConfig::Instance().TryGetObjectWithFailed(conditionItem.PredicateId(), nullptr);
			Log::AssertNotNullFormat(predicate, "Cannot find predicate id:{}", conditionItem.PredicateId());
			if (predicate != nullptr&&predicate->EvaluateBool(userData))
			{
				const DropPoolItem& tempItem = conditionItem.Item();

				intp index = outItems.IndexOfOther(tempItem);
				if (index < 0)
				{
					DropPoolItem& newItem = outItems.NewAdd();
					newItem = tempItem;	//copy base part
				}
				else
				{
					DropPoolItem& resultItem = outItems[index];
					resultItem.SetCount(resultItem.Count() + tempItem.Count());
				}
			}
		}

	}

	//check sub drop id
	if (!outItems.IsEmpty())
	{
		List<size_t> subItemIndices;
		List<size_t> subDropIds;

		uintp outCount = outItems.Count();
		FOR_EACH_SIZE(i, outCount)
		{
			DropPoolItem& item = outItems[i];
			if (item.Type() == -1)	//this is a sub drop id
			{
				subItemIndices.Add(i);
				subDropIds.Add(item.Id());
			}
		}

		outItems.RemoveIndexes(subItemIndices);
		if (!subDropIds.IsEmpty())
		{
			for (size_t subDropId : subDropIds)
			{
				const DropPool* dropPool = config.Find((uint)subDropId);
				Log::AssertNotNullFormat(dropPool, "Cannot find sub drop id:{}", subDropId);
				if (dropPool != nullptr)
				{
					List<DropPoolItem> subOutItems;
					dropPool->Generate(config, subOutItems, userData);	//do not use outItems directly because we don't want current outItems to be limited inside
					outItems.AddRange(subOutItems);
				}
			}
		}
	}


	//apply limits
	if (!mItemLimits.IsEmpty())
	{
		for (const DropPoolItemLimit& itemLimit : mItemLimits)
		{
			intp index = outItems.IndexOfOther(itemLimit);
			CONTINUE_IF(index < 0);
			DropPoolItem& resultItem = outItems[index];

			if (resultItem.Count() < itemLimit.MinCount())
			{
				resultItem.SetCount(itemLimit.MinCount());
			}

			if (resultItem.Count() > itemLimit.MaxCount())
			{
				resultItem.SetCount(itemLimit.MaxCount());
			}

			if (resultItem.Count() == 0)		//this item is removed
			{
				outItems.RemoveAt(index);
			}
		}
	}


	return true;
}

const DropPoolItem* DropPool::GenerateFixedSingle() const
{
	uintp count = mFixedItems.Count();
	RETURN_NULL_IF_ZERO(count);
	if (count==1)
	{
		return &mFixedItems.First();
	}

	uintp index = Random::Global().Next((int)count - 1);
	return &mFixedItems[index];
}

DropPool::~DropPool()
{
	//SIREN_BODY_DESTRUCT_BEGIN
//SIREN_BODY_DESTRUCT_END
}

//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(DropPool, 8);
SIREN_PROPERTY_METADATA_STRUCT(0, DropPool, FixedItems, 10);
SIREN_PROPERTY_METADATA_STRUCT(1, DropPool, RandomGroups, 12);
SIREN_PROPERTY_METADATA_STRUCT(2, DropPool, ConditionItems, 14);
SIREN_PROPERTY_METADATA_STRUCT(3, DropPool, ItemLimits, 10);
//SIREN_BODY_METADATA_END

MEDUSA_END;