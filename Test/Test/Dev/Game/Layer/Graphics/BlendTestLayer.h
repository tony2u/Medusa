// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"


STRONG_ENUM_CUSTOM_15(GraphicsBlendSrcFuncHelper,

	Zero, GL_ZERO,
	One, GL_ONE,
	SrcColor, GL_SRC_COLOR,
	OneMinusSrcColor, GL_ONE_MINUS_SRC_COLOR,
	DestColor, GL_DST_COLOR,

	OneMinusDestColor, GL_ONE_MINUS_DST_COLOR,
	SrcAlpha, GL_SRC_ALPHA,
	OneMinusSrcAlpha, GL_ONE_MINUS_SRC_ALPHA,
	DestAlpha, GL_DST_ALPHA,
	OneMinusDestAlpha, GL_ONE_MINUS_DST_ALPHA,

	ConstantColor, GL_CONSTANT_COLOR,
	OneMinusConstantColor, GL_ONE_MINUS_CONSTANT_COLOR,
	ConstantAlpha, GL_CONSTANT_ALPHA,
	OneMinusConstantAlpha, GL_ONE_MINUS_CONSTANT_ALPHA,
	SrcAlphaSaturate, GL_SRC_ALPHA_SATURATE
	);

STRONG_ENUM_CUSTOM_14(GraphicsBlendDestFuncHelper,
	Zero, GL_ZERO,
	One, GL_ONE,
	SrcColor, GL_SRC_COLOR,
	OneMinusSrcColor, GL_ONE_MINUS_SRC_COLOR,
	DestColor, GL_DST_COLOR,

	OneMinusDestColor, GL_ONE_MINUS_DST_COLOR,
	SrcAlpha, GL_SRC_ALPHA,
	OneMinusSrcAlpha, GL_ONE_MINUS_SRC_ALPHA,
	DestAlpha, GL_DST_ALPHA,
	OneMinusDestAlpha, GL_ONE_MINUS_DST_ALPHA,

	ConstantColor, GL_CONSTANT_COLOR,
	OneMinusConstantColor, GL_ONE_MINUS_CONSTANT_COLOR,
	ConstantAlpha, GL_CONSTANT_ALPHA,
	OneMinusConstantAlpha, GL_ONE_MINUS_CONSTANT_ALPHA
	);


class BlendTestLayer :public BaseCaseLayer
{
	MEDUSA_NODE(BlendTestLayer, BaseCaseLayer);
public:
	BlendTestLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~BlendTestLayer(void);
	virtual bool Initialize()override;
	void OnSrcChanged(INode* sender, TapGestureEventArg& e);
	void OnDestChanged(INode* sender, TapGestureEventArg& e);

protected:
	Sprite* mBackSrite;
	Sprite* mFrontSprite;

	LabelButton* mSrcFuncButton;
	LabelButton* mDestFuncButton;

	GraphicsBlendSrcFuncHelper mSrcFunc;
	GraphicsBlendDestFuncHelper mDestFunc;
};

