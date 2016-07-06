// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "SirenSharpGenerator.h"
#include "Core/Siren/Schema/Type/SirenCustomClass.h"
#include "Core/Siren/Schema/Type/SirenCustomEnum.h"

#include "Core/IO/Path.h"
#include "Core/IO/File.h"
#include "Core/Log/Log.h"
#include "Core/Siren/Schema/SirenMachine.h"
#include "Core/String/Format/Format.h"
#include "Core/IO/FileSystem.h"

const StringRef mHeaderMask = "<SIREN_HEADER>";

void SirenSharpGenerator::SetTemplateName(StringRef val)
{
	ISirenGenerator::SetTemplateName(val);
	//load template
	mHeaderTemplate = FileSystem::Instance().ReadAllText(mTemplateName + ".cs");
}


bool SirenSharpGenerator::GenerateType(BaseSirenCustomType& sirenClass) const
{
	if (!sirenClass.IsGenerate())
	{
		return true;
	}

	auto hName = sirenClass.Name() + ".cs";
	auto hPath = Path::Combine(mOutputPath, sirenClass.Directory(), hName);

	if (sirenClass.IsCustomEnum())
	{
		SirenCustomEnum& customEnum = (SirenCustomEnum&)sirenClass;

		HeapString header(mHeaderTemplate);

		auto headerStr = OnEnumHeader(customEnum);
		header.ReplaceFirst(mHeaderMask, headerStr);
		UpdateFile(hPath, header.ToString());
	}
	else
	{
		SirenCustomClass& customClass = (SirenCustomClass&)sirenClass;
		HeapString header(mHeaderTemplate);
		HeapString body(mBodyTemplate);

		auto headerStr = OnClassHeader(customClass);
		header.ReplaceFirst(mHeaderMask, headerStr);

		UpdateFile(hPath, header.ToString());
	}

	return true;
}

HeapString SirenSharpGenerator::OnEnumHeader(SirenCustomEnum& sirenClass)const
{
	auto typeName = sirenClass.Name();
	HeapString sb;
	auto& names = sirenClass.FieldNames();
	auto& values = sirenClass.FieldValues();
	int count = (int)names.Count();

	switch (sirenClass.Attribute().Mode())
	{
	case SirenEnumGenerateMode::CustomFlag:
		sb.AppendLine("\t[SirenEnum]");
		sb.AppendLine("\t[Flags]");
		sb.AppendFormat("\tpublic enum {0}\n", typeName);
		sb.AppendLine("\t{");

		for (int i = 0; i < count; i++)
		{
			auto name = names[i];
			auto val = values[i];
			sb.AppendFormat("\t\t{0} = {1},\n", name, val);
		}

		sb.AppendLine("\t}");
		break;
	case SirenEnumGenerateMode::CustomEnum:
	default:
	{
		sb.AppendLine("\t[SirenEnum]");
		sb.AppendFormat("\tpublic enum {0}\n", typeName);
		sb.AppendLine("\t{");

		for (int i = 0; i < count; i++)
		{
			auto name = names[i];
			auto val = values[i];
			sb.AppendFormat("\t{0} = {1},\n", name, val);
		}

		sb.AppendLine("\t}");
		break;
	}
	}

	return sb.ToString();

}

HeapString SirenSharpGenerator::OnClassHeader(SirenCustomClass& sirenClass)const
{
	auto typeName = sirenClass.Name();
	HeapString sb;
	HeapString attrStr = sirenClass.Attribute().ToString();
	if (attrStr.IsEmpty())
	{
		sb.AppendFormat("\t[SirenClass]\n");
	}
	else
	{
		sb.AppendFormat("\t[SirenClass(\"{0}\")]\n", attrStr);
	}


	if (sirenClass.BaseType() == nullptr)
	{
		if (sirenClass.Attribute().IsStruct())
		{
			sb.AppendFormat("\tpublic struct {0}\n", typeName);
		}
		else
		{
			sb.AppendFormat("\tpublic class {0}\n", typeName);
		}

	}
	else
	{
		if (sirenClass.Attribute().IsStruct())
		{
			sb.AppendFormat("\tpublic struct {0}:{1}\n", typeName, sirenClass.BaseType()->Name());
		}
		else
		{
			sb.AppendFormat("\tpublic class {0}:{1}\n", typeName, sirenClass.BaseType()->Name());
		}
	}
	sb.AppendLine("\t{");

	//add fields
	sb.Append(OnClassFields(sirenClass));

	sb.AppendLine("\t}");
	sb.AppendLine();

	return sb.ToString();

}

HeapString SirenSharpGenerator::OnClassFields(SirenCustomClass& sirenClass)const
{
	HeapString sb;
	//sb.AppendLine();

	//add fields
	for (auto sirenFieldPair : sirenClass.Fields())
	{
		SirenField* field = sirenFieldPair.Value;
		
		HeapString attrStr = field->Attribute().ToString();
		auto modifier = field->Attribute().Modifier();
		if (attrStr.IsEmpty())
		{
			if (modifier.IsEmpty()||modifier=="Required")
			{
				sb.AppendFormat("\t\t[SirenField]\n");
			}
			else
			{
				sb.AppendFormat("\t\t[SirenField(SirenFieldGenerateMode.{})]\n",modifier);
			}
		}
		else
		{
			if (modifier.IsEmpty() || modifier == "Required")
			{
				sb.AppendFormat("\t\t[SirenField(\"{}\")]\n", attrStr);
			}
			else
			{
				sb.AppendFormat("\t\t[SirenField(SirenFieldGenerateMode.{},\"{}\")]\n", modifier, attrStr);
			}
		}


		auto methodType = GetMethodType(*field);

		switch (methodType)
		{
		case SirenFieldMethodType::Value:
			sb.AppendFormat("\t\tpublic {0} {1} {{ get; set; }}\n", GetTypeName(field->Type()), field->Name());
			break;
		case SirenFieldMethodType::Pointer:
			sb.AppendFormat("\t\tpublic {0}* {1} {{ get; set; }}\n", GetTypeName(field->Type()), field->Name());
			break;
		case SirenFieldMethodType::List:
		{
			auto itemType = field->ValueType();
			sb.AppendFormat("\t\tpublic List<{0}> {1} {{ get; set; }}\n", GetTypeName(itemType), field->Name());

		}
		break;
		case SirenFieldMethodType::Dictionary:
		{

			auto keyType = field->KeyType();
			auto valueType = field->ValueType();
			sb.AppendFormat("\t\tpublic Dictionary<{0}, {1}> {2} {{ get; set; }}\n", GetTypeName(keyType), GetTypeName(valueType), field->Name());
		}
		break;
		}

	}

	return sb.ToString();

}

SirenFieldMethodType SirenSharpGenerator::GetMethodType(const SirenField& field)
{
	auto* type = field.Type();
	if (type == &SirenMachine::Instance().List())
	{
		return SirenFieldMethodType::List;
	}
	else if (type == &SirenMachine::Instance().Dictionary())
	{
		return SirenFieldMethodType::Dictionary;
	}
	else if (type->IsBuildIn() || type->IsCustomEnum())
	{
		return SirenFieldMethodType::Value;
	}
	else
	{
		//custom class
		if (field.IsRequired())
		{
			return SirenFieldMethodType::Value;
		}
		else
		{
			return SirenFieldMethodType::Pointer;
		}
	}


}

SirenFieldValueType SirenSharpGenerator::GetValueType(const SirenField& field)
{
	auto* type = field.Type();
	if (type == &SirenMachine::Instance().List())
	{
		return SirenFieldValueType::List;
	}
	else if (type == &SirenMachine::Instance().Dictionary())
	{
		return SirenFieldValueType::Dictionary;
	}
	else if (type->IsBuildIn())
	{
		if (type == &SirenMachine::Instance().String())
		{
			return SirenFieldValueType::String;
		}
		if (type == &SirenMachine::Instance().Blob())
		{
			return SirenFieldValueType::Blob;
		}
		return SirenFieldValueType::Value;
	}
	else
	{
		if (type->IsCustomEnum())
		{
			return SirenFieldValueType::Value;
		}

		//custom class
		if (field.IsRequired())
		{
			return SirenFieldValueType::Struct;
		}
		else
		{
			return SirenFieldValueType::Pointer;
		}
	}

}

HeapString SirenSharpGenerator::GetDefaultValueString(const SirenField& field)
{
	auto* type = field.Type();
	StringRef defaultStr = field.DefaultValueString();

	if (type->IsCustomClass())
	{
		return StringRef::Empty;
	}

	if (type->IsCustomEnum())
	{
		if (!field.DefaultValue().IsNull())
		{
			return String::Format("({}){}", type->Name(), field.DefaultValue().GetEnum());
		}
		else
		{
			return String::Format("({})0", type->Name());
		}
	}

	if (!defaultStr.IsEmpty())
	{
		return defaultStr;
	}
	else
	{
		if (type == &SirenMachine::Instance().String())
		{
			return StringRef::Empty;
		}

		if (type == &SirenMachine::Instance().Blob())
		{
			return StringRef::Empty;
		}

		if (type == &SirenMachine::Instance().Bool())
		{
			return HeapString("false");
		}
		if (type == &SirenMachine::Instance().Float())
		{
			return HeapString("0.f");
		}
		if (type == &SirenMachine::Instance().Double())
		{
			return HeapString("0.0");
		}

		return HeapString("0");
	}

}

HeapString SirenSharpGenerator::GetTypeName(ISirenType* type)
{
	HeapString outStr;
	if (type == &SirenMachine::Instance().String())
	{
		return HeapString("string");
	}

	if (type->IsBuildIn())
	{
		return type->Name();
	}


	return type->Name();
}
