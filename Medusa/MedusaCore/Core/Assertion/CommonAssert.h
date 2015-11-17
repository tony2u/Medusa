// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"

/*
 *level:
 *0:highest
 *1:first
 *
 *ASSERT_LEVEL:
 *-1:disable all assert
 *0:enable level 0
 **/
//

/*
printf("{}\n",__DATE__);
printf("{}\n",__TIME__);
printf("{}\n",__TIMESTAMP__);


printf("{}\n",__FILE__);
printf("{}\n",__FUNCTION__);
printf("{}\n",__FUNCDNAME__);
printf("{}\n",__FUNCSIG__);

printf("{}\n",__LINE__);

Output:

Dec 23 2011
14:29:04
Fri Dec 23 14:28:48 2011
d:\workspace\testarray\testarray\testst~1.cpp
main
main
int __cdecl main(int,char **)
133


*/
#ifdef MEDUSA_DEBUG
static inline void __MedusaAssertFailed()
{
	assert(false);
}
#else
static inline void __MedusaAssertFailed()
{
	
}
#endif

#define MEDUSA_ASSERT_FAILED_SILENT	{\
	__MedusaAssertFailed();\
}
#define MEDUSA_ASSERT_FAILED(msg)	{\
	__MedusaAssertFailed();assert(false&&msg);\
}


#define MEDUSA_ASSERT_SILENT(cond)		if(!(cond)){MEDUSA_ASSERT_FAILED_SILENT;}

#define MEDUSA_ASSERT(cond,msg)		if(!(cond)){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_IF(cond,msg)		if(!(cond)){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_TRUE(cond,msg)		if((cond)!=true){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_FALSE(cond,msg)	if((cond)!=false){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_NULL(cond,msg)		if((cond)!=nullptr){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_EMPTY(cond,msg)	if(!(cond).IsEmpty()){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_ZERO(cond,msg)		if((cond)!=0){MEDUSA_ASSERT_FAILED(msg);}

#define MEDUSA_ASSERT_NOT(cond,msg)			if((cond)){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_NOT_NULL(cond,msg)		if((cond)==nullptr){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_NOT_EMPTY(cond,msg)	if((cond).IsEmpty()){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_NOT_ZERO(cond,msg)		if((cond)==0){MEDUSA_ASSERT_FAILED(msg);}

#define MEDUSA_ASSERT_EQUAL(object,cond,msg)			if(!((object)==(cond))){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_NOT_EQUAL(object,cond,msg)		if(!((object)!=(cond))){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_LESS(object,cond,msg)			if(!((object)<(cond))){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_LESS_EQUAL(object,cond,msg)			if(!((object)<=(cond))){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_GREATER(object,cond,msg)			if(!((object)>(cond))){MEDUSA_ASSERT_FAILED(msg);}
#define MEDUSA_ASSERT_GREATER_EQUAL(object,cond,msg)			if(!((object)>=(cond))){MEDUSA_ASSERT_FAILED(msg);}

#define MEDUSA_ASSERT_NOT_IMPLEMENT()	assert(false&&"Not implement!");
