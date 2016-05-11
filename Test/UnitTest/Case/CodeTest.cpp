// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "Case/CodeTest.h"
#include "Core/Coder/LZMA/LZMAEncoder.h"
#include "Core/Coder/LZMA/LZMADecoder.h"

#include "Core/Coder/LZ4/LZ4Decoder.h"
#include "Core/Coder/LZ4/LZ4Encoder.h"

#include "Core/Coder/Crypt/Aes256Decoder.h"
#include "Core/Coder/Crypt/Aes256Encoder.h"




void CodeTest::TestLZMA()
{
	MemoryData testData = MemoryData::Alloc(1024 * 100);	//100K data
	byte* buffer= testData.MutableData();
	FOR_EACH_SIZE(i, 100)
	{
		FOR_EACH_SIZE(j, 1024)
		{
			buffer[i * 1024 + j] = (byte)i;
		}
	}

	//Random::Global().NextBytes(testData);

	MemoryStream input((const MemoryData&)testData);
	MemoryStream output;

	LZMAEncoder encoder;
	encoder.Code(input, output);

	LZMADecoder decoder;
	const auto encodedData = output.CurrentBuffer();
	MemoryStream input2(encodedData);
	MemoryStream output2;

	decoder.Code(input2, output2);

	auto decodedData= output2.CurrentBuffer();
	if (!testData.IsContentEqual(decodedData))
	{
		Log::FormatError("Failed");
	}
}

void CodeTest::TestLZ4()
{
	MemoryData testData = MemoryData::Alloc(1024 * 100);	//100K data
	byte* buffer = testData.MutableData();
	FOR_EACH_SIZE(i, 100)
	{
		FOR_EACH_SIZE(j, 1024)
		{
			buffer[i * 1024 + j] = (byte)i;
		}
	}

	//Random::Global().NextBytes(testData);

	MemoryStream input((const MemoryData&)testData);
	MemoryStream output;

	LZ4Encoder encoder;
	encoder.Code(input, output);

	LZ4Decoder decoder;
	const auto encodedData = output.CurrentBuffer();
	MemoryStream input2(encodedData);
	MemoryStream output2;

	decoder.Code(input2, output2);

	auto decodedData = output2.CurrentBuffer();
	if (!testData.IsContentEqual(decodedData))
	{
		Log::FormatError("Failed");
	}
}

void CodeTest::TestAES256()
{
	MemoryData key = MemoryData::Alloc(Aes256Encoder::KeyMaxSize);
	Random::Global().NextBytes(key);


	MemoryData testData = MemoryData::Alloc(1024 * 100);	//100K data
	byte* buffer = testData.MutableData();
	FOR_EACH_SIZE(i, 100)
	{
		FOR_EACH_SIZE(j, 1024)
		{
			buffer[i * 1024 + j] = (byte)i;
		}
	}

	//Random::Global().NextBytes(testData);

	MemoryStream input((const MemoryData&)testData);
	MemoryStream output;

	Aes256Encoder encoder(key);
	encoder.Code(input, output);

	Aes256Decoder decoder(key);
	const auto encodedData = output.CurrentBuffer();
	MemoryStream input2(encodedData);
	MemoryStream output2;

	decoder.Code(input2, output2);

	auto decodedData = output2.CurrentBuffer();
	if (!testData.IsContentEqual(decodedData))
	{
		Log::FormatError("Failed");
	}
}
