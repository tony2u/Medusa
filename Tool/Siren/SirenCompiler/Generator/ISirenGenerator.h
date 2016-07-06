// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
USING_MEDUSA;

#include "Core/Collection/List.h"
#include "Core/String/HeapString.h"
#include "Core/Siren/Schema/SirenAssembly.h"

enum class SirenFieldMethodType
{
	Value,
	List,
	Dictionary,
	Pointer,
	Unsupported
};


enum class SirenFieldValueType
{
	Value,
	String,
	Blob,
	List,
	Dictionary,
	Struct,
	Pointer
};

class ISirenGenerator
{
public:
	ISirenGenerator(SirenAssembly& assembly);
	virtual ~ISirenGenerator(void) = default;

	bool Run()const;

	StringRef TypeName() const { return mTypeName; }
	void SetTypeName(StringRef val) { mTypeName = val; }
	StringRef TemplateName() const { return mTemplateName; }
	virtual void SetTemplateName(StringRef val);
	StringRef OutputPath() const { return mOutputPath; }
	void SetOutputPath(StringRef val) { mOutputPath = val; }
protected:
	virtual bool GenerateType(BaseSirenCustomType& type)const=0;

	static void UpdateFile(StringRef path, StringRef content);
	static void ReplaceBeginEnd(HeapString& text, StringRef begin, StringRef end, StringRef content);
protected:
	SirenAssembly& mAssembly;
	HeapString mTypeName;
	HeapString mTemplateName;
	HeapString mOutputPath;

	HeapString mHeaderTemplate;
	HeapString mBodyTemplate;

};

