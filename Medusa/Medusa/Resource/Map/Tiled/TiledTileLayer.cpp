// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledTileLayer.h"
#include "Core/Compress/ZipReader.h"
#include "Core/Coder/Crypt/Base64Decoder.h"
#include "Core/Log/Log.h"
#include "TiledTilesetRef.h"
#include "TiledMap.h"
#include "Node/Layer/NormalLayer.h"
#include "TiledTileset.h"
#include "Node/NodeFactory.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"
#include "TiledMapInstantiateInfo.h"
#include "Node/Input/InputDispatcher.h"

MEDUSA_BEGIN;
TiledTileLayer::TiledTileLayer()
{
}

TiledTileLayer::~TiledTileLayer()
{
}

bool TiledTileLayer::Parse(const pugi::xml_node& node)
{
	RETURN_FALSE_IF_FALSE(ITiledLayer::Parse(node));

	pugi::xml_node dataNode = node.child("data");
	StringRef encodingStr = dataNode.attribute("encoding").as_string(nullptr);
	StringRef compressionStr = dataNode.attribute("compression").as_string(nullptr);
	StringRef text = dataNode.child_value();
	uint jump = 0;
	for (; jump < text.Length(); jump++)
	{
		BREAK_IF(StdString::IsAlpha(text[jump]));
	}

	text = text.SubString(jump);	//skip "\n "

	if (encodingStr == "base64")
	{
		Base64Decoder decoder;
		MemoryData data = decoder.Code(text);
		MemoryData resultData;
		if (compressionStr == "gzip")
		{
#ifdef MEDUSA_UNZIP
			resultData = ZipReader::DecompressGZIP(data, mSize.Area() * sizeof(uint));
#endif

		}
		else if (compressionStr == "zlib")
		{
#ifdef MEDUSA_ZLIB
			// Use zlib to uncompress the tile layer into the temporary array of tiles.
			uLongf outlen = mSize.Area() * sizeof(uint);
			resultData = MemoryData::Alloc(outlen);
			int err = uncompress(resultData.MutableData(), &outlen, data.Data(), data.Size());
			if (err != 0)
			{
				Log::FormatError("decompression error:{}", err);
				return false;
			}
#endif
		}
		else if (compressionStr.IsEmpty())
		{
			resultData = data;
		}
		else
		{
			Log::FormatError("Unsupported compression type:{}", compressionStr.c_str());
			return false;
		}

		const uint* buffer = (const uint*)resultData.Data();
		InitializeTiles();

		//the decoded data is an array of 32 - bit integers.
		uint tileCount = mSize.Area();
		FOR_EACH_UINT32(i, tileCount)
		{
			uint globalId = buffer[i];
			TiledTileRef& tileRef = MutableTile(i);

			const TiledTilesetRef* tilesetRef = mMap->FindTilesetContainsGlobalId(globalId);
			tileRef.Initialize(Point2I(i%mSize.Width, AdjustY(i / mSize.Height)), globalId, tilesetRef);
			tileRef.SetLayer(this);
		}
	}
	else if (encodingStr == "csv")
	{
		int index = 0;
		List<uint> outValues;
		StringParser::SplitToValues(text, StringRef(","), outValues);
		for (auto globalId : outValues)
		{
			TiledTileRef& tileRef = MutableTile(index);
			const TiledTilesetRef* tileset = mMap->FindTilesetContainsGlobalId(globalId);
			tileRef.Initialize(Point2I(index%mSize.Width, AdjustY(index / mSize.Height)), globalId, tileset);
			tileRef.SetLayer(this);
			++index;
		}

	}
	else if (encodingStr == "xml")
	{
		int index = 0;
		for (auto tileNode : node.children())
		{
			uint globalId = tileNode.attribute("gid").as_uint(0);
			TiledTileRef& tileRef = MutableTile(index);
			const TiledTilesetRef* tileset = mMap->FindTilesetContainsGlobalId(globalId);
			tileRef.Initialize(Point2I(index%mSize.Width, AdjustY(index / mSize.Height)), globalId, tileset);
			tileRef.SetLayer(this);
			++index;
		}
	}
	else
	{
		Log::FormatError("Unsupported encoding type:{}", encodingStr.c_str());
		return false;
	}

	AnalyzeTiles();

	return true;
}

void TiledTileLayer::InitializeTiles()
{
	mTiles.ForceReserveCount(mSize.Area());
}

void TiledTileLayer::AnalyzeTiles()
{
	mHasSingleTexture = true;
	TextureAtlasPage* uniqueTexturePage = nullptr;

	for (const auto& tileRef : mTiles)
	{
		auto* tile = tileRef.Tile();
		CONTINUE_IF_NULL(tile);
		auto* texturePage = tile->Page();
		CONTINUE_IF_NULL(texturePage);

		if (uniqueTexturePage == nullptr)
		{
			uniqueTexturePage = texturePage;
		}
		else if (uniqueTexturePage != texturePage)
		{
			mHasSingleTexture = false;
			return;
		}
	}

}

INode* TiledTileLayer::Instantiate(NodeInstantiateInfo* instantiateInfo /*= nullptr*/)const
{
	TiledMapInstantiateInfo* mapInstantiateInfo = (TiledMapInstantiateInfo*)instantiateInfo;

	InstantiateMode mode = InstantiateMode::None;
	if (instantiateInfo != nullptr)
	{
		mode = instantiateInfo->Mode;
	}

	if (mode == InstantiateMode::None)
	{
		mode = mInstantiateMode;	//use config rendering mode
	}

	if (!mHasSingleTexture)
	{
		mode = InstantiateMode::Sprite;
	}


	INode* curLayer = nullptr;
	if (instantiateInfo != nullptr)
	{
		curLayer = instantiateInfo->ParentNode;
	}

	if (curLayer == nullptr)
	{
		StringRef layerClassName = mInstantiateLayer;
		if (layerClassName.IsEmpty())
		{
			layerClassName = NormalLayer::ClassNameStatic();
		}

		curLayer = NodeFactory::Instance().Create(layerClassName);
	}

	Point2I offset = Point2I::Zero;
	if (instantiateInfo != nullptr)
	{
		offset = mapInstantiateInfo->Offset;
	}
	switch (mode)
	{
	case InstantiateMode::None:
	case InstantiateMode::Mesh:
	{
		//create quad mesh
		/*for (const auto& tileRef : mTiles)
		{

		}*/
	}

	break;
	case InstantiateMode::Sprite:
		for (const auto& tileRef : mTiles)
		{
			INode* node = tileRef.Instantiate(instantiateInfo);
			if (node != nullptr)
			{
				Point2I tilePos = tileRef.Position()+offset;
				curLayer->AddChild(node);
				Point2F pos = mPosition;
				pos.X += tilePos.X*mMap->TileSize().Width;
				pos.Y += tilePos.Y*mMap->TileSize().Height;	//from top down
				node->SetPosition(pos);
			}
		}
		break;
	default:
		break;
	}

	curLayer->SetName(mName);
	curLayer->SetOpacity(mOpacity);
	curLayer->SetState(mRunningState);
	curLayer->SetVisible(mIsVisible);
	curLayer->MutableInput().Enable(mInputEnabled);

	if (mapInstantiateInfo != nullptr&&mapInstantiateInfo->UpdateSize)
	{
		Size2F newSize = mMap->PixelSize();
		newSize.Width += mapInstantiateInfo->Offset.X*mMap->Width();
		newSize.Height += mapInstantiateInfo->Offset.Y*mMap->Height();
		curLayer->SetSize(newSize);
		curLayer->SetStretch(Stretch::None);	//not stretch 
	}


#ifdef MEDUSA_SCRIPT
	if (!mScriptFile.IsEmpty())
	{
		curLayer->TryAddScriptFile(mScriptFile);
	}
#endif

	return curLayer;

}




MEDUSA_END;