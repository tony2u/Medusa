#pragma once
#include "MedusaPreDeclares.h"
MEDUSA_BEGIN;

enum class InputBehaviors
{
	None = 0,
	SuppressTouchBegan = 1,
	PlayAudio = 2,
	DisableEventBinding = 4,
	DisableScriptBinding = 8,

	All = SuppressTouchBegan | PlayAudio
};


enum class InputType
{
	None = -1,
	Tap = 0,
	Pinch = 1,
	Rotation = 2,
	Swipe = 3,
	Pan = 4,
	LongPress = 5,
	Drag = 6,
	DoubleTap = 7,

	IME = 8,
	Keyboard = 9,

	Count = 10
};

enum class InputState
{
	None,
	Begin,
	Recognizing,
	Valid,
	End,
	Failed,
	Disabled
};


enum class InputEventType
{
	None = -1,
	//pure
	TouchBegan = 0,
	TouchMoved,
	TouchEnded,
	TouchCancelled,


	KeyDown,
	KeyUp,
	CharInput,
	Scroll,

	KeyboardWillShow,
	KeyboardShowed,
	KeyboardWillHide,
	KeyboardHided,

	//high level
	Tap,
	TapFailed,
	DoubleTap,

	DragBegan,
	Draging,
	DragEnd,
	DragFailed,

	LongPressBegan,
	LongPressFailed,

	PanBegin,
	Pan,
	PanEnd,

	Pinch,

	SwipeBegin,
	SwipeMoved,
	SwipeFailed,
	SwipeSuccess,

	Count,
};

#define MEDUSA_INPUT_BIND(className,func) MutableInput().Bind(#func,Bind(&className::func, this));

MEDUSA_END;
