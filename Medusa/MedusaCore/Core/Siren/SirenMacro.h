// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Compile/TypeList.h"

#define MEDUSA_SIREN_BEGIN namespace Medusa{namespace Siren{
#define MEDUSA_SIREN_END }}


MEDUSA_SIREN_BEGIN;

MEDUSA_SIREN_END;

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
Value* Find(const Key& key){return m##Name.TryGetValue(key);}\
const Value* Find(const Key& key)const { return m##Name.TryGetValue(key); }

#define SIREN_METHOD_PTR(Type,Name)		\
bool Has##Name() const { return m##Name != nullptr; }\
Type& Mutable##Name() { if (m##Name == nullptr) { m##Name = new Type(); }return *m##Name; }\
void Delete##Name() { SAFE_DELETE(m##Name); }\
const Type& Name() const { return *m##Name; }\
const Type& Name##OrDefault(const Type& val) const { if (m##Name != nullptr){return *m##Name;}return val; }\
void Set##Name(const Type& val) { if (m##Name == nullptr) { m##Name = new Type(); }*m##Name = val; }

#define SIREN_PROPERTY(Index,Id,Modifier,ClassType,PropertyType,Name) typedef Siren::PropertyInfo<Id,SirenPropertyModifier::Modifier,ClassType, PropertyType, &ClassType::Name> Property##Index;
#define SIREN_PROPERTY_LIST(Index,Id,Modifier,ClassType,PropertyType,Name) typedef Siren::PropertyInfo<Id,SirenPropertyModifier::Modifier,ClassType, List<PropertyType>, &ClassType::Name,PropertyType> Property##Index;
#define SIREN_PROPERTY_DICTIONARY(Index,Id,Modifier,ClassType,KeyType,ValueType,Name) typedef Siren::PropertyInfo<Id,SirenPropertyModifier::Modifier,ClassType, Dictionary<KeyType,ValueType>, &ClassType::Name,KeyType,ValueType> Property##Index;


#define SIREN_METADATA(ClassType,NameLength) MEDUSA_WEAK_MULTIPLE_DEFINE const ClassType::Schema::MetadataType ClassType::Schema::Metadata(#ClassType, NameLength);
#define SIREN_PROPERTY_METADATA(Index,ClassType,Name,NameLength,Default) template<> MEDUSA_WEAK_MULTIPLE_DEFINE  const ClassType::Schema::Property##Index::MetadataType ClassType::Schema::Property##Index::Metadata(#Name, NameLength,Default);
#define SIREN_PROPERTY_METADATA_STRUCT(Index,ClassType,Name,NameLength) template<>  MEDUSA_WEAK_MULTIPLE_DEFINE  const ClassType::Schema::Property##Index::MetadataType ClassType::Schema::Property##Index::Metadata(#Name,NameLength);



#define SIREN_PROPERTIES_BASE(Base,This) typedef Base BaseType;typedef This ClassType; typedef Siren::SirenTraits<This>::MetadataType MetadataType; const static MetadataType Metadata;
#define SIREN_PROPERTIES_0(Base,This) typedef Compile::Typelist<void> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_1(Base,This) typedef Compile::Typelist<Property0> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_2(Base,This) typedef Compile::Typelist<Property0,Property1> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_3(Base,This) typedef Compile::Typelist<Property0,Property1,Property2> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_4(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_5(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_6(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_7(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_8(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_9(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_10(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_11(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_12(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_13(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_14(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12,Property13> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_15(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12,Property13,Property14> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_16(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12,Property13,Property14,Property15> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_17(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12,Property13,Property14,Property15,Property16> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_18(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12,Property13,Property14,Property15,Property16,Property17> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_19(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12,Property13,Property14,Property15,Property16,Property17,Property18> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_20(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12,Property13,Property14,Property15,Property16,Property17,Property18,Property19> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_21(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12,Property13,Property14,Property15,Property16,Property17,Property18,Property19,Property20> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_22(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12,Property13,Property14,Property15,Property16,Property17,Property18,Property19,Property20,Property21> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_23(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12,Property13,Property14,Property15,Property16,Property17,Property18,Property19,Property20,Property21,Property22> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_24(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12,Property13,Property14,Property15,Property16,Property17,Property18,Property19,Property20,Property21,Property22,Property23> Properties;SIREN_PROPERTIES_BASE(Base,This);
#define SIREN_PROPERTIES_25(Base,This) typedef Compile::Typelist<Property0,Property1,Property2,Property3,Property4,Property5,Property6,Property7,Property8,Property9,Property10,Property11,Property12,Property13,Property14,Property15,Property16,Property17,Property18,Property19,Property20,Property21,Property22,Property23,Property24> Properties;SIREN_PROPERTIES_BASE(Base,This);



