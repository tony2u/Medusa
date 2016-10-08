// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaPreDeclares.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Resource/Effect/Pass/IRenderPass.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Share.h"
#include "Resource/Effect/Shader/IShader.h"

MEDUSA_BEGIN;

class RenderPassCreater:public MapObjectFactory<StringRef, IRenderPass*(const FileIdRef& fileId, const Share<IShader>& vertexShader, const Share<IShader>& pixelShader,int index)>, public Singleton<RenderPassCreater>
{
	RenderPassCreater();
	~RenderPassCreater() {}
	friend class Singleton<RenderPassCreater>;
public:
	using MapObjectFactory<StringRef, IRenderPass*(const FileIdRef& fileId, const Share<IShader>& vertexShader, const Share<IShader>& pixelShader,int index)>::Create;
	template<typename T>
	Share<IRenderPass> Create(const FileIdRef& fileId, const Share<IShader>& vertexShader, const Share<IShader>& pixelShader,int index=0)
	{
		return Create(typename T::ClassNameStatic(),fileId,vertexShader,pixelShader,index);
	}
};


#define MEDUSA_DECLARE_RENDER_PASS_CREATER() 				   \
public:													   \
	const static StaticConstructor mStaticConstructor;		   \
	static void RegisterShader();

#define MEDUSA_IMPLEMENT_RENDER_PASS_CREATER(className,id) 																 \
	const StaticConstructor className::mStaticConstructor(RegisterShader);						 \
	void className::RegisterShader(){RenderPassCreater::Instance().Register<className>(id);}				 

MEDUSA_END;