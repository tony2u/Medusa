// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "SirenCppGenerator.h"
#include "Core/Siren/Schema/Type/SirenCustomClass.h"
#include "Core/Siren/Schema/Type/SirenCustomEnum.h"

#include "Core/IO/Path.h"
#include "Core/IO/File.h"
#include "Core/Log/Log.h"
#include "Core/Siren/Schema/SirenMachine.h"
#include "Core/String/Format/Format.h"

const StringRef mHeaderIncludeMask = "<SIREN_HEADER_INCLUDE>";
const StringRef mHeaderMask = "<SIREN_HEADER>";
const StringRef mBodyIncludeMask = "<SIREN_BODY_INCLUDE>";
const StringRef mBodyMask = "<SIREN_BODY>";

const StringRef mHeaderIncludeBegin = "//SIREN_HEADER_INCLUDE_BEGIN";
const StringRef mHeaderIncludeEnd = "//SIREN_HEADER_INCLUDE_END";

const StringRef mHeaderCopyBegin = "//SIREN_HEADER_COPY_BEGIN";
const StringRef mHeaderCopyEnd = "//SIREN_HEADER_COPY_END";

const StringRef mHeaderCompareBegin = "//SIREN_HEADER_COMPARE_BEGIN";
const StringRef mHeaderCompareEnd = "//SIREN_HEADER_COMPARE_END";

const StringRef mHeaderMethodBegin = "//SIREN_HEADER_METHOD_BEGIN";
const StringRef mHeaderMethodEnd = "//SIREN_HEADER_METHOD_END";

const StringRef mHeaderFieldBegin = "//SIREN_HEADER_FIELD_BEGIN";
const StringRef mHeaderFieldEnd = "//SIREN_HEADER_FIELD_END";


const StringRef mHeaderSchemaBegin = "//SIREN_HEADER_SCHEMA_BEGIN";
const StringRef mHeaderSchemaEnd = "//SIREN_HEADER_SCHEMA_END";


const StringRef mBodyIncludeBegin = "//SIREN_BODY_INCLUDE_BEGIN";
const StringRef mBodyIncludeEnd = "//SIREN_BODY_INCLUDE_END";

const StringRef mBodyConstructBegin = "//SIREN_BODY_CONSTRUCT_BEGIN";
const StringRef mBodyConstructEnd = "//SIREN_BODY_CONSTRUCT_END";
const StringRef mBodyDestructBegin = "//SIREN_BODY_DESTRUCT_BEGIN";
const StringRef mBodyDestructEnd = "//SIREN_BODY_DESTRUCT_END";

const StringRef mBodyMetadataBegin = "//SIREN_BODY_METADATA_BEGIN";
const StringRef mBodyMetadataEnd = "//SIREN_BODY_METADATA_END";

bool SirenCppGenerator::GenerateType(BaseSirenCustomType& sirenClass) const
{
	if (!sirenClass.IsGenerate())
	{
		return true;
	}

	auto hName = sirenClass.Name() + ".h";
	auto cppName = sirenClass.Name() + ".cpp";

	auto hPath = Path::Combine(mOutputPath, sirenClass.Directory(),hName);
	auto cppPath = Path::Combine(mOutputPath, sirenClass.Directory(),cppName);

	if (sirenClass.IsCustomEnum())
	{
		SirenCustomEnum& customEnum = (SirenCustomEnum&)sirenClass;

		HeapString header(mHeaderTemplate);

		auto headerStr = OnEnumHeader(customEnum);
		header.ReplaceFirst(mHeaderIncludeMask, StringRef::Empty);
		header.ReplaceFirst(mHeaderMask, headerStr);
		UpdateFile(hPath, header.ToString());
	}
	else
	{
		SirenCustomClass& customClass = (SirenCustomClass&)sirenClass;
		/*	if (customClass.Types().Count() > 0)
			{
				Log::FormatError("Not support generate class that has sub class.{}", customClass.Name());
				return false;
			}*/

		if (!File::Exists(hPath) || !File::Exists(cppPath) || customClass.Attribute().Mode() == SirenClassGenerateMode::Generate)
		{
			HeapString header(mHeaderTemplate);
			HeapString body(mBodyTemplate);

			auto headerInclude = OnClassIncludeWrapper(customClass);
			auto headerStr = OnClassHeader(customClass);
			header.ReplaceFirst(mHeaderIncludeMask, headerInclude);
			header.ReplaceFirst(mHeaderMask, headerStr);

			auto bodyInclude = GenerateAllBodyInclude(customClass);
			auto bodyStr = GenerateAllBody(customClass);
			body.ReplaceFirst(mBodyIncludeMask, bodyInclude);
			body.ReplaceFirst(mBodyMask, bodyStr);


			UpdateFile(hPath, header.ToString());
			UpdateFile(cppPath, body.ToString());
		}
		else
		{
			HeapString header = File::ReadAllText(hPath);
			HeapString body = File::ReadAllText(cppPath);

			auto headerInclude = OnClassInclude(customClass);
			headerInclude.Push("\n");
			ReplaceBeginEnd(header, mHeaderIncludeBegin, mHeaderIncludeEnd, headerInclude);

			if (!customClass.Attribute().Has(SirenClassGenerateMode::SuppressCompare))
			{
				auto hederCompare = OnClassCompare(customClass);
				hederCompare.Push("\n");
				ReplaceBeginEnd(header, mHeaderCompareBegin, mHeaderCompareEnd, hederCompare);
			}

			if (!customClass.Attribute().Has(SirenClassGenerateMode::SuppressCopy))
			{
				auto hederCopy = OnClassCopy(customClass);
				hederCopy.Push("\n");
				ReplaceBeginEnd(header, mHeaderCopyBegin, mHeaderCopyEnd, hederCopy);
			}


			auto hederMethod = OnClassMethods(customClass);
			hederMethod.Push("\n");
			ReplaceBeginEnd(header, mHeaderMethodBegin, mHeaderMethodEnd, hederMethod);

			auto hederField = OnClassFields(customClass);
			hederField.Push("\n");
			ReplaceBeginEnd(header, mHeaderFieldBegin, mHeaderFieldEnd, hederField);

			auto hederSchema = OnClassSchema(customClass);
			hederSchema.Push("\n");
			ReplaceBeginEnd(header, mHeaderSchemaBegin, mHeaderSchemaEnd, hederSchema);


			auto bodyInclude = GenerateBodyInclude(customClass);
			bodyInclude.Push("\n");
			ReplaceBeginEnd(body, mBodyIncludeBegin, mBodyIncludeEnd, bodyInclude);

			auto bodyConstruct = GenerateBodyConstruct(customClass);
			bodyConstruct.Push("\n");
			ReplaceBeginEnd(body, mBodyConstructBegin, mBodyConstructEnd, bodyConstruct);

			auto bodyDestruct = GenerateBodyDestruct(customClass);
			bodyDestruct.Push("\n");
			ReplaceBeginEnd(body, mBodyDestructBegin, mBodyDestructEnd, bodyDestruct);

			auto bodySchema = GenerateBodyMetadata(customClass);
			bodySchema.Push("\n");
			ReplaceBeginEnd(body, mBodyMetadataBegin, mBodyMetadataEnd, bodySchema);


			UpdateFile(hPath, header);
			UpdateFile(cppPath, body);
		}
	}

	return true;
}

HeapString SirenCppGenerator::OnEnumHeader(SirenCustomEnum& sirenClass)const
{
	auto typeName = sirenClass.Name();
	HeapString sb;
	auto& names = sirenClass.FieldNames();
	auto& values = sirenClass.FieldValues();
	int count = names.Count();

	switch (sirenClass.Attribute().Mode())
	{
	case SirenEnumGenerateMode::CustomEnum:
		sb.AppendFormat("STRONG_ENUM_CUSTOM_{0}({1}", count, typeName);
		for (int i = 0; i < count; i++)
		{
			auto name = names[i];
			auto val = values[i];
			sb.AppendFormat(",{0},{1}", name, val);
		}
		sb.AppendLine(");");


		break;
	case SirenEnumGenerateMode::CustomFlag:
		sb.AppendFormat("STRONG_FLAGS_CUSTOM_{0}({1}", count, typeName);
		for (int i = 0; i < count; i++)
		{
			auto name = names[i];
			auto val = values[i];
			sb.AppendFormat(",{0},{1}", name, val);
		}
		sb.AppendLine(");");
		break;
	default:
	{
		StringRef underlyType = sirenClass.UnderlyType();
		if (underlyType.IsEmpty())
		{
			sb.AppendFormat("enum class {0}\n", typeName);
		}
		else
		{
			sb.AppendFormat("enum class {}:{}\n", typeName, underlyType);
		}
		sb.AppendLine("{");

		for (int i = 0; i < count; i++)
		{
			auto name = names[i];
			auto val = values[i];
			sb.AppendFormat("\t{0} = {1},\n", name, val);
		}

		sb.AppendLine("};");

		break;
	}
	}


	return sb.ToString();

}

HeapString SirenCppGenerator::OnClassIncludeWrapper(SirenCustomClass& sirenClass)const
{
	HeapString sb;
	sb.AppendLine();
	sb.AppendLine(mHeaderIncludeBegin);
	sb.Append(OnClassInclude(sirenClass));
	sb.AppendLine(mHeaderIncludeEnd);

	return sb;
}


HeapString SirenCppGenerator::OnClassInclude(SirenCustomClass& sirenClass)const
{
	HeapString sb;
	//sb.AppendLine();
	auto* baseType= sirenClass.BaseType();
	if (baseType!=nullptr)
	{
		StringRef dir = baseType->Directory();
		if (dir.IsEmpty())
		{
			sb.AppendFormat("#include \"{0}.h\"\n", baseType->Name());
		}
		else if(Path::IsDirectory(dir))
		{
			sb.AppendFormat("#include \"{0}/{}.h\"\n", dir, baseType->Name());
		}
		else
		{
			sb.AppendFormat("#include \"{}\"\n", dir);
		}
	}

	for (auto* includeType : sirenClass.IncludeTypes())
	{
		StringRef dir = includeType->Directory();
		if (dir.IsEmpty())
		{
			sb.AppendFormat("#include \"{0}.h\"\n", includeType->Name());
		}
		else if (Path::IsDirectory(dir))
		{
			sb.AppendFormat("#include \"{0}/{}.h\"\n", dir, includeType->Name());
		}
		else
		{
			sb.AppendFormat("#include \"{}\"\n", dir);
		}
	}

	if (sirenClass.Attribute().Has(SirenClassGenerateMode::SirenConfig))
	{
		sb.AppendFormat("#include \"Core/Siren/ISirenConfig.h\"\n");
	}
	return sb.ToString();
}

HeapString SirenCppGenerator::OnClassHeader(SirenCustomClass& sirenClass)const
{
	auto typeName = sirenClass.Name();
	HeapString sb;
	if (!sirenClass.Attribute().IsEmbeded())
	{
		if (sirenClass.BaseType() == nullptr)
		{
			if (sirenClass.Attribute().Has(SirenClassGenerateMode::SirenConfig))
			{
				sb.AppendFormat("class {0} :  ISirenConfig<{1}>\n", typeName, typeName);
			}
			else
			{
				sb.AppendFormat("class {0}\n", typeName);
			}
		}
		else
		{
			if (sirenClass.Attribute().Has(SirenClassGenerateMode::SirenConfig))
			{
				sb.AppendFormat("class {0} :  {1}, ISirenConfig<{2}>\n", typeName, sirenClass.BaseType()->Name(), typeName);
			}
			else
			{
				sb.AppendFormat("class {0} :  {1}\n", typeName, sirenClass.BaseType()->Name());

			}
		}
		sb.AppendLine("{");
	}

	sb.Append(OnClassConstruct(sirenClass));

	if (!sirenClass.Attribute().Has(SirenClassGenerateMode::SuppressCopy))
	{
		sb.AppendLine(mHeaderCopyBegin);
		sb.Append(OnClassCopy(sirenClass));
		sb.AppendLine(mHeaderCopyEnd);
	}

	if (!sirenClass.Attribute().Has(SirenClassGenerateMode::SuppressCompare))
	{
		sb.AppendLine(mHeaderCompareBegin);
		sb.Append(OnClassCompare(sirenClass));
		sb.AppendLine(mHeaderCompareEnd);
	}

	//add method
	sb.AppendLine(mHeaderMethodBegin);
	sb.Append(OnClassMethods(sirenClass));
	sb.AppendLine(mHeaderMethodEnd);

	//add fields
	sb.AppendLine(mHeaderFieldBegin);
	sb.Append(OnClassFields(sirenClass));
	sb.AppendLine(mHeaderFieldEnd);

	sb.AppendLine("};");
	sb.AppendLine();

	sb.AppendLine(mHeaderSchemaBegin);
	sb.AppendLine(OnClassSchema(sirenClass));
	sb.AppendLine(mHeaderSchemaEnd);
	return sb.ToString();

}

HeapString SirenCppGenerator::OnClassConstruct(SirenCustomClass& sirenClass)const
{
	auto typeName = sirenClass.Name();
	HeapString sb;
	//sb.AppendLine();

	sb.AppendLine("public:");
	sb.AppendLine("\tstruct Schema;");
	sb.AppendFormat("\t{0}();\n", typeName);
	sb.AppendFormat("\t~{0}();\n", typeName);

	return sb.ToString();

}

HeapString SirenCppGenerator::OnClassCompare(SirenCustomClass& sirenClass)const
{
	auto typeName = sirenClass.Name();
	HeapString sb;
	//sb.AppendLine();

	sb.AppendLine("public:");
	//sb.AppendFormat("\tbool operator<(const {0}&)const { return true; }\n", typeName);
	//sb.AppendFormat("\tbool operator==(const {0}&)const { return true; }\n", typeName);

	sb.AppendFormat("\tSIREN_COMMON({0});\n", typeName);

	return sb;

}

HeapString SirenCppGenerator::OnClassCopy(SirenCustomClass& sirenClass)const
{
	auto typeName = sirenClass.Name();
	HeapString sb;
	//sb.AppendLine();

	sb.AppendLine("public:");
	//copy construct
	sb.AppendFormat("\t{0}(const {1}& other)\n", typeName, typeName);
	sb.AppendFormat("\t{\n");
	for (auto sirenFieldPair : sirenClass.Fields())
	{
		SirenField* field = sirenFieldPair.Value;
		auto methodType = GetMethodType(*field);
		switch (methodType)
		{
		case SirenFieldMethodType::Pointer:
			sb.AppendFormat("\t\tSAFE_CONSTRUCT_PTR({0},m{1},other.m{2});\n", GetTypeName(field->Type()), field->Name(), field->Name());
			break;
		case SirenFieldMethodType::Value:
		case SirenFieldMethodType::List:
		case SirenFieldMethodType::Dictionary:
			sb.AppendFormat("\t\tm{0} = other.m{1};\n", field->Name(), field->Name());
			break;
		}

	}
	sb.AppendFormat("\t}\n");

	//assign 
	sb.AppendFormat("\t{0}& operator=(const {1}& other)\n", typeName, typeName);
	sb.AppendFormat("\t{\n");
	for (auto sirenFieldPair : sirenClass.Fields())
	{
		SirenField* field = sirenFieldPair.Value;
		auto methodType = GetMethodType(*field);
		switch (methodType)
		{
		case SirenFieldMethodType::Pointer:

			sb.AppendFormat("\t\tSAFE_COPY_PTR({0},m{1},other.m{2});\n", GetTypeName(field->Type()), field->Name(), field->Name());
			break;
		case SirenFieldMethodType::Value:
		case SirenFieldMethodType::List:
		case SirenFieldMethodType::Dictionary:
			sb.AppendFormat("\t\tm{0} = other.m{1};\n", field->Name(), field->Name());
			break;
		}
	}
	sb.AppendFormat("\t\treturn *this;\n");

	sb.AppendFormat("\t}\n");


	return sb.ToString();

}


HeapString SirenCppGenerator::OnClassMethods(SirenCustomClass& sirenClass)const
{
	HeapString sb;
	//sb.AppendLine();

	//add methods
	sb.AppendLine("public:");
	for (auto sirenFieldPair : sirenClass.Fields())
	{
		SirenField* field = sirenFieldPair.Value;
		auto methodType = GetMethodType(*field);

		if (field->Attribute().Has(SirenFieldGenerateMode::SuppressMethod))
		{
			continue;
		}

		switch (methodType)
		{
		case SirenFieldMethodType::Value:
			sb.AppendFormat("\tSIREN_METHOD({0}, {1});\n", GetTypeName(field->Type()), field->Name());
			break;
		case SirenFieldMethodType::Pointer:
			sb.AppendFormat("\tSIREN_METHOD_PTR({0}, {1});\n", GetTypeName(field->Type()), field->Name());
			break;
		case SirenFieldMethodType::List:
		{

			auto itemType = field->ValueType();
			sb.AppendFormat("\tSIREN_METHOD_LIST({0}, {1});\n", GetTypeName(itemType, field->Attribute().Has(SirenFieldGenerateMode::ForceValueToPtr)), field->Name());
		}
		break;
		case SirenFieldMethodType::Dictionary:
		{
			auto keyType = field->KeyType();
			auto valueType = field->ValueType();
			if (field->Attribute().Has(SirenFieldGenerateMode::AddDictionaryMethods))
			{
				sb.AppendFormat("\tSIREN_METHOD_DICTIONARY_EX({0}, {1}, {2});\n", GetTypeName(keyType, field->Attribute().Has(SirenFieldGenerateMode::ForceKeyToPtr)), GetTypeName(valueType, field->Attribute().Has(SirenFieldGenerateMode::ForceValueToPtr)), field->Name());
			}
			else
			{
				sb.AppendFormat("\tSIREN_METHOD_DICTIONARY({0}, {1}, {2});\n", GetTypeName(keyType, field->Attribute().Has(SirenFieldGenerateMode::ForceKeyToPtr)), GetTypeName(valueType, field->Attribute().Has(SirenFieldGenerateMode::ForceValueToPtr)), field->Name());
			}
		}

		break;
		}

	}

	return sb.ToString();

}
HeapString SirenCppGenerator::OnClassFields(SirenCustomClass& sirenClass)const
{
	HeapString sb;
	//sb.AppendLine();

	//add fields
	sb.AppendLine("protected:");
	for (auto sirenFieldPair : sirenClass.Fields())
	{
		SirenField* field = sirenFieldPair.Value;
		auto methodType = GetMethodType(*field);

		switch (methodType)
		{
		case SirenFieldMethodType::Value:
			sb.AppendFormat("\t{0} m{1};\n", GetTypeName(field->Type()), field->Name());
			break;
		case SirenFieldMethodType::Pointer:
			sb.AppendFormat("\t{0}* m{1};\n", GetTypeName(field->Type()), field->Name());
			break;
		case SirenFieldMethodType::List:
		{
			auto itemType = field->ValueType();

			sb.AppendFormat("\tList<{0}> m{1};\n", GetTypeName(itemType, field->Attribute().Has(SirenFieldGenerateMode::ForceValueToPtr)), field->Name());

		}
		break;
		case SirenFieldMethodType::Dictionary:
		{

			auto keyType = field->KeyType();
			auto valueType = field->ValueType();
			sb.AppendFormat("\tDictionary<{0}, {1}> m{2};\n", GetTypeName(keyType, field->Attribute().Has(SirenFieldGenerateMode::ForceKeyToPtr)), GetTypeName(valueType, field->Attribute().Has(SirenFieldGenerateMode::ForceValueToPtr)), field->Name());
		}
		break;
		}

	}

	return sb.ToString();

}

HeapString SirenCppGenerator::OnClassSchema(SirenCustomClass& sirenClass)const
{
	auto typeName = sirenClass.Name();
	HeapString sb;
	//sb.AppendLine();

	//add schema
	sb.AppendFormat("struct {0}::Schema\n", typeName);
	sb.AppendLine("{");

	for (auto sirenFieldPair : sirenClass.Fields())
	{
		SirenField* field = sirenFieldPair.Value;
		auto methodType = GetMethodType(*field);

		switch (methodType)
		{
		case SirenFieldMethodType::Value:
			sb.AppendFormat("\tSIREN_FIELD({0}, {1}, {2}, {3}, {4}, m{5});\n", field->Index(), field->Id(), field->Attribute().Modifier(), typeName, GetTypeName(field->Type()), field->Name());
			break;
		case SirenFieldMethodType::Pointer:
			sb.AppendFormat("\tSIREN_FIELD({0}, {1}, {2}, {3}, {4}*, m{5});\n", field->Index(), field->Id(), field->Attribute().Modifier(), typeName, GetTypeName(field->Type()), field->Name());
			break;
		case SirenFieldMethodType::List:
		{

			auto itemType = field->ValueType();

			sb.AppendFormat("\tSIREN_FIELD_LIST({0}, {1}, {2}, {3}, {4}, m{5});\n", field->Index(), field->Id(), field->Attribute().Modifier(), typeName, GetTypeName(itemType, field->Attribute().Has(SirenFieldGenerateMode::ForceValueToPtr)), field->Name());
		}
		break;
		case SirenFieldMethodType::Dictionary:
		{
			auto keyType = field->KeyType();
			auto valueType = field->ValueType();
			sb.AppendFormat("\tSIREN_FIELD_DICTIONARY({0}, {1}, {2}, {3}, {4}, {5}, m{6});\n", field->Index(), field->Id(), field->Attribute().Modifier(), typeName, GetTypeName(keyType, field->Attribute().Has(SirenFieldGenerateMode::ForceKeyToPtr)), GetTypeName(valueType, field->Attribute().Has(SirenFieldGenerateMode::ForceValueToPtr)), field->Name());

		}
		break;
		}
	}

	//add properties
	if (sirenClass.BaseType() == nullptr)
	{
		sb.AppendFormat("\tSIREN_FIELDS_{0}(void,{1});\n", sirenClass.Fields().Count(), typeName);
	}
	else
	{
		sb.AppendFormat("\tSIREN_FIELDS_{0}({1},{2});\n", sirenClass.Fields().Count(), sirenClass.BaseType()->Name(), typeName);
	}

	sb.Append("};\n");

	return sb.ToString();
}

HeapString SirenCppGenerator::GenerateAllBodyInclude(SirenCustomClass& sirenClass)const
{
	HeapString sb;
	//sb.AppendLine();
	sb.AppendLine(mBodyIncludeBegin);
	sb.Append(GenerateBodyInclude(sirenClass));
	sb.AppendLine(mBodyIncludeEnd);

	return sb.ToString();

}

HeapString SirenCppGenerator::GenerateBodyInclude(SirenCustomClass& sirenClass)const
{
	HeapString sb;
	//sb.AppendLine();

	sb.AppendFormat("#include \"{0}.h\"\n", sirenClass.Name());

	return sb.ToString();

}


HeapString SirenCppGenerator::GenerateAllBody(SirenCustomClass& sirenClass)const
{
	auto typeName = sirenClass.Name();
	HeapString sb;

	sb.AppendFormat("{0}::{1}()\n", typeName, typeName);
	sb.AppendLine("{");
	sb.AppendLine(mBodyConstructBegin);
	sb.Append(GenerateBodyConstruct(sirenClass));
	sb.AppendLine(mBodyConstructEnd);

	sb.AppendLine("}");
	sb.AppendLine();

	sb.AppendFormat("{0}::~{1}()\n", typeName, typeName);
	sb.AppendLine("{");
	sb.AppendLine(mBodyDestructBegin);
	sb.Append(GenerateBodyDestruct(sirenClass));
	sb.AppendLine(mBodyDestructEnd);

	sb.AppendLine("}");
	sb.AppendLine();

	sb.AppendLine(mBodyMetadataBegin);
	sb.Append(GenerateBodyMetadata(sirenClass));
	sb.AppendLine(mBodyMetadataEnd);


	return sb.ToString();
}

HeapString SirenCppGenerator::GenerateBodyConstruct(SirenCustomClass& sirenClass)const
{
	auto typeName = sirenClass.Name();
	HeapString sb;
	//sb.AppendLine();

	//add construct
	//add default assignment
	for (auto sirenFieldPair : sirenClass.Fields())
	{
		SirenField* field = sirenFieldPair.Value;
		auto valueType = GetValueType(*field);

		switch (valueType)
		{
		case SirenFieldValueType::Value:
			sb.AppendFormat("\tm{0} = {1};\n", field->Name(), GetDefaultValueString(*field));
			break;
		case SirenFieldValueType::Pointer:
			sb.AppendFormat("\tm{0} = NULL;\n", field->Name());
			break;
		}
	}

	return sb.ToString();
}

HeapString SirenCppGenerator::GenerateBodyDestruct(SirenCustomClass& sirenClass)const
{
	auto typeName = sirenClass.Name();
	HeapString sb;
	// sb.AppendLine();

	//add destruct

	for (auto sirenFieldPair : sirenClass.Fields())
	{
		SirenField* field = sirenFieldPair.Value;
		auto methodType = GetMethodType(*field);

		switch (methodType)
		{
		case SirenFieldMethodType::Pointer:
			sb.AppendFormat("\tSAFE_DELETE(m{0});\n", field->Name());
			break;
		case SirenFieldMethodType::List:
			if (field->Attribute().Has(SirenFieldGenerateMode::ForceValueToPtr))
			{
				sb.AppendFormat("\tSAFE_DELETE_COLLECTION(m{0});\n", field->Name());
			}
			break;
		case SirenFieldMethodType::Dictionary:
			if (field->Attribute().Has(SirenFieldGenerateMode::ForceKeyToPtr))
			{
				if (field->Attribute().Has(SirenFieldGenerateMode::ForceValueToPtr))
				{
					sb.AppendFormat("\tSAFE_DELETE_DICTIONARY_BOTH(m{0});\n", field->Name());
				}
				else
				{
					sb.AppendFormat("\tSAFE_DELETE_DICTIONARY_KEY(m{0});\n", field->Name());
				}
			}
			else
			{
				if (field->Attribute().Has(SirenFieldGenerateMode::ForceValueToPtr))
				{
					sb.AppendFormat("\tSAFE_DELETE_DICTIONARY_VALUE(m{0});\n", field->Name());
				}
				else
				{
				}
			}

			break;
		}
	}

	return sb.ToString();
}


HeapString SirenCppGenerator::GenerateBodyMetadata(SirenCustomClass& sirenClass)const
{
	auto typeName = sirenClass.Name();
	HeapString sb;
	// sb.AppendLine();

	//add class metadata
	sb.AppendFormat("SIREN_METADATA({0}, {1});\n", typeName, typeName.Length());

	//add property metadata
	for (auto sirenFieldPair : sirenClass.Fields())
	{
		SirenField* field = sirenFieldPair.Value;
		auto valueType = GetValueType(*field);

		switch (valueType)
		{
		case SirenFieldValueType::Value:
		{
			bool hasDefault = !field->DefaultValue().IsNull();
			HeapString str2 = StringParser::ToString(hasDefault);
			str2.ToLower();
			sb.AppendFormat("SIREN_FIELD_METADATA({0}, {1}, {2}, {3}, {4}, {5});\n", field->Index(), typeName, field->Name(), field->Name().Length(), GetDefaultValueString(*field), str2);
		}

		break;
		case SirenFieldValueType::Pointer:
		case SirenFieldValueType::Struct:
		case SirenFieldValueType::String:
		case SirenFieldValueType::Blob:
		case SirenFieldValueType::List:
		case SirenFieldValueType::Dictionary:
			sb.AppendFormat("SIREN_FIELD_METADATA_STRUCT({0}, {1}, {2}, {3});\n", field->Index(), typeName, field->Name(), field->Name().Length());
			break;
		}
	}

	return sb.ToString();


}

SirenFieldMethodType SirenCppGenerator::GetMethodType(const SirenField& field)
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

SirenFieldValueType SirenCppGenerator::GetValueType(const SirenField& field)
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

HeapString SirenCppGenerator::GetDefaultValueString(const SirenField& field)
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

HeapString SirenCppGenerator::GetTypeName(ISirenType* type, bool forceToPtr /*= false*/)
{
	HeapString outStr;

	if (type->IsBuildIn())
	{
		return type->Name();
	}

	if (forceToPtr)
	{
		return type->Name() + "*";
	}
	return type->Name();
}
