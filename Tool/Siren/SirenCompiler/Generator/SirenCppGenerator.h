// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "ISirenGenerator.h"





class SirenCppGenerator :public ISirenGenerator
{

public:
	using ISirenGenerator::ISirenGenerator;
	virtual ~SirenCppGenerator(void) = default;

	virtual void SetTemplateName(StringRef val);

protected:
	virtual bool GenerateType(BaseSirenCustomType& type)const override;

	HeapString OnEnumHeader(SirenCustomEnum& sirenClass)const;

	HeapString OnClassIncludeWrapper(SirenCustomClass& sirenClass)const;

	HeapString OnClassInclude(SirenCustomClass& sirenClass)const;

	HeapString OnClassHeader(SirenCustomClass& sirenClass)const;
	HeapString OnClassConstruct(SirenCustomClass& sirenClass)const;
	HeapString OnClassCompare(SirenCustomClass& sirenClass)const;
	HeapString OnClassCopy(SirenCustomClass& sirenClass)const;
	HeapString OnClassMethods(SirenCustomClass& sirenClass)const;
	HeapString OnClassFields(SirenCustomClass& sirenClass)const;
	HeapString OnClassSchema(SirenCustomClass& sirenClass)const;
	HeapString GenerateAllBodyInclude(SirenCustomClass& sirenClass)const;
	HeapString GenerateBodyInclude(SirenCustomClass& sirenClass)const;
	HeapString GenerateAllBody(SirenCustomClass& sirenClass)const;
	HeapString GenerateBodyConstruct(SirenCustomClass& sirenClass)const;
	HeapString GenerateBodyDestruct(SirenCustomClass& sirenClass)const;
	HeapString GenerateBodyMetadata(SirenCustomClass& sirenClass)const;
private:
	static SirenFieldMethodType GetMethodType(const SirenField& field);
	static SirenFieldValueType GetValueType(const SirenField& field);
	static HeapString GetDefaultValueString(const SirenField& field);


	static HeapString GetTypeName(ISirenType* type, bool forceToPtr = false);
};

