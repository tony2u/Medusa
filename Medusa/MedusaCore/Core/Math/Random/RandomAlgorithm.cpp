// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "RandomAlgorithm.h"


MEDUSA_BEGIN;

bool RandomAlgorithm::SelectIndex(uintp& outResult, Random& random, const List<uint>& probs, uint maxProb /*= 0*/)
{
	RETURN_FALSE_IF_EMPTY(probs);
	if (probs.Count()==1)
	{
		outResult = 0;
		return true;
	}

	if (maxProb == 0)
	{
		FOR_EACH_COLLECTION(i, probs)
		{
			maxProb += *i;
		}
	}

	uintp count = probs.Count();
	uint resultProb = random.Next(maxProb - 1);
	FOR_EACH_SIZE(i, count)
	{
		uint prob = probs[i];
		if (resultProb < prob)
		{
			outResult = i;
			return true;
		}
		resultProb -= prob;
	}

	return false;
}

bool RandomAlgorithm::SelectIndices(List<uintp>& outResults, uintp resultCount, Random& random, const List<uint>& probs, bool allowDuplicate /*= true*/, uint maxProb /*= 0*/)
{
	RETURN_FALSE_IF_EMPTY(probs);
	if (maxProb == 0)
	{
		FOR_EACH_COLLECTION(i, probs)
		{
			maxProb += *i;
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
				uint prob = probs[j];
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
			List<uint> cloneProbs = probs;
			FOR_EACH_SIZE(i, resultCount)
			{
				uint resultProb = random.Next(maxProb - 1);
				FOR_EACH_SIZE(j, count)
				{
					uint prob = cloneProbs[j];
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

MEDUSA_END;
