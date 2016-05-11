// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenField.h"
#include "Core/Log/Log.h"
#include "Core/Siren/Schema/SirenTextParser.h"
#include "Core/Siren/Schema/SirenAssembly.h"
#include "Core/Siren/Schema/SirenMachine.h"
#include "Core/Siren/Schema/Type/SirenCustomClass.h"
#include "Core/Siren/Schema/Type/SirenCustomEnum.h"
#include "Core/IO/Stream/IStream.h"


MEDUSA_BEGIN;

SirenField::SirenField()
{

}

SirenField::~SirenField(void)
{
}

ushort SirenField::Id() const
{
	if (mParentType->BaseType() != nullptr)
	{
		return mIndex + (ushort)mParentType->BaseType()->GetFieldCountRecursively();
	}
	return mIndex;
}

bool SirenField::Parse(SirenAssembly& assembly, SirenCustomClass* parentClass, StringRef token, StringRef& refProto)
{
	mTypeName = token;
	if (token == SirenMachine::Instance().List().Name())
	{
		mType = (ISirenType*)&SirenMachine::Instance().List();
		//list<type>
		RETURN_FALSE_IF_FALSE(SirenTextParser::ReadExpectedChar(refProto, '<'));
		mValueTypeName = SirenTextParser::ReadTypeName(refProto);
		if (mValueTypeName.IsEmpty())
		{
			Log::Error("Cannot parse field");
			return false;
		}

		RETURN_FALSE_IF_FALSE(SirenTextParser::ReadExpectedChar(refProto, '>'));
	}
	else if (token == SirenMachine::Instance().Dictionary().Name())
	{
		mType = (ISirenType*)&SirenMachine::Instance().Dictionary();

		//dictionary<key,value>
		RETURN_FALSE_IF_FALSE(SirenTextParser::ReadExpectedChar(refProto, '<'));
		mKeyTypeName = SirenTextParser::ReadTypeName(refProto);
		if (mKeyTypeName.IsEmpty())
		{
			Log::Error("Cannot parse field");
			return false;
		}

		RETURN_FALSE_IF_FALSE(SirenTextParser::ReadExpectedChar(refProto, ','));

		mValueTypeName = SirenTextParser::ReadTypeName(refProto);
		if (mValueTypeName.IsEmpty())
		{
			Log::Error("Cannot parse field");
			return false;
		}

		RETURN_FALSE_IF_FALSE(SirenTextParser::ReadExpectedChar(refProto, '>'));
	}
	else
	{
		//x.y.z  have been read into name

	}

	mName = SirenTextParser::ReadToken(refProto);
	if (mName.IsEmpty())
	{
		Log::Error("Cannot parse field");
		return false;
	}

	char c = SirenTextParser::ReadNextPrintChar(refProto);
	if (c == '=')
	{
		//has default value
		intp nextIndex = refProto.IndexOfAny("[;");	//has attribute next
		if (nextIndex < 0)
		{
			Log::Error("Cannot parse field");
			return false;
		}

		mDefaultValueString = refProto.SubString(0, nextIndex);
		mDefaultValueString.TrimAll();



		c = refProto[nextIndex];
		refProto = refProto.SubString(nextIndex + 1);
	}

	if (c == '[')
	{
		//has attribute
		StringRef attributeStr = SirenTextParser::ReadAttribute(refProto);
		if (attributeStr.IsEmpty())
		{
			Log::Error("Cannot get attribute.");
			return false;
		}

		if (!SetAttribute(attributeStr))
		{
			Log::FormatError("Invalid property attribute:{}", attributeStr);
			return false;
		}

		c = SirenTextParser::ReadNextPrintChar(refProto);
	}

	if (c == ';')
	{
		return true;
	}

	Log::FormatError("Invalid property end:{} of {}", c,mName);
	return false;
}


bool SirenField::SetAttribute(const StringRef& val)
{
	return mAttribute.Load(val);
}

bool SirenField::IsCompleted() const
{
	RETURN_FALSE_IF(!mTypeName.IsEmpty() && mType == nullptr);
	RETURN_FALSE_IF(!mKeyTypeName.IsEmpty() && mKeyType == nullptr);
	RETURN_FALSE_IF(!mValueTypeName.IsEmpty() && mKeyType == nullptr);
	return true;
}

bool SirenField::Link(SirenAssembly& assembly)
{
	if (!mTypeName.IsEmpty() && mType == nullptr)
	{
		mType = OnFindType(assembly, mParentType, mTypeName);
		if (mType == nullptr)
		{
			Log::FormatError("Cannot find field declare type:{}", mTypeName);
			return false;
		}
	}

	if (!mKeyTypeName.IsEmpty() && mKeyType == nullptr)
	{
		mKeyType = OnFindType(assembly, mParentType, mKeyTypeName);
		if (mKeyType == nullptr)
		{
			Log::FormatError("Cannot find key type:{}", mKeyTypeName);
			return false;
		}
	}

	if (!mValueTypeName.IsEmpty() && mValueType == nullptr)
	{
		mValueType = OnFindType(assembly, mParentType, mValueTypeName);
		if (mValueType == nullptr)
		{
			Log::FormatError("Cannot find value type:{}", mValueTypeName);
			return false;
		}
	}


	if (mDefaultValueString.BeginWith('"') && mDefaultValueString.EndWith('"'))
	{
		//is a string
		StringRef val = mDefaultValueString.SubString(1, mDefaultValueString.Length() - 2);
		mDefaultValue.Set(val);
	}
	else
	{
		intp index = mDefaultValueString.IndexOf("::");
		if (index > 0)
		{
			HeapString typeName = mDefaultValueString.SubString(0, index);
			HeapString fieldName = mDefaultValueString.SubString(index + 2);
			auto type = OnFindType(assembly, mParentType, typeName);
			if (type == nullptr)
			{
				Log::FormatError("Cannot find default value declare type:{}", typeName);
				return false;
			}

			if (type->Id() != SirenTypeId::Enum)
			{
				Log::FormatError("Default value declare type:{} is not a enum", typeName);
				return false;
			}
			SirenCustomEnum* enumType = (SirenCustomEnum*)type;
			if (!enumType->HasField(fieldName))
			{
				Log::FormatError("Cannot find field£º{} in type:{}", fieldName, typeName);
				return false;
			}

			mDefaultValueString = StringParser::ToString(enumType->GetValue(fieldName));
			mDefaultValue.SetEnum(enumType->GetValue(fieldName));
		}
		else
		{
			if (!mDefaultValueString.IsEmpty())
			{
				mDefaultValue.SetTypeAndValue(mType->Id(), mDefaultValueString);
			}
		}
	}


	return true;
}

bool SirenField::LoadFrom(IStream& stream)
{
	RETURN_FALSE_IF_FALSE(mAttribute.LoadFrom(stream));
	mName = stream.ReadString();
	mDefaultValueString = stream.ReadString();
	mTypeName = stream.ReadString();
	mKeyTypeName = stream.ReadString();
	mValueTypeName = stream.ReadString();
	return true;
}

bool SirenField::SaveTo(IStream& stream) const
{
	RETURN_FALSE_IF_FALSE(mAttribute.SaveTo(stream));
	stream.WriteString(mName);
	stream.WriteString(mDefaultValueString);

	//type
	stream.WriteString(mTypeName);
	stream.WriteString(mKeyTypeName);
	stream.WriteString(mValueTypeName);
	return true;
}

ISirenType* SirenField::OnFindType(SirenAssembly& assembly, SirenCustomClass* parentClass, const StringRef& name)const
{
	auto* type = parentClass->FindType(name);
	RETURN_SELF_IF_NOT_NULL(type);
	return assembly.FindTypeWithReference(name);
}

MEDUSA_END;