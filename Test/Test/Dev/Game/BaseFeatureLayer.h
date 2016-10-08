// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"
#include "Game/BaseCaseLayer.h"

class BaseFeatureLayer:public ILayer
{
	MEDUSA_NODE(BaseFeatureLayer,ILayer);
public:
	BaseFeatureLayer(StringRef name=StringRef::Empty,const IEventArg& e=IEventArg::Empty);
	virtual ~BaseFeatureLayer(void);
	virtual bool Initialize()override;
protected:
	void OnReturn(INode* sender, TapGestureEventArg& e);
	void OnLeft(INode* sender, TapGestureEventArg& e);
	void OnRight(INode* sender, TapGestureEventArg& e);
	void OnRefresh(INode* sender, TapGestureEventArg& e);
protected:
	virtual bool OnEnter()override;
	virtual void OnRestart();

	template<typename T>
	void Register()
	{
		mLayers.Add(T::ClassNameStatic());
		mLayerEditorFiles.Add(T::EditorFileNameStatic());
	}
protected:
	List<HeapString> mLayers;
	List<FileIdRef> mLayerEditorFiles;

	size_t mIndex;
	BaseCaseLayer* mCurrentLayer;
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(BaseFeatureLayer);
