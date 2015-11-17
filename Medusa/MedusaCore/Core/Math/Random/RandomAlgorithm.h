// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "Random.h"

MEDUSA_BEGIN;
class RandomAlgorithm
{
public:
	template<typename T>
	struct DefaultProbalityFunc
	{
		static uint Get(const T& t1)
		{
			return (uint)t1;
		}
	};

	template<typename T, typename TUserData>
	struct DefaultPredicateFunc
	{
		static bool Get(const T& t1, const TUserData& userData)
		{
			return true;
		}
	};

	static bool SelectIndex(uintp& outResult, Random& random, const List<uint>& probs, uint maxProb = 0);
	static bool SelectIndices(List<uintp>& outResults, uintp resultCount, Random& random, const List<uint>& probs, bool allowDuplicate = true, uint maxProb = 0);

	template<typename T, class TProbalityFunc = DefaultProbalityFunc<T>>
	static bool SelectIndex(uintp& outResult, Random& random, const List<T>& probs, uint maxProb = 0)
	{
		RETURN_FALSE_IF_EMPTY(probs);
		if (probs.Count() == 1)
		{
			outResult = 0;
			return true;
		}

		if (maxProb == 0)
		{
			FOR_EACH_COLLECTION(i, probs)
			{
				typename List<T>::TConstReferenceType item = *i;
				uint prob = TProbalityFunc::Get(item);
				maxProb += prob;
			}
		}

		uintp count = probs.Count();
		uint resultProb = random.Next(maxProb - 1);
		FOR_EACH_SIZE(i, count)
		{
			typename List<T>::TConstReferenceType item = probs[i];
			uint prob = TProbalityFunc::Get(item);
			if (resultProb < prob)
			{
				outResult = i;
				return true;
			}
			resultProb -= prob;
		}

		return false;
	}

	template<typename T, typename TUserData, class TProbalityFunc = DefaultProbalityFunc<T>, class TPredicateFunc = DefaultPredicateFunc<T, TUserData>>
	static bool SelectIndex(uintp& outResult, Random& random, const List<T>& probs, TUserData userData, uint maxProb = 0)
	{
		RETURN_FALSE_IF_EMPTY(probs);
		if (probs.Count() == 1)
		{
			outResult = 0;
			return true;
		}
		if (maxProb == 0)
		{
			FOR_EACH_COLLECTION(i, probs)
			{
				typename List<T>::TConstReferenceType item = *i;
				if (TPredicateFunc::Get(item, userData))
				{
					uint prob = TProbalityFunc::Get(item);
					maxProb += prob;
				}
			}
		}
		RETURN_FALSE_IF_ZERO(maxProb);

		uintp count = probs.Count();
		uint resultProb = random.Next(maxProb - 1);
		FOR_EACH_SIZE(i, count)
		{
			typename List<T>::TConstReferenceType item = probs[i];
			if (TPredicateFunc::Get(item, userData))
			{
				uint prob = TProbalityFunc::Get(item);
				if (resultProb < prob)
				{
					outResult = i;
					return true;
				}
				resultProb -= prob;
			}
		}

		return false;
	}

	template<typename T, class TProbalityFunc = DefaultProbalityFunc<T>>
	static bool SelectIndices(List<uintp>& outResults, uintp resultCount, Random& random, const List<T>& probs, bool allowDuplicate = true, uint maxProb = 0)
	{
		RETURN_FALSE_IF_EMPTY(probs);
		if (maxProb == 0)
		{
			FOR_EACH_COLLECTION(i, probs)
			{
				typename List<T>::TConstReferenceType item = *i;
				uint prob = TProbalityFunc::Get(item);
				maxProb += prob;
			}
		}
		uintp count = probs.Count();

		if (allowDuplicate)
		{
			resultCount = Math::Min(resultCount, count);
			FOR_EACH_SIZE(i, resultCount)
			{
				uint resultProb = random.Next(maxProb - 1);
				FOR_EACH_SIZE(j, count)
				{
					typename List<T>::TConstReferenceType item = probs[j];
					uint prob = TProbalityFunc::Get(item);
					if (resultProb < prob)
					{
						outResults.Add(j);
						break;
					}
					resultProb -= prob;
				}
			}
		}
		else
		{
			if (count <= resultCount)
			{
				//all items should be selected
				FOR_EACH_SIZE(i, count)
				{
					outResults.Add(i);
				}
			}
			else
			{
				List<T> cloneProbs = probs;
				FOR_EACH_SIZE(i, resultCount)
				{
					uint resultProb = random.Next(maxProb - 1);
					FOR_EACH_SIZE(j, count)
					{
						typename List<T>::TConstReferenceType item = probs[j];
						uint prob = TProbalityFunc::Get(item);
						if (resultProb < prob)
						{
							outResults.Add(j);
							cloneProbs.RemoveAtUnordered(j);
							--count;
							//update max prob
							maxProb -= prob;
							break;
						}
						resultProb -= prob;
					}
				}
			}
		}


		return true;
	}

};

MEDUSA_END;
