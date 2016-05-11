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



int _tmain(int argc, _TCHAR* argv[])
{
	Log::Initialize();
	FileSystem::Instance().Initialize();

	auto* ass = SirenMachine::Instance().NewAssembly("test");
	ass->Parse("person.mp");
	ass->Execute();
	ass->Link();

	auto* personType = ass->FindCustomType("person");

	HeapString str("test blob data");
	MemoryData blobData = MemoryData::FromStatic((byte*)str.c_str(), str.Length());

	SirenObject obj;
	obj.SetStruct();
	obj.NewField("id") = 123;
	obj.NewField("name") = "abc";
	auto& sub = obj.NewStruct("address");
	sub.AddField("id", 456);
	sub.AddField("address", "Beijing");

	obj.NewField("factor") = 5.f;
	obj.AddEnum("gender", 1);
	obj.AddField("data", blobData);

	HeapString printStr = obj.Print();
	Log::Info(printStr);

	auto data = Siren::Serialize(obj, *personType);
	SirenObject otherObj = Siren::Deserialize(data, *personType);

	printStr = otherObj.Print();
	Log::Info(printStr);
	system("PAUSE");

	return 0;

}