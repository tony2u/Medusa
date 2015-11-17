// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/IO/FileId.h"

MEDUSA_BEGIN;

struct RenderPassDescription
{
	RenderPassDescription() :Index(0)
	{

	}
	RenderPassDescription(StringRef name, const FileIdRef& vertexShaderFile, const FileIdRef& pixelShaderFile, int index = 0, const ICollection<HeapString>* defines = nullptr)
		:Name(name), VertexShaderFile(vertexShaderFile), PixelShaderFile(pixelShaderFile), Index(index)
	{
		if (defines != nullptr)
		{
			Defines.AddRange(*defines);
		}
	}

	HeapString Name;
	FileId VertexShaderFile;
	FileId PixelShaderFile;
	int Index;
	List<HeapString> Defines;
};

MEDUSA_END;