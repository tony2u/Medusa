// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PODMesh.h"
#include "Rendering/RenderingContext.h"
#include "Rendering/RenderingStatics.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"
#include "Resource/ResourceNames.h"
#include "Resource/Effect/Shader/Parameter/ShaderAttribute.h"
#include "Node/Sprite/Sprite.h"

MEDUSA_BEGIN;

PODMesh::PODMesh( bool isStatic/*=false*/)
	:IMesh(isStatic),
	mVertexBufferObject(GraphicsDataType::Float,GraphicsBufferUsage::StaticDraw,1),
	mIndexBufferObject(GraphicsDataType::UShort,GraphicsBufferUsage::StaticDraw,1)
{

}


PODMesh::~PODMesh(void)
{
	
}

void PODMesh::FixInterleavedEndianness()
{
	RETURN_IF(InterleavedData.IsNull()||Utility::IsLittleEndian());
	VertexList.FixInterleavedEndianness(InterleavedData,mVertexCount);
	NormalList.FixInterleavedEndianness(InterleavedData,mVertexCount);
	TangentList.FixInterleavedEndianness(InterleavedData,mVertexCount);
	BinormalList.FixInterleavedEndianness(InterleavedData,mVertexCount);

	FOR_EACH_COLLECTION(i,UVWList)
	{
		PODData& data=*i;
		data.FixInterleavedEndianness(InterleavedData,mVertexCount);
	}
	VertexColorList.FixInterleavedEndianness(InterleavedData,mVertexCount);
	BoneIndexList.FixInterleavedEndianness(InterleavedData,mVertexCount);
	BoneWeights.FixInterleavedEndianness(InterleavedData,mVertexCount);

	//TODO: update mHasAlpha
}


bool PODMesh::Initialzie()
{
	if (!InterleavedData.IsNull())
	{
		mVertexBufferObject.SetDataAndSize((byte*)InterleavedData.Data(),mVertexCount*VertexList.Stride);
	}
	else
	{
		mVertexBufferObject.SetDataAndSize((byte*)VertexList.Data.Data(),mVertexCount*VertexList.Stride);
	}

	if (!Faces.Data.IsNull())
	{
		mIndexBufferObject.SetDataAndSize((byte*)Faces.Data.Data(),IndexCount()*Faces.Stride);
	}

	
	return true;
}


void PODMesh::Apply()
{
	BaseProgramRenderPass* pass = RenderingContext::Instance().ProgramRenderPass();
	ShaderAttribute* vertices= pass->GetAttributeByIndex(ShaderAttributeIndex::VertexArray);
	if (vertices!=nullptr)
	{
		mVertexBufferObject.Apply();
		vertices->Invalidate();
		vertices->SetPointer(3,GraphicsDataType::Float,false,VertexList.Stride,VertexList.GetDataOrOffset());

	}

	ShaderAttribute* normals=pass->GetAttributeByIndex(ShaderAttributeIndex::NormalArray);
	if (normals!=nullptr)
	{
		normals->Invalidate();
		normals->SetPointer(3,GraphicsDataType::Float,false,NormalList.Stride,NormalList.GetDataOrOffset());
	}

	ShaderAttribute* texCoords= pass->GetAttributeByIndex(ShaderAttributeIndex::TexCoordArray);
	if (texCoords!=nullptr)
	{
		texCoords->Invalidate();
		texCoords->SetPointer(2,GraphicsDataType::Float,false,UVWList[0].Stride,UVWList[0].GetDataOrOffset());
	}

	ShaderAttribute* tangents= RenderingContext::Instance().ProgramRenderPass()->GetAttribute(ShaderAttributeNames::TangentArray);
	if (tangents!=nullptr)
	{
		tangents->Invalidate();
		tangents->SetPointer(3,GraphicsDataType::Float,false,TangentList.Stride,TangentList.GetDataOrOffset());
	}


	mIndexBufferObject.Apply();
}

void PODMesh::Restore()
{
	mIndexBufferObject.Restore();
	BaseProgramRenderPass* pass = RenderingContext::Instance().ProgramRenderPass();

	ShaderAttribute* vertices= pass->GetAttributeByIndex(ShaderAttributeIndex::VertexArray);
	if (vertices!=nullptr)
	{
		vertices->EnableArray(false);
		mVertexBufferObject.Restore();
	}

	ShaderAttribute* normals=pass->GetAttributeByIndex(ShaderAttributeIndex::NormalArray);
	if (normals!=nullptr)
	{
		normals->EnableArray(false);
	}

	ShaderAttribute* texCoords= pass->GetAttributeByIndex(ShaderAttributeIndex::TexCoordArray);
	if (texCoords!=nullptr)
	{
		texCoords->EnableArray(false);
	}

	ShaderAttribute* tangents= RenderingContext::Instance().ProgramRenderPass()->GetAttribute(ShaderAttributeNames::TangentArray);
	if (tangents!=nullptr)
	{
		tangents->EnableArray(false);
	}
}

void PODMesh::Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags/*=RenderingFlags::None*/)
{
	if (StripCount==0)
	{
		if(!mIndexBufferObject.IsEmpty())
		{
			mIndexBufferObject.DrawElements(GraphicsDrawMode::Triangles,FaceCount*3,GraphicsDataType::UShort,nullptr);
		}
		else
		{
			mVertexBufferObject.DrawArray(GraphicsDrawMode::Triangles,0,FaceCount*3);
		}
	}
	else
	{
		uint offset=0;
		FOR_EACH_SIZE(i,StripCount)
		{
			uint count=StripLengths[i]+2;
			if(!mIndexBufferObject.IsEmpty())
			{
				// Indexed Triangle strips
				mIndexBufferObject.DrawElements(GraphicsDrawMode::TriangleStrip,count,GraphicsDataType::UShort,(void*)(uintp)(offset*Faces.Stride));
			}
			else
			{
				// Non-Indexed Triangle strips
				mVertexBufferObject.DrawArray(GraphicsDrawMode::TriangleStrip,offset,count);
			}
			offset+=count;
		}
		
	}

	RenderingStatics::Instance().CountOriginalAndBatchDraw();
	RenderingStatics::Instance().CountVertexCount(mVertexCount);
	RenderingStatics::Instance().CountTriangleCount(FaceCount);
}

size_t PODMesh::IndexCount() const
{
	return StripCount>0 ? FaceCount + (StripCount * 2) : FaceCount * 3;
}

INode* PODMesh::CreateCloneInstance()const
{
	Sprite* sprite=new Sprite();
	sprite->Mesh()->CopyFrom(*this);
	return sprite;
}


const byte* PODData::GetDataOrOffset() const
{
	return Data.Data();
}

void PODData::FixInterleavedEndianness( MemoryByteData interleavedData,uint size )
{
	RETURN_IF_ZERO(ComponentCount);
	RETURN_IF_FALSE(IsInterleaved);

	uint typeSize=GetPODDataComponentByteSize(Type);
	byte* data = interleavedData.MutableData() + (intp)GetDataOrOffset();

	switch(typeSize)
	{
	case 1:
		return;
	case 2:
	case 4:
		{
			FOR_EACH_SIZE(i,size)	//each vertex
			{
				FOR_EACH_SIZE(j,ComponentCount)	//each component
				{
					Utility::SwapBytes((byte*)data,typeSize);
				}
				data+=Stride;
			}
		}
		break;
	default:
		MEDUSA_ASSERT_FAILED("Invalid type size");
		break;
	}
}

uint PODData::GetPODDataComponentByteSize( PODDataType type )
{
	switch(type)
	{
	case PODDataType::Float:
		return sizeof(float);
	case PODDataType::Int:
	case PODDataType::UInt:
		return sizeof(int);
	case PODDataType::Short:
	case PODDataType::ShortNorm:
	case PODDataType::UShort:
	case PODDataType::UShortNorm:
		return sizeof(ushort);
	case PODDataType::RGBA:
	case PODDataType::ARGB:
	case PODDataType::D3DCOLOR:
	case PODDataType::UBYTE4:
	case PODDataType::DEC3N:
	case PODDataType::Fixed16_16:
		return sizeof(uint);
	case PODDataType::Byte:
	case PODDataType::CharNorm:
	case PODDataType::Char:
	case PODDataType::ByteNorm:
		return sizeof(byte);
	default:
		MEDUSA_ASSERT_FAILED("invalid pod data type");
		return 0;
		break;
	}
}

MEDUSA_END;