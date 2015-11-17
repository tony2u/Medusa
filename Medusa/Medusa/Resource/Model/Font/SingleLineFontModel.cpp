// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SingleLineFontModel.h"
#include "Core/String/StringParser.h"
#include "Core/Log/Log.h"
#include "Resource/Font/TextLayout/TextLayouter.h"
#include "Resource/Model/Mesh/Font/FntTextMesh.h"


MEDUSA_BEGIN;

SingleLineFontModel::SingleLineFontModel( IFont* font,Alignment alignment/*=Alignment::LeftBottom*/,Size2U restrictSize/*=Size2U::Zero*/)
	:BaseFontModel(font,alignment,restrictSize)
{
}


SingleLineFontModel::~SingleLineFontModel(void)
{
	
}


void SingleLineFontModel::SetText( StringRef text )
{
	RETURN_IF_EMPTY(text);

	WHeapString wText= StringParser::ToW(text);
	SetText(wText);
}

void SingleLineFontModel::SetText( WStringRef text )
{
	RETURN_IF_EQUAL(mText,text);
	mText=text;
	RemoveAllMeshes();
	ResetCachedMeshes();

	RETURN_IF_EMPTY(mText);

	Size2F outSize;
	List<BaseFontMesh*> meshes;

	TextLayouter::LayoutSingleLineText(meshes,outSize,*mFont,mText,mAlignment,mRestrictSize);

	//AddMeshes(meshes);
	SetSize(outSize);
}


MEDUSA_END;