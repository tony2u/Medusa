// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenCustomClass.h"
#include "Core/Log/Log.h"
#include "Core/Siren/Schema/SirenTextParser.h"
#include "Core/Siren/Schema/SirenAssembly.h"
#include "SirenCustomEnum.h"
#include "Core/IO/Stream/IStream.h"

MEDUSA_BEGIN;

SirenCustomClass::SirenCustomClass()
{

}

SirenCustomClass::~SirenCustomClass(void)
{
	SAFE_DELETE_DICTIONARY_VALUE(mTypes);
	SAFE_DELETE_DICTIONARY_VALUE(mFields);

}

bool SirenCustomClass::SetAttribute(const StringRef& val)
{
	return mAttribute.Load(val);
}

BaseSirenCustomType* SirenCustomClass::FindType(const StringRef& name) const
{
	if (name.Contains('.'))
	{
		List<StringRef> outPaths;
		StringParser::Split(name, ".", outPaths, false);
		if (outPaths.Count() <= 1)
		{
			return nullptr;
		}

		auto* rootType = mTypes.GetOptional(outPaths[0], nullptr);
		if (rootType == nullptr || !rootType->IsCustomClass())
		{
			return nullptr;
		}

		SirenCustomClass* parentType = (SirenCustomClass*)rootType;
		for (size_t i = 1; i < outPaths.Count(); ++i)
		{
			auto* childType = parentType->FindType(outPaths[i]);
			if (childType == nullptr || !childType->IsCustomClass())
			{
				return nullptr;
			}
			parentType = (SirenCustomClass*)childType;
		}

		return parentType;
	}
	else
	{
		return mTypes.GetOptional(name, nullptr);
	}
}

bool SirenCustomClass::HasType(const StringRef& name) const
{
	return mTypes.ContainsKey(name);
}

size_t SirenCustomClass::GetFieldCountRecursively() const
{
	if (mBaseType != nullptr)
	{
		return mBaseType->GetFieldCountRecursively() + mFields.Count();
	}
	return mFields.Count();
}

bool SirenCustomClass::Link(SirenAssembly& assembly)
{
	if (!mBaseTypeName.IsEmpty() && mBaseType == nullptr)
	{
		ISirenType* baseType = assembly.FindTypeWithReference(mBaseTypeName);
		if (baseType == nullptr)
		{
			Log::FormatError("Cannot find base class:{}", mBaseTypeName);
			return false;
		}
		if (!baseType->IsCustomClass())
		{
			Log::FormatError("{} cannot be a base class", mBaseTypeName);
			return false;
		}
		mBaseType = (SirenCustomClass*)baseType;
	}

	for (auto& typePair : mTypes)
	{
		auto* type = typePair.Value;
		RETURN_FALSE_IF_FALSE(type->Link(assembly));
	}

	for (auto& fieldPair : mFields)
	{
		auto* field = fieldPair.Value;
		RETURN_FALSE_IF_FALSE(field->Link(assembly));

		TryAddIncludeType(field->Type());
		TryAddIncludeType(field->KeyType());
		TryAddIncludeType(field->ValueType());
	}

	return true;
}

bool SirenCustomClass::IsCompleted() const
{
	RETURN_FALSE_IF(!mBaseTypeName.IsEmpty() && mBaseType == nullptr);

	for (auto& typePair : mTypes)
	{
		auto* type = typePair.Value;
		RETURN_FALSE_IF_FALSE(type->IsCompleted());
	}

	for (auto& fieldPair : mFields)
	{
		auto* field = fieldPair.Value;
		RETURN_FALSE_IF_FALSE(field->IsCompleted());
	}

	return true;
}

bool SirenCustomClass::Merge(const BaseSirenCustomType& other)
{
	if (!other.IsCustomClass())
	{
		return false;
	}

	SirenCustomClass& otherCustom = (SirenCustomClass&)other;
	for (auto& typePair : otherCustom.mTypes)
	{
		auto* curType = FindType(typePair.Key);
		if (curType == nullptr)
		{
			AddType((BaseSirenCustomType*)typePair.Value->Clone());
		}
		else
		{
			auto* otherType = typePair.Value;
			if (!curType->Merge(*otherType))
			{
				Log::FormatError("Cannot merge class:{}", typePair.Key);
				return false;
			}
		}
	}

	return true;
}

SirenCustomClass* SirenCustomClass::Clone() const
{
	SirenCustomClass* clone = new SirenCustomClass();
	clone->mName = mName;
	clone->mFullName = mFullName;
	clone->mBaseTypeName = mBaseTypeName;

	for (auto filePair:mFields)
	{
		clone->mFields.Add(filePair.Key, filePair.Value->Clone());
	}

	for (auto typePair : mTypes)
	{
		clone->mTypes.Add(typePair.Key, (BaseSirenCustomType*)typePair.Value->Clone());
	}

	return clone;
}

bool SirenCustomClass::LoadFrom(IStream& stream)
{
	RETURN_FALSE_IF_FALSE(BaseSirenCustomType::LoadFrom(stream));
	RETURN_FALSE_IF_FALSE(mAttribute.LoadFrom(stream));

	mBaseTypeName = stream.ReadString();

	//types
	uint typeCount = stream.Read<uint32>();
	FOR_EACH_SIZE(i, typeCount)
	{
		char isClass = (char)stream.ReadChar();
		if (isClass == 1)
		{
			std::unique_ptr<SirenCustomClass> type(new SirenCustomClass());
			RETURN_FALSE_IF_FALSE(type->LoadFrom(stream));
			type->SetParentType(this);
			mTypes.Add(type->Name(), type.get());
			type.release();
		}
		else
		{
			std::unique_ptr<SirenCustomEnum> type(new SirenCustomEnum());
			RETURN_FALSE_IF_FALSE(type->LoadFrom(stream));
			type->SetParentType(this);
			mTypes.Add(type->Name(), type.get());
			type.release();
		}
	}

	//fields
	uint fieldCount = stream.Read<uint32>();
	FOR_EACH_SIZE(i, fieldCount)
	{
		std::unique_ptr<SirenField> field(new SirenField());
		RETURN_FALSE_IF_FALSE(field->LoadFrom(stream));
		field->SetParentType(this);
		mFields.Add(field->Name(), field.get());
		field->SetIndex((ushort)mFields.Count()-1);
		field.release();
	}

	return true;
}


bool SirenCustomClass::SaveTo(IStream& stream) const
{
	RETURN_FALSE_IF_FALSE(BaseSirenCustomType::SaveTo(stream));
	RETURN_FALSE_IF_FALSE(mAttribute.SaveTo(stream));

	stream.WriteString(mBaseTypeName);

	//types
	uint typeCount = (uint)mTypes.Count();
	stream.Write(typeCount);
	for (auto& typePair : mTypes)
	{
		auto* type = typePair.Value;
		char isClass = type->IsCustomClass() ? 1 : 0;
		stream.WriteChar(isClass);
		type->SaveTo(stream);
	}

	//fields
	uint fieldCount = (uint)mFields.Count();
	stream.Write(fieldCount);
	for (auto& fieldPair : mFields)
	{
		auto* field = fieldPair.Value;
		field->SaveTo(stream);
	}

	return true;
}

bool SirenCustomClass::AddField(SirenField* val)
{
	if (mFields.TryAdd(val->Name(), val))
	{
		val->SetIndex((ushort)mFields.Count()-1);
		val->SetParentType(this);
		return true;
	}

	Log::FormatError("Duplicate property name:{}", val->Name());
	return false;
}

bool SirenCustomClass::AddType(BaseSirenCustomType* val)
{
	if (mTypes.TryAdd(val->Name(), val))
	{
		val->SetParentType(this);
		return true;
	}

	Log::FormatError("Duplicate child class name:{}", val->Name());
	return false;
}


bool SirenCustomClass::TryAddIncludeType(ISirenType* val)
{
	RETURN_FALSE_IF_NULL(val);
	if (val->IsBuildIn())
	{
		return false;
	}

	BaseSirenCustomType* customType = (BaseSirenCustomType*)val;
	mIncludeTypes.TryAdd(customType);

	return true;
}

bool SirenCustomClass::AddAttribute(StringRef name, StringRef val)
{
	return mAttribute.AddAttribute(name, val);
}

bool SirenCustomClass::Parse(SirenAssembly& assembly, StringRef& refProto)
{
	mName = SirenTextParser::ReadToken(refProto);
	if (mName.IsEmpty())
	{
		Log::Error("Cannot get class name");
		return false;
	}

	char c = SirenTextParser::ReadNextPrintChar(refProto);
	if (c == '\0')
	{
		Log::Error("Invalid class declare");
		return false;
	}

	if (c == ':')
	{
		//may has base class
		mBaseTypeName = SirenTextParser::ReadTypeName(refProto);
		if (mBaseTypeName.IsEmpty())
		{
			Log::Error("Cannot get base class.");
			return false;
		}


		c = SirenTextParser::ReadNextPrintChar(refProto);
		if (c == '\0')
		{
			Log::Error("Invalid class declare");
			return false;
		}
	}

	if (c == '[')
	{
		StringRef attributeStr = SirenTextParser::ReadAttribute(refProto);
		if (attributeStr.IsEmpty())
		{
			Log::Error("Cannot get attribute.");
			return false;
		}

		if (!SetAttribute(attributeStr))
		{
			Log::FormatError("Invalid class attribute:{}", attributeStr);
			return false;
		}

		c = SirenTextParser::ReadNextPrintChar(refProto);
		if (c == '\0')
		{
			Log::Error("Invalid class declare");
			return false;
		}

	}

	if (c == '{')
	{
		while (true)
		{
			StringRef token = SirenTextParser::ReadTypeName(refProto);
			if (token.IsEmpty())
			{
				break;
			}

			if (token == SirenTextParser::EnumKeyword)
			{
				std::unique_ptr<SirenCustomEnum> child(new SirenCustomEnum());
				if (child->Parse(assembly, refProto))
				{
					RETURN_FALSE_IF_FALSE(AddType(child.get()));
					child.release();
				}
				else
				{
					Log::Error("Failed to parse enum.");
					return false;
				}
			}
			else if (token == SirenTextParser::ClassKeyword)
			{
				std::unique_ptr<SirenCustomClass> child(new SirenCustomClass());
				if (child->Parse(assembly, refProto))
				{
					RETURN_FALSE_IF_FALSE(AddType(child.get()));
					child.release();
				}
				else
				{
					Log::Error("Failed to parse class.");
					return false;
				}
			}
			else
			{
				//properties
				std::unique_ptr<SirenField> field(new SirenField());
				if (field->Parse(assembly, this, token, refProto))
				{
					RETURN_FALSE_IF_FALSE(AddField(field.get()));
					field.release();
				}
				else
				{
					Log::Error("Failed to parse property.");
					return false;
				}
			}
		}
	}
	else
	{
		Log::Error("Invalid class declare");
		return false;
	}



	return SirenTextParser::EndType(refProto);

}

MEDUSA_END;