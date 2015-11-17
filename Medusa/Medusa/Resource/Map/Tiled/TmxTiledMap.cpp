// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TmxTiledMap.h"
#include "TiledTileset.h"
#include "Core/IO/FileSystem.h"
#include "TiledTerrain.h"
#include "TiledImage.h"
#include "TiledTile.h"
#include "Core/Coder/Crypt/Base64Decoder.h"
#include "TiledObjectLayer.h"
#include "Core/Geometry/Ellipse.h"
#include "Core/Geometry/Polygon.h"
#include "TiledTileLayer.h"
#include "TiledObjectLayer.h"
#include "TiledImageLayer.h"
#include "Core/Compress/ZipReader.h"
#include "Core/Geometry/GeometryFactory.h"
#include "Core/Coder/Crypt/Base64Decoder.h"

MEDUSA_BEGIN;


TmxTiledMap::TmxTiledMap(const FileIdRef& fileId)
	:ITiledMap(fileId)
{
	mVersion = 0.f;
	mNextObjectId = 0;
}

TmxTiledMap::~TmxTiledMap()
{

}

bool TmxTiledMap::LoadFromData(StringRef path, const MemoryByteData& data, uint format /*= 0*/)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_buffer(data.Data(), data.Size());
	if (!result)
	{
		Log::AssertFailedFormat("Cannot parse xml:{} because {}", path.c_str(), result.description());
		return false;
	}

	pugi::xml_node rootNode = doc.first_child();
	return Parse(rootNode);
}

void TmxTiledMap::Unload()
{

}


bool TmxTiledMap::ParseProperties(pugi::xml_node node, StringPropertySet& outProperties)
{
	FOR_EACH_COLLECTION_STL(i, node.children())
	{
		pugi::xml_node child = *i;
		StringRef childName = child.name();
		if (childName == "property")
		{
			StringRef name = child.attribute("name").as_string(nullptr);
			StringRef value = child.attribute("value").as_string(nullptr);
			outProperties.Add(name, value);
		}
	}

	return true;
}

bool TmxTiledMap::ParseTileset(pugi::xml_node node, TiledTileset& outTileset, TmxTiledMap& map)
{
	// The firstgid and source attribute are kept in the TMX map,
	// since they are map specific.
	int firstGlobalId = node.attribute("firstgid").as_int(0);
	outTileset.SetFirstGlobalId(firstGlobalId);

	// If the <tileset> node contains a 'source' tag,
	// the tileset config should be loaded from an external
	// TSX (Tile Set XML) file. That file has the same structure
	// as the <tileset> element in the TMX map.
	const char* sourceName = node.attribute("source").as_string(nullptr);
	if (sourceName != nullptr)
	{
		pugi::xml_document doc;
		const MemoryByteData& data = FileSystem::Instance().ReadAllData(FileIdRef(sourceName));
		pugi::xml_parse_result result = doc.load_buffer(data.Data(), data.Size());
		if (!result)
		{
			Log::AssertFailedFormat("Cannot parse tileset:{} because {}", sourceName, result.description());
			return false;
		}

		node = doc.child("tileset");	//refer to outside node
	}

	Size2I tileSize;
	tileSize.Width = node.attribute("tilewidth").as_int(0);
	tileSize.Height = node.attribute("tileheight").as_int(0);
	outTileset.SetTileSize(tileSize);

	int margin = node.attribute("margin").as_int(0);
	outTileset.SetMargin(margin);
	int spacing = node.attribute("spacing").as_int(0);
	outTileset.SetSpacing(spacing);
	const char* name = node.attribute("name").as_string(nullptr);
	outTileset.SetName(name);

	Point2I tileOffset = Point2I::Zero;
	pugi::xml_node tileOffsetNode = node.child("tileoffset");
	if (!tileOffsetNode.empty())
	{
		tileOffset.X = tileOffsetNode.attribute("x").as_int(0);
		tileOffset.Y = tileOffsetNode.attribute("y").as_int(0);
		outTileset.SetTileOffset(tileOffset);
	}

	pugi::xml_node terrainNode = node.child("terraintypes");
	if (!terrainNode.empty())
	{
		FOR_EACH_COLLECTION_STL(i, terrainNode.children())
		{
			pugi::xml_node child = *i;
			StringRef childName = child.name();
			BREAK_IF_NOT_EQUAL(childName, "terrain");
			TiledTerrain* terrain = new TiledTerrain();
			ParseTerrain(child, *terrain);
			outTileset.AddTerrain(terrain);
		}
	}

	pugi::xml_node imageNode = node.child("image");
	if (!imageNode.empty())
	{
		TiledImage* image = new TiledImage();
		ParseImage(imageNode, *image);
		outTileset.SetImage(image);
	}


	//add tiles
	uint tileCount = node.attribute("tilecount").as_uint(0);
	if (tileCount == 0)
	{
		tileCount = (outTileset.Image()->Size().Width / tileSize.Width) * (outTileset.Image()->Size().Height / tileSize.Height);
	}

	FOR_EACH_INT32_BEGIN_END(i, 0, (int)tileCount)
	{
		TiledTile* tile = new TiledTile(i);
		outTileset.AddTile(tile);
	}


	pugi::xml_node tileNode = node.child("tile");
	while (!tileNode.empty())
	{
		int tileId = tileNode.attribute("id").as_int(0);
		TiledTile* tile = outTileset.MutableTileWithIndex(tileId);
		ParseTile(tileNode, *tile,map);
		tileNode = tileNode.next_sibling("tile");
	}


	pugi::xml_node propertiesNode = node.child("properties");
	if (!propertiesNode.empty())
	{
		ParseProperties(propertiesNode, outTileset.MutableProperties());
	}


	return true;

}

bool TmxTiledMap::ParseTerrain(pugi::xml_node node, TiledTerrain& outTerrain)
{
	const char* name = node.attribute("name").as_string(nullptr);
	int tileId = node.attribute("tile").as_int(0);

	outTerrain.SetName(name);
	outTerrain.SetTileId(tileId);

	pugi::xml_node propertiesNode = node.child("properties");
	if (!propertiesNode.empty())
	{
		ParseProperties(propertiesNode, outTerrain.MutableProperties());
	}

	return true;
}

bool TmxTiledMap::ParseImage(pugi::xml_node node, TiledImage& outImage)
{
	// Read all the attribute into member variables.
	const char* source = node.attribute("name").as_string(nullptr);
	Size2I imageSize;
	imageSize.Width = node.attribute("width").as_int(0);
	imageSize.Height = node.attribute("height").as_int(0);

	const char* transparentColorStr = node.attribute("trans").as_string(nullptr);
	Color4B transparentColor = ParseColor(transparentColorStr);

	outImage.SetSource(source);
	outImage.SetSize(imageSize);
	outImage.SetTransparentColor(transparentColor);

	StringRef formatStr = node.attribute("format").as_string(nullptr);

	if (formatStr == "png")
	{
		outImage.SetEmbeddedFileType(FileType::png);
	}
	else if (formatStr == "jpg")
	{
		outImage.SetEmbeddedFileType(FileType::jpeg);
	}
	else if (!formatStr.IsEmpty())
	{
		Log::FormatError("Unsupported image type:{}", formatStr.c_str());
		return false;
	}


	pugi::xml_node dataNode = node.child("data");
	if (!dataNode.empty())
	{
		StringRef encodingStr = node.attribute("encoding").as_string(nullptr);
		StringRef compressionStr = node.attribute("compression").as_string(nullptr);
		if (encodingStr != "base64")
		{
			Log::FormatError("Unsupported encoding type:{}", encodingStr.c_str());
			return false;
		}

		const char* text = dataNode.value();
		Base64Decoder decoder;
		MemoryByteData data = decoder.Code(text);
		outImage.SetEmbeddedImageData(data);
	}

	return true;

}

bool TmxTiledMap::ParseTile(pugi::xml_node node, TiledTile& outTile, TmxTiledMap& map)
{
	//int id = node.attribute("id").as_int(0);
	pugi::xml_node propertiesNode = node.child("properties");
	if (!propertiesNode.empty())
	{
		ParseProperties(propertiesNode, outTile.MutableProperties());
	}

	StringRef terrainStr = node.attribute("terrain").as_string();
	if (!terrainStr.IsEmpty())
	{
		List<HeapString> strs;
		StringParser::Split(terrainStr, StringRef(","), strs);
		outTile.MutableTerrains().LeftTop = (int)strs[0].ToIntWithFailed(0);
		outTile.MutableTerrains().RightTop =  (int)strs[1].ToIntWithFailed(0);
		outTile.MutableTerrains().LeftBottom =  (int)strs[2].ToIntWithFailed(0);
		outTile.MutableTerrains().RightBottom =  (int)strs[3].ToIntWithFailed(0);
	}

	float probalbility = node.attribute("probability").as_float();
	outTile.SetProbability(probalbility);

	pugi::xml_node imageNode = node.child("image");
	if (!imageNode.empty())
	{
		TiledImage* image = new TiledImage();
		ParseImage(imageNode, *image);
		outTile.SetImage(image);
	}

	pugi::xml_node objectGroupNode = node.child("objectgroup");
	if (!objectGroupNode.empty())
	{
		TiledObjectLayer* objectLayer = new TiledObjectLayer();
		ParseObjectLayer(objectGroupNode, *objectLayer,map);
		outTile.SetObjectLayer(objectLayer);
	}

	pugi::xml_node animationNode = node.child("animation");
	if (!animationNode.empty())
	{
		FOR_EACH_COLLECTION_STL(i, animationNode.children())
		{
			pugi::xml_node frameNode = *i;
			int tileId = frameNode.attribute("tileid").as_int(0);
			uint durationMilliseconds = frameNode.attribute("duration").as_uint(0);
			outTile.AddFrame(tileId, durationMilliseconds);
		}
	}

	return true;

}

bool TmxTiledMap::ParseObject(pugi::xml_node node, TiledObject& outObject)
{
	StringRef name = node.attribute("name").as_string();
	outObject.SetName(name);

	StringRef typeStr = node.attribute("type").as_string();
	outObject.SetType(typeStr);

	Point2I pos;
	pos.X = node.attribute("x").as_int(0);
	pos.Y = node.attribute("y").as_int(0);
	outObject.SetPosition(pos);

	Size2I size;
	size.Width = node.attribute("width").as_int(0);
	size.Height = node.attribute("height").as_int(0);
	outObject.SetSize(size);

	bool isVisible = node.attribute("visible").as_bool(true);
	outObject.SetVisible(isVisible);

	float rotation = node.attribute("rotation").as_float(0.f);
	//The rotation of the object in degrees clockwise(defaults to 0). (since 0.10)
	rotation=Math::ToRadian(rotation);
	rotation = Math::PI2 - rotation; //to counter-clockwise
	outObject.SetRotation(rotation);

	pugi::xml_node propertiesNode = node.child("properties");
	if (!propertiesNode.empty())
	{
		ParseProperties(propertiesNode, outObject.MutableProperties());
	}


	pugi::xml_node ellipseNode = node.child("ellipse");
	if (!ellipseNode.empty())
	{
		EllipseI* ellipse = new EllipseI();
		ellipse->InitializeWithRect(pos.X, pos.Y, size.Width, size.Height);
		outObject.SetEllipse(ellipse);
	}

	pugi::xml_node polygonNode = node.child("polygon");
	if (!polygonNode.empty())
	{
		PolygonI* polygon = new PolygonI();
		StringRef pointStr = polygonNode.attribute("points").as_string(nullptr);
		StringParser::SplitToValues(pointStr, StringRef(","), polygon->MutableVertices());
		outObject.SetPolygon(polygon);
	}

	pugi::xml_node polylineNode = node.child("polyline");
	if (!polylineNode.empty())
	{
		PolygonI* polygon = new PolygonI();
		StringRef pointStr = polylineNode.attribute("points").as_string(nullptr);
		StringParser::SplitToValues(pointStr, StringRef(","), polygon->MutableVertices());
		outObject.SetPolyline(polygon);
	}

	return true;
}

bool TmxTiledMap::ParseLayerBase(pugi::xml_node node, ITiledLayer& outLayer)
{
	StringRef name = node.attribute("name").as_string();
	outLayer.SetName(name);

	Point2I pos;
	pos.X = node.attribute("x").as_int(0);
	pos.Y = node.attribute("y").as_int(0);
	outLayer.SetPosition(pos);

	Size2I size;
	size.Width = node.attribute("width").as_int(0);
	size.Height = node.attribute("height").as_int(0);
	outLayer.SetSize(size);

	float opacity = node.attribute("opacity").as_float(1.f);
	outLayer.SetOpacity(opacity);

	bool isVisible = node.attribute("visible").as_bool(true);
	outLayer.SetVisible(isVisible);

	pugi::xml_node propertiesNode = node.child("properties");
	if (!propertiesNode.empty())
	{
		ParseProperties(propertiesNode, outLayer.MutableProperties());
	}

	return true;
}

bool TmxTiledMap::ParseTileLayer(pugi::xml_node node, TiledTileLayer& outTileLayer, TmxTiledMap& map)
{
	RETURN_FALSE_IF_FALSE(ParseLayerBase(node, outTileLayer));

	pugi::xml_node dataNode = node.child("data");
	StringRef encodingStr = node.attribute("encoding").as_string(nullptr);
	StringRef compressionStr = node.attribute("compression").as_string(nullptr);
	StringRef text = dataNode.value();

	if (encodingStr == "base64")
	{
		Base64Decoder decoder;
		MemoryByteData data = decoder.Code(text);
		MemoryByteData resultData;
		if (compressionStr == "gzip")
		{
			resultData = ZipReader::DecompressGZIP(data,outTileLayer.Size().Area()*sizeof(uint));

		}
		else if (compressionStr == "zlib")
		{
			// Use zlib to uncompress the tile layer into the temporary array of tiles.
			uLongf outlen = outTileLayer.Size().Area()*sizeof(uint);
			resultData = MemoryByteData::Alloc(outlen);
			uncompress(resultData.MutableData(), &outlen, data.Data(), data.Size());
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
		outTileLayer.InitializeTiles();

		//the decoded data is an array of 32 - bit integers.
		uint tileCount = outTileLayer.Size().Area();
		FOR_EACH_INT32_BEGIN_END(i, 0, (int)tileCount)
		{
			uint globalId = buffer[i];

			TiledTileRef& tileRef = outTileLayer.MutableTile(i);
			const TiledTileset* tileset = map.FindTilesetContainsGlobalId(globalId);
			int firstGlobalId = tileset != nullptr ? tileset->FirstGlobalId() : 0;
			tileRef.Initialize(globalId, firstGlobalId, tileset);
		}
	}
	else if (encodingStr == "csv")
	{
		int index = 0;
		List<uint> outValues;
		StringParser::SplitToValues(text, StringRef(","), outValues);
		FOR_EACH_COLLECTION(i, outValues)
		{
			uint globalId = *i;
			TiledTileRef& tileRef = outTileLayer.MutableTile(index++);
			const TiledTileset* tileset = map.FindTilesetContainsGlobalId(globalId);
			int firstGlobalId = tileset != nullptr ? tileset->FirstGlobalId() : 0;
			tileRef.Initialize(globalId, firstGlobalId, tileset);
		}

	}
	else if (encodingStr == "xml")
	{
		int index = 0;
		FOR_EACH_COLLECTION_STL(i, node.children())
		{
			pugi::xml_node tileNode = *i;
			uint globalId = tileNode.attribute("gid").as_uint(0);
			TiledTileRef& tileRef = outTileLayer.MutableTile(index++);
			const TiledTileset* tileset = map.FindTilesetContainsGlobalId(globalId);
			int firstGlobalId = tileset != nullptr ? tileset->FirstGlobalId() : 0;
			tileRef.Initialize(globalId, firstGlobalId, tileset);

		}
	}
	else
	{
		Log::FormatError("Unsupported encoding type:{}", encodingStr.c_str());
		return false;
	}

	return true;
}

bool TmxTiledMap::ParseImageLayer(pugi::xml_node node, TiledImageLayer& outLayer, TmxTiledMap& map)
{
	RETURN_FALSE_IF_FALSE(ParseLayerBase(node, outLayer));
	pugi::xml_node imageNode = node.child("image");
	if (!imageNode.empty())
	{
		TiledImage* image = new TiledImage();
		ParseImage(imageNode, *image);
		outLayer.SetImage(image);
	}
	return true;
}

bool TmxTiledMap::ParseObjectLayer(pugi::xml_node node, TiledObjectLayer& outLayer, TmxTiledMap& map)
{
	RETURN_FALSE_IF_FALSE(ParseLayerBase(node, outLayer));
	const char* colorStr = node.attribute("color").as_string(nullptr);
	Color4B color = ParseColor(colorStr);
	outLayer.SetColor(color);
	FOR_EACH_COLLECTION_STL(i, node.children())
	{
		pugi::xml_node objectNode = *i;
		TiledObject& obj = outLayer.NewObject();
		ParseObject(objectNode, obj);
	}

	return true;
}

Color4B TmxTiledMap::ParseColor(const StringRef& str)
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

bool TmxTiledMap::Parse(pugi::xml_node& rootNode)
{
	mVersion = rootNode.attribute("version").as_float(0.f);
	mSize.Width = rootNode.attribute("width").as_int(0);
	mSize.Height = rootNode.attribute("height").as_int(0);
	mTileSize.Width = rootNode.attribute("tilewidth").as_int(0);
	mTileSize.Height = rootNode.attribute("tileheight").as_int(0);
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

	FOR_EACH_COLLECTION_STL(i, rootNode.children())
	{
		pugi::xml_node child = *i;
		StringRef childName = child.name();

		if (childName == "properties")
		{
			ParseProperties(child, mProperties);
		}
		else if (childName == "tileset")
		{
			TiledTileset *tileset = new TiledTileset();
			ParseTileset(child, *tileset,*this);
			mTilesets.Add(tileset);

		}
		else if (childName == "layer")
		{
			TiledTileLayer* tileLayer = new TiledTileLayer();
			ParseTileLayer(child, *tileLayer, *this);
			mLayers.Add(tileLayer);
			mTileLayers.Add(tileLayer);
		}
		else if (childName == "imagelayer")
		{
			TiledImageLayer* imageLayer = new TiledImageLayer();
			ParseImageLayer(child, *imageLayer, *this);
			mLayers.Add(imageLayer);
			mImageLayers.Add(imageLayer);
		}
		else if (childName == "objectgroup")
		{
			TiledObjectLayer* objectLayer = new TiledObjectLayer();
			ParseObjectLayer(child, *objectLayer, *this);
			mLayers.Add(objectLayer);
			mObjectLayers.Add(objectLayer);
		}
	}
	return true;
}

MEDUSA_END;