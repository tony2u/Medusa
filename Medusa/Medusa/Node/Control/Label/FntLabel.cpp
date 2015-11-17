// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "FntLabel.h"
#include "Resource/ResourceNames.h"
#include "Resource/Font/IFont.h"
#include "Resource/Material/IMaterial.h"
#include "Core/String/StringParser.h"
#include "Resource/Font/TextLayout/TextLayouter.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Model/Mesh/Font/FntTextMesh.h"
#include "Node/Sprite/Sprite.h"
#include "Resource/Effect/EffectFactory.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


FntLabel::FntLabel(StringRef name, IFont* font, Alignment alignment/*=Alignment::LeftBottom*/, Size2F restrictSize/*=Size2F::Zero*/, bool isMultipleLine/*=true*/, bool isStatic/*=false*/)
	:ILabel(name, font, alignment, restrictSize, isMultipleLine, isStatic)
{
	CreateMesh();
}

FntLabel::~FntLabel(void)
{

}

void FntLabel::UpdateMesh()
{
	if (mString.IsEmpty())
	{
		if (mFont->IsSingleMaterial() && mFont->IsFixedMaterial())
		{
			SetMesh(nullptr);
		}

		if (!mManagedNodes.IsEmpty())
		{
			DeleteAllChilds(NodeRemoveFlags::OnlyManaged);
		}
		SetSize(Size2F::Zero);
		mInternalMeshes.Clear();
		return;
	}
	else if (mMesh==nullptr)
	{
		CreateMesh();
	}


	Size2F outSize;

	if (mIsMultipleLine)
	{
		TextLayouter::LayoutMultipleLineText(mInternalMeshes, outSize, *mFont, mString, mAlignment, mRestrictSize, this, mIsStatic);
	}
	else
	{
		TextLayouter::LayoutSingleLineText(mInternalMeshes, outSize, *mFont, mString, mAlignment, mRestrictSize, this, mIsStatic);
	}

	SetSize(outSize);

	//check if there are some mesh has no char after layout,this is rarely hit
	size_t meshCount = mInternalMeshes.Count();
	if (meshCount>1)
	{
		List<size_t> unusedIndices;
		List<INode*> unusedSprites;
		FOR_EACH_SIZE(i, meshCount)
		{
			BaseFontMesh* mesh = mInternalMeshes[i];
			if (!mesh->HasChars())
			{
				unusedIndices.Add(i);
				unusedSprites.Add(mManagedNodes[i]);
			}
		}

		if (!unusedIndices.IsEmpty())
		{
			mInternalMeshes.RemoveIndexes(unusedIndices);

			FOR_EACH_COLLECTION(i, unusedSprites)
			{
				DeleteChild(*i);
			}
		}

	}
	

}

void FntLabel::OnUpdateFont()
{
	DeleteAllChilds(NodeRemoveFlags::OnlyManaged);

	if (mFont == nullptr)
	{
		SetMesh(nullptr);
		SetSize(Size3F::Zero);
		mInternalMeshes.Clear();

		return;
	}
	else
	{
		CreateMesh();
	}


}

BaseFontMesh* FntLabel::CreateFontMesh(IMaterial* material, bool isStatic /*= false*/)
{
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::FntFont);
	FntTextMesh* mesh = new FntTextMesh(effect, material, isStatic);
	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	mInternalMeshes.Add(mesh);
	sprite->EnableManaged();
	AddChild(sprite);

	return mesh;
}

Point2F FntLabel::GetCharPosition(uint charIndex) const
{
	BaseFontMesh* mesh = nullptr;
	if (mFont->IsSingleMaterial() && mFont->IsFixedMaterial())
	{
		mesh = (BaseFontMesh*)mMesh;
	}

	if (mManagedNodes.Count()==1)
	{
		mesh = (BaseFontMesh*)mManagedNodes[0]->Mesh();
	}

	if (mesh!=nullptr)
	{
		return mesh->GetCharPosition(charIndex);
	}

	Log::AssertFailed("Only support single material now");
	return Point2F::Zero;
}

Point2F FntLabel::GetCursorPosition(uint charIndex) const
{
	BaseFontMesh* mesh = nullptr;
	if (mFont->IsSingleMaterial() && mFont->IsFixedMaterial())
	{
		mesh = (BaseFontMesh*)mMesh;
	}

	if (mManagedNodes.Count() == 1)
	{
		mesh = (BaseFontMesh*)mManagedNodes[0]->Mesh();
	}

	if (mesh != nullptr)
	{
		return mesh->GetCursorPosition(charIndex);
	}

	Log::AssertFailed("Only support single material now");
	return Point2F::Zero;
}

uint FntLabel::FindCharIndex(const Point2F& touchPosition, Point2F& outCharPosition) const
{
	BaseFontMesh* mesh = nullptr;
	if (mFont->IsSingleMaterial() && mFont->IsFixedMaterial())
	{
		mesh = (BaseFontMesh*)mMesh;
	}

	if (mManagedNodes.Count() == 1)
	{
		mesh = (BaseFontMesh*)mManagedNodes[0]->Mesh();
	}

	if (mesh != nullptr)
	{
		return mesh->FindCharIndex(touchPosition,outCharPosition);
	}

	Log::AssertFailed("Only support single material now");
	return Math::UIntMaxValue;
}

void FntLabel::CreateMesh()
{
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::FntFont);
	const List<IMaterial*>& materials = mFont->Materials();

	if (mFont->IsSingleMaterial() && mFont->IsFixedMaterial())
	{
		IMaterial* material = materials[0];
		FntTextMesh* mesh = new FntTextMesh(effect, material, mIsStatic);
		SetMesh(mesh);
		mInternalMeshes.Add(mesh);
	}
	else
	{
		size_t count = materials.Count();
		FOR_EACH_SIZE(i, count)
		{
			IMaterial* material = materials[i];
			Sprite* sprite = new Sprite();
			sprite->SetMesh(new FntTextMesh(effect, material, mIsStatic));

			mInternalMeshes.Add((BaseFontMesh*)sprite->Mesh());
			sprite->EnableManaged();

			AddChild(sprite);
		}
	}

}

MEDUSA_IMPLEMENT_RTTI(FntLabel, ILabel);



MEDUSA_END;
