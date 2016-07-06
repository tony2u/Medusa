// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SQL
#include "SqlDefines.h"
#include "Core/Collection/List.h"
#include "Core/String/HeapString.h"
#include "Core/String/StringParser.h"
#include "Core/Siren/Siren.h"
#include "Core/Siren/Code/Sql/SirenSqlFieldChecker.h"
#include "Core/Siren/Serialization/SirenSchemaChecker.h"
#include "Core/Siren/Code/Sql/SirenSqlPreparedWriter.h"
#include "Core/Siren/Code/Sql/SirenSqlPreparedReader.h"


//[IGNORE_PRE_DECLARE_FILE]

MEDUSA_BEGIN;

namespace SqlBinder
{
	namespace Detail
	{
#pragma region Check Field Type
		template <uint TIndex, typename T>
		struct CheckFieldTypeHelper
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				SirenSqlFieldChecker checker(fields + TIndex, fieldCount - TIndex, Siren::GetFieldCount<T>::value);
				SirenSchemaChecker::Visit<SirenSqlFieldChecker, T>(checker);
			}
		};

		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, bool>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_BIT, "Invalid field type:{} to bool", field.type);
			}
		};

		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, char>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_TINY && ((field.flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to char", field.type);

			}
		};

		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, byte>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_TINY && ((field.flags&UNSIGNED_FLAG) != 0), "Invalid field type:{} to byte", field.type);
			}
		};


		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, short>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_SHORT && ((field.flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to short", field.type);
			}
		};

		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, ushort>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_SHORT && ((field.flags&UNSIGNED_FLAG) != 0), "Invalid field type:{} to ushort", field.type);
			}
		};

		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, int>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_LONG && ((field.flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to int", field.type);
			}
		};

		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, uint>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_LONG && ((field.flags&UNSIGNED_FLAG) != 0), "Invalid field type:{} to uint", field.type);
			}
		};

		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, int64>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_LONGLONG && ((field.flags&UNSIGNED_FLAG) == 0), "Invalid field type:{} to int64", field.type);
			}
		};

		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, uint64>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_LONGLONG && ((field.flags&UNSIGNED_FLAG) != 0), "Invalid field type:{} to uint64", field.type);
			}
		};


		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, float>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_FLOAT, "Invalid field type:{} to float", field.type);
			}
		};


		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, double>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_DOUBLE, "Invalid field type:{} to double", field.type);
			}
		};

		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, HeapString>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_VAR_STRING ||
					field.type == MYSQL_TYPE_STRING ||
					field.type == MYSQL_TYPE_VARCHAR, "Invalid field type:{} to HeapString", field.type);
			}
		};


		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, MemoryData>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(field.type == MYSQL_TYPE_BLOB ||
					field.type == MYSQL_TYPE_TINY_BLOB ||
					field.type == MYSQL_TYPE_MEDIUM_BLOB ||
					field.type == MYSQL_TYPE_LONG_BLOB, "Invalid field type:{} to MemoryData", field.type);
			}
		};

		template <uint TIndex>
		struct CheckFieldTypeHelper<TIndex, DateTime>
		{
			static void Run(const MYSQL_FIELD* fields, uint fieldCount)
			{
				auto& field = fields[TIndex];
				Log::AssertOrThrow<SqlException>(, "Invalid field type:{} to char", field.type);
				return field.type == MYSQL_TYPE_TIMESTAMP ||
					field.type == MYSQL_TYPE_DATE ||
					field.type == MYSQL_TYPE_TIME ||
					field.type == MYSQL_TYPE_DATETIME;
			}
		};

#pragma endregion Check Field Type

#pragma region Store Text Result
		template <uint TIndex, typename T>
		struct StoreResultHelper
		{
			static bool Run(T& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				return Siren::DeserializeSqlTextTo(row + TIndex, rowLengths + TIndex, fields + TIndex, fieldCount - TIndex, outResult);
			}
		};

		template <uint TIndex>
		struct StoreResultHelper<TIndex, bool>
		{
			static bool Run(bool& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				StringRef val(row[TIndex], (size_t)rowLengths[TIndex]);
				outResult = val == "1";
				return true;
			}
		};

		template <uint TIndex>
		struct StoreResultHelper<TIndex, char>
		{
			static bool Run(char& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				outResult = StringParser::StringTo<char>(StringRef(row[TIndex], (size_t)rowLengths[TIndex]));
				return true;
			}
		};

		template <uint TIndex>
		struct StoreResultHelper<TIndex, byte>
		{
			static bool Run(byte& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				outResult = StringParser::StringTo<byte>(StringRef(row[TIndex], (size_t)rowLengths[TIndex]));
				return true;
			}
		};
		template <uint TIndex>
		struct StoreResultHelper<TIndex, short>
		{
			static bool Run(short& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				outResult = StringParser::StringTo<short>(StringRef(row[TIndex], (size_t)rowLengths[TIndex]));
				return true;
			}
		};

		template <uint TIndex>
		struct StoreResultHelper<TIndex, ushort>
		{
			static bool Run(ushort& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				outResult = StringParser::StringTo<ushort>(StringRef(row[TIndex], (size_t)rowLengths[TIndex]));
				return true;
			}
		};

		template <uint TIndex>
		struct StoreResultHelper<TIndex, int>
		{
			static bool Run(int& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				outResult = StringParser::StringTo<int>(StringRef(row[TIndex], (size_t)rowLengths[TIndex]));
				return true;
			}
		};

		template <uint TIndex>
		struct StoreResultHelper<TIndex, uint>
		{
			static bool Run(uint& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				outResult = StringParser::StringTo<uint>(StringRef(row[TIndex], (size_t)rowLengths[TIndex]));
				return true;
			}
		};


		template <uint TIndex>
		struct StoreResultHelper<TIndex, int64>
		{
			static bool Run(int64& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				outResult = StringParser::StringTo<int64>(StringRef(row[TIndex], (size_t)rowLengths[TIndex]));
				return true;
			}
		};


		template <uint TIndex>
		struct StoreResultHelper<TIndex, uint64>
		{
			static bool Run(uint64& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				outResult = StringParser::StringTo<uint64>(StringRef(row[TIndex], (size_t)rowLengths[TIndex]));
				return true;
			}
		};

		template <uint TIndex>
		struct StoreResultHelper<TIndex, float>
		{
			static bool Run(float& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				outResult = StringParser::StringTo<float>(StringRef(row[TIndex], (size_t)rowLengths[TIndex]));
				return true;
			}
		};

		template <uint TIndex>
		struct StoreResultHelper<TIndex, double>
		{
			static bool Run(double& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				outResult = StringParser::StringTo<double>(StringRef(row[TIndex], (size_t)rowLengths[TIndex]));
				return true;
			}
		};

		template <uint TIndex>
		struct StoreResultHelper<TIndex, HeapString>
		{
			static bool Run(HeapString& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				StringRef val(row[TIndex], (size_t)rowLengths[TIndex]);
				outResult = val;
				return true;
			}
		};

		template <uint TIndex>
		struct StoreResultHelper<TIndex, MemoryData>
		{
			static bool Run(MemoryData& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				outResult = MemoryData::CopyFrom((const byte*)row[TIndex], (size_t)rowLengths[TIndex]);
				return true;
			}
		};
		template <uint TIndex>
		struct StoreResultHelper<TIndex, DateTime>
		{
			static bool Run(DateTime& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
			{
				StringRef val(row[TIndex], (size_t)rowLengths[TIndex]);
				outResult = outResult.Parse(val);
				return true;
			}
		};

#pragma endregion Store Text Result

#pragma region Bind Parameter

		//bind.length = nullptr
		//length is ignored for numeric and temporal data types because the buffer_type value determines the length of the data value.

		template <uint TIndex, typename T>
		struct BindParameterHelper
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const T& arg)
			{
				SirenSqlPreparedWriter writer(binds, TIndex);
				SirenSchemaSerializer<false>::Visit(writer, arg);
			}
		};

		template <uint TIndex>
		struct BindParameterHelper<TIndex, bool>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const bool& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_BIT;
				bind.buffer = (void*)&arg;
				bind.buffer_length = sizeof(arg);
			}
		};

		template <uint TIndex>
		struct BindParameterHelper<TIndex, char>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const char& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_TINY;
				bind.buffer = (void*)&arg;
				bind.buffer_length = sizeof(arg);
			}
		};


		template <uint TIndex>
		struct BindParameterHelper<TIndex, byte>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const byte& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_TINY;
				bind.buffer = (void*)&arg;
				bind.buffer_length = sizeof(arg);
				bind.is_unsigned = 1;

			}
		};

		template <uint TIndex>
		struct BindParameterHelper<TIndex, short>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const short& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_SHORT;
				bind.buffer = (void*)&arg;
				bind.buffer_length = sizeof(arg);
			}
		};

		template <uint TIndex>
		struct BindParameterHelper<TIndex, ushort>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const ushort& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_SHORT;
				bind.buffer = (void*)&arg;
				bind.buffer_length = sizeof(arg);
				bind.is_unsigned = 1;

			}
		};

		template <uint TIndex>
		struct BindParameterHelper<TIndex, int>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const int& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_LONG;
				bind.buffer = (void*)&arg;
				bind.buffer_length = sizeof(arg);
			}
		};


		template <uint TIndex>
		struct BindParameterHelper<TIndex, uint>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const uint& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_LONG;
				bind.buffer = (void*)&arg;
				bind.buffer_length = sizeof(arg);
				bind.is_unsigned = 1;
			}
		};

		template <uint TIndex>
		struct BindParameterHelper<TIndex, int64>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const int64& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_LONGLONG;
				bind.buffer = (void*)&arg;
				bind.buffer_length = sizeof(arg);
			}
		};


		template <uint TIndex>
		struct BindParameterHelper<TIndex, uint64>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const uint64& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_LONGLONG;
				bind.buffer = (void*)&arg;
				bind.buffer_length = sizeof(arg);
				bind.is_unsigned = 1;
			}
		};

		template <uint TIndex>
		struct BindParameterHelper<TIndex, float>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const float& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_FLOAT;
				bind.buffer = (void*)&arg;
				bind.buffer_length = sizeof(arg);
			}
		};

		template <uint TIndex>
		struct BindParameterHelper<TIndex, double>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const double& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_DOUBLE;
				bind.buffer = (void*)&arg;
				bind.buffer_length = sizeof(arg);
			}
		};

		template <uint TIndex>
		struct BindParameterHelper<TIndex, char*>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const char* arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_STRING;
				bind.buffer = (void*)arg;
				bind.buffer_length = strlen(arg);
			}
		};

		template <uint TIndex, size_t size>
		struct BindParameterHelper<TIndex, char[size]>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const char(&arg)[size])
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_STRING;
				bind.buffer = (void*)arg;
				bind.buffer_length = size - 1;
			}
		};

		template <uint TIndex>
		struct BindParameterHelper<TIndex, StringRef>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const StringRef& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_STRING;
				bind.buffer = (void*)arg.c_str();
				bind.buffer_length = (ulong)arg.Length();
			}
		};

		template <uint TIndex>
		struct BindParameterHelper<TIndex, MemoryData>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const MemoryData& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_BLOB;
				bind.buffer = (void*)arg.Data();
				bind.buffer_length = (ulong)arg.ByteSize();
			}
		};

		template <uint TIndex>
		struct BindParameterHelper<TIndex, std::nullptr_t>
		{
			static void Run(NoCompareList<MYSQL_BIND>& binds, const std::nullptr_t& arg)
			{
				MYSQL_BIND& bind = binds[TIndex];
				bind.buffer_type = MYSQL_TYPE_NULL;
				bind.is_null = 1;
			}
		};

#pragma endregion Bind Parameter

#pragma region Bind result 
		template <uint TIndex, typename T, bool isSiren = false>
		struct BindResultHelper;

		template <uint TIndex, typename T>
		struct BindResultHelper<TIndex, T, false>
		{
			static bool Run(T& outResult, NoCompareList<MYSQL_BIND>& binds, const NoCompareList<MYSQL_FIELD*>& fields)
			{
				MYSQL_BIND& bind = binds[TIndex];
				MYSQL_FIELD* field = fields[TIndex];
				CheckFieldTypeHelper<TIndex, T>::Run((const MYSQL_FIELD*)fields.First(), (uint)fields.Count());
				bind.buffer_type = field->type;
				bind.buffer = (void*)&outResult;
				bind.buffer_length = sizeof(T);
				return true;
			}
		};

		template <uint TIndex, typename T>
		struct BindResultHelper<TIndex, T, true>
		{
			static bool Run(T& outResult, NoCompareList<MYSQL_BIND>& binds, const NoCompareList<MYSQL_FIELD*>& fields)
			{
				NoCompareList<MYSQL_BIND> tempBinds;
				tempBinds.ForceSetItems(binds.MutableItems() + TIndex);
				tempBinds.ForceSetSize(binds.Size() - TIndex);
				tempBinds.ForceSetCount(binds.Count() - TIndex);

				NoCompareList<MYSQL_FIELD*> tempFields;
				tempFields.ForceSetItems((MYSQL_FIELD**)fields.Items() + TIndex);
				tempFields.ForceSetSize(fields.Size() - TIndex);
				tempFields.ForceSetCount(fields.Count() - TIndex);


				SirenSqlPreparedReader reader(tempBinds, tempFields, Siren::GetFieldCount<T>::value);
				SirenSchemaDeserializer::Visit(reader, outResult);

				tempBinds.ForceSetItems(nullptr);
				tempFields.ForceSetItems(nullptr);

				return true;
			}
		};

		template <uint TIndex>
		struct BindResultHelper<TIndex, HeapString, false>
		{
			static bool Run(HeapString& outResult, NoCompareList<MYSQL_BIND>& binds, const NoCompareList<MYSQL_FIELD*>& fields)
			{
				MYSQL_BIND& bind = binds[TIndex];
				MYSQL_FIELD* field = fields[TIndex];
				CheckFieldTypeHelper<TIndex, HeapString>::Run((const MYSQL_FIELD*)fields.First(), (uint)fields.Count());
				outResult.ReserveSize(field->length);
				bind.buffer_type = field->type;
				bind.buffer = (void*)outResult.Buffer();
				bind.buffer_length = (ulong)outResult.Size();
				bind.length = (ulong*)outResult.ForceMutableLengthPtr();
				bind.extension = &outResult;
				return true;
			}
		};
		template <uint TIndex>
		struct BindResultHelper<TIndex, MemoryData, false>
		{
			static bool Run(MemoryData& outResult, NoCompareList<MYSQL_BIND>& binds, const NoCompareList<MYSQL_FIELD*>& fields)
			{
				MYSQL_BIND& bind = binds[TIndex];
				MYSQL_FIELD* field = fields[TIndex];
				CheckFieldTypeHelper<TIndex, MemoryData>::Run((const MYSQL_FIELD*)fields.First(), (uint)fields.Count());
				outResult = MemoryData::Alloc(field->length);

				bind.buffer_type = field->type;
				bind.buffer = (void*)outResult.MutableData();
				bind.buffer_length = (ulong)outResult.Size();
				bind.length = (ulong*)outResult.ForceMutableSizePtr();
				bind.extension = &outResult;
				return true;
			}
		};



#pragma endregion Bind result 

		template <typename THead, typename... TTails>
		struct CountArgsHelper :public std::integral_constant<size_t, CountArgsHelper<THead>::value + CountArgsHelper<TTails...>::value>
		{

		};

		template <typename THead>
		struct CountArgsHelper<THead> :public std::integral_constant<size_t, Siren::HasSchema<THead>::value ? Siren::GetFieldCount<THead>::value : 1>
		{

		};

	}

	static void SerializeToString(List<HeapString>& refArgStrings)
	{

	}

	template <typename THead, typename... TTails>
	static std::enable_if_t<!Siren::HasSchema<THead>::value> SerializeToString(List<HeapString>& refArgStrings, const THead& head, const TTails&... args)
	{
		refArgStrings.NewAdd().Format("'{}'", head);
		SerializeToString(refArgStrings, args...);
	}

	template <typename THead, typename... TTails>
	static  std::enable_if_t<Siren::HasSchema<THead>::value> SerializeToString(List<HeapString>& refArgStrings, const THead& head, const TTails&... args)
	{
		refArgStrings.NewAdd() = Siren::SerializeSqlText(head);
		SerializeToString(refArgStrings, args...);
	}

	template <uint TIndex>
	static void CheckFieldTypes(const MYSQL_FIELD* fields, uint fieldCount)
	{
	}

	template <uint TIndex, typename THead, typename... TTails>
	static void CheckFieldTypes(const MYSQL_FIELD* fields, uint fieldCount)
	{
		constexpr uint newIndex = TIndex + CountArgs<THead>::value;
		Detail::CheckFieldTypeHelper<TIndex, THead>::Run(fields, fieldCount);
		CheckFieldTypes<newIndex, TTails...>(fields, fieldCount);
	}

	template <typename... TTails>
	struct CountArgs :public Detail::CountArgsHelper<TTails...>
	{

	};

	template <>
	struct CountArgs<> :public std::integral_constant<size_t, 0>
	{

	};

	template <uint TIndex, typename TTuple>
	static typename std::enable_if<TIndex + 1 == std::tuple_size<TTuple>::value, bool > ::type StoreResults(TTuple& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
	{
		using HeadType = std::tuple_element<TIndex, TTuple>::type;
		return Detail::StoreResultHelper<TIndex, HeadType>::Run(std::get<TIndex>(outResult), row, rowLengths, fields, fieldCount);
	}

	template <uint TIndex, typename TTuple>
	static  typename std::enable_if < TIndex + 1 < std::tuple_size<TTuple>::value, bool > ::type StoreResults(TTuple& outResult, MYSQL_ROW row, ulong* rowLengths, const MYSQL_FIELD* fields, uint fieldCount)
	{
		using HeadType = std::tuple_element<TIndex, TTuple>::type;
		constexpr uint newIndex = TIndex + CountArgs<HeadType>::value;

		return Detail::StoreResultHelper<TIndex, HeadType>::Run(std::get<TIndex>(outResult), row, rowLengths, fields, fieldCount) && StoreResults<newIndex, TTuple>(outResult, row, rowLengths, fields, fieldCount);
	}


	template <uint TIndex>
	static void BindParameters(NoCompareList<MYSQL_BIND>& binds)
	{
	}

	template <uint TIndex, typename THead, typename... TTails>
	static void BindParameters(NoCompareList<MYSQL_BIND>& binds, const THead& head, const TTails&... args)
	{
		Detail::BindParameterHelper<TIndex, THead>::Run(binds, head);
		constexpr uint newIndex = TIndex + CountArgs<THead>::value;

		BindParameters<newIndex, TTails...>(binds, args...);
	}

	template <uint TIndex, typename TTuple>
	static typename std::enable_if<TIndex + 1 == std::tuple_size<TTuple>::value, void > ::type BindParametersFromTuple(NoCompareList<MYSQL_BIND>& binds, TTuple& args)
	{
		using HeadType = std::tuple_element<TIndex, TTuple>::type;
		Detail::BindParameterHelper<TIndex, HeadType>::Run(binds, std::get<TIndex>(args));
	}

	template <uint TIndex, typename TTuple>
	static  typename std::enable_if < TIndex + 1 < std::tuple_size<TTuple>::value, void > ::type BindParametersFromTuple(NoCompareList<MYSQL_BIND>& binds, TTuple& args)
	{
		using HeadType = std::tuple_element<TIndex, TTuple>::type;
		constexpr uint newIndex = TIndex + CountArgs<HeadType>::value;

		Detail::BindParameterHelper<TIndex, HeadType>::Run(binds, std::get<TIndex>(args));
		BindParametersFromTuple<TIndex, TTuple>(binds, args);
	}


	template <uint TIndex, typename TTuple>
	static typename std::enable_if<TIndex + 1 == std::tuple_size<TTuple>::value, void > ::type BindResults(TTuple& outResult, NoCompareList<MYSQL_BIND>& binds, const NoCompareList<MYSQL_FIELD*>& fields)
	{
		using HeadType = std::tuple_element<TIndex, TTuple>::type;
		Detail::BindResultHelper<TIndex, HeadType, Siren::HasSchema<HeadType>::value>::Run(std::get<TIndex>(outResult), binds, fields);
	}

	template <uint TIndex, typename TTuple>
	static  typename std::enable_if < TIndex + 1 < std::tuple_size<TTuple>::value, void > ::type BindResults(TTuple& outResult, NoCompareList<MYSQL_BIND>& binds, const NoCompareList<MYSQL_FIELD*>& fields)
	{
		using HeadType = std::tuple_element<TIndex, TTuple>::type;
		constexpr uint newIndex = TIndex + CountArgs<HeadType>::value;
		Detail::BindResultHelper<TIndex, HeadType, Siren::HasSchema<HeadType>::value>::Run(std::get<TIndex>(outResult), binds, fields);
		BindResults<newIndex>(outResult, binds, fields);
	}


}


MEDUSA_END;
#endif