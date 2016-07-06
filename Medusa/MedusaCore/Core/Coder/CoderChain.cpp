// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Coder/CoderChain.h"
#include "Core/Coder/CoderFactory.h"
#include "Core/Log/Log.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Pattern/SwapValue.h"
#include "Core/Event/EventArg/UserDataEventArg.h"


MEDUSA_BEGIN;

CoderChain::CoderChain(CoderList coders, const MemoryData& key)
{
	Initialize(coders, key);
}



CoderChain::CoderChain(const CoderChain& other)
	:mCoders(other.mCoders),
	mEncoders(other.mEncoders),
	mDecoders(other.mDecoders)
{

}

CoderChain& CoderChain::operator=(const CoderChain& other)
{
	mCoders = other.mCoders;
	mEncoders = other.mEncoders;
	mDecoders = other.mDecoders;
	return *this;
}

CoderChain::CoderChain(CoderChain&& other)
	:mCoders(other.mCoders),
	mEncoders(std::move(other.mEncoders)),
	mDecoders(std::move(other.mDecoders))
{
	other.Uninitialize();
}

CoderChain& CoderChain::operator=(CoderChain&& other)
{
	if (this != &other)
	{
		mCoders = other.mCoders;
		mEncoders = std::move(other.mEncoders);
		mDecoders = std::move(other.mDecoders);

		other.Uninitialize();
	}


	return *this;
}


CoderChain::~CoderChain()
{
	Uninitialize();
}

uint64 CoderChain::AddCoders(uint64 coders, CoderType coderType)
{
	uint64 codersCopy = coders;

	//find most left not 0 byte
	size_t i = 0;
	for (; i < 8; ++i)
	{
		byte coderByte = (byte)(codersCopy >> 56);
		if (coderByte == 0)
		{
			break;
		}
		codersCopy <<= 8;
	}

	if (i == 8)
	{
		return Math::UInt64MaxValue;
	}
	coders |= ((uint64)coderType << ((7 - i) * 8));
	return coders;
}

bool CoderChain::RequireKey(uint64 coders)
{
	while (true)
	{
		byte coderByte = (byte)(coders >> 56);
		if (coderByte != 0)
		{
			if (coderByte >= (byte)CoderType::Decoder_Begin)
			{
				Log::FormatError("Invalid coder type {}", coderByte);
				return false;
			}

			coders <<= 8;
			if (CoderFactory::RequireKey((CoderType)coderByte))
			{
				return true;
			}
		}
		else
		{
			break;
		}
	}
	return false;
}

bool CoderChain::Initialize(CoderList coders, const MemoryData& key)
{
	if (mCoders == coders&&mKey.IsContentEqual(key))
	{
		return true;
	}
	
	mCoders = coders;
	mKey = key.Clone();
	return InitializeHelper();
}

bool CoderChain::InitializeHelper()
{
	RETURN_TRUE_IF_ZERO(mCoders);
	mEncoders.Clear();
	mDecoders.Clear();

	CoderList coders = mCoders;

	while (true)
	{
		byte coderByte = (byte)(coders >> 56);
		if (coderByte != 0)
		{
			if (coderByte >= (byte)CoderType::Decoder_Begin)
			{
				Log::FormatError("Invalid coder type {}", coderByte);
				return false;
			}

			coders <<= 8;
			UserDataEventArg<MemoryData> e(mKey);
			ICoder* coder = CoderFactory::Instance().Create((CoderType)coderByte, e);
			if (coder == nullptr)
			{
				Log::FormatError("Cannot find coder:{}", coder);
				return false;
			}
			else
			{
				mEncoders.Add(coder);
			}
		}
		else
		{
			break;
		}
	}

	coders = mCoders;
	//decoders
	while (coders != 0)
	{
		byte coderByte = (byte)(coders & 0xFF);
		if (coderByte != 0)
		{
			if (coderByte >= (byte)CoderType::Decoder_Begin)
			{
				Log::FormatError("Invalid coder type {}", coderByte);
				return false;
			}

			coderByte += (byte)CoderType::Decoder_Begin;

			UserDataEventArg<MemoryData> e(mKey);
			ICoder* coder = CoderFactory::Instance().Create((CoderType)coderByte, e);
			if (coder == nullptr)
			{
				Log::FormatError("Cannot find coder:{}", coder);
				return false;
			}
			else
			{
				mDecoders.Add(coder);
			}
		}
		coders >>= 8;
	}

	return true;
}


bool CoderChain::Uninitialize()
{
	mCoders = 0;
	mKey = MemoryData::Empty;
	SAFE_DELETE_COLLECTION(mEncoders);
	SAFE_DELETE_COLLECTION(mDecoders);

	return true;
}

void CoderChain::SetCoders(CoderList val)
{
	RETURN_IF_EQUAL(mCoders, val);
	mCoders = val;
	InitializeHelper();
}

bool CoderChain::Validate() const
{
	for (const auto* coder:mEncoders)
	{
		RETURN_FALSE_IF_FALSE(coder->Validate());
	}

	for (const auto* coder : mDecoders)
	{
		RETURN_FALSE_IF_FALSE(coder->Validate());
	}

	return true;
}

void CoderChain::SetKey(const MemoryData& val)
{
	if (mKey.IsContentEqual(val))
	{
		return;
	}

	mKey = val.Clone();
	InitializeHelper();
}

size_t CoderChain::Encode(IStream& input, IStream& output) const
{
	return OnCode(mEncoders, input, output);
}
size_t CoderChain::Encode(const IStream& input, IStream& output) const
{
	return OnCode(mEncoders, input, output);
}

size_t CoderChain::Encode(const MemoryData& input, MemoryData& output) const
{
	return OnCode(mEncoders, input, output);
}

size_t CoderChain::Decode(const MemoryData& input, MemoryData& output) const
{
	return OnCode(mDecoders, input, output);

}

size_t CoderChain::Decode(IStream& input, IStream& output) const
{
	return OnCode(mDecoders, input, output);
}

size_t CoderChain::Decode(const IStream& input, IStream& output) const
{
	return OnCode(mDecoders, input, output);
}

size_t CoderChain::OnCode(const List<ICoder*>& coders, IStream& input, IStream& output)
{
	RETURN_ZERO_IF_EMPTY(coders);
	

	size_t count = coders.Count();
	if (count == 1)
	{
		return coders.First()->Code(input, output);
	}

	SwapValue<MemoryStream> tempStream;
	FOR_EACH_SIZE(i, count)
	{
		const ICoder* coder = coders[i];
		if (i == 0)
		{
			//first
			MemoryStream& temp = tempStream.MutableFront();
			coder->Code(input, temp);
		}
		else if (i == count - 1)
		{
			//last
			MemoryStream& temp = tempStream.MutableFront();
			auto tempData= temp.CurrentBuffer();
			const MemoryStream tempInput(tempData);
			return coder->Code(tempInput, output);
		}
		else
		{
			MemoryStream& temp = tempStream.MutableFront();
			auto tempData = temp.CurrentBuffer();
			const MemoryStream tempInput(tempData);

			MemoryStream& temp2 = tempStream.MutableBack();
			temp2.Rewind();
			coder->Code(tempInput, temp2);
			tempStream.Swap();
		}
	}


	return 0;
}

size_t CoderChain::OnCode(const List<ICoder*>& coders, const IStream& input, IStream& output)
{
	RETURN_ZERO_IF_EMPTY(coders);
	size_t count = coders.Count();
	if (count == 1)
	{
		return coders.First()->Code(input, output);
	}

	SwapValue<MemoryStream> tempStream;
	FOR_EACH_SIZE(i, count)
	{
		const ICoder* coder = coders[i];
		if (i == 0)
		{
			//first
			MemoryStream& temp = tempStream.MutableFront();
			coder->Code(input, temp);
		}
		else if (i == count - 1)
		{
			//last
			MemoryStream& temp = tempStream.MutableFront();
			auto tempData = temp.CurrentBuffer();
			const MemoryStream tempInput(tempData);
			return coder->Code(tempInput, output);
		}
		else
		{
			MemoryStream& temp = tempStream.MutableFront();
			auto tempData = temp.CurrentBuffer();
			const MemoryStream tempInput(tempData);

			MemoryStream& temp2 = tempStream.MutableBack();
			temp2.Rewind();
			coder->Code(tempInput, temp2);
			tempStream.Swap();
		}
	}


	return 0;
}

size_t CoderChain::OnCode(const List<ICoder*>& coders, const MemoryData& input, MemoryData& output)
{
	const MemoryStream inputStream(input);
	MemoryStream outputStream(output);

	return OnCode(coders, inputStream, outputStream);
}

size_t CoderChain::OnCode(const List<ICoder*>& coders, MemoryData& input, MemoryData& output)
{
	MemoryStream inputStream(input);
	MemoryStream outputStream(output);

	return OnCode(coders, inputStream, outputStream);
}

const CoderChain CoderChain::Empty;

MEDUSA_END;

