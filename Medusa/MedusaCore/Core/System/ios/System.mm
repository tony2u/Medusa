// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"

#ifdef MEDUSA_IOS

#import "System.h"
#include "Core/Log/Log.h"
#include "Core/IO/Directory.h"
#include "Core/String/StringParser.h"
#include "Core/IO/Path.h"
#include <Foundation/Foundation.h>

MEDUSA_BEGIN;
System::System( void )
{
    UpdatePaths();
}

void System::UpdatePaths()
{
	{
		NSString *documentsDirectory =[[NSBundle mainBundle] resourcePath];
        const char* buffer = [documentsDirectory UTF8String];
        mReadonlyPath=buffer;
    }
    {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
		NSString *documentsDirectory = [paths objectAtIndex:0];
		const char* buffer = [documentsDirectory UTF8String];
		mWritablePath=buffer;
    }
    
    {
		
		NSString *documentsDirectory = NSTemporaryDirectory();
		const char* buffer = [documentsDirectory UTF8String];
		mTempPath=buffer;
    }
    
	mReadonlyPath=Path::CombineNoChecks(mReadonlyPath,mReadonlySubPath);
	mWritablePath=Path::CombineNoChecks(mWritablePath,mWritableSubPath);
	mTempPath=Path::CombineNoChecks(mTempPath,mTempSubPath);
    
    
}



MEDUSA_END;

#endif