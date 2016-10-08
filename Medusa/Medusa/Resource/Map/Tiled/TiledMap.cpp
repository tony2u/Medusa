// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledMap.h"
#include "TiledTileset.h"
#include "Core/IO/FileSystem.h"
#include "TiledTerrain.h"
#include "TiledImage.h"
#include "TiledTile.h"
#include "TiledObjectLayer.h"
#include "TiledTileLayer.h"
#include "TiledObjectLayer.h"
#include "TiledImageLayer.h"
#include "TiledTilesetRef.h"
#include "Geometry/GeometryFactory.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"
#include "Core/IO/FileIdRef.h"
#include "Node/NodeFactory.h"
#include "Node/Layer/ILayer.h"
#include "Node/Layer/NormalLayer.h"
#include "TiledMapInstantiateInfo.h"

MEDUSA_BEGIN;


TiledMap::TiledMap(const FileIdRef& fileId)
	:IResource(fileId),
	mBackgroundColor(Color4B::Black),
	mOrientation(TiledMapOrientation::Orthogonal),
	mRenderOrder(TiledMapRenderOrder::RightDown),
	mStaggerAxis(TiledMapStaggerAxis::None),
	mStaggerIndex(TiledMapStaggerIndex::None),
	mSize(Size2U::Zero),
	mTileSize(Size2U::Zero)
{
	mVersion = 0.f;
	mNextObjectId = 0;
}

TiledMap::~TiledMap()
{
	SAFE_DELETE_COLLECTION(mLayers);
	mTiledLayers.Clear();
	mObjectLayers.Clear();
	mImageLayers.Clear();

	mTilesets.Clear();
}


const TiledTilesetRef* TiledMap::FindTilesetContainsGlobalId(uint globalId) const
{
	// Clean up the flags from the globalId 
	globalId &= ~(TiledTileRef::FlippedHorizontallyFlag | TiledTileRef::FlippedVerticallyFlag | TiledTileRef::FlippedDiagonallyFlag);

	intp count = mTilesets.Count();
	FOR_EACH_INT_END_BEGIN(i, count - 1, 0)
	{
		// If the gid beyond the tileset global id return it.
		if (globalId >= mTilesets[i].FirstGlobalId())
		{
			return &mTilesets[i];
		}
	}

	return nullptr;
}


bool TiledMap::LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format /*= 0*/)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_buffer(data.Data(), data.Size());
	if (!result)
	{
		Log::AssertFailedFormat("Cannot parse xml:{} because {}", fileId, result.description());
		return false;
	}

	pugi::xml_node rootNode = doc.first_child();
	return Parse(rootNode);
}

void TiledMap::Unload()
{

}


bool TiledMap::ParseProperties(const pugi::xml_node& node, VariantPropertySet& outProperties)
{
	for (auto child : node.children())
	{
		StringRef childName = child.name();
		if (childName == "property")
		{
			StringRef name = child.attribute("name").as_string(nullptr);
			StringRef value = child.attribute("value").as_string(nullptr);
			StringRef type = child.attribute("type").as_string(nullptr);
			if (type == "bool")
			{
				auto val = StringParser::StringTo<bool>(value);
				outProperties.Set(name, val);
			}
			else if (type == "int")
			{
				auto val = StringParser::StringTo<int>(value);
				outProperties.Set(name, val);
			}
			else if (type == "float")
			{
				auto val = StringParser::StringTo<float>(value);
				outProperties.Set(name, val);
			}
			else if (type == "color")
			{
				auto val = ParseColor(value);
				outProperties.Set(name, (int)val.Data);

			}
			else
			{
				//string or file
				outProperties.Set(name, value);
			}

		}
	}

	return true;
}

Color4B TiledMap::ParseColor(const StringRef& str)
{
	if (str.IsEmpty())
	{
		return Color4B::Black;
	}

	Color4B color;
	if (str.First() == '#')
	{
		color = GeometryFactory::CreateColor(StringRef(str.c_str() + 1, str.Length() - 1));
	}
	else
	{
		color = GeometryFactory::CreateColor(str);
	}
	//"#FF00FF" for magenta means RGB
	color.Data <<= 8;	//we need to shift left 8 to add A
	return color;
}

bool TiledMap::Parse(const pugi::xml_node& rootNode)
{
	mVersion = rootNode.attribute("version").as_float(0.f);
	mSize.Width = rootNode.attribute("width").as_uint(0);
	mSize.Height = rootNode.attribute("height").as_uint(0);
	mTileSize.Width = rootNode.attribute("tilewidth").as_uint(0);
	mTileSize.Height = rootNode.attribute("tileheight").as_uint(0);
	mNextObjectId = rootNode.attribute("nextobjectid").as_int(0);

	const char* backgroundColorStr = rootNode.attribute("backgroundcolor").as_string(nullptr);
	mBackgroundColor = ParseColor(backgroundColorStr);

	// Read the orientation
	StringRef orientationStr = rootNode.attribute("orientation").as_string(nullptr);
	if (orientationStr == "orthogonal")
	{
		mOrientation = TiledMapOrientation::Orthogonal;
	}
	else if (orientationStr == "isometric")
	{
		mOrientation = TiledMapOrientation::Isometric;
	}
	else if (orientationStr == "staggered")
	{
		mOrientation = TiledMapOrientation::Staggered;
	}
	else if (orientationStr == "hexagonal")
	{
		mOrientation = TiledMapOrientation::Hexagonal;
	}

	StringRef renderorderStr = rootNode.attribute("renderorder").as_string(nullptr);
	if (renderorderStr == "right-down")
	{
		mRenderOrder = TiledMapRenderOrder::RightDown;
	}
	else if (renderorderStr == "right-up")
	{
		mRenderOrder = TiledMapRenderOrder::RightUp;
	}
	else if (renderorderStr == "left-down")
	{
		mRenderOrder = TiledMapRenderOrder::LeftDown;
	}
	else if (renderorderStr == "left-down")
	{
		mRenderOrder = TiledMapRenderOrder::LeftUp;
	}

	StringRef staggerAxisStr = rootNode.attribute("staggeraxis").as_string(nullptr);
	if (staggerAxisStr == "x")
	{
		mStaggerAxis = TiledMapStaggerAxis::X;
	}
	else if (staggerAxisStr == "y")
	{
		mStaggerAxis = TiledMapStaggerAxis::Y;
	}

	// Read the stagger index
	StringRef staggerIndexStr = rootNode.attribute("staggerindex").as_string(nullptr);

	if (staggerIndexStr == "even")
	{
		mStaggerIndex = TiledMapStaggerIndex::Even;
	}
	else if (staggerIndexStr == "odd")
	{
		mStaggerIndex = TiledMapStaggerIndex::Odd;
	}

	for (auto child : rootNode.children())
	{
		StringRef childName = child.name();

		if (childName == "properties")
		{
			ParseProperties(child, mProperties);
		}
		else if (childName == "tileset")
		{
			TiledTilesetRef& tilesetRef = mTilesets.NewAdd();
			tilesetRef.Parse(child);

		}
		else if (childName == "layer")
		{
			TiledTileLayer* tileLayer = new TiledTileLayer();
			tileLayer->SetMap(this);
			tileLayer->Parse(child);

			mLayers.Add(tileLayer);
			mTiledLayers.Add(tileLayer);
		}
		else if (childName == "imagelayer")
		{
			TiledImageLayer* imageLayer = new TiledImageLayer();
			imageLayer->SetMap(this);
			imageLayer->Parse(child);
			mLayers.Add(imageLayer);
			mImageLayers.Add(imageLayer);
		}
		else if (childName == "objectgroup")
		{
			TiledObjectLayer* objectLayer = new TiledObjectLayer();
			objectLayer->SetMap(this);
			objectLayer->Parse(child);
			mLayers.Add(objectLayer);
			mObjectLayers.Add(objectLayer);
		}
	}

	mInstantiateLayer = mProperties.GetString(TiledMapProperties::InstantiateLayer);
	return true;
}



INode* TiledMap::Instantiate(NodeInstantiateInfo* instantiateInfo/*=nullptr*/) const
{
	TiledMapInstantiateInfo* mapInstantiateInfo = (TiledMapInstantiateInfo*)instantiateInfo;
	StringRef layerClassName;
	if (mapInstantiateInfo != nullptr)
	{
		layerClassName = mapInstantiateInfo->NodeClassName;
	}

	if (layerClassName.IsEmpty())
	{
		layerClassName = mInstantiateLayer;
	}

	if (layerClassName.IsEmpty())
	{
		layerClassName = NormalLayer::ClassNameStatic();
	}

	INode* parentNode = nullptr;
	if (mapInstantiateInfo != nullptr)
	{
		parentNode = mapInstantiateInfo->ParentNode;
	}

	INode* curLayer = parentNode;
	if (curLayer == nullptr)
	{
		curLayer = NodeFactory::Instance().Create(layerClassName);
	}

	for (auto* layer : mLayers)
	{
		INode* prevChildLayer = nullptr;
		INode* childLayer = nullptr;

		if (instantiateInfo != nullptr)
		{
			prevChildLayer = curLayer->FindChild(layer->Name());
			instantiateInfo->ParentNode = prevChildLayer;
		}

		switch (layer->Type())
		{
		case TiledLayerType::Tile:
		{
			TiledTileLayer* tileLayer = (TiledTileLayer*)layer;
			childLayer = tileLayer->Instantiate(instantiateInfo);
		}

		break;
		case TiledLayerType::Image:
		{
			TiledImageLayer* imageLayer = (TiledImageLayer*)layer;
			childLayer = imageLayer->Instantiate(instantiateInfo);
		}
		break;
		case TiledLayerType::Object:
		{
			TiledObjectLayer* objectLayer = (TiledObjectLayer*)layer;
			childLayer = objectLayer->Instantiate(instantiateInfo);
		}
		break;
		default:
			break;
		};

		if (prevChildLayer == nullptr&&childLayer != nullptr)
		{
			curLayer->AddChild(childLayer);
		}
	}
	curLayer->SetName(mFileId.Name);
	curLayer->SetUserData((void*)this);

	if (mapInstantiateInfo != nullptr&&mapInstantiateInfo->UpdateSize)
	{
		Size2F newSize = PixelSize();
		newSize.Width += mapInstantiateInfo->Offset.X*mTileSize.Width;
		newSize.Height += mapInstantiateInfo->Offset.Y*mTileSize.Height;
		curLayer->SetSize(newSize);
		curLayer->SetStretch(Stretch::None);	//not stretch 
	}


	if (mapInstantiateInfo != nullptr)
	{
		mapInstantiateInfo->ParentNode = parentNode;
	}
	return curLayer;
}

MEDUSA_END;