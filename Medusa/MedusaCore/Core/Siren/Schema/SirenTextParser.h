// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/Schema/Type/BaseSirenCustomType.h"

MEDUSA_BEGIN;


class SirenTextParser
{
public:
	constexpr static char* EnumKeyword{ "enum" };
	constexpr static char* ClassKeyword{ "class" };
	constexpr static char* StructKeyword{ "struct" };
	constexpr static char* IncludeKeyword{ "include" };
	constexpr static char* AttributeKeyword{ "attribute" };
public:
	SirenTextParser(SirenAssembly& assembly);
	virtual ~SirenTextParser(void);
public:
	SirenAssembly& Assembly() const { return mAssembly; }
public:
	bool ParseStream(IStream& steam);
	bool ParseFile(const FileIdRef& fileId);

	bool Parse(HeapString& text);
	bool Parse(StringRef& text);
public:
	static StringRef ReadToken(StringRef& refProto);
	static StringRef ReadTypeName(StringRef& refProto);
	static StringRef ReadAttribute(StringRef& refProto);
	static bool ReadFunctionArguments(StringRef& refProto, List<StringRef>& outArguments);

	static char ReadNextPrintChar(StringRef& refProto);
	static bool ReadExpectedChar(StringRef& refProto, char val);

	static bool EndBlock(StringRef& refProto);
	static bool EndType(StringRef& refProto);

protected:
	static void Preprocess(HeapString& text);
private:
	SirenAssembly& mAssembly;

};

MEDUSA_END;
