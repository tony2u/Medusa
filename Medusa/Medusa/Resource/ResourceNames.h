// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/IO/FileIdRef.h"

MEDUSA_BEGIN;

namespace RenderPassNames
{

	//DO remember to register in RenderPassFactory
	//BEGIN_AUTO_GENERATE_RENDER_PASS_NAMES_H


	const extern StringRef Texture;
	const extern StringRef PositionColor;
	const extern StringRef POD;
	const extern StringRef FntFont;
	const extern StringRef Shape;


	//BEGIN_AUTO_GENERATE_RENDER_PASS_NAMES_H

}

namespace VertexShaderFiles
{
	//BEGIN_AUTO_GENERATE_VERTEX_SHADER_NAMES_H

	const extern FileIdRef Texture;
	const extern FileIdRef Position;
	const extern FileIdRef POD;
	const extern FileIdRef FntFont;
	const extern FileIdRef Shape;





	//END_AUTO_GENERATE_VERTEX_SHADER_NAMES_H

}

namespace PixelShaderFiles
{
	//BEGIN_AUTO_GENERATE_PIXEL_SHADER_NAMES_H

	const extern FileIdRef Texture;
	const extern FileIdRef Color;
	const extern FileIdRef POD;
	const extern FileIdRef FntFont;
	const extern FileIdRef Shape;





	//END_AUTO_GENERATE_PIXEL_SHADER_NAMES_H
}



namespace ShaderConstantNames
{
	const extern StringRef AlphaTest;

	const extern StringRef WorldViewProjectMatrix;
	const extern StringRef ViewProjectMatrix;

	const extern StringRef WorldMatrix;
	const extern StringRef WorldViewMatrixIT;




}

namespace ShaderSamplerNames
{
	const extern StringRef Texture;
	const extern StringRef Depth;

	const extern StringRef NormalMap;
	const extern StringRef DisplacementMap;
	const extern StringRef HeightMap;
	const extern StringRef Reflect;
	const extern StringRef Shadow;
	const extern StringRef Cube;
	const extern StringRef Mask;



}

enum class ShaderAttributeIndex
{
	VertexArray,
	TexCoordArray,
	ColorArray,
	NormalArray,
	TangentArray,
	Count
};

namespace ShaderAttributeNames
{
	const extern StringRef VertexArray;
	const extern StringRef TexCoordArray;
	const extern StringRef ColorArray;
	const extern StringRef NormalArray;
	const extern StringRef TangentArray;
}


namespace ShaderDefineNames
{
	const extern StringRef DirectionLight;
	const extern StringRef PointLight;
	const extern StringRef SpotLight;

	const extern StringRef GlobalAmbientEnabled;
	const extern StringRef AmbientEnabled;
	const extern StringRef DiffuseEnabled;
	const extern StringRef SpecularEnabled;
	const extern StringRef EmissionEnabled;
	const extern StringRef AttenuationEnabled;

	const extern StringRef FogLinear;
	const extern StringRef FogSmooth;

}

MEDUSA_END;