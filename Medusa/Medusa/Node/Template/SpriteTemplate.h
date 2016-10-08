// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TNodeTemplate.h"

MEDUSA_BEGIN;

class SpriteTemplate :public TNodeTemplate<FileId>
{
public:
	virtual Size2F Measure(const FileId& data, const Size2F& limitSize = Size2F::Zero)const override;
	virtual INode* Load(const FileId& data, const Size2F& limitSize = Size2F::Zero, INode* reloadNode = nullptr)const override;

};

MEDUSA_END;
