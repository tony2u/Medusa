// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Event.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;


class Console :public Singleton<Console>
{
	Console();
	~Console(void);
	friend class Singleton<Console>;
public:
	Event<void()> OnCtrlC;
	Event<void()> OnCtrlBreak;
	Event<void()> OnCtrlClose;
public:
	HeapString ReadLine()const
	{
		HeapString str;
		int c;
		while ((c = getchar()) != '\n')
		{
			str += (char)c;
		}
		return str;
	}
	char ReadChar()const;
	bool IsKeyboardHit()const;
protected:
	void RegisterCtrlHandler();
};

MEDUSA_END;
