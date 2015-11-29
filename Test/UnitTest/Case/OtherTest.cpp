// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "Case/OtherTest.h"

/*
TestFloat	1074.285570 / 10000000 = 0.000107
TestFloat2	30.188889 / 10000000 = 0.000003
*/
void OtherTest::TestFloat()
{
	const int count=10000000;
	float f=1.73f;
	float outi;

	StopWatch watch;
	watch.SetRunTimes(count);
	watch.SetName("TestFloat");

	watch.Start();
	FOR_EACH_SIZE(i,count)
	{
		float r= modf(f,&outi);
		int ii=(int)outi;
	}

	watch.Shot();
	watch.PrintResult();

	watch.SetName("TestFloat2");
	watch.Start();
	for (int i=0;i<count;i++)
	{
		int ii=(int)outi;
		float r=f-(float)ii;
	}
	watch.Shot();
	watch.PrintResult();

}

void OtherTest::TestMd5()
{
	const int count = 100000;

	StopWatch watch;
	watch.SetRunTimes(count);
	watch.SetName("TestMd5");

	byte temp[512];
	watch.Start();
	FOR_EACH_SIZE(i, count)
	{
		MD5 md5;
		md5.Process(temp,512);
		md5.Digest();
	}

	watch.Shot();
	watch.PrintResult();
}

void OtherTest::TestFlag()
{
	const int count = 100000;

	StopWatch watch;
	watch.SetRunTimes(count);
	watch.SetName("TestFlag");

	watch.Start();

	MoveableChangedFlags flag = MoveableChangedFlags::AnchorChanged;
	uint sum = 0;
	FOR_EACH_SIZE(i, count)
	{
		if (flag.Has(MoveableChangedFlags::AnchorChanged))
		{
			++sum;
		}
	}

	watch.Shot();
	watch.PrintResult();
}
