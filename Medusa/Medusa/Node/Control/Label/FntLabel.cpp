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
#include "Resource/Material/MaterialFactory.h"
#include "Resource/TextureAtlas/TextureAtlasPage.h"
#include "Resource/TextureAtlas/TextureAtlas.h"
#include "Resource/Image/IImage.h"
#include "Resource/Font/IFont.h"
#include "Graphics/State/ShaderUniformRenderState.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;


FntLabel::FntLabel(StringRef name, const Share<IFont>& font, Alignment alignment/*=Alignment::LeftBottom*/, Size2F restrictSize/*=Size2F::Zero*/, bool isMultipleLine/*=true*/, bool isStatic/*=false*/)
	:ILabel(name, font, alignment, restrictSize, isMultipleLine, isStatic)
{
	
}

FntLabel::FntLabel(const StringRef& name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	: ILabel(name, e)
{

}

FntLabel::~FntLabel(void)
{
	mInternalMeshes.Clear();
}

void FntLabel::UpdateMesh()
{
	if (mString.IsEmpty())
	{
		ClearMeshData();
		return;
	}

	Size2F outSize;

	if (mIsMultipleLine)
	{
		TextLayouter::LayoutMultipleLineText(mInternalMeshes, mInternalPages, outSize, *mFont, mString, mAlignment, mRestrictSize, this, mIsStatic);
	}
	else
	{
		TextLayouter::LayoutSingleLineText(mInternalMeshes, mInternalPages, outSize, *mFont, mString, mAlignment, mRestrictSize, this, mIsStatic);
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
			auto mesh = mInternalMeshes[i];
			if (!mesh->HasChars())
			{
				unusedIndices.Add(i);
				unusedSprites.Add(mManagedNodes[i]);
			}
		}

		if (!unusedIndices.IsEmpty())
		{
			mInternalMeshes.RemoveIndexes(unusedIndices);
			mInternalPages.RemoveIndexes(unusedIndices);

			FOR_EACH_APPLY(unusedSprites, DeleteChild);
		}

	}
	

}

void FntLabel::OnUpdateFont()
{
	DeleteAllChilds(NodeRemoveFlags::OnlyManaged);
	mInternalPages.Clear();
	mInternalPages.Clear();
	SetMesh(nullptr);
	SetMaterial(nullptr);
	SetSize(Size3F::Zero);

	if (mFont != nullptr)
	{
		CreateMesh();
	}
}

Share<BaseFontMesh> FntLabel::CreateFontMesh(TextureAtlasPage* page, bool isStatic /*= false*/)
{
	Share<FntTextMesh> mesh = new FntTextMesh(isStatic);
	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);

	auto material = CreateLabelMaterial(page->LoadTexture());
	sprite->SetMaterial(material);
	sprite->EnableManaged();
	AddChild(sprite);

	return mesh;
}

Point2F FntLabel::GetCharPosition(uint charIndex) const
{
	Share<BaseFontMesh> mesh;
	if (mFont->HasSinglePage() && mFont->IsFixed())
	{
		mesh = mRenderingObject.Mesh().CastPtr<BaseFontMesh>();
	}

	if (mManagedNodes.Count()==1)
	{
		mesh = mManagedNodes[0]->Mesh().CastPtr<BaseFontMesh>();
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
	Share<BaseFontMesh> mesh = nullptr;
	if (mFont->HasSinglePage() && mFont->IsFixed())
	{
		mesh = mRenderingObject.Mesh().CastPtr<BaseFontMesh>();
	}

	if (mManagedNodes.Count() == 1)
	{
		mesh = mManagedNodes[0]->Mesh().CastPtr<BaseFontMesh>();
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
	Share<BaseFontMesh> mesh = nullptr;
	if (mFont->HasSinglePage() && mFont->IsFixed())
	{
		mesh = mRenderingObject.Mesh().CastPtr<BaseFontMesh>();
	}

	if (mManagedNodes.Count() == 1)
	{
		mesh = mManagedNodes[0]->Mesh().CastPtr<BaseFontMesh>();
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
	auto atlas = mFont->Atlas();

	if (mFont->HasSinglePage() && mFont->IsFixed())
	{
		auto* page = atlas->GetPage(0);
		Share<FntTextMesh> mesh = new FntTextMesh(mIsStatic);
		SetMesh(mesh);
		auto material = CreateLabelMaterial(page->LoadTexture());
		

		SetMaterial(material);
		mInternalMeshes.Add(mesh);
		mInternalPages.Add(page);
	}
	else
	{
		size_t count = atlas->PageCount();
		FOR_EACH_SIZE(i, count)
		{
			auto* page = atlas->GetPage(i);
			auto material = CreateLabelMaterial(page->LoadTexture());

			Sprite* sprite = new Sprite();
			sprite->SetMesh(new FntTextMesh(mIsStatic));
			sprite->SetMaterial(material);
			mInternalMeshes.Add(sprite->Mesh().CastPtr<BaseFontMesh>());
			sprite->EnableManaged();
			mInternalPages.Add(page);

			AddChild(sprite);
		}
	}

}

void FntLabel::ClearMeshData()
{
	for (auto& mesh:mInternalMeshes)
	{
		FntTextMesh* fontMesh = (FntTextMesh*)mesh.Ptr();
		fontMesh->Clear();
	}

	
	SetSize(Size2F::Zero);
}

Share<IMaterial> FntLabel::CreateLabelMaterial(const Share<ITexture>& texture)
{
	//TODO:
	if (mFont->IsBitmap())
	{
		return MaterialFactory::Instance().CreateSingleTexture(texture);
	}

	//ttf font
	Share<IEffect> effect = nullptr;
	if (texture->Image()->GetPixelType() == PixelType::A8)
	{
		effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Label_TTF_Text);
		auto* uniform= this->MutableRenderState().FindOrCreateUniform(ShaderUniformNames::TextColor);
		uniform->Set(mFont->GetFontId().Color());
	}
	else if (texture->Image()->GetPixelType() == PixelType::IA88)
	{
		

		/*List<FileIdRef> renderPassNames;
		renderPassNames.Add(RenderPassNames::Label_TTF_Outline);
		renderPassNames.Add(RenderPassNames::Label_TTF_Text);*/

	//	effect = EffectFactory::Instance().CreateMultiplePasses( RenderPassNames::Label_TTF_OutlineText, renderPassNames);

		effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Label_TTF_OutlineText);
		auto* uniform = this->MutableRenderState().FindOrCreateUniform(ShaderUniformNames::TextColor);
		uniform->Set(mFont->GetFontId().Color());
		uniform = this->MutableRenderState().FindOrCreateUniform(ShaderUniformNames::OutlineColor);
		uniform->Set(mFont->GetFontId().OutlineColor());
	}
	else
	{
		Log::AssertFailed("Invalid texture format for ttf");
		return nullptr;
	}
	return new IMaterial(texture, effect);

}

MEDUSA_IMPLEMENT_NODE(FntLabel);


MEDUSA_END;
