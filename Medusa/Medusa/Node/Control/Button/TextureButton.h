// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "IButton.h"

MEDUSA_BEGIN;

class TextureButton :public IButton
{
	MEDUSA_NODE(TextureButton,IButton);
public:
	TextureButton(StringRef name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	TextureButton(StringRef name, const FileIdRef& normalTextureName, const FileIdRef& selectedTextureName = FileIdRef::Empty, const FileIdRef& disabledTextureName = FileIdRef::Empty, const FileIdRef& disabledSelectedTextureName = FileIdRef::Empty);
	virtual ~TextureButton(void);
	virtual bool Initialize() override;

	FileIdRef NormalTextureName() const { return mNormalTextureName.ToRef(); }
	void SetNormalTextureName(const FileIdRef& val);

	FileIdRef SelectedTextureName() const { return mSelectedTextureName.ToRef(); }
	void SetSelectedTextureName(const FileIdRef& val);

	FileIdRef DisabledTextureName() const { return mDisabledTextureName.ToRef(); }
	void SetDisabledTextureName(const FileIdRef& val);

	FileIdRef DisabledSelectedTextureName() const { return mDisabledSelectedTextureName.ToRef(); }
	void SetDisabledSelectedTextureName(const FileIdRef& val);

	bool IsNineGridEnabled() const { return mIsNineGridEnabled; }
	void EnableNineGrid(bool val);

	const ThicknessF& TexturePadding() const { return mTexturePadding; }
	void SetTexturePadding(const ThicknessF& val);
protected:
	virtual void OnMoveableDirty(MoveableChangedFlags changedFlags) override;
	virtual void OnUpdateMesh();
	void SetImage(const FileIdRef& image);
	virtual void OnButtonStateChanged() override;
protected:
	FileId mNormalTextureName;
	FileId mSelectedTextureName;
	FileId mDisabledTextureName;
	FileId mDisabledSelectedTextureName;

	bool mIsNineGridEnabled=false;
	Size2F mTargetSize;
	ThicknessF mTexturePadding;
};

MEDUSA_END;
