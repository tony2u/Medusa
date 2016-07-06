// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Geometry/Point3.h"
#include "Geometry/Size2.h"
#include "Geometry/Scale3.h"
#include "Geometry/Rect2.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Pattern/Event.h"
#include "Core/Collection/HashSet.h"
#include "Core/System/SystemDefines.h"
#include "Geometry/GeometryDefines.h"
#include "Resource/Camera/Camera.h"

MEDUSA_BEGIN;


class ResolutionAdapter :public Singleton<ResolutionAdapter>
{
	friend class Singleton<ResolutionAdapter>;
	ResolutionAdapter();
	~ResolutionAdapter(void);
public:
	bool Initialize(const Size2F& winSize);
	bool InitializeCameras();
	bool Uninitialize();

	const Rect2F& WinRect()const { return mWinRect; }
	const Size2F& WinSize() const { return mWinSize; }
	float WinWidth()const { return mWinSize.Width; }
	float WinHeight()const { return mWinSize.Height; }

	void SetWinSize(const Size2F& val);


	const Share<Camera>& DefaultCamera2D() const { return mDefaultCamera2D; }
	const Share<Camera>& DefaultCamera3D() const { return mDefaultCamera3D; }

	bool IsLayoutDirty() const;
	bool IsNodeLayoutDirty(INode* node)const;
	bool TryAddDirytNode(INode* node);
	bool TryRemoveDirytNode(INode* node);

	void UpdateLayout();

	Stretch GetStretch() const { return mStretch; }
	void SetStretch(Stretch val) { mStretch = val; }
	static Size2U ScreenSize();
private:
	bool IsTopDirtyNode(INode* node)const;
	void OnUIOrientationChanged(UIOrientation val);
protected:
	Share<Camera> mDefaultCamera2D;
	Share<Camera> mDefaultCamera3D;

	Size2F mWinSize;
	Rect2F mWinRect;	//cache

	HashSet<INode*> mDirtyNodes;
	List<INode*> mDirtyList;
	bool mIsLayoutUpdating = false;

	Stretch mStretch = Stretch::Uniform;
};

MEDUSA_END;
