// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeList.h"



#define SIREN_COMMON(Type) \
bool operator<(const Type&)const { assert(false);return true; }\
bool operator==(const Type&)const { assert(false);return true; }




#define SIREN_METHOD(Type,Name) \
const Type& Name() const { return m##Name; }\
Type& Mutable##Name() { return m##Name; }\
void Set##Name(const Type& val) { m##Name = val; }

#define SIREN_METHOD_LIST(Type,Name) \
const List<Type>& Name() const { return m##Name; }\
List<Type>& Mutable##Name() { return m##Name; }\
size_t Name##Count() const { return m##Name.Count(); }\
void Add##Name(Type const& val) { m##Name.Add(val); }\
Type& New##Name(){return m##Name.NewAdd();}\
void Set##Name(const List<Type>& val) { m##Name = val; }

#define SIREN_METHOD_DICTIONARY(Key,Value,Name) \
const Dictionary<Key,Value>& Name() const { return m##Name; }\
Dictionary<Key,Value>& Mutable##Name() { return m##Name; }\
size_t Name##Count() const { return m##Name.Count(); }\
void Add##Name(Key const& key,Value& val) { m##Name.Add(key,val); }\
void Set##Name(const Dictionary<Key,Value>& val) { m##Name = val; }


#define SIREN_METHOD_DICTIONARY_EX(Key,Value,Name) \
const Dictionary<Key,Value>& Name() const { return m##Name; }\
Dictionary<Key,Value>& Mutable##Name() { return m##Name; }\
size_t Name##Count() const { return m##Name.Count(); }\
void Add##Name(Key const& key,Value& val) { m##Name.Add(key,val); }\
void Set##Name(const Dictionary<Key,Value>& val) { m##Name = val; }\
Value* Find(const Key& key){return m##Name.TryGet(key);}\
const Value* Find(const Key& key)const { return m##Name.TryGet(key); }

#define SIREN_METHOD_PTR(Type,Name)		\
bool Has##Name() const { return m##Name != nullptr; }\
Type& Mutable##Name() { if (m##Name == nullptr) { m##Name = new Type(); }return *m##Name; }\
void Delete##Name() { SAFE_DELETE(m##Name); }\
const Type& Name() const { return *m##Name; }\
const Type& Name##OrDefault(const Type& val) const { if (m##Name != nullptr){return *m##Name;}return val; }\
void Set##Name(const Type& val) { if (m##Name == nullptr) { m##Name = new Type(); }*m##Name = val; }

#define SIREN_FIELD(Index,Id,Modifier,ClassType,FieldType,Name) typedef SirenFieldInfo<Id,SirenFieldModifier::Modifier,ClassType, FieldType, &ClassType::Name> Field##Index;
#define SIREN_FIELD_LIST(Index,Id,Modifier,ClassType,FieldType,Name) typedef SirenFieldInfo<Id,SirenFieldModifier::Modifier,ClassType, List<FieldType>, &ClassType::Name,FieldType> Field##Index;
#define SIREN_FIELD_DICTIONARY(Index,Id,Modifier,ClassType,KeyType,ValueType,Name) typedef SirenFieldInfo<Id,SirenFieldModifier::Modifier,ClassType, Dictionary<KeyType,ValueType>, &ClassType::Name,KeyType,ValueType> Field##Index;


#define SIREN_METADATA(ClassType,NameLength) MEDUSA_WEAK_MULTIPLE_DEFINE const ClassType::Schema::MetadataType ClassType::Schema::Metadata(#ClassType, NameLength);
#define SIREN_FIELD_METADATA(Index,ClassType,Name,NameLength,Default,HasDefault) template<> MEDUSA_WEAK_MULTIPLE_DEFINE  const ClassType::Schema::Field##Index::MetadataType ClassType::Schema::Field##Index::Metadata(#Name, NameLength,Default,HasDefault);
#define SIREN_FIELD_METADATA_STRUCT(Index,ClassType,Name,NameLength) template<>  MEDUSA_WEAK_MULTIPLE_DEFINE  const ClassType::Schema::Field##Index::MetadataType ClassType::Schema::Field##Index::Metadata(#Name,NameLength);



#define SIREN_FIELDS_BASE(Base,This) typedef Base BaseType;typedef This ClassType; typedef SirenTraits<This>::MetadataType MetadataType; const static MetadataType Metadata;
#define SIREN_FIELDS_0(Base,This) typedef Compile::Typelist<void> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_1(Base,This) typedef Compile::Typelist<Field0> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_2(Base,This) typedef Compile::Typelist<Field0,Field1> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_3(Base,This) typedef Compile::Typelist<Field0,Field1,Field2> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_4(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_5(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_6(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_7(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_8(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_9(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_10(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_11(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_12(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_13(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_14(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12,Field13> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_15(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12,Field13,Field14> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_16(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12,Field13,Field14,Field15> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_17(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12,Field13,Field14,Field15,Field16> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_18(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12,Field13,Field14,Field15,Field16,Field17> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_19(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12,Field13,Field14,Field15,Field16,Field17,Field18> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_20(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12,Field13,Field14,Field15,Field16,Field17,Field18,Field19> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_21(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12,Field13,Field14,Field15,Field16,Field17,Field18,Field19,Field20> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_22(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12,Field13,Field14,Field15,Field16,Field17,Field18,Field19,Field20,Field21> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_23(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12,Field13,Field14,Field15,Field16,Field17,Field18,Field19,Field20,Field21,Field22> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_24(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12,Field13,Field14,Field15,Field16,Field17,Field18,Field19,Field20,Field21,Field22,Field23> Fields;SIREN_FIELDS_BASE(Base,This);
#define SIREN_FIELDS_25(Base,This) typedef Compile::Typelist<Field0,Field1,Field2,Field3,Field4,Field5,Field6,Field7,Field8,Field9,Field10,Field11,Field12,Field13,Field14,Field15,Field16,Field17,Field18,Field19,Field20,Field21,Field22,Field23,Field24> Fields;SIREN_FIELDS_BASE(Base,This);



