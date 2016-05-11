// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledObject.h"
#include "Geometry/Ellipse.h"
#include "Geometry/Polygon.h"
#include "TmxTiledMap.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"

MEDUSA_BEGIN;
TiledObject::TiledObject()
	:mPosition(Point2I::Zero),
	mSize(Size2I::Zero),
	mIsVisible(true),
	mRotation(0.f),
	mTile(nullptr),
	mEllipse(nullptr),
	mPolygon(nullptr),
	mPolyline(nullptr)
{
}

TiledObject::~TiledObject()
{
	SAFE_DELETE(mEllipse);
	SAFE_DELETE(mPolygon);
	SAFE_DELETE(mPolyline);
}


bool TiledObject::Parse(const pugi::xml_node& node)
{
	mName = node.attribute("name").as_string();
	mType = node.attribute("type").as_string();

	mPosition.X = node.attribute("x").as_int(0);
	mPosition.Y = node.attribute("y").as_int(0);

	mSize.Width = node.attribute("width").as_int(0);
	mSize.Height = node.attribute("height").as_int(0);

	mIsVisible = node.attribute("visible").as_bool(true);

	mRotation = node.attribute("rotation").as_float(0.f);
	//The rotation of the object in degrees clockwise(defaults to 0). (since 0.10)
	mRotation = Math::ToRadian(mRotation);
	mRotation = Math::PI2 - mRotation; //to counter-clockwise
	

	pugi::xml_node propertiesNode = node.child("properties");
	if (!propertiesNode.empty())
	{
		TmxTiledMap::ParseProperties(propertiesNode, MutableProperties());
	}


	pugi::xml_node ellipseNode = node.child("ellipse");
	if (!ellipseNode.empty())
	{
		mEllipse = new EllipseI();
		mEllipse->InitializeWithRect(mPosition.X, mPosition.Y, mSize.Width, mSize.Height);
		
	}

	pugi::xml_node polygonNode = node.child("polygon");
	if (!polygonNode.empty())
	{
		mPolygon = new PolygonI();
		StringRef pointStr = polygonNode.attribute("points").as_string(nullptr);
		List<HeapString> outStrs;
		StringParser::SplitToValues(pointStr, StringRef(" "), outStrs);
		for (auto& str : outStrs)
		{
			Point2I vert;
			int index = str.IndexOf(',');
			vert.X = StringParser::StringTo<int>(str);
			vert.Y = StringParser::StringTo<int>(StringRef(str.c_str() + index + 1, str.Length() - index - 1));
			mPolygon->AddVertex(vert);
		}
		
	}

	pugi::xml_node polylineNode = node.child("polyline");
	if (!polylineNode.empty())
	{
		mPolyline = new PolygonI();
		StringRef pointStr = polylineNode.attribute("points").as_string(nullptr);
		List<HeapString> outStrs;
		StringParser::SplitToValues(pointStr, StringRef(" "), outStrs);
		for (auto& str : outStrs)
		{
			Point2I vert;
			int index = str.IndexOf(',');
			vert.X = StringParser::StringTo<int>(str);
			vert.Y = StringParser::StringTo<int>(StringRef(str.c_str() + index + 1, str.Length() - index - 1));
			mPolyline->AddVertex(vert);
		}

		
	}

	return true;
}

MEDUSA_END;
