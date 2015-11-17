// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "Case/CollectionTest.h"

/*
size:10
????TestDictionary	137.515038 / 100000 = 0.001375
????TestList	279.998563 / 100000 = 0.002800
*/
void CollectionTest::TestDictionary()
{
	const uint size=10;
	const int count=100000;
	HeapString strs[size];
	Dictionary<HeapString,int> dicItems;
	List<HeapString> listItems;
	FOR_EACH_SIZE(i,size)
	{
		strs[i]= StringParser::ToString(i);
		dicItems.Add(strs[i],i);
		listItems.Add(strs[i]);
	}


	StopWatch watch;
	watch.SetRunTimes(count);
	watch.SetName("TestDictionary");

	watch.Start();
	FOR_EACH_SIZE(i,count)
	{
		int j=rand()%size;
		int* p= dicItems.TryGetValue(strs[j]);
		if (*p!=j)
		{
			break;
		}
	}

	watch.Shot();
	watch.PrintResult();

	watch.SetName("TestList");
	watch.Start();
	for (int i=0;i<count;i++)
	{
		int v=rand()%size;
		FOR_EACH_SIZE(j,size)
		{
			if (listItems[j]==strs[v])
			{
				break;
			}
		}
	}
	watch.Shot();
	watch.PrintResult();

}

struct AAA 
{
	AAA(int v) { Value = v; }
	bool operator<(const AAA& val)const { return Value < val.Value; }
	int Value;
};
void CollectionTest::TestSortedList()
{
	List<AAA*> items;
	SortedList<AAA*, DefaultCompareForPointer<AAA>, DefaultCompareForPointer<AAA>> mySort;

	FOR_EACH_SIZE(i, 100)
	{
		AAA* a = new AAA(i);
		items.Add(a);
	}

	FOR_EACH_INT_END_BEGIN(i, 99, 0)
	{
		AAA* a = items[i];
		mySort.Add(a);
	}

	FOR_EACH_SIZE(i, 100)
	{
		AAA* a = items[i];
		AAA* b = mySort[i];
		if (a!=b)
		{
			Log::AssertFailed("NOt");
		}
	}


}
