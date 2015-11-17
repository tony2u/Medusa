// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
// Test.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>

#include "Case/MatrixTest.h"
#include "Case/CollectionTest.h"
#include "Case/OtherTest.h"
#include "Case/FormatTest.h"
#include "Case/CodeTest.h"

#include "Core/Siren/Siren.h"
#include "Core/Siren/Protocol/Binary/CompactBinaryWriter.h"
#include "Core/Siren/Protocol/Binary/CompactBinaryReader.h"
#include "Core/Siren/Protocol/Binary/FastBinaryWriter.h"
#include "Core/Siren/Protocol/Binary/FastBinaryReader.h"


#include "Core/Siren/Protocol/Binary/CompactBinarySizeCounter.h"
#include "Core/Siren/Protocol/Json/JsonWriter.h"


//#include "Core/Proto/BaseData.h"
//#include "Core/Proto/DerivedData.h"



STRONG_FLAGS_3(MyFlags, First, Second, Third);

int _tmain(int argc, _TCHAR* argv[])
{
	//StringRef aaaaaaaaa="abc";
	//std::string abc="Hello";

	//int l=aaaaaaaaa.Length();

	//aaaaaaaaa="";

	//printf("%d\n",sizeof(BaseSprite));
	//printf("%d\n",sizeof(INode));
	//printf("%d\n",sizeof(IMoveable));
	//printf("%d\n",sizeof(DefaultMoveable));


	//printf("%d\n",sizeof(LazyMatrix43::TUpdateDelegateType));
	//printf("%d\n",sizeof(LazyMatrix43));

	//printf("%d\n",sizeof(Matrix43));

	//printf("%d\n",sizeof(List<int*>));





	//MyFlags my;
	//my=MyFlags::Second;
	//printf("%s\n",my.ToString().Buffer());

	//my|=MyFlags::Third;
	//printf("%s\n",my.ToString().Buffer());
	//my|=MyFlags::First;

	//printf("%s\n",my.ToString().Buffer());

	//printf("%s\n",my.ToString().Buffer());

	//MatrixTest::TestTransformPartial();
	//MEDUSA_ASSERT_FAILED("Invalid enum val");
	//CollectionTest::TestDictionary();


	//OtherTest::TestFlag();
	/*
	Log::Initialize();

	DerivedData data;
	data.MutableFirst() = 2;
	data.MutableSecond() = 987;
	data.MutableThird() = "abc";

	data.NewForth() = 1;
	data.NewForth() = 2;

	data.AddFifth(1, 444);
	data.AddFifth(2, 555);

	HeapString str("123456");
	data.MutableSixth() = str.ToMemoryData().Cast<byte>();

	data.MutableSix() = 999;
	data.MutableSeven() = 888.7897f;

	data.MutableOther().SetFirst(555);
	data.MutableOther().SetSecond(666.f);
	data.MutableOther().SetStatus(OtherDataStatus::DontUpgrade);
	//data.MutableOther().SetTestFileType(FileType::jpeg);
	//data.MutableOther().MutableOtherType() = Siren::SirenDataType::Dictionary;

	data.MutableOther().MutablePos().X = 1.f;
	data.MutableOther().MutablePos().Y = 2.f;

	const MemoryByteData& bufferData = Siren::AutoSerialize(data);
	//const MemoryByteData& bufferData = Siren::Serialize<Siren::FastBinaryWriter>(data);

	//const MemoryByteData& bufferData = Siren::Serialize<Siren::SimpleJsonWriter>(data);
	//StringRef resultStr(bufferData.Cast<char>());

	DerivedData outData;
	Siren::DeserializeBinary(bufferData, outData);


	HeapString outStr;
	Siren::SerializeJson(data, outStr);
	//

	DerivedData outData2;
	Siren::DeserializeJson(outStr, outData2);
	/*MemoryStream readStream(bufferData,false);
	Siren::CompactBinaryReader<MemoryStream> reader(readStream);
	DerivedData outData;
	Siren::Deserialize(reader, outData);*/


	
	//Siren::Deserialize<Siren::FastBinaryReader>(bufferData, outData);

	
	//FormatTest::TestFormat();

	system("PAUSE");

	return 0;

}