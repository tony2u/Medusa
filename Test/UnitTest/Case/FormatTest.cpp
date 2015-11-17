// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "Case/FormatTest.h"
#include "format2.h"
#include "Core/String/Format/Format.h"


void FormatTest::TestInt()
{
	const int count=100000;
	int val = 1000;

	StopWatch watch;
	watch.SetRunTimes(count);
	watch.SetName("TestInt");

	watch.Start();
	std::string str1;
	FOR_EACH_SIZE(i, count)
	{
		char temp[64];
		sprintf_s(temp, "%d", val);
		str1.assign(temp);
	}

	watch.Shot();
	watch.PrintResult();

	watch.Start();
	HeapString str;
	FOR_EACH_SIZE(i,count)
	{
		str=String::Format("{}", val);
	}

	

	watch.Shot();
	watch.PrintResult();

	watch.SetName("TestInt");
	watch.Start();
	std::string str2;
	for (int i=0;i<count;i++)
	{
		str2=fmt::format("{}", val);
	}
	watch.Shot();
	watch.PrintResult();

}

void FormatTest::TestFloat()
{
	const int count = 100000;
	float val = 3333.45776f;

	StopWatch watch;
	watch.SetRunTimes(count);
	watch.SetName("TestInt");

	watch.Start();
	std::string str1;
	FOR_EACH_SIZE(i, count)
	{
		char temp[64];
		sprintf_s(temp, "%+.1f", val);
		str1.assign(temp);
	}

	watch.Shot();
	watch.PrintResult();

	watch.Start();
	HeapString str;
	FOR_EACH_SIZE(i, count)
	{
		str = String::Format("{:f+1}", val);
	}

	watch.Shot();
	watch.PrintResult();

	watch.SetName("TestInt");
	watch.Start();
	std::string str2;
	for (int i = 0; i < count; i++)
	{
		str2 = fmt::format("{:+.1f}", val);
	}
	watch.Shot();
	watch.PrintResult();

}

void FormatTest::TestFormat()
{
	StringRef str1("world");
	HeapString str2("world");
	StackString<10> str3("Fuck");


	HeapString str = String::Format("{},{},{},{}, {},{},{},{}, {},{:f3},{},{}, {},{},{}",
		true, 'c', (byte)'B', (short)-123, (ushort)123, -456, (uint)456, (int64)-789, (uint64)789, 123.456f, (double)123.456, "hello", str1,str2, str3);
	printf(str.c_str());

	WStringRef str9(L"world");
	WHeapString str10(L"world");
	WStackString<10> str11(L"fuck");

	WHeapString strA = String::Format(L"{},{},{},{}, {},{},{},{}, {},{:f3},{},{} , {},{},{}", 
		true, 'c', (byte)'B', (short)-123, (ushort)123, -456, (uint)456, (int64)-789, (uint64)789, 123.456f, (double)123.456, L"hello",str9,str10, str11);
	wprintf(strA.c_str());


	str.Format("{},{},{},{}, {},{},{},{}, {},{:f3},{},{}, {},{},{}",
		true, 'c', (byte)'B', (short)-123, (ushort)123, -456, (uint)456, (int64)-789, (uint64)789, 123.456f, (double)123.456, "hello", str1, str2, str3);
	printf(str.c_str());

}
