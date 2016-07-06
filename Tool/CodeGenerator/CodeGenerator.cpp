// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
// CodeGenerator.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include "Core/IO/Stream/FileStream.h"
#include "Core/String/StringParser.h"
#include "Core/IO/File.h"
#include "Core/Pattern/Event.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Pattern/Object/ArrayObjectFactory.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/Pattern/EnumPattern.h"
#include "Core/Pattern/FlagsPattern.h"
#include "Core/System/System.h"
#include "Core/Log/Log.h"

using namespace Medusa;

#define DEFINE_TEMPLATE_TYPENAME_1(N, T)			MACRO_COMMA_IF(MACRO_INT_DEC(N)) typename T##N
#define DEFINE_TEMPLATE_TYPENAME(N, T)			MACRO_IF_ELSE(N,DEFINE_TEMPLATE_TYPENAME_1(N,T),MACRO_EMPTY)


#define DEFINE_PARAMETER_TYPE_NAME_1(N, T)			MACRO_COMMA_IF(MACRO_INT_DEC(N)) T##N  p##N
#define DEFINE_PARAMETER_TYPE_NAME(N, T)			MACRO_IF_ELSE(N,DEFINE_PARAMETER_TYPE_NAME_1(N,T),MACRO_EMPTY)

void FormatCode(HeapString &str)
{
	str.ReplaceAll("{", "\n{\n");
	str.ReplaceAll("}", "\n}\n");
	str.ReplaceAll(")>", ")>\n");
	str.ReplaceAll("public:", "public:\n");
	str.ReplaceAll("protected:", "protected:\n");
	str.ReplaceAll("private:", "private:\n");
	str.ReplaceAll("default:", "default:\n");

	str.ReplaceAll(";", ";\n");
	str.ReplaceAll("}\n;", "};");
	str.ReplaceAll("\n\n", "\n");
	str.ReplaceAll("for(uint i=0;\ni<Size;\n++i)", "for(uint i=0;i<Size;++i)");

	str.ReplaceAll("for(j=0;\nj<Size;\n++j)", "for(j=0;j<Size;++j)");


	str.ReplaceAll("for(auto i = (names).GetEnumerator();\ni.MoveNext();\n)", "for(auto i = (names).GetEnumerator();i.MoveNext();)");

}

HeapString WriteLine(FileStream& fs, StringRef str)
{
	HeapString temp = str;
	temp += "\n";
	fs.WriteString(temp, false);

	return temp;
}

void AdjustEnumStr(HeapString &str, StringRef path, StringRef name)
{
	FormatCode(str);
	str.ReplaceAll("__declspec(selectany)", "MEDUSA_WEAK_MULTIPLE_DEFINE");

	HeapString classDefine;
	classDefine.AppendFormat("class {}", name.c_str());
	HeapString tempDefine = classDefine;
	tempDefine += "\t//[IGNORE_PRE_DECLARE]";
	str.ReplaceFirst(classDefine, tempDefine);

	HeapString filedDefine;
	filedDefine.AppendFormat("class {}Field", name.c_str());
	tempDefine = filedDefine;
	tempDefine += "\t//[IGNORE_PRE_DECLARE]";
	str.ReplaceFirst(filedDefine, tempDefine);

	{
		intp index = str.IndexOf("__MedusaAssertFailed");
		intp prevIndex = str.PrevIndexOf('{', index);
		intp nextIndex = str.IndexOf('}', index);
		str.RemoveAt(prevIndex, nextIndex - prevIndex + 1);
		str.Insert(prevIndex, "MEDUSA_ASSERT_FAILED(\"Invalid enum val.\")");
	}

	{
		intp index = str.IndexOf("__MedusaAssertFailed");
		intp prevIndex = str.PrevIndexOf('{', index);
		intp nextIndex = str.IndexOf('}', index);
		str.RemoveAt(prevIndex, nextIndex - prevIndex + 1);
		str.Insert(prevIndex, "MEDUSA_ASSERT_FAILED(\"Invalid enum name.\")");
	}


	HeapString temp = File::ReadAllText(path);
	if (temp != str)
	{
		File::WriteAllText(path, str);
	}

}

void AdjustFlagStr(HeapString &str, StringRef path, StringRef name)
{
	FormatCode(str);

	//MEDUSA_ASSERT(isSucceed,"Invalid flags names")

	str.ReplaceAll("__declspec(selectany)", "MEDUSA_WEAK_MULTIPLE_DEFINE");
	HeapString classDefine;
	classDefine.AppendFormat("class {}", name.c_str());
	HeapString tempDefine = classDefine;
	tempDefine += "\t//[IGNORE_PRE_DECLARE]";
	str.ReplaceFirst(classDefine, tempDefine);

	HeapString filedDefine;
	filedDefine.AppendFormat("class {}Field", name.c_str());
	tempDefine = filedDefine;
	tempDefine += "\t//[IGNORE_PRE_DECLARE]";
	str.ReplaceFirst(filedDefine, tempDefine);


	{
		//MEDUSA_ASSERT_FAILED("Invalid flags val.")
		intp index = str.IndexOf("__MedusaAssertFailed");
		intp prevIndex = str.PrevIndexOf('{', index);
		intp nextIndex = str.IndexOf('}', index);
		str.RemoveAt(prevIndex, nextIndex - prevIndex + 1);
		str.Insert(prevIndex, "MEDUSA_ASSERT_FAILED(\"Invalid flags val.\")");
	}


	{
		//MEDUSA_ASSERT(splitResult, "Invalid flags names")
		intp index = str.IndexOf("__MedusaAssertFailed");
		intp prevIndex = str.PrevIndexOf('{', index);
		intp nextIndex = str.IndexOf('}', index);

		str.RemoveAt(prevIndex, nextIndex - prevIndex + 1);
		str.Insert(prevIndex, "MEDUSA_ASSERT_FAILED(\"Invalid flags names\")");
	}

	{
		//MEDUSA_ASSERT(splitResult, "Invalid flags names")
		intp index = str.IndexOf("__MedusaAssertFailed");
		intp prevIndex = str.PrevIndexOf('{', index);
		intp nextIndex = str.IndexOf('}', index);

		str.RemoveAt(prevIndex, nextIndex - prevIndex + 1);
		str.Insert(prevIndex, "MEDUSA_ASSERT_FAILED(\"Invalid flags names\")");
	}

	HeapString temp = File::ReadAllText(path);
	if (temp != str)
	{
		File::WriteAllText(path, str);
	}
}


HeapString GenerateEnumClassEnd(int count)
{
	HeapString str;
	FileStream fs("EnumPattern.txt", FileOpenMode::DestoryWriteOrCreate);



	for (int i = 1; i <= count; ++i)
	{
		HeapString text = HeapString("#define ENUM_CLASS_END_");
		text += StringParser::ToString(i);
		text += "(TEnum,";
		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);

			text += ",P";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += ")\\\n";
		text += "private:\\\n";

		for (int j = 1; j <= i; ++j)
		{
			text += "static StringRef OnName";
			text += StringParser::ToString(j);
			text += "(){return #T";
			text += StringParser::ToString(j);
			text += ";}\\\n";
		}

		text += "public:\\\n";
		text += "explicit TEnum(int val):mState(val){}\\\n";
		text += "StringRef ToString()const{switch(mState){\\\n";
		for (int j = 1; j <= i; ++j)
		{
			text += "case P";
			text += StringParser::ToString(j);
			text += ":return #T";
			text += StringParser::ToString(j);
			text += ";";
		}
		text += "\\\ndefault:return nullptr;}}\\\n";
		text += "uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\\\n";

		text += "static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\\\n";
		text += "static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\\\n";
		text += "static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED(\"Invalid enum val.\");return TEnum::T1;}\\\n";
		text += "static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\\\n";
		text += "static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED(\"Invalid enum name.\");return TEnum::T1;}\\\n";
		text += "static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]); return true;}}return false;}\\\n";



		text += "public:\\\n";
		text += "static constexpr unsigned int Size=";
		text += StringParser::ToString(i);
		text += ";\\\n";

		text += "static const StringRef Names[Size];\\\n";
		text += "static const int Values[Size];\\\n";


		for (int j = 1; j <= i; ++j)
		{
			text += "static const TEnum##Field<P";
			text += StringParser::ToString(j);
			text += ",";
			text += StringParser::ToString(j - 1);
			text += ",TEnum::OnName";
			text += StringParser::ToString(j);
			text += "> T";
			text += StringParser::ToString(j);
			text += ";\\\n";
		}
		text += "TEnum():mState(P1){}\\\n";
		text += "};\\\n";

		text += "MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={";
		for (int j = 1; j <= i; ++j)
		{
			text += "#T";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += "};\\\n";

		text += "MEDUSA_WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={";
		for (int j = 1; j <= i; ++j)
		{
			text += "P";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += "};\\\n";

		for (int j = 1; j <= i; ++j)
		{
			text += "\tMEDUSA_WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P";
			text += StringParser::ToString(j);
			text += ",";
			text += StringParser::ToString(j - 1);
			text += ",TEnum::OnName";
			text += StringParser::ToString(j);
			text += "> TEnum::T";
			text += StringParser::ToString(j);
			if (j == i)
			{
				text += ";\n";
			}
			else
			{
				text += ";\\\n";
			}
		}

		str += WriteLine(fs, text);
	}


	return str;

}

HeapString GenerateEnumDefine(int count)
{
	HeapString str;
	FileStream fs("EnumDefine.txt", FileOpenMode::DestoryWriteOrCreate);


	for (int i = 1; i <= count; ++i)
	{
		HeapString text = HeapString("#define STRONG_ENUM_CUSTOM_");
		text += StringParser::ToString(i);
		text += "(TEnum,";
		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);

			text += ",P";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += ")\tENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_";
		text += StringParser::ToString(i);
		text += "(TEnum,";
		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);

			text += ",P";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += ")";
		str += WriteLine(fs, text);
	}


	str += WriteLine(fs, "\n\n\n");


	for (int i = 1; i <= count; ++i)
	{
		HeapString text = HeapString("#define STRONG_ENUM_");
		text += StringParser::ToString(i);
		text += "(TEnum,";
		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += ")\tSTRONG_ENUM_CUSTOM_";
		text += StringParser::ToString(i);
		text += "(TEnum,";
		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);
			text += ",";
			text += StringParser::ToString(j - 1);
			if (j != i)
			{
				text += ",";
			}
		}
		text += ")";
		str += WriteLine(fs, text);
	}


	return str;

}


HeapString GenerateFlagsClassEnd(int count)
{
	HeapString str;
	FileStream fs("FlagsPattern.txt", FileOpenMode::DestoryWriteOrCreate);


	for (int i = 1; i <= count; ++i)
	{
		HeapString allField;
		for (int j = 1; j <= i; ++j)
		{
			allField += "P";
			allField += StringParser::ToString(j);
			if (j != i)
			{
				allField += "|";
			}
		}


		HeapString text = HeapString("#define FLAGS_CLASS_END_");
		text += StringParser::ToString(i);
		text += "(TFlags,";
		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);

			text += ",P";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += ")\\\n";
		text += "private:\\\n";
		text += "static const StringRef& OnNameNone(){return NoneName;}\\\n";
		text += "static const StringRef& OnNameAll(){return AllName;}\\\n";

		for (int j = 0; j < i; ++j)
		{
			text += "static const StringRef& OnName";
			text += StringParser::ToString(j);
			text += "(){return Names[";
			text += StringParser::ToString(j);
			text += "];}\\\n";
		}

		text += "public:\\\n";
		text += "HeapString ToString()const{if (mState == None.IntValue) { return NoneName; }if (mState == All.IntValue) { return AllName; }HeapString result;for(uint i=0;i<Size;++i){if ((mState & Values[i]) == Values[i]) { if (!result.IsEmpty()) { result += '|'; }result += Names[i]; }}return result;}\\\n";

		text += "static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\\\n";
		text += "static bool HasField(const StringRef& name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\\\n";
		text += "static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED(\"Invalid flags val.\");return TFlags(val);}\\\n";
		text += "static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\\\n";
		text += "static TFlags Parse(const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { return None; } if (name.Compare(AllName, ignoreCase) == 0) { return All; }TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,\"|\",names);if(!splitResult){MEDUSA_ASSERT_FAILED(\"Invalid flags names.\");}for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}if(!isSucceed){MEDUSA_ASSERT_FAILED(\"Invalid flags names.\");}return result;}\\\n";
		text += "static bool TryParse(TFlags& outFlags,const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { outFlags = None; return true; } if (name.Compare(AllName, ignoreCase) == 0) { outFlags = All; return true; }bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,\"|\",names));for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\\\n";

		text += "static constexpr unsigned int Size=";
		text += StringParser::ToString(i);
		text += ";\\\n";
		text += "static const StringRef NoneName;\\\n";
		text += "static const StringRef AllName;\\\n";
		text += "static const StringRef Names[Size];\\\n";
		text += "static const int Values[Size];\\\n";

		text += "static const TFlags##Field<0,TFlags::OnNameNone> None;\\\n";
		text += "bool IsNone()const { return mState == None.IntValue; }\\\n";

		text += "static const TFlags##Field<";
		text += allField;
		text += ",TFlags::OnNameAll> All;\\\n";

		text += "bool IsAll()const { return mState == All.IntValue; }\\\n";

		for (int j = 1; j <= i; ++j)
		{
			text += "static const TFlags##Field<P";
			text += StringParser::ToString(j);
			text += ",TFlags::OnName";
			text += StringParser::ToString(j - 1);
			text += "> T";
			text += StringParser::ToString(j);
			text += ";\\\n";

			text += "bool Is##T";
			text += StringParser::ToString(j);
			text += "()const { return (mState&T";
			text += StringParser::ToString(j);
			text += ".IntValue) == T";
			text += StringParser::ToString(j);
			text += ".IntValue; }\\\n";
		}

		text += "};\\\n";
		text += "MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::NoneName = \"None\";\\\n";
		text += "MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::AllName = \"All\";\\\n";

		text += "MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={";
		for (int j = 1; j <= i; ++j)
		{
			text += "#T";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += "};\\\n";

		text += "MEDUSA_WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={";
		for (int j = 1; j <= i; ++j)
		{
			text += "P";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += "};\\\n";

		text += "MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnNameNone> TFlags::None;\\\n";
		text += "MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<";
		text += allField;
		text += ",TFlags::OnNameAll> TFlags::All;\\\n";

		for (int j = 1; j <= i; ++j)
		{
			text += "\tMEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P";
			text += StringParser::ToString(j);
			text += ",TFlags::OnName";
			text += StringParser::ToString(j - 1);
			text += "> TFlags::T";
			text += StringParser::ToString(j);
			if (j == i)
			{
				text += ";\n";
			}
			else
			{
				text += ";\\\n";
			}
		}

		str += WriteLine(fs, text);
	}


	return str;

}

HeapString GenerateFlagsDefine(int count)
{
	HeapString str;
	FileStream fs("FlagsDefine.txt", FileOpenMode::DestoryWriteOrCreate);


	for (int i = 1; i <= count; ++i)
	{
		HeapString text = HeapString("#define STRONG_FLAGS_CUSTOM_");
		text += StringParser::ToString(i);
		text += "(TFlags,";
		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);

			text += ",P";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += ")\tFLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_";
		text += StringParser::ToString(i);
		text += "(TFlags,";
		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);

			text += ",P";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += ")";
		str += WriteLine(fs, text);
	}


	str += WriteLine(fs, "\n\n\n");


	for (int i = 1; i <= count; ++i)
	{
		HeapString text = HeapString("#define STRONG_FLAGS_");
		text += StringParser::ToString(i);
		text += "(TEnum,";
		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += ")\tSTRONG_FLAGS_CUSTOM_";
		text += StringParser::ToString(i);
		text += "(TEnum,";
		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);
			text += ",";
			text += StringParser::ToString(1 << (j - 1));
			if (j != i)
			{
				text += ",";
			}
		}
		text += ")";
		str += WriteLine(fs, text);
	}


	return str;

}

HeapString GenerateTuple(int count)
{
	HeapString str;
	FileStream fs("Tuple.txt", FileOpenMode::DestoryWriteOrCreate);

	for (int i = 1; i <= count; ++i)
	{
		HeapString text = HeapString("#define MEDUSA_TUPLE_");
		text += StringParser::ToString(i);
		text += "(TClass,";
		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);

			text += ",P";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += ",";
			}
		}
		text += ")\t\\\n";
		text += "struct TClass	\\\n";
		text += "{	\\\n";
		for (int j = 1; j <= i; ++j)
		{
			text += "typedef Compile::TypeTraits<T";
			text += StringParser::ToString(j);

			text += ">::ParameterType T";
			text += StringParser::ToString(j);
			text += "ParameterType; \\\n";
		}

		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);

			text += " P";
			text += StringParser::ToString(j);
			text += "; \\\n";
		}


		text += "TClass():";
		for (int j = 1; j <= i; ++j)
		{
			text += "P";
			text += StringParser::ToString(j);

			text += "()";
			if (j != i)
			{
				text += ",";
			}
		}

		text += "{}	\\\n";

		text += "TClass(";
		for (int j = 1; j <= i; ++j)
		{
			text += "T";
			text += StringParser::ToString(j);
			text += "ParameterType";

			text += " p";
			text += StringParser::ToString(j);

			if (j != i)
			{
				text += ",";
			}
		}
		text += "):";
		for (int j = 1; j <= i; ++j)
		{
			text += "P";
			text += StringParser::ToString(j);
			text += "(";

			text += "p";
			text += StringParser::ToString(j);
			text += ")";

			if (j != i)
			{
				text += ",";
			}
		}

		text += "{}  \\\n";


		text += "TClass& operator=(const TClass& val){";
		for (int j = 1; j <= i; ++j)
		{
			text += "P";
			text += StringParser::ToString(j);
			text += "=";

			text += "val.P";
			text += StringParser::ToString(j);
			text += ";";
		}
		text += "return *this;}	\\\n";


		text += "bool operator==(const TClass& val)const{return ";
		for (int j = 1; j <= i; ++j)
		{
			text += "P";
			text += StringParser::ToString(j);
			text += "==";

			text += "val.P";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += "&&";
			}
		}
		text += ";}	\\\n";

		text += "bool operator!=(const TClass& val)const{return ";
		for (int j = 1; j <= i; ++j)
		{
			text += "P";
			text += StringParser::ToString(j);
			text += "!=";

			text += "val.P";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += "||";
			}
		}
		text += ";}	\\\n";

		text += "bool operator<(const TClass& val)const{return ";
		for (int j = 1; j <= i; ++j)
		{
			text += "P";
			text += StringParser::ToString(j);
			text += "<";

			text += "val.P";
			text += StringParser::ToString(j);
			if (j != i)
			{
				text += "&&";
			}
		}
		text += ";}	\\\n";

		text += "intp HashCode()const{return ";
		for (int j = 1; j <= i; ++j)
		{
			text += "HashUtility::Hash(P";
			text += StringParser::ToString(j);
			text += ")";

			if (j != i)
			{
				text += "^";
			}
		}
		text += ";}	\\\n";

		text += "};\n\n";

		str += WriteLine(fs, text);
	}

	str += WriteLine(fs, "\n\n\n");


	return str;

}
void ReplaceStr(HeapString& str, StringRef begin, StringRef end, StringRef target)
{
	intp index1 = str.IndexOf(begin);
	intp index2 = str.IndexOf(end);
	str.RemoveAt(index1, index2 - index1);

	HeapString result = HeapString(begin.Buffer());
	result += "\n";
	result += target;
	str.Insert(index1, result.Buffer());
}





void ModifyEnum(StringRef path)
{
	HeapString temp = File::ReadAllText(path);
	HeapString str = temp;


	int count = 20;
	ReplaceStr(str, "//BEGIN_AUTO_GENERATE_ENUM_CLASS_END", "//END_AUTO_GENERATE_ENUM_CLASS_END", GenerateEnumClassEnd(count));

	ReplaceStr(str, "//BEGIN_AUTO_GENERATE_ENUM_DEFINE", "//END_AUTO_GENERATE_ENUM_DEFINE", GenerateEnumDefine(count));


	if (str != temp)
	{
		bool isSuccess = File::WriteAllText(path, str);
		if (!isSuccess)
		{
			Log::FormatError("Cannot find path:{}", path.c_str());
		}
	}



}

void ModifyFlags(StringRef path)
{
	HeapString temp = File::ReadAllText(path);
	HeapString str = temp;

	int count = 10;
	ReplaceStr(str, "//BEGIN_AUTO_GENERATE_FLAGS_CLASS_END", "//END_AUTO_GENERATE_FLAGS_CLASS_END", GenerateFlagsClassEnd(count));

	ReplaceStr(str, "//BEGIN_AUTO_GENERATE_FLAGS_DEFINE", "//END_AUTO_GENERATE_FLAGS_DEFINE", GenerateFlagsDefine(count));


	if (str != temp)
	{
		File::WriteAllText(path, str);
	}


}

void ModifyTuple(StringRef path)
{
	HeapString temp = File::ReadAllText(path);
	HeapString str = temp;


	ReplaceStr(str, "//BEGIN_AUTO_GENERATE_TUPLE", "//END_AUTO_GENERATE_TUPLE", GenerateTuple(10));

	if (str != temp)
	{
		File::WriteAllText(path, str);
	}
}

#pragma region Enums



void GenerateSirenTypeId(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\Siren\\Schema\\Type\\SirenTypeId.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_18(SirenTypeId, Null,Bool, Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Float, Double, String,Blob, Enum,List, Dictionary, Struct));");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_18(SirenTypeId, Null, Bool, Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Float, Double, String, Blob, Enum, List, Dictionary, Struct)));
	str.AppendLine("MEDUSA_END;");
	AdjustEnumStr(str, path, MACRO_TO_STRING(SirenTypeId));


}



#pragma endregion Enums

#pragma region Flags




void GeneratePublishVersions(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\System\\PublishVersions.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_2(PublishVersions,main,free);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_2(PublishVersions, main, free)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(PublishVersions));


}

void GeneratePublishDevices(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\System\\PublishDevices.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_2(PublishDevices,sd,hd);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_2(PublishDevices, sd, hd)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(PublishDevices));


}

void GeneratePublishLanguages(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\System\\PublishLanguages.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_2(PublishLanguages,enus,zhcn);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_2(PublishLanguages, enus, zhcn)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(PublishLanguages));


}

#pragma endregion Flags


int _tmain(int argc, _TCHAR* argv[])
{
	System::Instance().Initialize();
	Log::Initialize();
	HeapString appPath = System::Instance().ApplicationPath();
	intp index = appPath.IndexOf("\\Tool\\CodeGenerator");
	HeapString rootpath = appPath.SubString(0, index);

	const HeapString corePath = rootpath + HeapString("\\Medusa\\MedusaCore\\");
	const HeapString medusaPath = rootpath + HeapString("\\Medusa\\Medusa\\");
	const HeapString medusaExtensionPath = rootpath + HeapString("\\Medusa\\MedusaExtension\\");


	const HeapString delegatePath = corePath + "Core\\Pattern\\Delegate.h";
	const HeapString eventPath = corePath + "Core\\Pattern\\Event.h";
	const HeapString arrayObjectFactoryPath = corePath + "Core\\Pattern\\Object\\ArrayObjectFactory.h";
	const HeapString mapObjectFactoryPath = corePath + "Core\\Pattern\\Object\\MapObjectFactory.h";
	const HeapString enumPath = corePath + "Core\\Pattern\\EnumPattern.h";
	const HeapString flagsPath = corePath + "Core\\Pattern\\FlagsPattern.h";
	const HeapString tuplePath = corePath + "Core\\Pattern\\TuplePattern.h";



	ModifyEnum(enumPath);
	ModifyFlags(flagsPath);

	ModifyTuple(tuplePath);


	GenerateSirenTypeId(corePath, medusaPath);

	GeneratePublishVersions(corePath, medusaPath);
	GeneratePublishDevices(corePath, medusaPath);
	GeneratePublishLanguages(corePath, medusaPath);


	return 0;
}
