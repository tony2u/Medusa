// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "ISirenGenerator.h"



class SirenSharpGenerator :public ISirenGenerator
{

public:
	using ISirenGenerator::ISirenGenerator;
	virtual ~SirenSharpGenerator(void) = default;
	virtual void SetTemplateName(StringRef val);

protected:
	virtual bool GenerateType(BaseSirenCustomType& type)const override;

	HeapString OnEnumHeader(SirenCustomEnum& sirenClass)const;

	HeapString OnClassHeader(SirenCustomClass& sirenClass)const;
	HeapString OnClassFields(SirenCustomClass& sirenClass)const;
private:
	static SirenFieldMethodType GetMethodType(const SirenField& field);
	static SirenFieldValueType GetValueType(const SirenField& field);
	static HeapString GetDefaultValueString(const SirenField& field);


	static HeapString GetTypeName(ISirenType* type);
};

