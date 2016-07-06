// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureButton.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"
#include "Rendering/RenderingObjectFactory.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Model/Mesh/Fixed/TextureNineGridMesh.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;


TextureButton::TextureButton(StringRef name, 
							const FileIdRef& normalTextureName, 
							const FileIdRef& selectedTextureName /*= FileIdRef::Empty*/, 
							const FileIdRef& disabledTextureName /*= FileIdRef::Empty*/, 
							const FileIdRef& disabledSelectedTextureName /*= FileIdRef::Empty*/)
							:IButton(name),
							mNormalTextureName(normalTextureName),
							mSelectedTextureName(selectedTextureName),
							mDisabledTextureName(disabledTextureName),
							mDisabledSelectedTextureName(disabledSelectedTextureName),
							mTexturePadding(ThicknessF::Zero)
{

}


TextureButton::TextureButton(StringRef name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:IButton(name, e), mTexturePadding(ThicknessF::Zero)
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

void TextureButton::EnableNineGrid(bool val)
{
	RETURN_IF_EQUAL(mIsNineGridEnabled, val);
	mIsNineGridEnabled = val;
	OnUpdateMesh();
}

void TextureButton::SetTexturePadding(const ThicknessF& val)
{
	RETURN_IF_EQUAL(mTexturePadding, val);
	mTexturePadding = val;
	if (mIsNineGridEnabled)
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


void TextureButton::OnMoveableDirty(MoveableChangedFlags changedFlags)
{
	INode::OnMoveableDirty(changedFlags);

	if (MEDUSA_FLAG_HAS(changedFlags, MoveableChangedFlags::SizeChanged)&& mIsNineGridEnabled)
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
	auto renderingObject = mIsNineGridEnabled ? RenderingObjectFactory::Instance().CreateNineGridTexture(mSize.To2D(), image, mTexturePadding) : RenderingObjectFactory::Instance().CreateFromTexture(image);
	SetRenderingObject(renderingObject);
	Size2U textureSize = renderingObject.Material()->FirstTexture()->Size();
	SetSize(textureSize);

	if (mIsNineGridEnabled)
	{
		auto mesh = mRenderingObject.Mesh().CastPtr<TextureNineGridMesh>();
		RETURN_IF_NULL(mesh);
		mesh->UpdateToNewTargetSize(mSize.To2D());
	}
	
}

void TextureButton::OnButtonStateChanged()
{
	OnUpdateMesh();
}

MEDUSA_IMPLEMENT_NODE(TextureButton);
MEDUSA_END;
