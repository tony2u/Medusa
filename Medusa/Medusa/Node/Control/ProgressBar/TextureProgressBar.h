// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "IProgressBar.h"

MEDUSA_BEGIN;


class TextureProgressBar :public IProgressBar
{
	MEDUSA_NODE(TextureProgressBar,IProgressBar);

public:
	TextureProgressBar(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	TextureProgressBar(StringRef name, ProgressType progressType, const FileIdRef& textureName,float percent=1.f);
	virtual ~TextureProgressBar(void);
	virtual bool Initialize()override;
protected:
	virtual void OnUpdateMesh(bool isProgressTypeChanged = false)override;
protected:
	FileId mTextureName;

	Array<Point3F, 4> mVertices;	//initial data
	Array<Point2F, 4> mTexcoords;	//initial data
};

MEDUSA_END;
