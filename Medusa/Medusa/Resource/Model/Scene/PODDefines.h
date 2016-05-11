// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Geometry/Scale3.h"
#include "Geometry/Point3.h"
#include "PODAnimiationFlags.h"

MEDUSA_BEGIN;

/************************************************************************/
/*
FIle:
POD Version Block	|	Data Blocks
Block:
Start Tag(8 bytes)	|	Data(0+bytes)	|	End Tag(8 bytes)

Reading algorithm:
while not EOF
{
read 8 bytes
{
if identifier is start tag
{
read 'length' bytes of Data
Handle 'Data'
Go down a level in nested struct
}
}
else if identifier is end tag
{
read 'length' bytes of Data
Handle 'Data'
Go up a level in nested struct
}
}
*/
/************************************************************************/

//SO BIG enum,so that I cannot use strong enum

enum class PODIdentifier
{
	Version				= 1000,
		Scene,
		ExportOption,
		History,
		EndiannessMisMatch  = -402456576,

		BackgroundColor	= 2000,
		AmbientColor,
		NumCamera,
		NumLight,
		NumMesh,
		NumNode,
		NumMeshNode,
		NumTexture,
		NumMaterial,
		NumFrame,
		Camera,		// Will come multiple times
		Light,		// Will come multiple times
		Mesh,		// Will come multiple times
		Node,		// Will come multiple times
		Texture,	// Will come multiple times
		Material,	// Will come multiple times
		Flags,
		FPS,
		UserData,

		MaterialName				= 3000,
		MaterialDiffuseTextureIndex,
		MaterialOpacity,
		MaterialAmbientColor,
		MaterialDiffuseColor,
		MaterialSpecularColor,
		MaterialShininess,
		MaterialEffectFile,
		MaterialEffectName,
		MaterialAmbientTextureIndex,
		MaterialSpecularColorTextureIndex,
		MaterialSpecularLevelTextureIndex,
		MaterialBumpMapTextureIndex,
		MaterialEmissiveTextureIndex,
		MaterialGlossinessTextureIndex,
		MaterialOpacityTextureIndex,
		MaterialReflectionTextureIndex,
		MaterialRefractionTextureIndex,
		MaterialBlendSrcRGB,
		MaterialBlendSrcAlpha,
		MaterialBlendDestRGB,
		MaterialBlendDestAlpha,
		MaterialBlendOperationRGB,
		MaterialBlendOperationAlpha,
		MaterialBlendColor,
		MaterialBlendFactor,
		MaterialFlags,
		MaterialUserData,

		TextureName				= 4000,

		NodeIndex				= 5000,
		NodeName,
		NodeMaterialIndex,
		NodeParentIndex,
		NodePosition,	//older format
		NodeRotation,	//older format
		NodeScale,	//older format

		NodeAnimationPositions=5007,
		NodeAnimationRotations,
		NodeAnimationScales,
		NodeAnimationMatrixes=5010,
		NodeMatrix=5011,	//older format
		NodeAnimationFlags=5012,
		NodeAnimationPositionIndexes,
		NodeAnimationRotationIndexes,
		NodeAnimationScaleIndexes,
		NodeAnimationMatrixIndexes,
		NodeUserData,

		MeshVertexCount			= 6000,
		MeshFaceCount,
		MeshUVWChannelCount,
		MeshFaces,
		MeshStripLengths,
		MeshStripCount,
		MeshVertexList,
		MeshNormalList,
		MeshTangentList,
		MeshBinormalList,
		MeshUVWList,			// Will come multiple times
		MeshVertexColorList,
		MeshBoneIndexList,
		MeshBoneWeights,
		MeshInterleavedData,
		MeshBoneBatchIndexList,
		MeshBoneBatchIndexCounts,
		MeshBoneBatchOffsets,
		MeshBoneBatchMaxCount,
		MeshBoneBatchCount,
		MeshUnpackMatrix,

		LightTargetObjectIndex			= 7000,
		LightColor,
		LightType,
		LightConstantAttenuation,
		LightLinearAttenuation,
		LightQuadraticAttenuation,
		LightFalloffAngle,
		LightFalloffExponent,

		CameraTargetObjectIndex			= 8000,
		CameraFOV,
		CameraFar,
		CameraNear,
		CameraFOVAnimation,

		DataType			= 9000,
		ComponentCount,
		Stride,
		Data
};


enum class PODPrimitiveType { Triangles=0 };

struct PODScale
{
	PODScale():Scale(Scale3F::One),Axis(Point3F::Zero),StretchRotation(0.f)
	{

	}
	PODScale(const Scale3F& scale):Scale(scale),Axis(Point3F::Zero),StretchRotation(0.f)
	{

	}
	union
	{
		float Buffer[7];
		struct  
		{
			Scale3F Scale;
			Point3F Axis;
			float StretchRotation;
		};
	};

};


MEDUSA_END;