// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ApplePropertyListNode.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"
#include "Core/Log/Log.h"
#include "Core/Coder/Crypt/Base64Decoder.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/System/BitConverter.h"

MEDUSA_BEGIN;

ApplePropertyListNode::ApplePropertyListNode()
{

}

ApplePropertyListNode::~ApplePropertyListNode(void)
{
	Clear();
}

void ApplePropertyListNode::Clear()
{
	if (mData.is<NodeList>())
	{
		auto& items = mData.get<NodeList>();
		SAFE_DELETE_COLLECTION(items);
	}
	else if (mData.is<NodeDict>())
	{
		auto& items = mData.get<NodeDict>();
		SAFE_DELETE_DICTIONARY_VALUE(items);
	}
	mData.clear();
}

bool ApplePropertyListNode::Parse(const pugi::xml_node& node)
{
	StringRef nodeName = node.name();
	if (nodeName == "true")
	{
		mData = true;
	}
	else if (nodeName == "false")
	{
		mData = false;
	}
	else if (nodeName == "integer")
	{
		mData = (int64)StringParser::ToInt(node.first_child().value());
	}
	else if (nodeName == "real")
	{
		mData = StringParser::StringTo<double>(node.first_child().value());
	}
	else if (nodeName == "string")
	{
		mData = HeapString(node.first_child().value());
	}
	else if (nodeName == "date")
	{
		mData = DateTime::Parse(node.first_child().value(), "{}-{}-{}T{}:{}:{}Z");
	}
	else if (nodeName == "data")
	{
		Base64Decoder decoder;
		mData = decoder.Code(node.first_child().value());
	}
	else if (nodeName == "array")
	{
		auto& childs = mData.set<NodeList>();
		for (const auto& childNode : node)
		{
			std::unique_ptr<ApplePropertyListNode> child(new ApplePropertyListNode());
			RETURN_FALSE_IF_FALSE(child->Parse(childNode));
			childs.Add(child.release());
		}

	}
	else if (nodeName == "dict")
	{
		auto& dict = mData.set<NodeDict>();
		for (auto i = node.begin(); i != node.end(); ++i)
		{
			if (StringRef(i->name()) != "key")
			{
				Log::Error("Plist: XML dictionary key expected but not found");
				return false;
			}

			StringRef key = i->first_child().value();
			++i;
			if (i == node.end())
			{
				Log::FormatError("Plist: XML dictionary value expected for key {} but not found.", key);
				return false;
			}
			else if (StringRef(i->name()) == "key")
			{
				Log::FormatError("Plist: XML dictionary value expected for key {} but found another key node.", key);
				return false;
			}
			std::unique_ptr<ApplePropertyListNode> child(new ApplePropertyListNode());
			RETURN_FALSE_IF_FALSE(child->Parse(*i));
			dict.Add(key, child.release());

		}
	}
	else
	{
		Log::FormatError("Plist: XML unknown node type:", nodeName);
		return false;
	}

	return true;
}



bool ApplePropertyListNode::Parse(MemoryStream& stream, const BinaryHeader& header, int objIndex)
{
	auto offset = header.Offsets[objIndex];
	stream.Seek(offset, SeekOrigin::Begin);
	int type = stream.ReadChar();

	switch (type & 0xF0)
	{
	case 0x00:	//bool
		if (type == 0x09)
		{
			mData = true;
		}
		else if (type == 0x08)
		{
			mData = false;
		}
		else
		{
			Log::FormatError("Plist: Invalid bool value:{}", type);
			return false;
		}
		break;
	case 0x10:	//int
	{
		int byteCount = 1 << (type & 0xf);
		auto ptr = stream.Ptr();
		mData = (int64)BitConverter::ToInt(ptr, byteCount);
		stream.Skip(byteCount);
		break;
	}
	case 0x20:	//double
	{
		int byteCount = 1 << (type & 0xf);
		auto ptr = stream.Ptr();
		if (byteCount == sizeof(float))
		{
			mData = (double)BitConverter::ToFloat(ptr);
			stream.Skip(byteCount);
		}
		else if (byteCount == sizeof(double))
		{
			mData = BitConverter::ToDouble(ptr);
			stream.Skip(byteCount);
		}
		else
		{
			Log::FormatError("Plist: Invalid double byteCount:{}", byteCount);
			return false;
		}

		break;
	}
	case 0x30://date
	{
		auto ptr = stream.Ptr();
		BitConverter::SwapBytes((byte*)ptr, sizeof(double));

		// Date is stored as Apple Epoch and big endian.
		double appleTime = BitConverter::ToDouble(ptr);
		stream.Skip(sizeof(double));

		// Apple epoch is # of seconds since  01-01-2001. So we need to add the
		// number of seconds since 01-01-1970 which is proper unix epoch
		auto timeVal = time_t(978307200 + appleTime);
		mData = DateTime(std::chrono::system_clock::from_time_t(timeVal));
		break;
	}
	case 0x40://data
	{
		int byteCount = 1 << (type & 0xf);
		if (byteCount > 15)
		{
			//next int
			type = stream.ReadChar();
			byteCount = 1 << (type & 0xf);
			auto ptr = stream.Ptr();
			int dataSize = BitConverter::ToInt(ptr, byteCount);
			stream.Skip(byteCount);
			byteCount = dataSize;
		}
		mData = stream.ReadData(byteCount);

		break;
	}
	case 0x50:	//string
	{
		int byteCount = 1 << (type & 0xf);
		if (byteCount > 15)
		{
			//next int
			type = stream.ReadChar();
			byteCount = 1 << (type & 0xf);
			auto ptr = stream.Ptr();
			int dataSize = BitConverter::ToInt(ptr, byteCount);
			stream.Skip(byteCount);
			byteCount = dataSize;
		}

		auto& str = mData.set<HeapString>();
		str.ReserveLength(byteCount);
		stream.ReadDataToString(str, byteCount);
		break;

	}
	case 0x60://unicode string
	{
		int byteCount = 1 << (type & 0xf);
		if (byteCount > 15)
		{
			//next int
			type = stream.ReadChar();
			byteCount = 1 << (type & 0xf);
			auto ptr = stream.Ptr();
			int dataSize = BitConverter::ToInt(ptr, byteCount);
			stream.Skip(byteCount);
			byteCount = dataSize;
		}
		WHeapString str;
		str.ReserveLength(byteCount);
		stream.ReadDataToString(str, byteCount);
		mData = StringParser::ToA(str);
		break;
	}
	case 0xA0:
	case 0xC0:
	{
		int itemCount = 1 << (type & 0xf);
		if (itemCount > 15)
		{
			//next int
			type = stream.ReadChar();
			itemCount = 1 << (type & 0xf);
			auto ptr = stream.Ptr();
			int dataSize = BitConverter::ToInt(ptr, itemCount);
			stream.Skip(itemCount);
			itemCount = dataSize;
		}

		auto& items = mData.set<NodeList>();
		items.ReserveSize(itemCount);
		auto ptr = stream.Ptr();

		FOR_EACH_INT32(i, itemCount)
		{
			int childObjectIndex = BitConverter::ToInt(ptr, header.ObjectIntByteSize);
			ptr += header.ObjectIntByteSize;
			std::unique_ptr<ApplePropertyListNode> child(new ApplePropertyListNode());
			RETURN_FALSE_IF_FALSE(child->Parse(stream, header, childObjectIndex));
			items.Add(child.release());
		}
	}
	case 0xD0:
	{
		int itemCount = 1 << (type & 0xf);
		if (itemCount > 15)
		{
			//next int
			type = stream.ReadChar();
			itemCount = 1 << (type & 0xf);
			auto ptr = stream.Ptr();
			int dataSize = BitConverter::ToInt(ptr, itemCount);
			stream.Skip(itemCount);
			itemCount = dataSize;
		}

		auto& items = mData.set<NodeDict>();
		items.ReserveSize(itemCount);
		auto keyPtr = stream.Ptr();
		auto valuePtr = keyPtr + itemCount*header.ObjectIntByteSize;


		FOR_EACH_INT32(i, itemCount)
		{
			int keyObjectIndex = BitConverter::ToInt(keyPtr, header.ObjectIntByteSize);
			keyPtr += header.ObjectIntByteSize;

			int valueObjectIndex = BitConverter::ToInt(valuePtr, header.ObjectIntByteSize);
			valuePtr += header.ObjectIntByteSize;


			ApplePropertyListNode keyNode;
			keyNode.Parse(stream, header, keyObjectIndex);
			const HeapString& key = keyNode.mData.get<HeapString>();

			std::unique_ptr<ApplePropertyListNode> valueNode(new ApplePropertyListNode());
			RETURN_FALSE_IF_FALSE(valueNode->Parse(stream, header, valueObjectIndex));

			items.Add(key, valueNode.release());
		}
	}

	}

	return true;
}


const ApplePropertyListNode& ApplePropertyListNode::operator[](StringRef name) const
{
	return *mData.get<NodeDict>().Get(name);
}

const ApplePropertyListNode* ApplePropertyListNode::Find(StringRef name) const
{
	return mData.get<NodeDict>().GetOptional(name,nullptr);
}

MEDUSA_END;

