// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureFileIdTimelineModel.h"

MEDUSA_BEGIN;


TextureFileIdTimelineModel::TextureFileIdTimelineModel(const FileIdRef& fileId)
	:ITimelineModel(fileId)
{

}


TextureFileIdTimelineModel::~TextureFileIdTimelineModel(void)
{
}

void TextureFileIdTimelineModel::AddFileId(float time, const FileIdRef& fileId)
{
	mFileIds.Add(fileId);
	AddFrame(time,(uint) mFileIds.Count() - 1);

}

FileIdRef TextureFileIdTimelineModel::GetFileId(float time)const
{
	if (mIsPreCalculated)
	{
		intp index = GetPreCalculatedIndex(time);
		return mPreCalculatedFileIds[index].ToRef();
	}
	intp index = GetSteppedFrameIndex(time);
	return mFileIds[index].ToRef();
}

void TextureFileIdTimelineModel::RemovePreCalculated()
{
	ITimelineModel::RemovePreCalculated();
	mPreCalculatedFileIds.Clear();
}

void TextureFileIdTimelineModel::OnPreCalculateBegin()
{
	mPreCalculatedFileIds.Clear();
}

void TextureFileIdTimelineModel::AddPreCalcuatedItem(bool isFound, uint prevFrameIndex, uint nextFrameIndex, float percent)
{
	if (isFound)
	{
		mPreCalculatedFileIds.Add(mFileIds[prevFrameIndex]);
	}
	else
	{
		mPreCalculatedFileIds.Add(FileId::Empty);
	}

}




MEDUSA_END;