// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Geometry/Color3.h"
#include "Core/Geometry/Color4.h"



MEDUSA_BEGIN;


const Color3B Color3B::Black((byte)0,(byte)0,(byte)0);
const Color3B Color3B::White((byte)255,(byte)255,(byte)255);
const Color3B Color3B::Red((byte)255,(byte)0,(byte)0);
const Color3B Color3B::Green((byte)0,(byte)255,(byte)0);
const Color3B Color3B::Blue((byte)0,(byte)0,(byte)255);


const Color3F Color3F::Black((float)0.f,(float)0.f,(float)0.f);
const Color3F Color3F::White((float)1,(float)1,(float)1);
const Color3F Color3F::Red((float)1,(float)0,(float)0);
const Color3F Color3F::Green((float)0,(float)1,(float)0);
const Color3F Color3F::Blue((float)0,(float)0,(float)1);

Color3F Color3B::To3F() const
{
	return Color3F((float)R/255,(float)G/255,(float)B/255);
}

Color3B::Color3B( const Color4B& color ):R(color.R),G(color.G),B(color.B)
{

}

Color3B& Color3B::operator=( const Color4B& color )
{
	R=color.R;
	G=color.G;
	B=color.B;
	return *this;
}



Color3F::Color3F( const Color4F& color ):R(color.R),G(color.G),B(color.B)
{

}

Color3F& Color3F::operator=( const Color4F& color )
{
	R=color.R;
	G=color.G;
	B=color.B;
	return *this;

}

MEDUSA_END;
