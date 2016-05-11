// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenTextParser.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Log/Log.h"
#include "Core/Siren/Schema/SirenMachine.h"
#include "Core/Siren/Schema/Type/SirenCustomClass.h"
#include "Core/Siren/Schema/Type/SirenCustomEnum.h"
#include "Core/IO/FileSystem.h"
#include "Core/Siren/Schema/SirenAssembly.h"
#include "Core/IO/File.h"
#include "Core/Siren/Schema/Function/SirenAttributeFunction.h"




MEDUSA_BEGIN;

//className:baseClass[classAttribute] { } propertyName=[defaultValue][propertyAttribute];
//if has no className, then it's a anonymous type
//if has no propertyName,then it only declare a type
//if has no {}, then it's a property definition
//[classAttribute] [propertyAttribute] is optional


//func(arg1,arg2...)

SirenTextParser::SirenTextParser(SirenAssembly& assembly)
	:mAssembly(assembly)
{

}

SirenTextParser::~SirenTextParser(void)
{
}

void SirenTextParser::Preprocess(HeapString& text)
{
	//trim
	//remove all comment
	intp beginIndex = text.Length() - 1;
	while (true)
	{
		beginIndex = text.LastIndexOf("//", 0, beginIndex);
		if (beginIndex >= 0)
		{
			intp endIndex = text.IndexOfAny(StdString::ConstValues<char>::NewLineChars, beginIndex + 2);
			if (endIndex >= 0)
			{
				text.RemoveAt(beginIndex, endIndex - beginIndex);
			}
		}
		else
		{
			return;
		}
	}
}



bool SirenTextParser::EndBlock(StringRef& refProto)
{
	refProto = refProto.TrimBegin();
	intp index = refProto.IndexOf(';');
	if (index < 0)
	{
		Log::Error("Cannot find ;");
		return false;
	}

	refProto = refProto.SubString(index + 1);
	return true;
}



bool SirenTextParser::EndType(StringRef& refProto)
{
	refProto = refProto.TrimBegin();
	intp index = refProto.IndexOf('}');
	if (index < 0)
	{
		Log::Error("Cannot find }");
		return false;
	}

	refProto = refProto.SubString(index + 1);
	return EndBlock(refProto);;
}

StringRef SirenTextParser::ReadToken(StringRef& refProto)
{
	refProto = refProto.TrimBegin();
	if (refProto.IsEmpty())
	{
		return StringRef::Empty;
	}
	if (StdString::IsDigit(refProto[0]))
	{
		Log::FormatError("Token cannot begin with number:{}", refProto[0]);
		return StringRef::Empty;
	}

	size_t tokenLength = 0;
	size_t length = refProto.Length();
	for (size_t i = 0; i < length - 1; ++i)
	{
		int c = refProto[i];
		if (StdString::IsToken(c))
		{
			++tokenLength;
		}
		else
		{
			break;
		}
	}
	StringRef token = refProto.SubString(0, tokenLength);
	refProto = refProto.SubString(tokenLength);
	return token;

}


StringRef SirenTextParser::ReadTypeName(StringRef& refProto)
{
	refProto = refProto.TrimBegin();
	if (refProto.IsEmpty())
	{
		return StringRef::Empty;
	}
	if (StdString::IsDigit(refProto[0]))
	{
		Log::FormatError("Token cannot begin with number:{}", refProto[0]);
		return StringRef::Empty;
	}

	size_t tokenLength = 0;
	size_t length = refProto.Length();
	for (size_t i = 0; i < length - 1; ++i)
	{
		int c = refProto[i];
		if (StdString::IsToken(c) || c == '.')
		{
			++tokenLength;
		}
		else
		{
			break;
		}
	}
	StringRef token = refProto.SubString(0, tokenLength);
	refProto = refProto.SubString(tokenLength);
	return token;
}

StringRef SirenTextParser::ReadAttribute(StringRef& refProto)
{
	refProto = refProto.TrimBegin();
	intp index = refProto.IndexOf(']');
	if (index < 0)
	{
		Log::Error("Cannot find ] on attribute");
		return false;
	}

	StringRef result = refProto.SubString(0, index);
	refProto = refProto.SubString(index + 1);


	return result;
}


bool SirenTextParser::ReadFunctionArguments(StringRef& refProto, List<StringRef>& outArguments)
{
	//read arguments
	intp endIndex = refProto.IndexOf(')');
	if (endIndex < 0)
	{
		Log::Error("Invalid function.Lost ')' ");
		return false;
	}
	StringRef args = refProto.SubString(1, endIndex - 1);
	bool isSuccess = StringParser::Split(args, ",", outArguments, false);
	if (!isSuccess)
	{
		Log::FormatError("Invalid function argument:{}", args);
		return false;
	}

	refProto = refProto.SubString(endIndex);
	return EndBlock(refProto);
}

char SirenTextParser::ReadNextPrintChar(StringRef& refProto)
{
	refProto = refProto.TrimBegin();
	if (refProto.IsEmpty())
	{
		return '\0';
	}

	char c = refProto[0];
	refProto = refProto.SubString(1);
	return c;
}

bool SirenTextParser::ReadExpectedChar(StringRef& refProto, char val)
{
	refProto = refProto.TrimBegin();
	if (refProto.IsEmpty() || refProto[0] != val)
	{
		return false;
	}
	refProto = refProto.SubString(1);
	return true;
}


bool SirenTextParser::ParseStream(IStream& steam)
{
	HeapString text;
	steam.ReadDataToString(text, -1);
	return Parse(text);
}

bool SirenTextParser::ParseFile(const FileIdRef& fileId)
{
	HeapString text = FileSystem::Instance().ReadAllText(fileId);

	if (text.IsEmpty())
	{
		Log::FormatError("Cannot find file:{}", fileId.Name);
		return false;
	}
	Preprocess(text);
	StringRef proto = text;
	return Parse(proto);
}

bool SirenTextParser::Parse(HeapString& text)
{
	Preprocess(text);
	StringRef proto = text;
	return Parse(proto);
}

bool SirenTextParser::Parse(StringRef& proto)
{
	while (true)
	{
		StringRef token = SirenTextParser::ReadToken(proto);
		BREAK_IF_EMPTY(token);//reach end
		if (token == EnumKeyword)
		{
			std::unique_ptr<SirenCustomEnum> type(new SirenCustomEnum());
			if (type->Parse(mAssembly, proto))
			{
				RETURN_FALSE_IF_FALSE(mAssembly.AddType(type.release()));
			}
			else
			{
				Log::Error("Failed to parse class.");
				return false;
			}
		}
		else if (token == ClassKeyword)
		{
			std::unique_ptr<SirenCustomClass> type(new SirenCustomClass());
			if (type->Parse(mAssembly, proto))
			{
				RETURN_FALSE_IF_FALSE(mAssembly.AddType(type.release()));
			}
			else
			{
				Log::Error("Failed to parse class.");
				return false;
			}
		}
		else if (token == AttributeKeyword)
		{
			std::unique_ptr<SirenAttributeFunction> func(new SirenAttributeFunction());
			if (func->Parse(mAssembly, proto))
			{
				mAssembly.AddFunction(func.release());
			}
			else
			{
				Log::Error("Failed to parse function.");
				return false;
			}
		}
		else
		{
			Log::FormatError("Invalid syntax:{}", token);
			return false;
		}
	}

	return true;
}



MEDUSA_END;