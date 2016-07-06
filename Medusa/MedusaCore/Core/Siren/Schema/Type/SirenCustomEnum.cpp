// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SirenCustomEnum.h"
#include "Core/Log/Log.h"
#include "Core/Siren/Schema/SirenTextParser.h"
#include "Core/Siren/Schema/SirenAssembly.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Siren/Schema/SirenMachine.h"

MEDUSA_BEGIN;

SirenCustomEnum::SirenCustomEnum()
{

}

SirenCustomEnum::~SirenCustomEnum(void)
{
}

bool SirenCustomEnum::SetAttribute(const StringRef& val)
{
	return mAttribute.Load(val);
}

bool SirenCustomEnum::AddAttribute(StringRef name, StringRef val)
{
	return mAttribute.AddAttribute(name, val);
}


bool SirenCustomEnum::HasValue(int val) const
{
	return mFieldValues.Contains(val);
}

bool SirenCustomEnum::HasField(const StringRef& name) const
{
	return mFieldNames.Contains(name);
}

int SirenCustomEnum::GetValue(const StringRef& name) const
{
	intp index = mFieldNames.IndexOf(name);
	return mFieldValues[index];
}

bool SirenCustomEnum::LoadFrom(IStream& stream)
{
	RETURN_FALSE_IF_FALSE(BaseSirenCustomType::LoadFrom(stream));
	RETURN_FALSE_IF_FALSE(mAttribute.LoadFrom(stream));
	mUnderlyType = stream.ReadString();

	uint count = stream.Read<uint32>();

	FOR_EACH_SIZE(i, count)
	{
		mFieldNames.NewAdd() = stream.ReadString();
		mFieldValues.NewAdd() = stream.Read<int32>();
	}

	return true;
}

bool SirenCustomEnum::SaveTo(IStream& stream) const
{
	RETURN_FALSE_IF_FALSE(BaseSirenCustomType::SaveTo(stream));
	RETURN_FALSE_IF_FALSE(mAttribute.SaveTo(stream));

	stream.WriteString(mUnderlyType);

	uint count = (uint32)mFieldNames.Count();
	stream.Write(count);

	FOR_EACH_SIZE(i, count)
	{
		stream.WriteString(mFieldNames[i]);
		stream.Write(mFieldValues[i]);
	}

	return true;
}

bool SirenCustomEnum::AddField(const StringRef& name, int val)
{
	if (mFieldNames.Contains(name))
	{
		Log::FormatError("Duplicate enum filed:{}", name);
		return false;
	}
	mFieldNames.Add(name);
	mFieldValues.Add(val);
	return true;
}

bool SirenCustomEnum::ValidateUnderlyType(SirenAssembly& assembly, StringRef val)
{
	ISirenType* type = assembly.FindTypeWithReference(val);
	if (type == nullptr || !type->IsBuildIn())
	{
		return false;
	}

	if (type == &SirenMachine::Instance().List() ||
		type == &SirenMachine::Instance().Dictionary() ||
		type == &SirenMachine::Instance().String() ||
		type == &SirenMachine::Instance().Blob()
		)
	{
		return false;
	}

	return true;

}


bool SirenCustomEnum::Parse(SirenAssembly& assembly, StringRef& refProto)
{
	mName = SirenTextParser::ReadToken(refProto);
	if (mName.IsEmpty())
	{
		Log::Error("Cannot get enum name");
		return false;
	}

	char c = SirenTextParser::ReadNextPrintChar(refProto);
	if (c == '\0')
	{
		Log::Error("Invalid enum declare");
		return false;
	}

	if (c == ':')
	{
		//may has base class
		mUnderlyType = SirenTextParser::ReadTypeName(refProto);
		if (mUnderlyType.IsEmpty())
		{
			Log::Error("Cannot get enum underly type.");
			return false;
		}

		//check underly type
		if (!ValidateUnderlyType(assembly, mUnderlyType))
		{
			Log::FormatError("Invalid enum:{} underly type:{}", mName, mUnderlyType);
			return false;
		}

		c = SirenTextParser::ReadNextPrintChar(refProto);
		if (c == '\0')
		{
			Log::Error("Invalid enum declare");
			return false;
		}
	}

	switch (c)
	{
	case '[':
	{
		StringRef attributeStr = SirenTextParser::ReadAttribute(refProto);
		if (attributeStr.IsEmpty())
		{
			Log::Error("Cannot get attribute.");
			return false;
		}

		if (!SetAttribute(attributeStr))
		{
			Log::FormatError("Invalid enum attribute:{}", attributeStr);
			return false;
		}

		c = SirenTextParser::ReadNextPrintChar(refProto);
		if (c == '\0')
		{
			Log::Error("Invalid enum declare");
			return false;
		}
	}
	case '{':
	{
		intp index = refProto.IndexOf('}');
		if (index < 0)
		{
			Log::Error("Cannot get match enum }.");
			return false;
		}
		StringRef fields = refProto.SubString(0, index);
		//parse fields
		List<StringRef> fieldPairs;
		if (!StringParser::Split(fields, ",", fieldPairs))
		{
			Log::Error("Cannot parse enum fields.");
			return false;
		}

		int currentValue = -1;
		List<StringRef> keyValuePair;
		for (auto& optionPair : fieldPairs)
		{
			keyValuePair.Clear();
			StringParser::Split(optionPair, "=", keyValuePair);
			if (keyValuePair.Count() == 2)
			{
				auto& valueStr = keyValuePair[1];
				valueStr = valueStr.TrimAll();
				long outValue;
				if (StringParser::TryParseInt(valueStr, outValue))
				{
					currentValue = outValue;
				}
				else
				{
					List<StringRef> outRefs;
					StringParser::Split(valueStr, "|", outRefs);

					if (outRefs.Count() > 0)
					{
						//refs
						int refValues = 0;
						for (auto& refItem : outRefs)
						{
							if (HasField(refItem))
							{
								refValues |= GetValue(refItem);
							}
							else
							{
								Log::FormatError("Cannot find {} in enum.", refItem);
								return false;
							}
						}

						currentValue = refValues;
					}
					else
					{
						Log::FormatError("Cannot convert {} to int", valueStr);
						return false;
					}

				}
				auto& keyStr = keyValuePair[0];
				keyStr = keyStr.TrimAll();
				RETURN_FALSE_IF_FALSE(AddField(keyStr, currentValue));
			}
			else if (keyValuePair.Count() == 1)
			{
				//has no custom value, so +1 from current value
				++currentValue;
				auto& keyStr = keyValuePair[0];
				keyStr = keyStr.TrimAll();
				RETURN_FALSE_IF_FALSE(AddField(keyStr, currentValue));
			}
			else
			{
				Log::FormatError("Invalid attribute str:{}", optionPair.c_str());
				return false;
			}
		}

		refProto = refProto.SubString(index + 1);
	}
	break;
	default:
		Log::Error("Invalid enum declare");
		return false;
	}


	return SirenTextParser::EndBlock(refProto);
}
MEDUSA_END;