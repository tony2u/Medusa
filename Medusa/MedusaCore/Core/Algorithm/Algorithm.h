// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Collection/ICollection.h"
#include "Core/Collection/IList.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;

class Algorithm
{
private:
	Algorithm();
	~Algorithm();
public:
	template<typename T,typename TCompare>
	static int STLCompare(const void* p,const void* q)
	{
		return TCompare::Compare(*(T*)p,*(T*)q);
	}
public:
	template<typename T>
	struct InnerTypes
	{
		typedef typename Compile::TypeTraits<T>::ReferenceType TReferenceType;
		typedef typename Compile::TypeTraits<T>::ConstReferenceType TConstReferenceType;

		typedef typename Compile::TypeTraits<T>::PointerType TPointerType;
		typedef typename Compile::TypeTraits<T>::ConstPointerType TConstPointerType;


		typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

		typedef const Delegate<void(TReferenceType item)>& CustomIteratorType;
		typedef const Delegate<void(TConstReferenceType item)>& CustomConstIteratorType;
	};

public:
	template<typename T,typename TCompare>
	static void QuickSort(ICollection<T>& items)
	{
		if (items.Count()<=1)
		{
			return;
		}
		if (items.IsLinear())
		{
			std::qsort(items.Items(),items.Count(),sizeof(T),Algorithm::STLCompare<T,TCompare>);
			//QuickSortHelper<TCompare>(items.Items(),0,items.Count()-1);
		}
		else
		{
			MEDUSA_ASSERT_FAILED("");	//not implement
		}
	}

	template<typename T,typename TCompare>
	static void InsertSort(ICollection<T>& items)
	{
		if (items.Count()<=1)
		{
			return;
		}
		if (items.IsLinear())
		{
			InsertSortHelper<T, TCompare>(items.MutableItems(), 0, items.Count() - 1);
		}
		else
		{
			MEDUSA_ASSERT_FAILED("");	//not implement
		}
	}

	template<typename T,typename TCompare>
	static intp BinarySearch(ICollection<T>& items,typename InnerTypes<T>::TParameterType key)
	{
		if (items.Count()==0)
		{
			return -1;
		}
		if (items.IsLinear())
		{
			return std::bsearch(&key,items.Items(),items.Count(),sizeof(T),Algorithm::STLCompare<T,TCompare>);
			//return BinarySearchFirst<TCompare>(items.Items(),key,0,items.Count()-1);
		}
		else
		{
			MEDUSA_ASSERT_FAILED("");	//not implement
			return -1;
		}
	}

	template<typename T,typename TCompare>
	static intp BinarySearchFirst(typename InnerTypes<T>::TConstPointerType items, typename InnerTypes<T>::TParameterType key, size_t min, size_t max)
	{
		//http://en.wikipedia.org/wiki/Binary_search_algorithm
		//Deferred detection of equality
		// continually narrow search until just one element remains
		while(min<max)
		{
			size_t mid=(min+max)/2;
			// code must guarantee the interval is reduced at each iteration
			assert(mid<max);
			// note: 0 <= imin < imax implies imid will always be less than imax
			if( TCompare::Compare(items[mid],key)<0)
			{
				min=mid+1;
			}
			else
			{
				max=mid;
			}
		}

		// At exit of while:
		//   if A[] is empty, then imax < imin
		//   otherwise imax == imin
		if (max==min&& TCompare::Compare(items[min],key)==0)
		{
			return min;
		}
		else
		{
			return -1;
		}
	}

	template<typename T,typename TCompare>
	static intp BinarySearchLast(typename InnerTypes<T>::TConstPointerType items, typename InnerTypes<T>::TParameterType key, size_t min, size_t max)
	{
		//http://en.wikipedia.org/wiki/Binary_search_algorithm
		//Deferred detection of equality
		// continually narrow search until just one element remains
		while(min<max)
		{
			size_t mid=(min+max)/2;
			// code must guarantee the interval is reduced at each iteration
			assert(mid<max);
			// note: 0 <= imin < imax implies imid will always be less than imax
			if( TCompare::Compare(items[mid],key)>0)
			{
				max=mid-1;
			}
			else
			{
				min=mid;
			}
		}

		// At exit of while:
		//   if A[] is empty, then imax < imin
		//   otherwise imax == imin
		if (max==min&& TCompare::Compare(items[min],key)==0)
		{
			return min;
		}
		else
		{
			return -1;
		}
	}

	template<typename T,typename TCompare>
	static intp BinarySearchRandom(typename InnerTypes<T>::TConstPointerType items, typename InnerTypes<T>::TParameterType key, size_t min, size_t max)
	{
		//http://en.wikipedia.org/wiki/Binary_search_algorithm
		//Match the first one
		while(min<max)
		{
			intp mid=(min+max)/2;
			int compareResult=typename TCompare::Compare(items[mid],key);
			if (compareResult<0)
			{
				min=mid+1;
			}
			else if(compareResult>0)
			{
				max=mid-1;
			}
			else
			{
				return mid;
			}
		}
		return -1;
	}

	template<typename T,typename TCompare>
	static intp BinarySearchLastGreaterThan(typename InnerTypes<T>::TConstPointerType items,typename InnerTypes<T>::TParameterType key,size_t min,size_t max)
	{
		size_t originalMax=max;
		while(min<max)
		{
			size_t mid=(min+max)/2;
			assert(mid<max);
			if( TCompare::Compare(items[mid],key)<=0)
			{
				min=mid+1;
			}
			else
			{
				max=mid;
			}
		}

		//not found 
		if (max==originalMax&&TCompare::Compare(items[max],key)<=0)
		{
			return -1;
		}

		return max;
	}


	template<typename T,typename TCompare>
	static void QuickSortHelper(typename InnerTypes<T>::TPointerType items,size_t left,size_t right)
	{
		//TODO: some error?
		RETURN_IF(left>=right);
		size_t i=left;
		size_t j=right;
		T mid= items[(left + right) / 2]; 
		do  
		{  
			while( TCompare::Compare(items[i],mid)<0&&i<j)
				i++;        
			while( TCompare::Compare(items[j],mid)>0&&i<j)
				j--;          
			if(i<j)                                 
			{  
				T tmp = items[i];  
				items[i] = items[j];  
				items[j] = tmp;  
				i++;
				j--;
			}
			else
			{
				break;
			}
		}while(true);  

		if (left+1<(size_t)i)	//prevent i-1 to 0-1
		{
			QuickSortHelper<T,TCompare>(items,left,i-1);     
		}
		if ((size_t)i+1<right)
		{
			QuickSortHelper<T,TCompare>(items,i+1,right);   
		}

	}

	template<typename T,typename TCompare>
	static void InsertSortHelper(typename InnerTypes<T>::TPointerType items,size_t left,size_t right)
	{
		RETURN_IF(left>=right);

		T post_key;  
		for(size_t i=left+1;i<=right;i++)
		{  
			post_key=items[i];  
		
			intp low=0,high=i-1;  
			while(low<=high)
			{  
				intp middle=(low+high)/2;  
				if( TCompare::Compare(post_key,items[middle])<0)
				{
					high=middle-1;  
				}
				else 
				{
					low=middle+1;  
				}
			}  
	
			for(intp j=i-1;j>=high+1;j--)  
				items[j+1]=items[j];  
			items[high+1]=post_key;  
		}  
	}


};

MEDUSA_END;