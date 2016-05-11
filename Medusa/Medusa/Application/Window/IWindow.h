// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"		  
#include "Geometry/Size2.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/Pattern/Runnable/DefaultRunnable.h"

MEDUSA_BEGIN;

class IWindow :public IInitializable,public RTTIObject,public DefaultRunnable
{
	MEDUSA_DECLARE_RTTI_ROOT;

public:
	IWindow(MedusaWindowHandle parentWindow,StringRef name=StringRef::Empty);
	virtual ~IWindow(void);
public:
	StringRef Text() const { return mText; }
	void SetText(StringRef val) { mText = val; }

	MedusaWindowHandle ParentWindowHandle() const { return mParentWindowHandle; }
	void SetParentWindowHandle(MedusaWindowHandle inParentWindow) { mParentWindowHandle = inParentWindow; }
	MedusaWindowHandle WindowHandle() const { return mWindowHandle; }

	virtual void Show()=0;
	virtual void MakeCenter()=0;
	virtual void Resize(const Size2F& newSize){}
	void AddView(IView* view);
    IView* FirstView()const{return mViews.First();}
	
	virtual bool Start()override;
	virtual bool Stop()override;
	virtual bool Pause()override;
	virtual bool Resume()override;

	virtual bool OnEvent(IEventArg& eventArg) { return false; }


	const Size2F& Size() const { return mSize; }
	void SetSize(const Size2F& val) { mSize = val; }
protected:
	HeapString mName;
	HeapString mText;
	
	MedusaWindowHandle mParentWindowHandle;
	MedusaWindowHandle mWindowHandle;
	Size2F mSize;
	
	List<IView*> mViews;
};

MEDUSA_END;
