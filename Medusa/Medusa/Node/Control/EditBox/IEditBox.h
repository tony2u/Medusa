// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Node/INode.h"
#include "Core/IO/FileId.h"

MEDUSA_BEGIN;

enum class CursorVisibility
{
	Disabled = -1,
	Auto = 0,	//only visible on editing
	AlwaysVisible = 2,
};

class IEditBox :public INode
{
	MEDUSA_DECLARE_RTTI;
public:
	IEditBox(StringRef name, const Size2F& size, const FontId& fontId, WStringRef text = WStringRef::Empty, Alignment alignment = Alignment::LeftBottom);
	virtual ~IEditBox(void);
public:
	InputMode GetInputMode() const { return mInputMode; }
	void SetInputMode(InputMode val) { mInputMode = val; }

	InputFlag GetInputFlag() const { return mInputFlag; }
	void SetInputFlag(InputFlag val) { mInputFlag = val; }

	uint MaxCharCount() const { return mMaxCharCount; }
	void SetMaxCharCount(uint val) { mMaxCharCount = val; }

	bool HasText()const;

	//////////////////////////////////////////////////////////////////////////
	WStringRef Text() const;
	void SetText(WStringRef val);

	const FontId& TextFontId()const;
	void SetTextFontId(const FontId& val);

	Alignment TextAlignment() const;
	void SetTextAlignment(Alignment val);

	const Color4F& TextColor() const;
	void SetTextColor(const Color4F& val);

	//////////////////////////////////////////////////////////////////////////
	WStringRef PlaceHolderText() const;
	void SetPlaceHolderText(WStringRef val);

	const FontId& PlaceHolderFontId()const;
	void SetPlaceHolderFontId(const FontId& val);

	Alignment PlaceHolderTextAlignment() const;
	void SetPlaceHolderTextAlignment(Alignment val);

	const Color4F& PlaceHolderColor() const;
	void SetPlaceHolderColor(const Color4F& val);
	//////////////////////////////////////////////////////////////////////////

	NineGridSprite* BackgroundSprite() const { return mBackgroundSprite; }
	void SetBackgroundSprite(NineGridSprite* val);

	CursorVisibility GetCursorVisibility() const { return mCursorVisibility; }
	void SetCursorVisibility(CursorVisibility val);

	const Color4F& CursorColor() const { return mCursorColor; }
	void SetCursorColor(const Color4F& val);

	float CursorWidth() const { return mCursorWidth; }
	void SetCursorWidth(float val);

	float CursorBlinkRate() const { return mCursorBlinkRate; }
	void SetCursorBlinkRate(float val);

public:
	virtual bool ArrangeChildren(const Rect2F& limitRect = Rect2F::Zero, NodeLayoutArrangeFlags arrangeFlags = NodeLayoutArrangeFlags::None)override;

protected:
	virtual void OnPanBegin(INode* sender, PanBeginGestureEventArg& e);
	virtual void OnPan(INode* sender, PanGestureEventArg& e);
	virtual void OnPanEnd(INode* sender, PanEndGestureEventArg& e);

	virtual void OnKeyDown(INode* sender, KeyDownEventArg& e);
	virtual void OnKeyUp(INode* sender, KeyUpEventArg& e);
	virtual void OnCharInput(INode* sender, CharInputEventArg& e);

	virtual void OnTap(INode* sender, TapGestureEventArg& e);
	virtual void OnTapFailed(INode* sender);



	virtual void OnUpdateStatus();
	virtual void OnUpdateCursor();


protected:
	InputMode mInputMode=InputMode::Any;
	InputFlag mInputFlag=InputFlag::Sensitive;
	uint mMaxCharCount= Math::UIntMaxValue;

	//text
	ILabel* mTextLabel=nullptr;
	//placeholder
	ILabel* mPlaceHolderLabel=nullptr;

	//background
	NineGridSprite* mBackgroundSprite=nullptr;

	//cursor
	CursorVisibility mCursorVisibility=CursorVisibility::Auto;
	Color4F mCursorColor;
	float mCursorWidth=1.f;
	float mCursorBlinkRate=1.f;	//the duration by seconds per blink
	uint mCursorCharOffset=0;	//target at the end aft fist 

	IShape* mCursorSprite=nullptr;	//cursor height=font size

protected:
	bool mIsEditing=false;
};

MEDUSA_END;
