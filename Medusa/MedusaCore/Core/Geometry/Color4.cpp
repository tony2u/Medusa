// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Geometry/Color4.h"
#include "Core/Geometry/Color3.h"
#include "Core/Assertion/CommonAssert.h"



MEDUSA_BEGIN;

//////////////////////////////////////////////////////////////////////////

const Color4B Color4B::Zero(0,0,0,0);

const Color4B Color4B::AliceBlue((byte)0xf0,(byte)0xf8,(byte)0xff,(byte)0xff);
const Color4B Color4B::AntiqueWhite((byte)0xfa,(byte)0xeb,(byte)0xd7,(byte)0xff);
const Color4B Color4B::Aqua((byte)0x00,(byte)0xff,(byte)0xff,(byte)0xff);
const Color4B Color4B::Aquamarine((byte)0x7f,(byte)0xff,(byte)0xd4,(byte)0xff);
const Color4B Color4B::Azure((byte)0xf0,(byte)0xff,(byte)0xff,(byte)0xff);
const Color4B Color4B::Beige((byte)0xf5,(byte)0xf5,(byte)0xdc,(byte)0xff);
const Color4B Color4B::Bisque((byte)0xff,(byte)0xe4,(byte)0xc4,(byte)0xff);
const Color4B Color4B::Black((byte)0x00,(byte)0x00,(byte)0x00,(byte)0xff);
const Color4B Color4B::BlanchedAlmond((byte)0xff,(byte)0xeb,(byte)0xcd,(byte)0xff);
const Color4B Color4B::Blue((byte)0x00,(byte)0x00,(byte)0xff,(byte)0xff);
const Color4B Color4B::BlueViolet((byte)0x8a,(byte)0x2b,(byte)0xe2,(byte)0xff);
const Color4B Color4B::Brown((byte)0xa5,(byte)0x2a,(byte)0x2a,(byte)0xff);
const Color4B Color4B::BurlyWood((byte)0xde,(byte)0xb8,(byte)0x87,(byte)0xff);
const Color4B Color4B::CadetBlue((byte)0x5f,(byte)0x9e,(byte)0xa0,(byte)0xff);
const Color4B Color4B::Chartreuse((byte)0x7f,(byte)0xff,(byte)0x00,(byte)0xff);
const Color4B Color4B::Chocolate((byte)0xd2,(byte)0x69,(byte)0x1e,(byte)0xff);
const Color4B Color4B::Coral((byte)0xff,(byte)0x7f,(byte)0x50,(byte)0xff);
const Color4B Color4B::CornflowerBlue((byte)0x64,(byte)0x95,(byte)0xed,(byte)0xff);
const Color4B Color4B::Cornsilk((byte)0xff,(byte)0xf8,(byte)0xdc,(byte)0xff);
const Color4B Color4B::Crimson((byte)0xdc,(byte)0x14,(byte)0x3c,(byte)0xff);
const Color4B Color4B::Cyan((byte)0x00,(byte)0xff,(byte)0xff,(byte)0xff);
const Color4B Color4B::DarkBlue((byte)0x00,(byte)0x00,(byte)0x8b,(byte)0xff);
const Color4B Color4B::DarkCyan((byte)0x00,(byte)0x8b,(byte)0x8b,(byte)0xff);
const Color4B Color4B::DarkGoldenrod((byte)0xb8,(byte)0x86,(byte)0x0b,(byte)0xff);
const Color4B Color4B::DarkGray((byte)0xa9,(byte)0xa9,(byte)0xa9,(byte)0xff);
const Color4B Color4B::DarkGreen((byte)0x00,(byte)0x64,(byte)0x00,(byte)0xff);
const Color4B Color4B::DarkKhaki((byte)0xbd,(byte)0xb7,(byte)0x6b,(byte)0xff);
const Color4B Color4B::DarkMagenta((byte)0x8b,(byte)0x00,(byte)0x8b,(byte)0xff);
const Color4B Color4B::DarkOliveGreen((byte)0x55,(byte)0x6b,(byte)0x2f,(byte)0xff);
const Color4B Color4B::DarkOrange((byte)0xff,(byte)0x8c,(byte)0x00,(byte)0xff);
const Color4B Color4B::DarkOrchid((byte)0x99,(byte)0x32,(byte)0xcc,(byte)0xff);
const Color4B Color4B::DarkRed((byte)0x8b,(byte)0x00,(byte)0x00,(byte)0xff);
const Color4B Color4B::DarkSalmon((byte)0xe9,(byte)0x96,(byte)0x7a,(byte)0xff);
const Color4B Color4B::DarkSeaGreen((byte)0x8f,(byte)0xbc,(byte)0x8f,(byte)0xff);
const Color4B Color4B::DarkSlateBlue((byte)0x48,(byte)0x3d,(byte)0x8b,(byte)0xff);
const Color4B Color4B::DarkSlateGray((byte)0x2f,(byte)0x4f,(byte)0x4f,(byte)0xff);
const Color4B Color4B::DarkTurquoise((byte)0x00,(byte)0xce,(byte)0xd1,(byte)0xff);
const Color4B Color4B::DarkViolet((byte)0x94,(byte)0x00,(byte)0xd3,(byte)0xff);
const Color4B Color4B::DeepPink((byte)0xff,(byte)0x14,(byte)0x93,(byte)0xff);
const Color4B Color4B::DeepSkyBlue((byte)0x00,(byte)0xbf,(byte)0xff,(byte)0xff);
const Color4B Color4B::DimGray((byte)0x69,(byte)0x69,(byte)0x69,(byte)0xff);
const Color4B Color4B::DodgerBlue((byte)0x1e,(byte)0x90,(byte)0xff,(byte)0xff);
const Color4B Color4B::Firebrick((byte)0xb2,(byte)0x22,(byte)0x22,(byte)0xff);
const Color4B Color4B::FloralWhite((byte)0xff,(byte)0xfa,(byte)0xf0,(byte)0xff);
const Color4B Color4B::ForestGreen((byte)0x22,(byte)0x8b,(byte)0x22,(byte)0xff);
const Color4B Color4B::Fuchsia((byte)0xff,(byte)0x00,(byte)0xff,(byte)0xff);
const Color4B Color4B::Gainsboro((byte)0xdc,(byte)0xdc,(byte)0xdc,(byte)0xff);
const Color4B Color4B::GhostWhite((byte)0xf8,(byte)0xf8,(byte)0xff,(byte)0xff);
const Color4B Color4B::Gold((byte)0xff,(byte)0xd7,(byte)0x00,(byte)0xff);
const Color4B Color4B::Goldenrod((byte)0xda,(byte)0xa5,(byte)0x20,(byte)0xff);
const Color4B Color4B::Gray((byte)0x80,(byte)0x80,(byte)0x80,(byte)0xff);
const Color4B Color4B::Green((byte)0x00,(byte)0x80,(byte)0x00,(byte)0xff);
const Color4B Color4B::GreenYellow((byte)0xad,(byte)0xff,(byte)0x2f,(byte)0xff);
const Color4B Color4B::Honeydew((byte)0xf0,(byte)0xff,(byte)0xf0,(byte)0xff);
const Color4B Color4B::HotPink((byte)0xff,(byte)0x69,(byte)0xb4,(byte)0xff);
const Color4B Color4B::IndianRed((byte)0xcd,(byte)0x5c,(byte)0x5c,(byte)0xff);
const Color4B Color4B::Indigo((byte)0x4b,(byte)0x00,(byte)0x82,(byte)0xff);
const Color4B Color4B::Ivory((byte)0xff,(byte)0xff,(byte)0xf0,(byte)0xff);
const Color4B Color4B::Khaki((byte)0xf0,(byte)0xe6,(byte)0x8c,(byte)0xff);
const Color4B Color4B::Lavender((byte)0xe6,(byte)0xe6,(byte)0xfa,(byte)0xff);
const Color4B Color4B::LavenderBlush((byte)0xff,(byte)0xf0,(byte)0xf5,(byte)0xff);
const Color4B Color4B::LawnGreen((byte)0x7c,(byte)0xfc,(byte)0x00,(byte)0xff);
const Color4B Color4B::LemonChiffon((byte)0xff,(byte)0xfa,(byte)0xcd,(byte)0xff);
const Color4B Color4B::LightBlue((byte)0xad,(byte)0xd8,(byte)0xe6,(byte)0xff);
const Color4B Color4B::LightCoral((byte)0xf0,(byte)0x80,(byte)0x80,(byte)0xff);
const Color4B Color4B::LightCyan((byte)0xe0,(byte)0xff,(byte)0xff,(byte)0xff);
const Color4B Color4B::LightGoldenrodYellow((byte)0xfa,(byte)0xfa,(byte)0xd2,(byte)0xff);
const Color4B Color4B::LightGray((byte)0xd3,(byte)0xd3,(byte)0xd3,(byte)0xff);
const Color4B Color4B::LightGreen((byte)0x90,(byte)0xee,(byte)0x90,(byte)0xff);
const Color4B Color4B::LightPink((byte)0xff,(byte)0xb6,(byte)0xc1,(byte)0xff);
const Color4B Color4B::LightSalmon((byte)0xff,(byte)0xa0,(byte)0x7a,(byte)0xff);
const Color4B Color4B::LightSeaGreen((byte)0x20,(byte)0xb2,(byte)0xaa,(byte)0xff);
const Color4B Color4B::LightSkyBlue((byte)0x87,(byte)0xce,(byte)0xfa,(byte)0xff);
const Color4B Color4B::LightSlateGray((byte)0x77,(byte)0x88,(byte)0x99,(byte)0xff);
const Color4B Color4B::LightSteelBlue((byte)0xb0,(byte)0xc4,(byte)0xde,(byte)0xff);
const Color4B Color4B::LightYellow((byte)0xff,(byte)0xff,(byte)0xe0,(byte)0xff);
const Color4B Color4B::Lime((byte)0x00,(byte)0xff,(byte)0x00,(byte)0xff);
const Color4B Color4B::LimeGreen((byte)0x32,(byte)0xcd,(byte)0x32,(byte)0xff);
const Color4B Color4B::Linen((byte)0xfa,(byte)0xf0,(byte)0xe6,(byte)0xff);
const Color4B Color4B::Magenta((byte)0xff,(byte)0x00,(byte)0xff,(byte)0xff);
const Color4B Color4B::Maroon((byte)0x80,(byte)0x00,(byte)0x00,(byte)0xff);
const Color4B Color4B::MediumAquamarine((byte)0x66,(byte)0xcd,(byte)0xaa,(byte)0xff);
const Color4B Color4B::MediumBlue((byte)0x00,(byte)0x00,(byte)0xcd,(byte)0xff);
const Color4B Color4B::MediumOrchid((byte)0xba,(byte)0x55,(byte)0xd3,(byte)0xff);
const Color4B Color4B::MediumPurple((byte)0x93,(byte)0x70,(byte)0xdb,(byte)0xff);
const Color4B Color4B::MediumSeaGreen((byte)0x3c,(byte)0xb3,(byte)0x71,(byte)0xff);
const Color4B Color4B::MediumSlateBlue((byte)0x7b,(byte)0x68,(byte)0xee,(byte)0xff);
const Color4B Color4B::MediumSpringGreen((byte)0x00,(byte)0xfa,(byte)0x9a,(byte)0xff);
const Color4B Color4B::MediumTurquoise((byte)0x48,(byte)0xd1,(byte)0xcc,(byte)0xff);
const Color4B Color4B::MediumVioletRed((byte)0xc7,(byte)0x15,(byte)0x85,(byte)0xff);
const Color4B Color4B::MidnightBlue((byte)0x19,(byte)0x19,(byte)0x70,(byte)0xff);
const Color4B Color4B::MintCream((byte)0xf5,(byte)0xff,(byte)0xfa,(byte)0xff);
const Color4B Color4B::MistyRose((byte)0xff,(byte)0xe4,(byte)0xe1,(byte)0xff);
const Color4B Color4B::Moccasin((byte)0xff,(byte)0xe4,(byte)0xb5,(byte)0xff);
const Color4B Color4B::NavajoWhite((byte)0xff,(byte)0xde,(byte)0xad,(byte)0xff);
const Color4B Color4B::Navy((byte)0x00,(byte)0x00,(byte)0x80,(byte)0xff);
const Color4B Color4B::OldLace((byte)0xfd,(byte)0xf5,(byte)0xe6,(byte)0xff);
const Color4B Color4B::Olive((byte)0x80,(byte)0x80,(byte)0x00,(byte)0xff);
const Color4B Color4B::OliveDrab((byte)0x6b,(byte)0x8e,(byte)0x23,(byte)0xff);
const Color4B Color4B::Orange((byte)0xff,(byte)0xa5,(byte)0x00,(byte)0xff);
const Color4B Color4B::OrangeRed((byte)0xff,(byte)0x45,(byte)0x00,(byte)0xff);
const Color4B Color4B::Orchid((byte)0xda,(byte)0x70,(byte)0xd6,(byte)0xff);
const Color4B Color4B::PaleGoldenrod((byte)0xee,(byte)0xe8,(byte)0xaa,(byte)0xff);
const Color4B Color4B::PaleGreen((byte)0x98,(byte)0xfb,(byte)0x98,(byte)0xff);
const Color4B Color4B::PaleTurquoise((byte)0xaf,(byte)0xee,(byte)0xee,(byte)0xff);
const Color4B Color4B::PaleVioletRed((byte)0xdb,(byte)0x70,(byte)0x93,(byte)0xff);
const Color4B Color4B::PapayaWhip((byte)0xff,(byte)0xef,(byte)0xd5,(byte)0xff);
const Color4B Color4B::PeachPuff((byte)0xff,(byte)0xda,(byte)0xb9,(byte)0xff);
const Color4B Color4B::Peru((byte)0xcd,(byte)0x85,(byte)0x3f,(byte)0xff);
const Color4B Color4B::Pink((byte)0xff,(byte)0xc0,(byte)0xcb,(byte)0xff);
const Color4B Color4B::Plum((byte)0xdd,(byte)0xa0,(byte)0xdd,(byte)0xff);
const Color4B Color4B::PowderBlue((byte)0xb0,(byte)0xe0,(byte)0xe6,(byte)0xff);
const Color4B Color4B::Purple((byte)0x80,(byte)0x00,(byte)0x80,(byte)0xff);
const Color4B Color4B::Red((byte)0xff,(byte)0x00,(byte)0x00,(byte)0xff);
const Color4B Color4B::RosyBrown((byte)0xbc,(byte)0x8f,(byte)0x8f,(byte)0xff);
const Color4B Color4B::RoyalBlue((byte)0x41,(byte)0x69,(byte)0xe1,(byte)0xff);
const Color4B Color4B::SaddleBrown((byte)0x8b,(byte)0x45,(byte)0x13,(byte)0xff);
const Color4B Color4B::Salmon((byte)0xfa,(byte)0x80,(byte)0x72,(byte)0xff);
const Color4B Color4B::SandyBrown((byte)0xf4,(byte)0xa4,(byte)0x60,(byte)0xff);
const Color4B Color4B::SeaGreen((byte)0x2e,(byte)0x8b,(byte)0x57,(byte)0xff);
const Color4B Color4B::SeaShell((byte)0xff,(byte)0xf5,(byte)0xee,(byte)0xff);
const Color4B Color4B::Sienna((byte)0xa0,(byte)0x52,(byte)0x2d,(byte)0xff);
const Color4B Color4B::Silver((byte)0xc0,(byte)0xc0,(byte)0xc0,(byte)0xff);
const Color4B Color4B::SkyBlue((byte)0x87,(byte)0xce,(byte)0xeb,(byte)0xff);
const Color4B Color4B::SlateBlue((byte)0x6a,(byte)0x5a,(byte)0xcd,(byte)0xff);
const Color4B Color4B::SlateGray((byte)0x70,(byte)0x80,(byte)0x90,(byte)0xff);
const Color4B Color4B::Snow((byte)0xff,(byte)0xfa,(byte)0xfa,(byte)0xff);
const Color4B Color4B::SpringGreen((byte)0x00,(byte)0xff,(byte)0x7f,(byte)0xff);
const Color4B Color4B::SteelBlue((byte)0x46,(byte)0x82,(byte)0xb4,(byte)0xff);
const Color4B Color4B::Tan((byte)0xd2,(byte)0xb4,(byte)0x8c,(byte)0xff);
const Color4B Color4B::Teal((byte)0x00,(byte)0x80,(byte)0x80,(byte)0xff);
const Color4B Color4B::Thistle((byte)0xd8,(byte)0xbf,(byte)0xd8,(byte)0xff);
const Color4B Color4B::Tomato((byte)0xff,(byte)0x63,(byte)0x47,(byte)0xff);
const Color4B Color4B::Transparent((byte)0xff,(byte)0xff,(byte)0x00,(byte)0xff);
const Color4B Color4B::Turquoise((byte)0x40,(byte)0xe0,(byte)0xd0,(byte)0xff);
const Color4B Color4B::Violet((byte)0xee,(byte)0x82,(byte)0xee,(byte)0xff);
const Color4B Color4B::Wheat((byte)0xf5,(byte)0xde,(byte)0xb3,(byte)0xff);
const Color4B Color4B::White((byte)0xff,(byte)0xff,(byte)0xff,(byte)0xff);
const Color4B Color4B::WhiteSmoke((byte)0xf5,(byte)0xf5,(byte)0xf5,(byte)0xff);
const Color4B Color4B::Yellow((byte)0xff,(byte)0xff,(byte)0x00,(byte)0xff);
const Color4B Color4B::YellowGreen((byte)0x9a,(byte)0xcd,(byte)0x32,(byte)0xff);

Color4F Color4B::To4F() const
{
	return Color4F((float)R/255,(float)G/255,(float)B/255,(float)A/255);
}

Color4B::Color4B( const Color3B& color ):R(color.R),G(color.G),B(color.B),A(255)
{

}

Color4B& Color4B::operator=( const Color3B& color )
{
	Data=color.Data;
	A=255;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
const Color4F Color4F::Zero((float)0.f,(float)0.f,(float)0.f,(float)0.f);

const Color4F Color4F::AliceBlue((byte)0xf0,(byte)0xf8,(byte)0xff,(byte)0xff);
const Color4F Color4F::AntiqueWhite((byte)0xfa,(byte)0xeb,(byte)0xd7,(byte)0xff);
const Color4F Color4F::Aqua((byte)0x00,(byte)0xff,(byte)0xff,(byte)0xff);
const Color4F Color4F::Aquamarine((byte)0x7f,(byte)0xff,(byte)0xd4,(byte)0xff);
const Color4F Color4F::Azure((byte)0xf0,(byte)0xff,(byte)0xff,(byte)0xff);
const Color4F Color4F::Beige((byte)0xf5,(byte)0xf5,(byte)0xdc,(byte)0xff);
const Color4F Color4F::Bisque((byte)0xff,(byte)0xe4,(byte)0xc4,(byte)0xff);
const Color4F Color4F::Black((byte)0x00,(byte)0x00,(byte)0x00,(byte)0xff);
const Color4F Color4F::BlanchedAlmond((byte)0xff,(byte)0xeb,(byte)0xcd,(byte)0xff);
const Color4F Color4F::Blue((byte)0x00,(byte)0x00,(byte)0xff,(byte)0xff);
const Color4F Color4F::BlueViolet((byte)0x8a,(byte)0x2b,(byte)0xe2,(byte)0xff);
const Color4F Color4F::Brown((byte)0xa5,(byte)0x2a,(byte)0x2a,(byte)0xff);
const Color4F Color4F::BurlyWood((byte)0xde,(byte)0xb8,(byte)0x87,(byte)0xff);
const Color4F Color4F::CadetBlue((byte)0x5f,(byte)0x9e,(byte)0xa0,(byte)0xff);
const Color4F Color4F::Chartreuse((byte)0x7f,(byte)0xff,(byte)0x00,(byte)0xff);
const Color4F Color4F::Chocolate((byte)0xd2,(byte)0x69,(byte)0x1e,(byte)0xff);
const Color4F Color4F::Coral((byte)0xff,(byte)0x7f,(byte)0x50,(byte)0xff);
const Color4F Color4F::CornflowerBlue((byte)0x64,(byte)0x95,(byte)0xed,(byte)0xff);
const Color4F Color4F::Cornsilk((byte)0xff,(byte)0xf8,(byte)0xdc,(byte)0xff);
const Color4F Color4F::Crimson((byte)0xdc,(byte)0x14,(byte)0x3c,(byte)0xff);
const Color4F Color4F::Cyan((byte)0x00,(byte)0xff,(byte)0xff,(byte)0xff);
const Color4F Color4F::DarkBlue((byte)0x00,(byte)0x00,(byte)0x8b,(byte)0xff);
const Color4F Color4F::DarkCyan((byte)0x00,(byte)0x8b,(byte)0x8b,(byte)0xff);
const Color4F Color4F::DarkGoldenrod((byte)0xb8,(byte)0x86,(byte)0x0b,(byte)0xff);
const Color4F Color4F::DarkGray((byte)0xa9,(byte)0xa9,(byte)0xa9,(byte)0xff);
const Color4F Color4F::DarkGreen((byte)0x00,(byte)0x64,(byte)0x00,(byte)0xff);
const Color4F Color4F::DarkKhaki((byte)0xbd,(byte)0xb7,(byte)0x6b,(byte)0xff);
const Color4F Color4F::DarkMagenta((byte)0x8b,(byte)0x00,(byte)0x8b,(byte)0xff);
const Color4F Color4F::DarkOliveGreen((byte)0x55,(byte)0x6b,(byte)0x2f,(byte)0xff);
const Color4F Color4F::DarkOrange((byte)0xff,(byte)0x8c,(byte)0x00,(byte)0xff);
const Color4F Color4F::DarkOrchid((byte)0x99,(byte)0x32,(byte)0xcc,(byte)0xff);
const Color4F Color4F::DarkRed((byte)0x8b,(byte)0x00,(byte)0x00,(byte)0xff);
const Color4F Color4F::DarkSalmon((byte)0xe9,(byte)0x96,(byte)0x7a,(byte)0xff);
const Color4F Color4F::DarkSeaGreen((byte)0x8f,(byte)0xbc,(byte)0x8f,(byte)0xff);
const Color4F Color4F::DarkSlateBlue((byte)0x48,(byte)0x3d,(byte)0x8b,(byte)0xff);
const Color4F Color4F::DarkSlateGray((byte)0x2f,(byte)0x4f,(byte)0x4f,(byte)0xff);
const Color4F Color4F::DarkTurquoise((byte)0x00,(byte)0xce,(byte)0xd1,(byte)0xff);
const Color4F Color4F::DarkViolet((byte)0x94,(byte)0x00,(byte)0xd3,(byte)0xff);
const Color4F Color4F::DeepPink((byte)0xff,(byte)0x14,(byte)0x93,(byte)0xff);
const Color4F Color4F::DeepSkyBlue((byte)0x00,(byte)0xbf,(byte)0xff,(byte)0xff);
const Color4F Color4F::DimGray((byte)0x69,(byte)0x69,(byte)0x69,(byte)0xff);
const Color4F Color4F::DodgerBlue((byte)0x1e,(byte)0x90,(byte)0xff,(byte)0xff);
const Color4F Color4F::Firebrick((byte)0xb2,(byte)0x22,(byte)0x22,(byte)0xff);
const Color4F Color4F::FloralWhite((byte)0xff,(byte)0xfa,(byte)0xf0,(byte)0xff);
const Color4F Color4F::ForestGreen((byte)0x22,(byte)0x8b,(byte)0x22,(byte)0xff);
const Color4F Color4F::Fuchsia((byte)0xff,(byte)0x00,(byte)0xff,(byte)0xff);
const Color4F Color4F::Gainsboro((byte)0xdc,(byte)0xdc,(byte)0xdc,(byte)0xff);
const Color4F Color4F::GhostWhite((byte)0xf8,(byte)0xf8,(byte)0xff,(byte)0xff);
const Color4F Color4F::Gold((byte)0xff,(byte)0xd7,(byte)0x00,(byte)0xff);
const Color4F Color4F::Goldenrod((byte)0xda,(byte)0xa5,(byte)0x20,(byte)0xff);
const Color4F Color4F::Gray((byte)0x80,(byte)0x80,(byte)0x80,(byte)0xff);
const Color4F Color4F::Green((byte)0x00,(byte)0x80,(byte)0x00,(byte)0xff);
const Color4F Color4F::GreenYellow((byte)0xad,(byte)0xff,(byte)0x2f,(byte)0xff);
const Color4F Color4F::Honeydew((byte)0xf0,(byte)0xff,(byte)0xf0,(byte)0xff);
const Color4F Color4F::HotPink((byte)0xff,(byte)0x69,(byte)0xb4,(byte)0xff);
const Color4F Color4F::IndianRed((byte)0xcd,(byte)0x5c,(byte)0x5c,(byte)0xff);
const Color4F Color4F::Indigo((byte)0x4b,(byte)0x00,(byte)0x82,(byte)0xff);
const Color4F Color4F::Ivory((byte)0xff,(byte)0xff,(byte)0xf0,(byte)0xff);
const Color4F Color4F::Khaki((byte)0xf0,(byte)0xe6,(byte)0x8c,(byte)0xff);
const Color4F Color4F::Lavender((byte)0xe6,(byte)0xe6,(byte)0xfa,(byte)0xff);
const Color4F Color4F::LavenderBlush((byte)0xff,(byte)0xf0,(byte)0xf5,(byte)0xff);
const Color4F Color4F::LawnGreen((byte)0x7c,(byte)0xfc,(byte)0x00,(byte)0xff);
const Color4F Color4F::LemonChiffon((byte)0xff,(byte)0xfa,(byte)0xcd,(byte)0xff);
const Color4F Color4F::LightBlue((byte)0xad,(byte)0xd8,(byte)0xe6,(byte)0xff);
const Color4F Color4F::LightCoral((byte)0xf0,(byte)0x80,(byte)0x80,(byte)0xff);
const Color4F Color4F::LightCyan((byte)0xe0,(byte)0xff,(byte)0xff,(byte)0xff);
const Color4F Color4F::LightGoldenrodYellow((byte)0xfa,(byte)0xfa,(byte)0xd2,(byte)0xff);
const Color4F Color4F::LightGray((byte)0xd3,(byte)0xd3,(byte)0xd3,(byte)0xff);
const Color4F Color4F::LightGreen((byte)0x90,(byte)0xee,(byte)0x90,(byte)0xff);
const Color4F Color4F::LightPink((byte)0xff,(byte)0xb6,(byte)0xc1,(byte)0xff);
const Color4F Color4F::LightSalmon((byte)0xff,(byte)0xa0,(byte)0x7a,(byte)0xff);
const Color4F Color4F::LightSeaGreen((byte)0x20,(byte)0xb2,(byte)0xaa,(byte)0xff);
const Color4F Color4F::LightSkyBlue((byte)0x87,(byte)0xce,(byte)0xfa,(byte)0xff);
const Color4F Color4F::LightSlateGray((byte)0x77,(byte)0x88,(byte)0x99,(byte)0xff);
const Color4F Color4F::LightSteelBlue((byte)0xb0,(byte)0xc4,(byte)0xde,(byte)0xff);
const Color4F Color4F::LightYellow((byte)0xff,(byte)0xff,(byte)0xe0,(byte)0xff);
const Color4F Color4F::Lime((byte)0x00,(byte)0xff,(byte)0x00,(byte)0xff);
const Color4F Color4F::LimeGreen((byte)0x32,(byte)0xcd,(byte)0x32,(byte)0xff);
const Color4F Color4F::Linen((byte)0xfa,(byte)0xf0,(byte)0xe6,(byte)0xff);
const Color4F Color4F::Magenta((byte)0xff,(byte)0x00,(byte)0xff,(byte)0xff);
const Color4F Color4F::Maroon((byte)0x80,(byte)0x00,(byte)0x00,(byte)0xff);
const Color4F Color4F::MediumAquamarine((byte)0x66,(byte)0xcd,(byte)0xaa,(byte)0xff);
const Color4F Color4F::MediumBlue((byte)0x00,(byte)0x00,(byte)0xcd,(byte)0xff);
const Color4F Color4F::MediumOrchid((byte)0xba,(byte)0x55,(byte)0xd3,(byte)0xff);
const Color4F Color4F::MediumPurple((byte)0x93,(byte)0x70,(byte)0xdb,(byte)0xff);
const Color4F Color4F::MediumSeaGreen((byte)0x3c,(byte)0xb3,(byte)0x71,(byte)0xff);
const Color4F Color4F::MediumSlateBlue((byte)0x7b,(byte)0x68,(byte)0xee,(byte)0xff);
const Color4F Color4F::MediumSpringGreen((byte)0x00,(byte)0xfa,(byte)0x9a,(byte)0xff);
const Color4F Color4F::MediumTurquoise((byte)0x48,(byte)0xd1,(byte)0xcc,(byte)0xff);
const Color4F Color4F::MediumVioletRed((byte)0xc7,(byte)0x15,(byte)0x85,(byte)0xff);
const Color4F Color4F::MidnightBlue((byte)0x19,(byte)0x19,(byte)0x70,(byte)0xff);
const Color4F Color4F::MintCream((byte)0xf5,(byte)0xff,(byte)0xfa,(byte)0xff);
const Color4F Color4F::MistyRose((byte)0xff,(byte)0xe4,(byte)0xe1,(byte)0xff);
const Color4F Color4F::Moccasin((byte)0xff,(byte)0xe4,(byte)0xb5,(byte)0xff);
const Color4F Color4F::NavajoWhite((byte)0xff,(byte)0xde,(byte)0xad,(byte)0xff);
const Color4F Color4F::Navy((byte)0x00,(byte)0x00,(byte)0x80,(byte)0xff);
const Color4F Color4F::OldLace((byte)0xfd,(byte)0xf5,(byte)0xe6,(byte)0xff);
const Color4F Color4F::Olive((byte)0x80,(byte)0x80,(byte)0x00,(byte)0xff);
const Color4F Color4F::OliveDrab((byte)0x6b,(byte)0x8e,(byte)0x23,(byte)0xff);
const Color4F Color4F::Orange((byte)0xff,(byte)0xa5,(byte)0x00,(byte)0xff);
const Color4F Color4F::OrangeRed((byte)0xff,(byte)0x45,(byte)0x00,(byte)0xff);
const Color4F Color4F::Orchid((byte)0xda,(byte)0x70,(byte)0xd6,(byte)0xff);
const Color4F Color4F::PaleGoldenrod((byte)0xee,(byte)0xe8,(byte)0xaa,(byte)0xff);
const Color4F Color4F::PaleGreen((byte)0x98,(byte)0xfb,(byte)0x98,(byte)0xff);
const Color4F Color4F::PaleTurquoise((byte)0xaf,(byte)0xee,(byte)0xee,(byte)0xff);
const Color4F Color4F::PaleVioletRed((byte)0xdb,(byte)0x70,(byte)0x93,(byte)0xff);
const Color4F Color4F::PapayaWhip((byte)0xff,(byte)0xef,(byte)0xd5,(byte)0xff);
const Color4F Color4F::PeachPuff((byte)0xff,(byte)0xda,(byte)0xb9,(byte)0xff);
const Color4F Color4F::Peru((byte)0xcd,(byte)0x85,(byte)0x3f,(byte)0xff);
const Color4F Color4F::Pink((byte)0xff,(byte)0xc0,(byte)0xcb,(byte)0xff);
const Color4F Color4F::Plum((byte)0xdd,(byte)0xa0,(byte)0xdd,(byte)0xff);
const Color4F Color4F::PowderBlue((byte)0xb0,(byte)0xe0,(byte)0xe6,(byte)0xff);
const Color4F Color4F::Purple((byte)0x80,(byte)0x00,(byte)0x80,(byte)0xff);
const Color4F Color4F::Red((byte)0xff,(byte)0x00,(byte)0x00,(byte)0xff);
const Color4F Color4F::RosyBrown((byte)0xbc,(byte)0x8f,(byte)0x8f,(byte)0xff);
const Color4F Color4F::RoyalBlue((byte)0x41,(byte)0x69,(byte)0xe1,(byte)0xff);
const Color4F Color4F::SaddleBrown((byte)0x8b,(byte)0x45,(byte)0x13,(byte)0xff);
const Color4F Color4F::Salmon((byte)0xfa,(byte)0x80,(byte)0x72,(byte)0xff);
const Color4F Color4F::SandyBrown((byte)0xf4,(byte)0xa4,(byte)0x60,(byte)0xff);
const Color4F Color4F::SeaGreen((byte)0x2e,(byte)0x8b,(byte)0x57,(byte)0xff);
const Color4F Color4F::SeaShell((byte)0xff,(byte)0xf5,(byte)0xee,(byte)0xff);
const Color4F Color4F::Sienna((byte)0xa0,(byte)0x52,(byte)0x2d,(byte)0xff);
const Color4F Color4F::Silver((byte)0xc0,(byte)0xc0,(byte)0xc0,(byte)0xff);
const Color4F Color4F::SkyBlue((byte)0x87,(byte)0xce,(byte)0xeb,(byte)0xff);
const Color4F Color4F::SlateBlue((byte)0x6a,(byte)0x5a,(byte)0xcd,(byte)0xff);
const Color4F Color4F::SlateGray((byte)0x70,(byte)0x80,(byte)0x90,(byte)0xff);
const Color4F Color4F::Snow((byte)0xff,(byte)0xfa,(byte)0xfa,(byte)0xff);
const Color4F Color4F::SpringGreen((byte)0x00,(byte)0xff,(byte)0x7f,(byte)0xff);
const Color4F Color4F::SteelBlue((byte)0x46,(byte)0x82,(byte)0xb4,(byte)0xff);
const Color4F Color4F::Tan((byte)0xd2,(byte)0xb4,(byte)0x8c,(byte)0xff);
const Color4F Color4F::Teal((byte)0x00,(byte)0x80,(byte)0x80,(byte)0xff);
const Color4F Color4F::Thistle((byte)0xd8,(byte)0xbf,(byte)0xd8,(byte)0xff);
const Color4F Color4F::Tomato((byte)0xff,(byte)0x63,(byte)0x47,(byte)0xff);
const Color4F Color4F::Transparent((byte)0xff,(byte)0xff,(byte)0x00,(byte)0xff);
const Color4F Color4F::Turquoise((byte)0x40,(byte)0xe0,(byte)0xd0,(byte)0xff);
const Color4F Color4F::Violet((byte)0xee,(byte)0x82,(byte)0xee,(byte)0xff);
const Color4F Color4F::Wheat((byte)0xf5,(byte)0xde,(byte)0xb3,(byte)0xff);
const Color4F Color4F::White((byte)0xff,(byte)0xff,(byte)0xff,(byte)0xff);
const Color4F Color4F::WhiteSmoke((byte)0xf5,(byte)0xf5,(byte)0xf5,(byte)0xff);
const Color4F Color4F::Yellow((byte)0xff,(byte)0xff,(byte)0x00,(byte)0xff);
const Color4F Color4F::YellowGreen((byte)0x9a,(byte)0xcd,(byte)0x32,(byte)0xff);


Color4F::Color4F( const Color3F& color ):R(color.R),G(color.G),B(color.B),A(1.f)
{

}

Color4F& Color4F::operator=( const Color3F& color )
{
	R=color.R;
	G=color.G;
	B=color.B;
	A=1.f;
	return *this;
}

MEDUSA_END;


#ifdef MEDUSA_SCRIPT
#include "CoreLib/Common/angelscript.h"

MEDUSA_SCRIPT_BEGIN;

void RegisterColor4F(asIScriptEngine* engine)
{
	int r;
	r = engine->RegisterObjectType("Color4F", sizeof(Color4F), asOBJ_VALUE | asOBJ_POD); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Color4F", "float R", asOFFSET(Color4F, R)); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Color4F", "float G", asOFFSET(Color4F, G)); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Color4F", "float B", asOFFSET(Color4F, B)); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Color4F", "float A", asOFFSET(Color4F, A)); MEDUSA_ASSERT_SILENT(r >= 0);


}

MEDUSA_SCRIPT_END;


#endif
