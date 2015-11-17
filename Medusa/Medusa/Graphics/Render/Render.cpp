// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Render.h"
#include "Graphics/Render/OpenGLES2Render.h"
#include "Graphics/Render/OpenGLES3Render.h"



MEDUSA_BEGIN;


Render::Render()
{

}

Render::~Render()
{

}

bool Render::SetupRender(GraphicsAPI api)
{
	SAFE_DELETE(mRender);
	
	switch (api)
	{
	case GraphicsAPI::OpenGLES2:
		if (GraphicsSupportAPI::Support(api))
		{
			mRender = new OpenGLES2Render();
			return true;
		}
		break;
	case GraphicsAPI::OpenGLES3:
		if (GraphicsSupportAPI::Support(api))
		{
			mRender = new OpenGLES3Render();
			return true;
		}
		break;
	case GraphicsAPI::DirectX:
	default:
		break;
	}
	return false;
}

bool Render::DestoryRender()
{
	SAFE_DELETE(mRender);
	return true;
}

IRender* Render::mRender = nullptr;

MEDUSA_END;