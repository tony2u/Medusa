// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/IO/FileIdRef.h"
#include "Core/Siren/Siren.h"

MEDUSA_BEGIN;

class FileId
{
public:
	struct Schema;
	FileId() :Order(0) {}
	FileId(const StringRef& name, uint order = 0) :Name(name), Order(order) {}

	FileId(const FileIdRef& other) :Name(other.Name), Order(other.Order) {}
	FileId(const FileId& other) :Name(other.Name), Order(other.Order) {}
	FileId(FileId&& other) :Name(std::move(other.Name)), Order(other.Order) {}
	FileId(FileIdRef&& other) :Name(std::move(other.Name)), Order(other.Order) {}

	FileId& operator=(const FileId& other) { Name = other.Name; Order = other.Order; return *this; }
	FileId& operator=(FileId&& other) { Name = std::move(other.Name); Order = other.Order; return *this; }
	FileId& operator=(const FileIdRef& other) { Name = other.Name; Order = other.Order; return *this; }
	FileId& operator=(FileIdRef&& other) { Name = std::move(other.Name); Order = other.Order; return *this; }


	~FileId() {}
	bool operator<(const FileId& fileId)const;
	
	

	bool operator==(const FileId& fileId)const { return Name == fileId.Name && Order == fileId.Order; }
	bool operator!=(const FileId& fileId)const { return Name != fileId.Name || Order != fileId.Order ; }
	bool operator==(const FileIdRef& fileId)const { return Name == fileId.Name && Order == fileId.Order; }
	bool operator!=(const FileIdRef& fileId)const { return Name != fileId.Name || Order != fileId.Order; }

	bool IsValid()const { return !Name.IsEmpty(); }
	void Reset() { Name.Clear(); Order = 0; }

	FileIdRef ToRef()const { return FileIdRef(Name, Order); }
	operator FileIdRef()const { return FileIdRef(Name, Order); }

	intp HashCode()const
	{
		return Name.HashCode() ^ Order;
	}

	static FileId ParseFrom(const StringRef& name);
	HeapString ToString(const PublishTarget& tag = PublishTarget::MatchAll)const;

public:
	HeapString Name;
	uint Order;
	const static FileId Empty;
};

struct FileId::Schema
{
	SIREN_PROPERTY(0, 0, Required, FileId, HeapString, Name);
	SIREN_PROPERTY(1, 1, Optional, FileId, uint, Order);
	SIREN_PROPERTIES_2(void, FileId);
};


MEDUSA_END;
