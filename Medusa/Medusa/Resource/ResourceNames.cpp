// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/ResourceNames.h"

MEDUSA_BEGIN;

namespace RenderPassNames
{
	//BEGIN_AUTO_GENERATE_RENDER_PASS_NAMES_CPP

	const StringRef Texture = "Texture.pass";
	const StringRef PositionColor = "PositionColor.pass";
	const StringRef POD = "POD.pass";
	const StringRef FntFont = "FntFont.pass";
	const StringRef Shape = "Shape.pass";


	//BEGIN_AUTO_GENERATE_RENDER_PASS_NAMES_CPP

}

namespace VertexShaderFiles
{
	//BEGIN_AUTO_GENERATE_VERTEX_SHADER_NAMES_CPP

	const FileIdRef Texture = "Texture.vsh";
	const FileIdRef Position = "Position.vsh";
	const FileIdRef POD = "POD.vsh";
	const FileIdRef FntFont = "FntFont.vsh";
	const FileIdRef Shape = "Shape.vsh";







	//END_AUTO_GENERATE_VERTEX_SHADER_NAMES_CPP

}

namespace PixelShaderFiles
{
	//BEGIN_AUTO_GENERATE_PIXEL_SHADER_NAMES_CPP

	const FileIdRef Texture = "Texture.fsh";
	const FileIdRef Color = "Color.fsh";
	const FileIdRef POD = "POD.fsh";
	const FileIdRef FntFont = "FntFont.fsh";
	const FileIdRef Shape = "Shape.fsh";







	//END_AUTO_GENERATE_PIXEL_SHADER_NAMES_CPP
}


namespace ShaderConstantNames
{
	const StringRef AlphaTest = "uAlphaTest";

	const StringRef WorldViewProjectMatrix = "uWorldViewProjectMatrix";
	const StringRef ViewProjectMatrix = "uViewProjectMatrix";

	const StringRef WorldMatrix = "uWorldMatrix";
	const StringRef WorldViewMatrixIT = "uWorldViewMatrixIT";




}

namespace ShaderSamplerNames
{
	const StringRef Texture = "uTextureSampler";
	const StringRef Depth = "uDepthSampler";

	const StringRef NormalMap = "uNormalMapSampler";
	const StringRef DisplacementMap = "uDisplacementMapSampler";
	const StringRef HeightMap = "uHeightMapSampler";
	const StringRef Reflect = "uReflectSampler";
	const StringRef Shadow = "uShadowSampler";
	const StringRef Cube = "uCubeSampler";
	const StringRef Mask = "uMaskSampler";





}

namespace ShaderAttributeNames
{
	const StringRef VertexArray = "aVertex";
	const StringRef TexCoordArray = "aTexCoord";
	const StringRef ColorArray = "aColor";
	const StringRef NormalArray = "aNormal";
	const StringRef TangentArray = "aTangent";

}

namespace ShaderDefineNames
{
	const StringRef DirectionLight = "#define DIRECTION_LIGHT\n";
	const StringRef PointLight = "#define POINT_LIGHT\n";
	const StringRef SpotLight = "#define SPOT_LIGHT\n";

	const StringRef GlobalAmbientEnabled = "#define GLOBAL_AMBIENT_ENABLED\n";
	const StringRef AmbientEnabled = "#define AMBIENT_ENABLED\n";
	const StringRef DiffuseEnabled = "#define DIFFUSE_ENABLED\n";
	const StringRef SpecularEnabled = "#define SPECULAR_ENABLED\n";
	const StringRef EmissionEnabled = "#define EMISSION_ENABLED\n";
	const StringRef AttenuationEnabled = "#define ATTENUATION_ENABLED\n";

	const StringRef FogLinear = "#define FOG_LINEAR\n";
	const StringRef FogSmooth = "#define FOG_SMOOTH\n";

}
MEDUSA_END;