// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/PFXEffect.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/Stream/MemoryStream.h"

MEDUSA_BEGIN;

PFXEffect::PFXEffect(const FileIdRef& fileId):IEffect(fileId)
{

}

PFXEffect::~PFXEffect()
{
}

PFXEffect* PFXEffect::CreateFromFile( const FileIdRef& fileId )
{
	/*List<HeapString> allLines;
	if(FileSystem::Instance().ReadFileAllLinesTo(name,allLines))
	{
	return CreateFromLines(name,allLines);
	}
	return nullptr;*/
	return nullptr;
}

PFXEffect* PFXEffect::CreateFromData( const FileIdRef& fileId,MemoryData data )
{
	MemoryStream stream(data);
	List<HeapString> allLines;

	stream.ReadAllLinesTo(allLines);
	if (!allLines.IsEmpty())
	{
		return CreateFromLines(fileId,allLines);
	}
	return nullptr;
}

PFXEffect* PFXEffect::CreateFromLines( const FileIdRef& fileId,const List<HeapString>& lines )
{
	return nullptr;
}

MEDUSA_END;