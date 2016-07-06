// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IEditBox.h"
#include "Node/Sprite/Sprite.h"
#include "Node/Sprite/NineGridSprite.h"
#include "Resource/Font/IFont.h"
#include "Resource/Font/FontFactory.h"
#include "Node/Input/InputDispatcher.h"
#include "Node/Input/Gesture/PanGestureRecognizer.h"
#include "Node/Input/Gesture/TapGestureRecognizer.h"
#include "Node/Input/InputManager.h"
#include "Node/Control/Label/ILabel.h"
#include "Node/Input/EventArg/CharInputEventArg.h"
#include "Node/Input/IMEHandler.h"
#include "Resource/Model/Mesh/Fixed/ShapeQuadMesh.h"
#include "Node/NodeFactory.h"
#include "Node/Shape/IShape.h"
#include "Node/Action/Basic/BlinkAction.h"
#include "Core/Action/Composite/RepeatedForeverAction.h"
#include "Resource/Model/Mesh/Font/FntTextMesh.h"

MEDUSA_BEGIN;



IEditBox::IEditBox(const StringRef& name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:INode(name,e),
	mCursorColor(Color4F::White)
{
	EnableClipToBound(true);
	PanGestureRecognizer* panGestureRecognizer = MutableInput().AddPanGestureHandler(Bind(&IEditBox::OnPan, this), 1.f);
	panGestureRecognizer->OnBegin += Bind(&IEditBox::OnPanBegin, this);
	panGestureRecognizer->OnEnd += Bind(&IEditBox::OnPanEnd, this);

	MutableInput().AddIMEHandler(Bind(&IEditBox::OnCharInput, this), Bind(&IEditBox::OnKeyDown, this), Bind(&IEditBox::OnKeyUp, this));
	TapGestureRecognizer* tapGestureRecognizer = MutableInput().AddTapGestureHandler(Bind(&IEditBox::OnTap, this));
	tapGestureRecognizer->OnTapFailed += Bind(&IEditBox::OnTapFailed, this);
}

IEditBox::~IEditBox(void)
{

}

bool IEditBox::ArrangeChildren(const Rect2F& limitRect /*= Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags /*= NodeLayoutArrangeFlags::None*/)
{
	//re layout mesh and move the cursor after size changed
	RETURN_FALSE_IF_FALSE(INode::ArrangeChildren(limitRect, arrangeFlags));

	mTextLabel->SetRestrictSize(mSize.To2D());
	mPlaceHolderLabel->SetRestrictSize(mSize.To2D());
	OnUpdateCursor();

	return true;
}


bool IEditBox::HasText() const
{
	return !mTextLabel->String().IsEmpty();
}


WStringRef IEditBox::Text() const
{
	return mTextLabel->String();
}


void IEditBox::SetText(WStringRef val)
{
	if (mTextLabel->SetString(val))
	{
		OnUpdateStatus();
	}
}

const FontId& IEditBox::TextFontId() const
{
	return mTextLabel->GetFontId();
}

void IEditBox::SetTextFontId(const FontId& val)
{
	mTextLabel->SetFontId(val);
}

Alignment IEditBox::TextAlignment() const
{
	return mTextLabel->GetAlignment();
}

void IEditBox::SetTextAlignment(Alignment val)
{
	mTextLabel->SetAlignment(val);
}

const Color4F& IEditBox::TextColor() const
{
	return mTextLabel->Color();
}

void IEditBox::SetTextColor(const Color4F& val)
{
	mTextLabel->SetColor(val);
}

const FontId& IEditBox::PlaceHolderFontId() const
{
	return mPlaceHolderLabel->GetFontId();
}


void IEditBox::SetPlaceHolderFontId(const FontId& val)
{
	if (mPlaceHolderLabel->SetFontId(val))
	{
		OnUpdateCursor();
	}

}

WStringRef IEditBox::PlaceHolderText() const
{
	return mPlaceHolderLabel->String();
}

void IEditBox::SetPlaceHolderText(WStringRef val)
{
	mPlaceHolderLabel->SetString(val);
}

Alignment IEditBox::PlaceHolderTextAlignment() const
{
	return mPlaceHolderLabel->GetAlignment();
}

void IEditBox::SetPlaceHolderTextAlignment(Alignment val)
{
	mPlaceHolderLabel->SetAlignment(val);
}

const Color4F& IEditBox::PlaceHolderColor() const
{
	return mPlaceHolderLabel->Color();
}

void IEditBox::SetPlaceHolderColor(const Color4F& val)
{
	mPlaceHolderLabel->SetColor(val);
}

void IEditBox::SetBackgroundSprite(NineGridSprite* val)
{
	RETURN_IF_EQUAL(mBackgroundSprite, val);
	if (mBackgroundSprite != nullptr)
	{
		RemoveChild(mBackgroundSprite);
	}
	mBackgroundSprite = val;
	if (mBackgroundSprite != nullptr)
	{
		mBackgroundSprite->EnableManaged();
		AddChild(mBackgroundSprite);
		mBackgroundSprite->SetStretch(Stretch::Fill);
	}
}


void IEditBox::SetCursorVisibility(CursorVisibility val)
{
	RETURN_IF_EQUAL(mCursorVisibility, val);
	mCursorVisibility = val;
	OnUpdateCursor();

}

void IEditBox::SetCursorColor(const Color4F& val)
{
	RETURN_IF_EQUAL(mCursorColor, val);
	mCursorColor = val;

	if (mCursorSprite != nullptr)
	{
		mCursorSprite->SetColor(mCursorColor);
	}
}

void IEditBox::SetCursorWidth(float val)
{
	RETURN_IF_EQUAL(mCursorWidth, val);
	mCursorWidth = val;

	if (mCursorSprite != nullptr)
	{
		auto mesh = mCursorSprite->Mesh().CastPtr<ShapeQuadMesh>();
		mesh->SetVertexBySize(Size2F(mCursorWidth, (float)mTextLabel->GetFontId().Size()));
	}
}

void IEditBox::SetCursorBlinkRate(float val)
{
	RETURN_IF_EQUAL(mCursorBlinkRate, val);
	mCursorBlinkRate = val;
	OnUpdateCursor();

}


void IEditBox::OnTap(INode* sender, TapGestureEventArg& e)
{
	if (!mIsEditing)
	{
		mIsEditing = true;
		//show keyboard
		InputManager::Instance().ShowKeyboard(this);
		OnUpdateCursor();
	}
}


void IEditBox::OnTapFailed(INode* sender)
{
	mIsEditing = false;
	//hide keyboard
	OnUpdateCursor();
	InputManager::Instance().HideKeyboard(this);

}


void IEditBox::OnMoveableDirty(MoveableChangedFlags changedFlags)
{
	mTextLabel->SetSize(mSize);
	mPlaceHolderLabel->SetSize(mSize);
	IRenderable::OnMoveableDirty(changedFlags);
}

void IEditBox::OnPanBegin(INode* sender, PanBeginGestureEventArg& e)
{

}

void IEditBox::OnPan(INode* sender, PanGestureEventArg& e)
{

}

void IEditBox::OnPanEnd(INode* sender, PanEndGestureEventArg& e)
{

}


void IEditBox::OnKeyDown(INode* sender, KeyDownEventArg& e)
{

}

void IEditBox::OnKeyUp(INode* sender, KeyUpEventArg& e)
{
	RETURN_IF_FALSE(mIsEditing);

	WHeapString& str = mTextLabel->MutableString();

	Keys keyCode = e.KeyCode();
	switch (keyCode)
	{
	case Keys::Back:
		str.RemoveLast();
		break;
	case Keys::Delete:
		str.RemoveLast();
		break;
	default:
		break;
	}

	mTextLabel->CommitChanges();
	OnUpdateCursor();
}

void IEditBox::OnCharInput(INode* sender, CharInputEventArg& e)
{
	RETURN_IF_FALSE(mIsEditing);
	Keys keyCode = e.KeyCode();
	switch (keyCode)
	{
	case Keys::Back:
	case Keys::Delete:
		break;
	default:
	{
		WHeapString& str = mTextLabel->MutableString();
		wchar_t c = e.Char();
		str += c;
		mTextLabel->CommitChanges();
		OnUpdateCursor();
		break;
	}
	}

}

void IEditBox::OnUpdateStatus()
{
	bool hasText = HasText() || mIsEditing;
	mTextLabel->SetVisible(hasText);
	mPlaceHolderLabel->SetVisible(!hasText);

	OnUpdateCursor();
}

void IEditBox::OnUpdateCursor()
{
	bool isShowCursor = false;
	switch (mCursorVisibility)
	{
	case CursorVisibility::AlwaysVisible:
		isShowCursor = true;
		break;
	case CursorVisibility::Auto:
		isShowCursor = mIsEditing;
		break;
	case CursorVisibility::Disabled:
		break;
	default:
		break;
	}

	if (isShowCursor)
	{
		if (mCursorSprite == nullptr)
		{
			mCursorSprite = NodeFactory::Instance().CreateRect(Size2F(mCursorWidth, (float)mTextLabel->GetFontId().Size()), mCursorColor);
			mCursorSprite->SetName(MEDUSA_PREFIX(Cursor));
			mCursorSprite->EnableManaged();
			AddChild(mCursorSprite);
		}

		if (!mCursorSprite->IsActionRunning())
		{
			BlinkAction* blinkAction = BlinkAction::Create(mCursorBlinkRate);
			RepeatedForeverAction* rep = RepeatedForeverAction::Create(blinkAction);
			mCursorSprite->RunAction(rep);
		}

		Point2F pos = mTextLabel->GetCursorPosition(mCursorCharOffset);
		mCursorSprite->SetPosition(pos);
	}
	else
	{
		if (mCursorSprite != nullptr)
		{
			mCursorSprite->StopAllActions();
			mCursorSprite->SetVisible(false);
		}
	}
}



MEDUSA_END;
