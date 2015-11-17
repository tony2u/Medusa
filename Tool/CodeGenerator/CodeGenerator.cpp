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


	HeapString temp;
	File::ReadAllTextTo(path, temp);
	if (temp != str)
	{
		File::WriteAllTextTo(path, str);
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

	HeapString temp;
	File::ReadAllTextTo(path, temp);
	if (temp != str)
	{
		File::WriteAllTextTo(path, str);
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
		text += "static TFlags Parse(const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { return None; } if (name.Compare(AllName, ignoreCase) == 0) { return All; }TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,\"|\",names);if(!splitResult){MEDUSA_ASSERT_FAILED(\"Invalid flags names.\");}FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}if(!isSucceed){MEDUSA_ASSERT_FAILED(\"Invalid flags names.\");}return result;}\\\n";
		text += "static bool TryParse(TFlags& outFlags,const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { outFlags = None; return true; } if (name.Compare(AllName, ignoreCase) == 0) { outFlags = All; return true; }bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,\"|\",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\\\n";

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
	HeapString temp;
	File::ReadAllTextTo(path, temp);
	HeapString str = temp;


	int count = 20;
	ReplaceStr(str, "//BEGIN_AUTO_GENERATE_ENUM_CLASS_END", "//END_AUTO_GENERATE_ENUM_CLASS_END", GenerateEnumClassEnd(count));

	ReplaceStr(str, "//BEGIN_AUTO_GENERATE_ENUM_DEFINE", "//END_AUTO_GENERATE_ENUM_DEFINE", GenerateEnumDefine(count));


	if (str != temp)
	{
		bool isSuccess = File::WriteAllTextTo(path, str);
		if (!isSuccess)
		{
			Log::FormatError("Cannot find path:{}", path.c_str());
		}
	}



}

void ModifyFlags(StringRef path)
{
	HeapString temp;
	File::ReadAllTextTo(path, temp);
	HeapString str = temp;

	int count = 10;
	ReplaceStr(str, "//BEGIN_AUTO_GENERATE_FLAGS_CLASS_END", "//END_AUTO_GENERATE_FLAGS_CLASS_END", GenerateFlagsClassEnd(count));

	ReplaceStr(str, "//BEGIN_AUTO_GENERATE_FLAGS_DEFINE", "//END_AUTO_GENERATE_FLAGS_DEFINE", GenerateFlagsDefine(count));


	if (str != temp)
	{
		File::WriteAllTextTo(path, str);
	}


}

void ModifyTuple(StringRef path)
{
	HeapString temp;
	File::ReadAllTextTo(path, temp);
	HeapString str = temp;


	ReplaceStr(str, "//BEGIN_AUTO_GENERATE_TUPLE", "//END_AUTO_GENERATE_TUPLE", GenerateTuple(10));

	if (str != temp)
	{
		File::WriteAllTextTo(path, str);
	}
}

#pragma region Enums



void GenerateSirenDataType(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\Siren\\SirenDataType.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_17(SirenDataType, StructEnd,Bool, Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Float, Double, String, List,Blob, Dictionary, Struct));");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_17(SirenDataType, StructEnd,Bool, Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Float, Double, String, Blob, List, Dictionary, Struct)));
	str.AppendLine("MEDUSA_END;");
	AdjustEnumStr(str, path, MACRO_TO_STRING(SirenDataType));


}


void GenerateFileUpdaterMessageType(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\IO\\Updater\\FileUpdaterMessageType.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_6(FileUpdaterMessageType, FileUpdaterNetworkError, FileUpdaterDontUpgragde, FileUpdaterServerMaintain, FileUpdaterIncompatiableClient, FileUpdaterSeverError, FileUpdaterDownloadingInterrupted);");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_6(FileUpdaterMessageType, FileUpdaterNetworkError, FileUpdaterDontUpgragde, FileUpdaterServerMaintain, FileUpdaterIncompatiableClient, FileUpdaterSeverError, FileUpdaterDownloadingInterrupted)));
	str.AppendLine("MEDUSA_END;");
	AdjustEnumStr(str, path, MACRO_TO_STRING(FileUpdaterMessageType));


}


void GenerateGraphicsHintMode(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\GraphicsHintMode.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_CUSTOM_3(GraphicsHintMode, Fastest, GL_FASTEST, Nicest, GL_NICEST, DontCare, GL_DONT_CARE);");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_CUSTOM_3(GraphicsHintMode, Fastest, GL_FASTEST, Nicest, GL_NICEST, DontCare, GL_DONT_CARE)));
	str.AppendLine("MEDUSA_END;");
	AdjustEnumStr(str, path, MACRO_TO_STRING(GraphicsHintMode));


}

void GenerateGraphicsBlendEquation(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\GraphicsBlendEquation.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_CUSTOM_3(GraphicsBlendEquation,Add, GL_FUNC_ADD,Subtract, GL_FUNC_SUBTRACT,ReverserSubtract, GL_FUNC_REVERSE_SUBTRACT);");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_CUSTOM_3(GraphicsBlendEquation, Add, GL_FUNC_ADD, Subtract, GL_FUNC_SUBTRACT, ReverserSubtract, GL_FUNC_REVERSE_SUBTRACT)));
	str.AppendLine("MEDUSA_END;");
	AdjustEnumStr(str, path, MACRO_TO_STRING(GraphicsBlendEquation));

}


void GenerateGraphicsPixelDataType(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\GraphicsPixelDataType.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_CUSTOM_7(GraphicsPixelDataType,Byte, GL_UNSIGNED_BYTE,UnsignedShort565, GL_UNSIGNED_SHORT_5_6_5,UnsignedShort4444, GL_UNSIGNED_SHORT_4_4_4_4,UnsignedShort5551, GL_UNSIGNED_SHORT_5_5_5_1,HalfFloatOES, GL_HALF_FLOAT_OES,FloatOES, GL_FLOAT,UInt, GL_UNSIGNED_INT);");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_CUSTOM_7(GraphicsPixelDataType, Byte, GL_UNSIGNED_BYTE, UnsignedShort565, GL_UNSIGNED_SHORT_5_6_5, UnsignedShort4444, GL_UNSIGNED_SHORT_4_4_4_4, UnsignedShort5551, GL_UNSIGNED_SHORT_5_5_5_1, HalfFloatOES, GL_HALF_FLOAT_OES, FloatOES, GL_FLOAT, UInt, GL_UNSIGNED_INT)));
	str.AppendLine("MEDUSA_END;");
	AdjustEnumStr(str, path, MACRO_TO_STRING(GraphicsPixelDataType));

}

void GenerateGraphicsFuncType(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\GraphicsFuncType.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_CUSTOM_8(GraphicsFuncType,Never, GL_NEVER,Less, GL_LESS,Equal, GL_EQUAL,LessOrEqual, GL_LEQUAL,Greater, GL_GREATER,NotEqual, GL_NOTEQUAL,GreaterOrEqual, GL_GEQUAL,Always, GL_ALWAYS);");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_CUSTOM_8(GraphicsFuncType, Never, GL_NEVER, Less, GL_LESS, Equal, GL_EQUAL, LessOrEqual, GL_LEQUAL, Greater, GL_GREATER, NotEqual, GL_NOTEQUAL, GreaterOrEqual, GL_GEQUAL, Always, GL_ALWAYS)));
	str.AppendLine("MEDUSA_END;");

	AdjustEnumStr(str, path, MACRO_TO_STRING(GraphicsFuncType));
}


void GenerateGraphicsStencilOperation(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\GraphicsStencilOperation.h";


	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_CUSTOM_8(GraphicsStencilOperation,Keep, GL_KEEP,Zero, GL_ZERO,ReplaceToRef, GL_REPLACE,Increase, GL_INCR,IncreaseWrap, GL_INCR_WRAP,Decrease, GL_DECR,DecreaseWrap, GL_DECR_WRAP,Invert, GL_INVERT);");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_CUSTOM_8(GraphicsStencilOperation, Keep, GL_KEEP, Zero, GL_ZERO, ReplaceToRef, GL_REPLACE, Increase, GL_INCR, IncreaseWrap, GL_INCR_WRAP, Decrease, GL_DECR, DecreaseWrap, GL_DECR_WRAP, Invert, GL_INVERT)));
	str.AppendLine("MEDUSA_END;");

	AdjustEnumStr(str, path, MACRO_TO_STRING(GraphicsStencilOperation));


}

void GenerateGraphicsFrontFace(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\GraphicsFrontFace.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_CUSTOM_2(GraphicsFrontFace, ClockWise, GL_CW, CounterClockWise, GL_CCW);");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_CUSTOM_2(GraphicsFrontFace, ClockWise, GL_CW, CounterClockWise, GL_CCW)));
	str.AppendLine("MEDUSA_END;");

	AdjustEnumStr(str, path, MACRO_TO_STRING(GraphicsFrontFace));


}

void GenerateGraphicsFace(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\GraphicsFace.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_CUSTOM_3(GraphicsFace, Front, GL_FRONT, Back, GL_BACK, FrontAndBack, GL_FRONT_AND_BACK);");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_CUSTOM_3(GraphicsFace, Front, GL_FRONT, Back, GL_BACK, FrontAndBack, GL_FRONT_AND_BACK)));
	str.AppendLine("MEDUSA_END;");

	AdjustEnumStr(str, path, MACRO_TO_STRING(GraphicsFace));


}


void GenerateSkeletonAttachmentType(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Resource\\Skeleton\\Attachment\\SkeletonAttachmentType.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_4(SkeletonAttachmentType, Region, Mesh, SkinnedMesh, BoundingBox);");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_4(SkeletonAttachmentType, Region, Mesh, SkinnedMesh, BoundingBox)));
	str.AppendLine("MEDUSA_END;");

	AdjustEnumStr(str, path, MACRO_TO_STRING(SkeletonAttachmentType));


}

void GenerateAnalyticsCurrencyType(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Analytics\\AnalyticsCurrencyType.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaExtensionPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_3(AnalyticsCurrencyType, CNY, USD, EUR);");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_3(AnalyticsCurrencyType, CNY, USD, EUR)));
	str.AppendLine("MEDUSA_END;");
	AdjustEnumStr(str, path, MACRO_TO_STRING(AnalyticsCurrencyType));


}

void GenerateAnalyticsPaymentType(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Analytics\\AnalyticsPaymentType.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaExtensionPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_8(AnalyticsPaymentType, AppStore, AliPay, WebBank, QQPay, ChinaMobile, Unicom, Telecom, Paypal);");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_8(AnalyticsPaymentType, AppStore, AliPay, WebBank, QQPay, ChinaMobile, Unicom, Telecom, Paypal)));
	str.AppendLine("MEDUSA_END;");
	AdjustEnumStr(str, path, MACRO_TO_STRING(AnalyticsPaymentType));


}

void GenerateAnalyticsRewardType(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Analytics\\AnalyticsRewardType.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaExtensionPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_ENUM_3(AnalyticsRewardType, FromPlayer, FromCompany, FromGame);");
	str.AppendLine(MACRO_TO_STRING(STRONG_ENUM_3(AnalyticsRewardType, FromPlayer, FromCompany, FromGame)));
	str.AppendLine("MEDUSA_END;");
	AdjustEnumStr(str, path, MACRO_TO_STRING(AnalyticsRewardType));


}

#pragma endregion Enums

#pragma region Flags

void GenerateGameFeatures(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Game\\GameFeatures.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_5(GameFeatures, SupportThreadEvent, SupportMessage,SupportScript, SupportFileUpdating,SupportSceneEditor);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_5(GameFeatures, SupportThreadEvent, SupportMessage, SupportScript, SupportFileUpdating, SupportSceneEditor)));
	str.AppendLine("MEDUSA_END;");

	AdjustFlagStr(str, path, MACRO_TO_STRING(GameFeatures));


}

void GenerateGraphicsBufferComponentMask(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\GraphicsBufferComponentMask.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_CUSTOM_3(GraphicsBufferComponentMask, Depth, GL_DEPTH_BUFFER_BIT, Stencil, GL_STENCIL_BUFFER_BIT, Color, GL_COLOR_BUFFER_BIT);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_CUSTOM_3(GraphicsBufferComponentMask, Depth, GL_DEPTH_BUFFER_BIT, Stencil, GL_STENCIL_BUFFER_BIT, Color, GL_COLOR_BUFFER_BIT)));
	str.AppendLine("MEDUSA_END;");

	AdjustFlagStr(str, path, MACRO_TO_STRING(GraphicsBufferComponentMask));


}

void GenerateGraphicsColorMask(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\GraphicsColorMask.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_4(GraphicsColorMask, R, G, B, A);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_4(GraphicsColorMask, R, G, B, A)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(GraphicsColorMask));


}

void GenerateGraphicsMapBufferMask(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\GraphicsMapBufferMask.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_CUSTOM_6(GraphicsMapBufferMask, Read, GL_MAP_READ_BIT, Write, GL_MAP_WRITE_BIT, InvalidateRange, GL_MAP_INVALIDATE_RANGE_BIT, InvalidateBuffer, GL_MAP_INVALIDATE_BUFFER_BIT, FlushExplicit, GL_MAP_FLUSH_EXPLICIT_BIT, Unsynchronized, GL_MAP_UNSYNCHRONIZED_BIT);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_CUSTOM_6(GraphicsMapBufferMask, Read, GL_MAP_READ_BIT, Write, GL_MAP_WRITE_BIT, InvalidateRange, GL_MAP_INVALIDATE_RANGE_BIT, InvalidateBuffer, GL_MAP_INVALIDATE_BUFFER_BIT, FlushExplicit, GL_MAP_FLUSH_EXPLICIT_BIT, Unsynchronized, GL_MAP_UNSYNCHRONIZED_BIT)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(GraphicsMapBufferMask));


}

void GenerateGraphicsSyncMask(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\GraphicsSyncMask.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_CUSTOM_1(GraphicsSyncMask, FlushCommands, GL_SYNC_FLUSH_COMMANDS_BIT);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_CUSTOM_1(GraphicsSyncMask, FlushCommands, GL_SYNC_FLUSH_COMMANDS_BIT)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(GraphicsSyncMask));


}


void GenerateMeshComponents(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Resource\\Model\\Mesh\\MeshComponents.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_5(MeshComponents, Vertex, Normal, Color, Texcoord, Index);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_5(MeshComponents, Vertex, Normal, Color, Texcoord, Index)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(MeshComponents));


}

void GenerateRenderingFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Rendering\\RenderingFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_1(RenderingFlags, KeepRenderTarget);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_1(RenderingFlags, KeepRenderTarget)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(RenderingFlags));


}


void GenerateRenderPassFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\RenderPassFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_1(RenderPassFlags, SuppressWorldViewProjectMatrixUniform);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_1(RenderPassFlags, SuppressWorldViewProjectMatrixUniform)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(RenderPassFlags));


}


void GenerateBufferObjectChangeFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Graphics\\Buffer\\BufferObjectChangeFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_4(BufferObjectChangeFlags,Vertex,TexCoord,Color,Indices);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_4(BufferObjectChangeFlags, Vertex, TexCoord, Color, Indices)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(BufferObjectChangeFlags));


}


void GenerateGestureFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Node\\Input\\Gesture\\GestureFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_2(GestureFlags,SuppressTouchBegan,SuppressAudio);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_2(GestureFlags, SuppressTouchBegan, SuppressAudio)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(GestureFlags));


}


void GenerateLayerCreateFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Node\\Layer\\LayerCreateFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_1(LayerCreateFlags,AlwaysCreate);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_1(LayerCreateFlags, AlwaysCreate)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(LayerCreateFlags));


}

void GenerateLayerDeleteFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Node\\Layer\\LayerDeleteFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_1(LayerDeleteFlags,Async);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_1(LayerDeleteFlags, Async)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(LayerDeleteFlags));


}

void GenerateLayerPushFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Node\\Layer\\LayerPushFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_6(LayerPushFlags,ShowPrevLayer,SuppressUpdateLogic,AlwaysCreate,DisableTouch,HideAllPrevLayers,SaveStatusBeforePush);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_6(LayerPushFlags, ShowPrevLayer, SuppressUpdateLogic, AlwaysCreate, DisableTouch, HideAllPrevLayers, SaveStatusBeforePush)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(LayerPushFlags));


}

void GenerateLayerPopFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Node\\Layer\\LayerPopFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_7(LayerPopFlags,ShowCurrentLayer,SuppressUpdateLogic,DisableTouch,IgnorePrevLayer,DeleteCurrentLayer,DeleteCurrentLayerAsync,RestoreStatusAfterPop);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_7(LayerPopFlags, ShowCurrentLayer, SuppressUpdateLogic, DisableTouch, IgnorePrevLayer, DeleteCurrentLayer, DeleteCurrentLayerAsync, RestoreStatusAfterPop)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(LayerPopFlags));


}

void GenerateScenePushFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Node\\Scene\\ScenePushFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_4(ScenePushFlags,ShowPrevScene,SuppressUpdateLogic,DisableTouch,HideAllPrevScenes);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_4(ScenePushFlags, ShowPrevScene, SuppressUpdateLogic, DisableTouch, HideAllPrevScenes)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(ScenePushFlags));


}

void GenerateScenePopFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Node\\Scene\\ScenePopFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_6(ScenePopFlags,ShowCurrentScene, SuppressUpdateLogic, DisableTouch, IgnorePrevScene, DeleteCurrentScene, DeleteCurrentSceneAsync);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_6(ScenePopFlags, ShowCurrentScene, SuppressUpdateLogic, DisableTouch, IgnorePrevScene, DeleteCurrentScene, DeleteCurrentSceneAsync)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(ScenePopFlags));


}

void GenerateNodeLayoutArrangeFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Node\\NodeLayoutArrangeFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_2(NodeLayoutArrangeFlags, SuppressArrangeSelf, SuppressArrangeChildren);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_2(NodeLayoutArrangeFlags, SuppressArrangeSelf, SuppressArrangeChildren)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(NodeLayoutArrangeFlags));


}

void GenerateNodeLayoutChangedFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Node\\NodeLayoutChangedFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_8(NodeLayoutChangedFlags, SizeChanged, ChildAdded, ChildRemoved, ChildCleard, ChildOrderChanged,PositionChanged,ArrangeChanged,CollapseChanged);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_8(NodeLayoutChangedFlags, SizeChanged, ChildAdded, ChildRemoved, ChildCleard, ChildOrderChanged, PositionChanged, ArrangeChanged, CollapseChanged)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(NodeLayoutChangedFlags));


}

void GenerateNodeRemoveFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Node\\NodeRemoveFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_2(NodeRemoveFlags, OnlyChildren, OnlyManaged);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_2(NodeRemoveFlags, OnlyChildren, OnlyManaged)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(NodeRemoveFlags));


}

void GenerateNodeUpdateFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Node\\NodeUpdateFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_2(NodeUpdateFlags, SuppressRunningAction, SuppressDispatchingInput);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_2(NodeUpdateFlags, SuppressRunningAction, SuppressDispatchingInput)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(NodeUpdateFlags));


}

void GenerateNodeVisitFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Node\\NodeVisitFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_2(NodeVisitFlags, ForceUpdateWorldMatrix, ForceUpdateWorldColor);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_2(NodeVisitFlags, ForceUpdateWorldMatrix, ForceUpdateWorldColor)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(NodeVisitFlags));


}


void GenerateRenderableChangedFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Rendering\\RenderableChangedFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_8(RenderableChangedFlags, RenderQueueChanged,BatchChanged,DataTotalChanged, NewVertex, NewNormal, NewTexCoord, NewColor, NewIndex);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_8(RenderableChangedFlags, RenderQueueChanged, BatchChanged, DataTotalChanged, NewVertex, NewNormal, NewTexCoord, NewColor, NewIndex)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(RenderableChangedFlags));


}

void GenerateApplicationDebugInfoFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Application\\ApplicationDebugInfoFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_3(ApplicationDebugInfoFlags, Performance, GPU, Touch);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_3(ApplicationDebugInfoFlags, Performance, GPU, Touch)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(ApplicationDebugInfoFlags));


}

void GenerateFontMarkupFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Resource\\Font\\FontMarkupFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_7(FontMarkupFlags,IsItalic,IsBold,HasUnderLine,HasOverline,HasStrikethrough,DisableAutoHint,DisableKerning);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_7(FontMarkupFlags, IsItalic, IsBold, HasUnderLine, HasOverline, HasStrikethrough, DisableAutoHint, DisableKerning)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(FontMarkupFlags));


}

void GenerateFontFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Resource\\Font\\FontFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_6(FontFlags,HasHorizontal,HasVertical,HasKerning,IsScalable,IsItalic,IsBold);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_6(FontFlags, HasHorizontal, HasVertical, HasKerning, IsScalable, IsItalic, IsBold)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(FontFlags));


}

void GeneratePngImageColorType(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Resource\\Image\\PngImageColorType.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_CUSTOM_5(PngImageColorType,Grey,0,RGB,2,Palette,3,GreyWithAlpha,4,RGBA,6);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_CUSTOM_5(PngImageColorType, Grey, 0, RGB, 2, Palette, 3, GreyWithAlpha, 4, RGBA, 6)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(PngImageColorType));


}



void GeneratePODAnimiationFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Resource\\Model\\Scene\\PODAnimiationFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_4(PODAnimiationFlags,HasPosition,HasRotation,HasScale,HasMatrix);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_4(PODAnimiationFlags, HasPosition, HasRotation, HasScale, HasMatrix)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(PODAnimiationFlags));


}

void GenerateModelLoadingOptions(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Resource\\Model\\ModelLoadingOptions.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_3(ModelLoadingOptions,NoCameraAnimation,NoSkeletonAnimation,NoLightAnimation);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_3(ModelLoadingOptions, NoCameraAnimation, NoSkeletonAnimation, NoLightAnimation)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(ModelLoadingOptions));


}

void GenerateFlipMask(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\Geometry\\FlipMask.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_3(FlipMask, X, Y, Z);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_3(FlipMask, X, Y, Z)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(FlipMask));


}

void GenerateMatrixFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\Geometry\\MatrixFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_2(MatrixFlags, Affine, Is2D);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_2(MatrixFlags, Affine, Is2D)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(MatrixFlags));


}

void GenerateMoveableInheritFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\Geometry\\MoveableInheritFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_3(MoveableInheritFlags, IgnoreScale, IgnoreRotation, IgnoreFlip);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_3(MoveableInheritFlags, IgnoreScale, IgnoreRotation, IgnoreFlip)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(MoveableInheritFlags));


}

void GenerateMoveableChangedFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\Geometry\\MoveableChangedFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_9(MoveableChangedFlags, SizeChanged, PositionChanged, RotationChanged, ScaleChanged, AnchorChanged, FlipChanged, MatrixChanged, WorldMatrixChanged,InheritChanged);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_9(MoveableChangedFlags, SizeChanged, PositionChanged, RotationChanged, ScaleChanged, AnchorChanged, FlipChanged, MatrixChanged, WorldMatrixChanged, InheritChanged)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(MoveableChangedFlags));


}

void GenerateOrientationMask(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\Geometry\\OrientationMask.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_CUSTOM_7(OrientationMask,Up, 1,Down, 2,Left, 4,Right, 8,UpAndDown, 3,LeftAndRight, 12,AllButDown, 13);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_CUSTOM_7(OrientationMask, Up, 1, Down, 2, Left, 4, Right, 8, UpAndDown, 3, LeftAndRight, 12, AllButDown, 13)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(OrientationMask));


}

void GeneratePackageFlags(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\IO\\Package\\PackageFlags.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_4(PackageFlags,Readonly,EncryptFileNames,WriteSaltData,WholeFileCoding);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_4(PackageFlags, Readonly,EncryptFileNames,WriteSaltData,WholeFileCoding)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(PackageFlags));


}

void GenerateLogLevel(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\Log\\LogLevel.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_CUSTOM_2(LogLevel,Info,0x1,Error,0x2);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_CUSTOM_2(LogLevel, Info, 0x1, Error, 0x2)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(LogLevel));


}

void GenerateMessageErrorReportSuppress(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = corePath + "Core\\Message\\MessageErrorReportSuppress.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaCorePreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//STRONG_FLAGS_6(MessageErrorReportSuppress,ConnectFail,AuthFailed,ServerFailed,SwitchUI,UpdateLogic,HideActivityIndicator);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_6(MessageErrorReportSuppress, ConnectFail, AuthFailed, ServerFailed, SwitchUI, UpdateLogic, HideActivityIndicator)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(MessageErrorReportSuppress));


}

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

void GenerateEngineFeatures(StringRef corePath, StringRef medusaPath)
{
	const HeapString path = medusaPath + "Platform\\EngineFeatures.h";

	HeapString str;
	str.AppendLine("#pragma once");
	str.AppendLine("//[IGNORE_PRE_DECLARE_FILE]");
	str.AppendLine("#include \"MedusaPreDeclares.h\"");
	str.AppendLine("#include \"Core/String/StringRef.h\"");
	str.AppendLine("#include \"Core/String/StringParser.h\"");
	str.AppendLine("#include \"Core/String/HeapString.h\"");
	str.AppendLine("MEDUSA_BEGIN;");
	str.AppendLine("//EngineFeatures, MultipleThreadUpdating,MultipleThreadRendering);");
	str.AppendLine(MACRO_TO_STRING(STRONG_FLAGS_2(EngineFeatures, MultipleThreadUpdating, MultipleThreadRendering)));
	str.AppendLine("MEDUSA_END;");


	AdjustFlagStr(str, path, MACRO_TO_STRING(EngineFeatures));


}
#pragma endregion Flags


int _tmain(int argc, _TCHAR* argv[])
{
	System::Instance().Initialize();
	Log::Initialize();
	HeapString appPath = System::Instance().ApplicationPath();
	HeapString rootpath = appPath.SubString(0, appPath.IndexOf("Engine") + 7);

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


	GenerateSirenDataType(corePath, medusaPath);
	GenerateFileUpdaterMessageType(corePath, medusaPath);

	GenerateGraphicsHintMode(corePath, medusaPath);
	GenerateGraphicsBlendEquation(corePath, medusaPath);
	GenerateGraphicsPixelDataType(corePath, medusaPath);
	GenerateGraphicsFuncType(corePath, medusaPath);
	GenerateGraphicsStencilOperation(corePath, medusaPath);
	GenerateGraphicsFrontFace(corePath, medusaPath);
	GenerateGraphicsFace(corePath, medusaPath);
	GenerateSkeletonAttachmentType(corePath, medusaPath);
	GenerateAnalyticsCurrencyType(corePath, medusaExtensionPath);
	GenerateAnalyticsPaymentType(corePath, medusaExtensionPath);
	GenerateAnalyticsRewardType(corePath, medusaExtensionPath);


	GenerateGameFeatures(corePath, medusaPath);
	GenerateGraphicsBufferComponentMask(corePath, medusaPath);
	GenerateGraphicsColorMask(corePath, medusaPath);
	GenerateGraphicsMapBufferMask(corePath, medusaPath);
	GenerateGraphicsSyncMask(corePath, medusaPath);
	GenerateMeshComponents(corePath, medusaPath);
	GenerateRenderingFlags(corePath, medusaPath);
	GenerateRenderPassFlags(corePath, medusaPath);
	GenerateBufferObjectChangeFlags(corePath, medusaPath);
	GenerateGestureFlags(corePath, medusaPath);
	GenerateLayerCreateFlags(corePath, medusaPath);
	GenerateLayerDeleteFlags(corePath, medusaPath);
	GenerateLayerPushFlags(corePath, medusaPath);
	GenerateLayerPopFlags(corePath, medusaPath);

	GenerateScenePushFlags(corePath, medusaPath);
	GenerateScenePopFlags(corePath, medusaPath);

	GenerateNodeLayoutArrangeFlags(corePath, medusaPath);
	GenerateNodeLayoutChangedFlags(corePath, medusaPath);
	GenerateNodeRemoveFlags(corePath, medusaPath);
	GenerateNodeUpdateFlags(corePath, medusaPath);
	GenerateNodeVisitFlags(corePath, medusaPath);



	GenerateRenderableChangedFlags(corePath, medusaPath);
	GenerateApplicationDebugInfoFlags(corePath, medusaPath);


	GenerateFontMarkupFlags(corePath, medusaPath);
	GenerateFontFlags(corePath, medusaPath);
	GeneratePngImageColorType(corePath, medusaPath);
	GeneratePODAnimiationFlags(corePath, medusaPath);
	GenerateModelLoadingOptions(corePath, medusaPath);

	GenerateFlipMask(corePath, medusaPath);
	GenerateMatrixFlags(corePath, medusaPath);
	GenerateMoveableInheritFlags(corePath, medusaPath);
	GenerateMoveableChangedFlags(corePath, medusaPath);
	GenerateOrientationMask(corePath, medusaPath);

	GeneratePackageFlags(corePath, medusaPath);
	GenerateLogLevel(corePath, medusaPath);
	GenerateMessageErrorReportSuppress(corePath, medusaPath);


	GeneratePublishVersions(corePath, medusaPath);
	GeneratePublishDevices(corePath, medusaPath);
	GeneratePublishLanguages(corePath, medusaPath);

	GenerateEngineFeatures(corePath, medusaPath);

	return 0;
}
