// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Node/Input/IInputHandler.h"
#include "Core/Pattern/Event.h"
#include "Core/Collection/List.h"
#include "Node/Input/Touch.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Core/IO/FileId.h"

#include "GestureFlags.h"

MEDUSA_BEGIN;

enum class GestureState
{
	None,
	Begin,
	Recognizing,
	Valid,
	End,
	Failed,
	Disabled
};


typedef Delegate<void(GestureState,GestureState)> GestureStateChangedHandler;

class IGestureRecognizer:public IInputHandler
{
public:
	Event<void(GestureState,GestureState)> StateChangedEvent;
public:
	IGestureRecognizer(INode* node,GestureFlags flags=GestureFlags::None,const FileIdRef& audioEffect=FileIdRef::Empty);
	virtual ~IGestureRecognizer(void);

	virtual bool Update(float dt){return true;}

	GestureState State() const { return mState; }
	void SetState(GestureState state);

	GestureFlags Flags() const { return mFlags; }
	void SetFlags(GestureFlags val) { mFlags = val; }

	bool HasTouch()const{return mTouchEventArg.IsValid();}

	void SetIsDisabled(bool val);
	virtual bool IsValid()const=0;
	virtual bool HasHandler()const=0;

	virtual bool IsFocus()const{return mState==GestureState::Valid;}


	FileIdRef AudioEffect() const { return mAudioEffect.ToRef(); }
	void SetAudioEffect(const FileIdRef& val) { mAudioEffect = val; }
protected:
	bool IsValidTouch(const Touch& touch)const;
	bool HasValidTouch(const List<Touch>& touches)const;

	Touch TransformToNodeSpace(const Touch& touch)const;
	bool TryTransformToNodeSpace(const Touch& touch,Touch& outTouch)const;
protected:
	GestureState mState;
	GestureFlags mFlags;

	TouchEventArg mTouchEventArg;
	FileId mAudioEffect;


};



MEDUSA_END;