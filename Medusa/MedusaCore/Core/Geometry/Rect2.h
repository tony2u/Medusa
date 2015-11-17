// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Size2.h"
#include "Core/Math/Math.h"
#include "Core/Pattern/LazyValue.h"
#include "Core/Siren/SirenDefines.h"

MEDUSA_BEGIN;

template<typename T>
class Rect2
{
public:
	const static Rect2 Zero;
	const static Rect2 Max;



	Point2<T> Origin;
    Size2<T> Size;

	T* GetBuffer(){return (T*)this;}

	T Left()const{return Origin.X;}
	T Right()const{return Origin.X+Size.Width;}
	T HorizontalCenter()const{return Origin.X+0.5f*Size.Width;}


	T Bottom()const{return Origin.Y;}
	T Top()const{return Origin.Y+Size.Height;}
	T VerticalCenter()const{return Origin.Y+0.5f*Size.Height;}

	T X()const { return Origin.X; }
	T Y()const { return Origin.Y; }
	T Width()const { return Size.Width; }
	T Height()const { return Size.Height; }



	Point2<T> LeftBottom()const{return Origin;}
	Point2<T> LeftCenter()const{return Point2<T>(Origin.X,Origin.Y+0.5f*Size.Height);}
	Point2<T> LeftTop()const{return Point2<T>(Origin.X,Origin.Y+Size.Height);}

	Point2<T> MiddleBottom()const{return Point2<T>(Origin.X+0.5f*Size.Width,Origin.Y);}
	Point2<T> MiddleCenter()const{return Point2<T>(Origin.X+0.5f*Size.Width,Origin.Y+0.5f*Size.Height);}
	Point2<T> MiddleTop()const{return Point2<T>(Origin.X+0.5f*Size.Width,Origin.Y+Size.Height);}

	Point2<T> RightBottom()const{return Point2<T>(Origin.X+Size.Width,Origin.Y);}
	Point2<T> RightCenter()const{return Point2<T>(Origin.X+Size.Width,Origin.Y+0.5f*Size.Height);}
	Point2<T> RightTop()const{return Point2<T>(Origin.X+Size.Width,Origin.Y+Size.Height);}

	bool Contains(const Point2<T>& point)const
	{
		return point.X>=Left()&&point.X<=Right()&&point.Y>=Bottom()&&point.Y<=Top();
	}

	bool Contains(T x,T y)const
	{
		return x >= Left() && x <= Right() && y >= Bottom() && y <= Top();
	}


	bool Contains(const Rect2& rect)const
	{
		return Contains(rect.LeftBottom())&&Contains(rect.RightTop());
	}

	bool IsIntersect(const Rect2& rect)const
	{
		return !(Left()>rect.Right()||Right()<rect.Left()||Top()<rect.Bottom()||Bottom()>rect.Top());
	}

	bool IsDisjoint(const Rect2& rect)const
	{
		return Right() <= rect.Left() || Left()>=rect.Right() || Top() <= rect.Bottom() || Bottom()>=rect.Top();
	}

	bool IsEmpty()const
	{
		return Size.IsEmpty();
	}

	void Inflate(const Point2<T>& amount)
	{
		Origin-=amount;
		Size+=amount*2;
	}

	Point2<T> Clamp(const Point2<T>& val)const
	{
		return Point2<T>(Math::Clamp(val.X, Origin.X, Origin.X + Size.Width), Math::Clamp(val.Y, Origin.Y, Origin.Y + Size.Height));
	}


	T Area()const{return Size.Area();}

	static Rect2 Intersect(const Rect2& rect1,const Rect2& rect2)
	{
		if (rect1.IsEmpty()||rect2.IsEmpty())
		{
			return Rect2::Zero;
		}

		
		T maxLeft=Math::Max(rect1.Left(),rect2.Left());
		T maxBottom=Math::Max(rect1.Bottom(),rect2.Bottom());

		T minRight=Math::Min(rect1.Right(),rect2.Right());
		T minTop=Math::Min(rect1.Top(),rect2.Top());

		if (minRight>maxLeft&&minTop>maxBottom)
		{
			return Rect2(maxLeft,maxBottom,minRight-maxLeft,minTop-maxBottom);
		}

		return Rect2::Zero;
	}

	void Intersect(const Rect2& val)
	{
		if (val.IsEmpty())
		{
			*this=Rect2::Zero;
			return;
		}

		T right1=Right();
		T right2=val.Right();

		T top1=Top();
		T top2=val.Top();

		T maxLeft=Math::Max(Left(),val.Left());
		T maxBottom=Math::Max(Bottom(),val.Bottom());

		T minRight=Math::Min(Right(),val.Right());
		T minTop=Math::Min(Top(),val.Top());

		if (minRight>maxLeft&&minTop>maxBottom)
		{
			Origin.X=maxLeft;
			Origin.Y=maxBottom;
			Size.Width=minRight-maxLeft;
			Size.Height=minTop-maxBottom;
		}

		Origin=Point2<T>::Zero;
		Size=Size2<T>::Zero;
	}


	static Rect2 Union(const Rect2& rect1,const Rect2& rect2)
	{
		if (rect1.IsEmpty())
		{
			return rect2;
		}

		if (rect2.IsEmpty())
		{
			return rect1;
		}

		T right1=rect1.Right();
		T right2=rect2.Right();

		T top1=rect1.Top();
		T top2=rect2.Top();

		T minLeft=Math::Min(rect1.Left(),rect2.Left());
		T minBottom=Math::Min(rect1.Bottom(),rect2.Bottom());

		T maxRight=Math::Max(rect1.Right(),rect2.Right());
		T maxTop=Math::Max(rect1.Top(),rect2.Top());

		return Rect2(minLeft,minBottom,maxRight-minLeft,maxTop-minBottom);
	}

	void Union(const Rect2& val)
	{
		RETURN_IF_EMPTY(val);

		if (IsEmpty())
		{
			*this=val;
			return;
		}

		T minLeft=Math::Min(Left(),val.Left());
		T minBottom=Math::Min(Bottom(),val.Bottom());

		T maxRight=Math::Max(Right(),val.Right());
		T maxTop=Math::Max(Top(),val.Top());

		Origin.X=minLeft;
		Origin.Y=minBottom;
		Size.Width=maxRight-minLeft;
		Size.Height=maxTop-minBottom;
	}

public:
	Rect2(void){}
	template<typename T1>
	Rect2(const Point2<T1>& origin,const Size2<T1>& size):Origin(origin),Size(size){}

	Rect2(const Point2<T>& origin,const Size2<T>& size):Origin(origin),Size(size){}

	template<typename T1>
	Rect2(T1 x,T1 y,T1 width,T1 height):Origin((T)x,(T)y),Size((T)width,(T)height){}
	
	Rect2(T x,T y,T width,T height):Origin(x,y),Size(width,height){}

	template<typename T1>
	Rect2(const Rect2<T1>& rect):Origin(rect.Origin),Size(rect.Size){}
	template<typename T1>
	Rect2& operator=(const Rect2<T1>& rect){Origin=rect.Origin;Size=rect.Size;return *this;}
	template<typename T1>
	Rect2& operator=(T1 val){Origin=val;Size=val;return *this;}

	template<typename T1>
	bool operator==(const Rect2<T1>& rect)const{return Math::IsEqual(Origin,rect.Origin)&&Math::IsEqual(Size,rect.Size);}
	template<typename T1>
	bool operator!=(const Rect2<T1>& rect)const{return !operator==(rect);}

	template<typename T1>
	bool operator<(const Rect2<T1>& rect)const{return Origin<rect.Origin&&Size<rect.Size;}
	template<typename T1>
	bool operator<=(const Rect2<T1>& rect)const{return Origin<=rect.Origin&&Size<=rect.Size;}

	template<typename T1>
	bool operator>(const Rect2<T1>& rect)const{return Origin>rect.Origin&&Size>rect.Size;}
	template<typename T1>
	bool operator>=(const Rect2<T1>& rect)const{return Origin>=rect.Origin&&Size>=rect.Size;}

	intp HashCode()const{return Origin.HashCode()^Size.HashCode();}
};

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Rect2<T> Rect2<T>::Zero(0,0,0,0);
template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Rect2<T> Rect2<T>::Max(0,0,Math::Values<T>::Max,Math::Values<T>::Max);

//[PRE_DECLARE_BEGIN]
typedef Rect2<int> Rect2I;
typedef Rect2<uint> Rect2U;
typedef Rect2<float> Rect2F;
typedef Rect2F BoundingBox2;
typedef LazyValue<BoundingBox2> LazyBoundingBox2;

//[PRE_DECLARE_END]

namespace Siren
{
	template <typename T>
	struct HasCustomSerialization<Rect2<T>> : std::true_type{};	//[IGNORE_PRE_DECLARE]

	template <typename TWriter, typename T>
	void Serialize(TWriter& writer, const Rect2<T>& obj)
	{
		writer.OnStructBegin();
		writer.template OnProperty<Point2<T>, false>("Origin",6, 0, obj.Origin);
		writer.template OnProperty<Size2<T>, false>("Size", 4, 1, obj.Size);
		writer.OnStructEnd();
	}

	template <typename TReader, typename T>
	bool DeserializeTo(TReader& reader, Rect2<T>& outObj)
	{
		reader.OnStructBegin();
		reader.template OnProperty<Point2<T>, false>("Origin", 6, 0, outObj.Origin);
		reader.template OnProperty<Size2<T>, false>("Size", 4, 1, outObj.Size);
		reader.OnStructEnd();

		return true;
	}
}

MEDUSA_END;


#ifdef MEDUSA_SCRIPT
MEDUSA_SCRIPT_BEGIN;
void RegisterRect2F(asIScriptEngine* engine);
MEDUSA_SCRIPT_END;
#endif