// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/GraphicsTypes.h"
#include "Core/String/HeapString.h"
#include "Geometry/Rect2.h"
#include "Geometry/Color4.h"
#include "Graphics/Buffer/FrameBuffer.h"
#include "Graphics/State/RenderTargetRenderState.h"
#include "Resource/IResource.h"

MEDUSA_BEGIN;

class IRenderTarget:public FrameBuffer,public IResource
{
public:
	IRenderTarget(const FileIdRef& fileId=FileIdRef::Empty);
	virtual ~IRenderTarget();
	virtual ResourceType Type()const{return ResourceType::RenderTarget;}
	static ResourceType ClassGetResourceType(){return ResourceType::RenderTarget;}
	

	bool operator<(const IRenderTarget& renderTarget)const{return ZOrder()<renderTarget.ZOrder();}
	int Compare(const IRenderTarget& renderTarget)const{return ZOrder()-renderTarget.ZOrder();}

	virtual void Apply();
	virtual void Restore();
	virtual void Clear();

	virtual int ZOrder() const=0;

	const Rect2I& ViewPort() const { return mViewPort; }
	void SetViewPort(const Rect2I& val) { mViewPort = val; }

	const Color4F& ClearColor() const { return mClearColor; }
	void SetClearColor(const Color4F& val) { mClearColor = val; }

	virtual void OnBeforeDraw();
	virtual void OnAfterDraw();

	virtual void Resize(const Size2U& val);


protected:
	Rect2I mViewPort;
	Color4F mClearColor;
	Share<RenderTargetRenderState> mRenderTargetRenderState;
};


MEDUSA_END;