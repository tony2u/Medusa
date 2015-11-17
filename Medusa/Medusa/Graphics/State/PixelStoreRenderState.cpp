// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/PixelStoreRenderState.h"
#include "Graphics/Render/Render.h"
#include "Rendering/RenderingContext.h"

MEDUSA_BEGIN;
PixelStoreRenderState::PixelStoreRenderState()
	:mPackAlignment(4),
	mUnpackAlignment(4)
{
	
}

PixelStoreRenderState::~PixelStoreRenderState()
{

}

void PixelStoreRenderState::Apply()const
{
	//Parameters set with glPixelStore defines how pixel addresses on the client side are generated when transferring between client and server in any direction. 
	//That means, it affects for example how glTexImage (client to server), glDrawPixels (client to server) and glReadPixels (server to client) 
	//should read/store the image data in client memory. 
	Render::Instance().SetPixelStore(GraphicsPixelStoreParameter::PackAlignment,mPackAlignment);
	Render::Instance().SetPixelStore(GraphicsPixelStoreParameter::UnpackAlignment,mUnpackAlignment);
}

PixelStoreRenderState* PixelStoreRenderState::Clone() const
{
	PixelStoreRenderState* state=new PixelStoreRenderState();
	state->SetPackAlignment(mPackAlignment);
	state->SetUnpackAlignment(mUnpackAlignment);
	return state;
}

bool PixelStoreRenderState::Equals( const IRenderState& state ) const
{
	RETURN_FALSE_IF_FALSE(IRenderState::Equals(state));
	const PixelStoreRenderState& val=(const PixelStoreRenderState&)state;
	return mPackAlignment==val.PackAlignment()&&
		mUnpackAlignment==val.UnpackAlignment();

}

PixelStoreRenderState* PixelStoreRenderState::Current()
{
	IRender& render=Render::Instance();
	PixelStoreRenderState* pixelState=new PixelStoreRenderState();
	pixelState->SetUnpackAlignment(render.GetInteger(GraphicsIntegerName::UnpackAlignment));
	pixelState->SetPackAlignment(render.GetInteger(GraphicsIntegerName::PackAlignment));
	return pixelState;
}

MEDUSA_IMPLEMENT_RTTI(PixelStoreRenderState,IRenderState);

MEDUSA_END;