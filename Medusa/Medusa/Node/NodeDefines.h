// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;



enum class PanelType { Stack, Wrap, Dock, Grid, UniformGrid, Canvas, Relative, View, Scroll };

enum class ProgressType
{
	HorizontalLeftToRight,
	HorizontalRightToLeft,
	VerticalBottomToTop,
	VerticalTopToBottom,
	RadialCounterClockWise,
	RadialClockWise,
};


enum class Keys
{
	A = 0x41,
	Add = 0x6b,
	Alt = 0x40000,
	Apps = 0x5d,
	Attn = 0xf6,
	B = 0x42,
	Back = 8,
	BrowserBack = 0xa6,
	BrowserFavorites = 0xab,
	BrowserForward = 0xa7,
	BrowserHome = 0xac,
	BrowserRefresh = 0xa8,
	BrowserSearch = 170,
	BrowserStop = 0xa9,
	C = 0x43,
	Cancel = 3,
	Capital = 20,
	CapsLock = 20,
	Clear = 12,
	Control = 0x20000,
	ControlKey = 0x11,
	Crsel = 0xf7,
	D = 0x44,
	D0 = 0x30,
	D1 = 0x31,
	D2 = 50,
	D3 = 0x33,
	D4 = 0x34,
	D5 = 0x35,
	D6 = 0x36,
	D7 = 0x37,
	D8 = 0x38,
	D9 = 0x39,
	Decimal = 110,
	Delete = 0x2e,
	Divide = 0x6f,
	Down = 40,
	E = 0x45,
	End = 0x23,
	Enter = 13,
	EraseEof = 0xf9,
	Escape = 0x1b,
	Execute = 0x2b,
	Exsel = 0xf8,
	F = 70,
	F1 = 0x70,
	F10 = 0x79,
	F11 = 0x7a,
	F12 = 0x7b,
	F13 = 0x7c,
	F14 = 0x7d,
	F15 = 0x7e,
	F16 = 0x7f,
	F17 = 0x80,
	F18 = 0x81,
	F19 = 130,
	F2 = 0x71,
	F20 = 0x83,
	F21 = 0x84,
	F22 = 0x85,
	F23 = 0x86,
	F24 = 0x87,
	F3 = 0x72,
	F4 = 0x73,
	F5 = 0x74,
	F6 = 0x75,
	F7 = 0x76,
	F8 = 0x77,
	F9 = 120,
	FinalMode = 0x18,
	G = 0x47,
	H = 0x48,
	HanguelMode = 0x15,
	HangulMode = 0x15,
	HanjaMode = 0x19,
	Help = 0x2f,
	Home = 0x24,
	I = 0x49,
	IMEAccept = 30,
	IMEAceept = 30,
	IMEConvert = 0x1c,
	IMEModeChange = 0x1f,
	IMENonconvert = 0x1d,
	Insert = 0x2d,
	J = 0x4a,
	JunjaMode = 0x17,
	K = 0x4b,
	KanaMode = 0x15,
	KanjiMode = 0x19,
	KeyCode = 0xffff,
	L = 0x4c,
	LaunchApplication1 = 0xb6,
	LaunchApplication2 = 0xb7,
	LaunchMail = 180,
	LButton = 1,
	LControlKey = 0xa2,
	Left = 0x25,
	LineFeed = 10,
	LMenu = 0xa4,
	LShiftKey = 160,
	LWin = 0x5b,
	M = 0x4d,
	MButton = 4,
	MediaNextTrack = 0xb0,
	MediaPlayPause = 0xb3,
	MediaPreviousTrack = 0xb1,
	MediaStop = 0xb2,
	Menu = 0x12,
	Modifiers = -65536,
	Multiply = 0x6a,
	N = 0x4e,
	Next = 0x22,
	NoName = 0xfc,
	None = 0,
	NumLock = 0x90,
	NumPad0 = 0x60,
	NumPad1 = 0x61,
	NumPad2 = 0x62,
	NumPad3 = 0x63,
	NumPad4 = 100,
	NumPad5 = 0x65,
	NumPad6 = 0x66,
	NumPad7 = 0x67,
	NumPad8 = 0x68,
	NumPad9 = 0x69,
	O = 0x4f,
	Oem1 = 0xba,
	Oem102 = 0xe2,
	Oem2 = 0xbf,
	Oem3 = 0xc0,
	Oem4 = 0xdb,
	Oem5 = 220,
	Oem6 = 0xdd,
	Oem7 = 0xde,
	Oem8 = 0xdf,
	OemBackslash = 0xe2,
	OemClear = 0xfe,
	OemCloseBrackets = 0xdd,
	Oemcomma = 0xbc,
	OemMinus = 0xbd,
	OemOpenBrackets = 0xdb,
	OemPeriod = 190,
	OemPipe = 220,
	Oemplus = 0xbb,
	OemQuestion = 0xbf,
	OemQuotes = 0xde,
	OemSemicolon = 0xba,
	Oemtilde = 0xc0,
	P = 80,
	Pa1 = 0xfd,
	Packet = 0xe7,
	PageDown = 0x22,
	PageUp = 0x21,
	Pause = 0x13,
	Play = 250,
	Print = 0x2a,
	PrintScreen = 0x2c,
	Prior = 0x21,
	ProcessKey = 0xe5,
	Q = 0x51,
	R = 0x52,
	RButton = 2,
	RControlKey = 0xa3,
	Return = 13,
	Right = 0x27,
	RMenu = 0xa5,
	RShiftKey = 0xa1,
	RWin = 0x5c,
	S = 0x53,
	Scroll = 0x91,
	Select = 0x29,
	SelectMedia = 0xb5,
	Separator = 0x6c,
	Shift = 0x10000,
	ShiftKey = 0x10,
	Sleep = 0x5f,
	Snapshot = 0x2c,
	Space = 0x20,
	Subtract = 0x6d,
	T = 0x54,
	Tab = 9,
	U = 0x55,
	Up = 0x26,
	V = 0x56,
	VolumeDown = 0xae,
	VolumeMute = 0xad,
	VolumeUp = 0xaf,
	W = 0x57,
	X = 0x58,
	XButton1 = 5,
	XButton2 = 6,
	Y = 0x59,
	Z = 90,
	Zoom = 0xfb
};

enum class InputMode
{
	Any,	//The user is allowed to enter any text, including line breaks.
	EmailAddress,	//The user is allowed to enter an e-mail address.
	Numeric,	//The user is allowed to enter an integer value.
	PhoneNumber,	//The user is allowed to enter a phone number.
	Url,	//The user is allowed to enter a URL.
	Decimal,	//The user is allowed to enter a real number value.This extends kEditBoxInputModeNumeric by allowing a decimal point.
	SingleLine,	//The user is allowed to enter any text, except for line breaks.
};

enum class TextInputFlag
{
	/**
	* Indicates that the text entered is confidential data that should be
	* obscured whenever possible. This implies EDIT_BOX_INPUT_FLAG_SENSITIVE.
	*/
	Password,

	/**
	* Indicates that the text entered is sensitive data that the
	* implementation must never store into a dictionary or table for use
	* in predictive, auto-completing, or other accelerated input schemes.
	* A credit card number is an example of sensitive data.
	*/
	Sensitive,

	/**
	* This flag is a hint to the implementation that during text editing,
	* the initial letter of each word should be capitalized.
	*/
	InitialCapsWord,

	/**
	* This flag is a hint to the implementation that during text editing,
	* the initial letter of each sentence should be capitalized.
	*/
	InitialCapsSentence,

	/**
	* Capitalize all characters automatically.
	*/
	InitialCapsAllChrarcters,
};

enum class CursorVisibility
{
	Disabled = -1,
	Auto = 0,	//only visible on editing
	AlwaysVisible = 2,
};


enum class ToastPosition
{
	Top = 0,
	Center = 1,
	Bottom = 2
};

enum class NodeLayoutArrangeFlags
{
	None = 0,
	SuppressArrangeSelf = 1,
	SuppressArrangeChildren = 2,
};



enum class NodeLayoutChangedFlags
{
	None = 0,
	SizeChanged = 1,
	ChildAdded = 2,
	ChildRemoved = 4,
	ChildCleard = 8,
	ChildOrderChanged = 16,
	PositionChanged = 32,
	ArrangeChanged = 64,
	CollapseChanged = 128,

};

enum class NodeRemoveFlags
{
	None = 0,
	OnlyChildren = 1,
	OnlyManaged = 2,
	All = OnlyChildren | OnlyManaged
};

enum class NodeUpdateFlags
{
	None = 0,
	SuppressRunningAction = 1,
	SuppressDispatchingInput = 2,
};

enum class NodeVisitFlags
{
	None = 0,
	ForceUpdateWorldMatrix = 1,
	ForceUpdateWorldColor = 2,
};


enum class NodeCreateFlags
{
	None = 0,
	BindScriptSelf = 1,
	BindScriptChildren = 2,

	BindScriptRecursively = BindScriptSelf | BindScriptChildren,	//bind script to self and children

	All= BindScriptRecursively,
	Count=2,
};

enum class NodeDeleteFlags
{
	None = 0,
	Async = 1,
	All = Async
};


enum class NodePushFlags
{
	None = 0,
	//create
	BindScriptSelf = 1,
	BindScriptChildren = 2,

	BindScriptRecursively = BindScriptSelf | BindScriptChildren,	//bind script to self and children
	//push

	ShowPrev = 1<<((uint)NodeCreateFlags::Count),
	SuppressUpdateLogic = 1 << ((uint)NodeCreateFlags::Count+1),
	DisableTouch = 1 << ((uint)NodeCreateFlags::Count + 2),
	HideAllPrevs = 1 << ((uint)NodeCreateFlags::Count + 3),
	SaveStatusBeforePush = 1 << ((uint)NodeCreateFlags::Count + 4),
};

enum class NodePopFlags
{
	None = 0,
	ShowCurrent = 1,
	SuppressUpdateLogic = 2,
	DisableTouch = 4,
	IgnorePrev = 8,
	DeleteCurrent = 16,
	DeleteCurrentAsync = 32,
	RestoreStatusAfterPop = 64,
};


namespace NodeProperties
{
	const extern StringRef FrameEvent;	//string
	const extern StringRef UserData;	//string
	const extern StringRef Script;	//string,	empty ? auto bind script : it's will be used as custom script file name, true==empty, false to disable scirpt
}

MEDUSA_END;