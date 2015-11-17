// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Timeline/ITimelineModel.h"
#include "Core/IO/FileId.h"

MEDUSA_BEGIN;

class TextureFileIdTimelineModel:public ITimelineModel
{
public:
	TextureFileIdTimelineModel(const FileIdRef& fileId);
	virtual ~TextureFileIdTimelineModel(void);

	void AddFileId(float time, const FileIdRef& fileId);

	FileIdRef GetFileId(float time)const;

	virtual void RemovePreCalculated()override;
protected:
	virtual void OnPreCalculateBegin()override;
	virtual void AddPreCalcuatedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent) override;
protected:
	List<FileId> mFileIds;
	List<FileId> mPreCalculatedFileIds;

};

MEDUSA_END;
