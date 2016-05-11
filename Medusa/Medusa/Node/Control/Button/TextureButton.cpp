// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureButton.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"
#include "Rendering/RenderingObjectFactory.h"
#include "Resource/Material/IMaterial.h"

MEDUSA_BEGIN;


Medusa::TextureButton::TextureButton(StringRef name, 
							const FileIdRef& normalTextureName, 
							const FileIdRef& selectedTextureName /*= FileIdRef::Empty*/, 
							const FileIdRef& disabledTextureName /*= FileIdRef::Empty*/, 
							const FileIdRef& disabledSelectedTextureName /*= FileIdRef::Empty*/, 
							bool isEnableNineGrid /*= false*/, 
							const Size2F& targetSize /*= Size2F::Zero*/, 
							const ThicknessF& padding /*= ThicknessF::Zero*/)
							:IButton(name),
							mNormalTextureName(normalTextureName),
							mSelectedTextureName(selectedTextureName),
							mDisabledTextureName(disabledTextureName),
							mDisabledSelectedTextureName(disabledSelectedTextureName),
							mIsEnableNineGrid(isEnableNineGrid),
							mTargetSize(targetSize),
							mPadding(padding)
{

}


TextureButton::~TextureButton(void)
{
	 
}

bool TextureButton::Initialize()
{
	OnUpdateMesh();

	return true;
}


void TextureButton::SetDisabledSelectedTextureName(const FileIdRef& val)
{
	mDisabledSelectedTextureName = val;
	if (mButtonState == ButtonState::DisabledSelected)
	{
		OnUpdateMesh();
	}
}

void TextureButton::SetDisabledTextureName(const FileIdRef& val)
{
	mDisabledTextureName = val;
	if (mButtonState == ButtonState::Disabled)
	{
		OnUpdateMesh();
	}
}

void TextureButton::SetSelectedTextureName(const FileIdRef& val)
{
	mSelectedTextureName = val;
	if (mButtonState == ButtonState::Selected)
	{
		OnUpdateMesh();
	}
}

void TextureButton::SetNormalTextureName(const FileIdRef& val)
{
	mNormalTextureName = val;
	if (mButtonState == ButtonState::Normal)
	{
		OnUpdateMesh();
	}
}


void TextureButton::OnUpdateMesh()
{
	switch (mButtonState)
	{
		case ButtonState::Normal:
			if (mNormalTextureName.IsValid())
			{
				SetImage(mNormalTextureName.ToRef());
			}
			break;
		case ButtonState::Selected:
			if (mSelectedTextureName.IsValid())
			{
				SetImage(mSelectedTextureName.ToRef());
			}
			break;
		case ButtonState::Disabled:
			if (mDisabledTextureName.IsValid())
			{
				SetImage(mDisabledTextureName.ToRef());
			}
			break;
		case ButtonState::DisabledSelected:
			if (mDisabledSelectedTextureName.IsValid())
			{
				SetImage(mDisabledSelectedTextureName.ToRef());
			}
			break;
	}
}

void TextureButton::SetImage(const FileIdRef& image)
{
	auto renderingObject = mIsEnableNineGrid ? RenderingObjectFactory::Instance().CreateNineGridTexture(mTargetSize, image, mPadding) : RenderingObjectFactory::Instance().CreateFromTexture(image);
	SetRenderingObject(renderingObject);
	Size2U textureSize = renderingObject.Material()->FirstTexture()->Size();
	SetSize(textureSize);
}

void TextureButton::OnButtonStateChanged()
{
	OnUpdateMesh();
}

MEDUSA_IMPLEMENT_RTTI(TextureButton, IButton);



MEDUSA_END;
