// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Size2.h"
#include "Core/Math/Math.h"
#include "Core/Siren/SirenDefines.h"

MEDUSA_BEGIN;

template<typename T>
class Ellipse
{
public:
	Point2<T> Center;
	Size2<T> Radius;

	T* GetBuffer() { return (T*)this; }

	T Left()const { return Center.X - Radius.Width; }
	T Right()const { return Center.X + Radius.Width; }


	T Bottom()const { return Center.Y - Radius.Height; }
	T Top()const { return Center.Y + Radius.Height; }

	T CenterX()const { return Center.X; }
	T CenterY()const { return Center.Y; }
	T RadiusWidth()const { return Radius.Width; }
	T RadiusHeight()const { return Radius.Height; }


	bool IsEmpty()const
	{
		return Radius.IsEmpty();
	}

public:
	Ellipse(void) {}
	template<typename T1>
	Ellipse(const Point2<T1>& center, const Size2<T1>& radius) :Center(center), Radius(radius) {}

	Ellipse(const Point2<T>& center, const Size2<T>& radius) :Center(center), Radius(radius) {}

	template<typename T1>
	Ellipse(T1 x, T1 y, T1 radiusWidth, T1 radiusHeight) : Center((T)x, (T)y), Radius((T)radiusWidth, (T)radiusHeight) {}

	Ellipse(T x, T y, T radiusWidth, T radiusHeight) :Center(x, y), Radius(radiusWidth, radiusHeight) {}

	template<typename T1>
	Ellipse(const Ellipse<T1>& ellipse) : Center(ellipse.Center), Radius(ellipse.Radius) {}
	template<typename T1>
	Ellipse& operator=(const Ellipse<T1>& ellipse) { Center = ellipse.Center; Radius = ellipse.Radius; return *this; }
	template<typename T1>
	Ellipse& operator=(T1 val) { Center = val; Radius = val; return *this; }

	template<typename T1>
	bool operator==(const Ellipse<T1>& ellipse)const { return Math::IsEqual(Center, ellipse.Center) && Math::IsEqual(Radius, ellipse.Radius); }
	template<typename T1>
	bool operator!=(const Ellipse<T1>& ellipse)const { return !operator==(ellipse); }

	template<typename T1>
	bool operator<(const Ellipse<T1>& ellipse)const { return Center < ellipse.Center&&Radius < ellipse.Radius; }
	template<typename T1>
	bool operator<=(const Ellipse<T1>& ellipse)const { return Center <= ellipse.Center&&Radius <= ellipse.Radius; }

	template<typename T1>
	bool operator>(const Ellipse<T1>& ellipse)const { return Center > ellipse.Center&&Radius > ellipse.Radius; }
	template<typename T1>
	bool operator>=(const Ellipse<T1>& ellipse)const { return Center >= ellipse.Center&&Radius >= ellipse.Radius; }

	intp HashCode()const { return Center.HashCode() ^ Radius.HashCode(); }

	static Ellipse CreateWithRect(T x, T y, T width, T height)
	{
		return Ellipse(x + width / 2, y + height / 2, width / 2, height / 2);
	}

	void InitializeWithRect(T x, T y, T width, T height)
	{
		Center.X = x + width / 2;
		Center.Y = y + height / 2;
		Radius.Width = width / 2;
		Radius.Height = height / 2;
	}
};

//[PRE_DECLARE_BEGIN]
typedef Ellipse<int> EllipseI;
typedef Ellipse<uint> EllipseU;
typedef Ellipse<float> EllipseF;
//[PRE_DECLARE_END]

namespace Siren
{
	template <typename T>
	struct HasCustomSerialization<Ellipse<T>> : std::true_type{};	//[IGNORE_PRE_DECLARE]

	template <typename TWriter, typename T>
	void Serialize(TWriter& writer, const Ellipse<T>& obj)
	{
		writer.OnStructBegin();
		writer.template OnProperty<Point2<T>, false>("Center", 6, 0, obj.Center);
		writer.template OnProperty<Size2<T>, false>("Radius", 6, 1, obj.Radius);
		writer.OnStructEnd();
	}

	template <typename TReader, typename T>
	bool DeserializeTo(TReader& reader, Ellipse<T>& outObj)
	{
		reader.OnStructBegin();
		reader.template OnProperty<Point2<T>, false>("Center", 6, 0, outObj.Center);
		reader.template OnProperty<Size2<T>, false>("Radius", 6, 1, outObj.Radius);
		reader.OnStructEnd();

		return true;
	}
}

MEDUSA_END;
