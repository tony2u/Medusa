// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Rendering/Batch/BaseBufferRenderBatch.h"
#include "Resource/Model/IModel.h"
#include "Rendering/IRenderable.h"
#include "Core/Profile/ProfileSample.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Core/Log/Log.h"
#include "Rendering/RenderingStatics.h"
#include "Application/ApplicationStatics.h"
#include "Rendering/RenderingContext.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"
#include "Resource/Effect/Shader/Parameter/ShaderAttribute.h"

MEDUSA_BEGIN;


BaseBufferRenderBatch::BaseBufferRenderBatch(RenderingStrategy renderingStrategy)
	:IRenderBatch(renderingStrategy)
{
	GraphicsBufferUsage bufferUsage;
	if (renderingStrategy == RenderingStrategy::MultipleStaticBatch)
	{
		bufferUsage = GraphicsBufferUsage::StaticDraw;
	}
	else
	{
		bufferUsage = GraphicsBufferUsage::DynamicDraw;
	}
	mVertexBufferObject.SetUsageType(bufferUsage);
	mTexcoordBufferObject.SetUsageType(bufferUsage);
	mColorBufferObject.SetUsageType(bufferUsage);
	mNormalBufferObject.SetUsageType(bufferUsage);
	mIndexBufferObject.SetUsageType(bufferUsage);
}


BaseBufferRenderBatch::~BaseBufferRenderBatch()
{
	Clear();
}

bool BaseBufferRenderBatch::Initialize()
{
	RETURN_FALSE_IF_FALSE(IRenderBatch::Initialize());
	return true;
}

bool BaseBufferRenderBatch::Uninitialize()
{
	RETURN_FALSE_IF_FALSE(IRenderBatch::Uninitialize());
	Clear();
	return true;
}

void BaseBufferRenderBatch::Clear()
{
	for (IRenderable* node : mNodes)
	{
		node->SetBatch(nullptr);
	}
	mNodes.Clear();
}

void BaseBufferRenderBatch::ReleaseBuffer()
{
	mVertexBufferObject.ClearData();
	mTexcoordBufferObject.ClearData();
	mColorBufferObject.ClearData();
	mNormalBufferObject.ClearData();
	mIndexBufferObject.ClearData();
}

void BaseBufferRenderBatch::Prepare()
{
	mNodes.Clear();
}

void BaseBufferRenderBatch::AddNode(IRenderable* node)
{
	mNodes.Add(node);
}

void BaseBufferRenderBatch::RemoveNode(IRenderable* node)
{
#ifdef MEDUSA_SAFE_CHECK
	Log::Assert(node->Batch() == this, "Inconsistent batch");
#endif
	mNodes.Remove(node);
	node->SetBatch(nullptr);
}



void BaseBufferRenderBatch::AddNodeToBuffer(uint& refVertexIndex, uint& refIndexIndex, IRenderable& node)
{
	IMesh* mesh = node.Mesh();
	const Matrix4& newMatrix = node.WorldMatrix();

	mesh->AddToVertexBufferObject(mVertexBufferObject, refVertexIndex,  newMatrix);
	mesh->AddToNormalBufferObject(mNormalBufferObject, refVertexIndex,  newMatrix);
	mesh->AddToTexCoordBufferObject(mTexcoordBufferObject, refVertexIndex);
	mesh->AddToColorBufferObject(mColorBufferObject, refVertexIndex, node.WorldColor());
	mesh->AddToIndexBufferObject(mIndexBufferObject, refVertexIndex, refIndexIndex);

	uintp vertexCount = mesh->VertexCount();
	uintp indexCount = mesh->IndexCount();
	node.SetBatch(this, refVertexIndex, (uint)vertexCount, refIndexIndex, (uint)indexCount);
	refVertexIndex += vertexCount;
	refIndexIndex += indexCount;
	RenderingStatics::Instance().IncreaseChangedNodeCount();

}

void BaseBufferRenderBatch::UpdateNodeToBuffer(uint& refVertexIndex, uint& refIndexIndex, IRenderable& node, RenderableChangedFlags changedFlags)
{
	IMesh* mesh = node.Mesh();
	if (MEDUSA_FLAG_HAS(changedFlags,RenderableChangedFlags::NewVertex))
	{
		const Matrix4& newMatrix = node.WorldMatrix();
		mesh->AddToVertexBufferObject(mVertexBufferObject, refVertexIndex,  newMatrix);
	}

	if (MEDUSA_FLAG_HAS(changedFlags, RenderableChangedFlags::NewNormal))
	{
		const Matrix4& newMatrix = node.WorldMatrix();
		mesh->AddToNormalBufferObject(mNormalBufferObject, refVertexIndex,  newMatrix);
	}

	if (MEDUSA_FLAG_HAS(changedFlags, RenderableChangedFlags::NewTexCoord))
	{
		mesh->AddToTexCoordBufferObject(mTexcoordBufferObject, refVertexIndex);
	}

	if (MEDUSA_FLAG_HAS(changedFlags, RenderableChangedFlags::NewColor))
	{
		mesh->AddToColorBufferObject(mColorBufferObject, refVertexIndex, node.WorldColor());
	}

	if (MEDUSA_FLAG_HAS(changedFlags, RenderableChangedFlags::NewIndex))
	{
		mesh->AddToIndexBufferObject(mIndexBufferObject, refVertexIndex, refIndexIndex);
	}

	uintp vertexCount = mesh->VertexCount();
	uintp indexCount = mesh->IndexCount();
	node.SetBatch(this, refVertexIndex, (uint)vertexCount, refIndexIndex, (uint)indexCount);
	refVertexIndex += vertexCount;
	refIndexIndex += indexCount;
	RenderingStatics::Instance().IncreaseChangedNodeCount();
}


void BaseBufferRenderBatch::TrimBuffer(size_t vertexIndex, size_t indexIndex)
{
	mVertexBufferObject.RemoveDataFrom(vertexIndex);
	mTexcoordBufferObject.RemoveDataFrom(vertexIndex);
	mColorBufferObject.RemoveDataFrom(vertexIndex);
	mIndexBufferObject.RemoveDataFrom(indexIndex);
	mNormalBufferObject.RemoveDataFrom(vertexIndex);
}

void BaseBufferRenderBatch::Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags /*= RenderingFlags::None*/)
{
	mIndexBufferObject.DrawElements(mDrawMode);

	RenderingStatics::Instance().CountDrawMode(mDrawMode);
	RenderingStatics::Instance().CountVertexCount(mVertexBufferObject.Count());
	RenderingStatics::Instance().CountTriangleCount(mIndexBufferObject.Count() / 3);
	RenderingStatics::Instance().CountOriginalDraw((uint)mNodes.Count());
	RenderingStatics::Instance().CountBatchDraw();
}

void BaseBufferRenderBatch::Print(HeapString& ioStr, uint level)
{
	ioStr.AppendFormat("{:x}", this);
	ioStr.Append('\t', level);

	switch (mDrawMode)
	{
		case GraphicsDrawMode::Points:
			ioStr.AppendLine("Points");
			break;
		case GraphicsDrawMode::Lines:
			ioStr.AppendLine("Lines");
			break;
		case GraphicsDrawMode::LineLoop:
			ioStr.AppendLine("LineLoop");
			break;
		case GraphicsDrawMode::LineStrip:
			ioStr.AppendLine("LineStrip");
			break;
		case GraphicsDrawMode::Triangles:
			ioStr.AppendLine("Triangles");
			break;
		case GraphicsDrawMode::TriangleStrip:
			ioStr.AppendLine("TriangleStrip");
			break;
		case GraphicsDrawMode::TriangleFan:
			ioStr.AppendLine("TriangleFan");
			break;
		default:
			break;
	}

	FOR_EACH_COLLECTION(i, mNodes)
	{
		const IRenderable* node = *i;
		ioStr.AppendFormat("{}:{}\t", node->Id(), node->Name().c_str());
	}

	ioStr.AppendLine();
}

void BaseBufferRenderBatch::PrintNodes()const
{
	HeapString testStr;
	FOR_EACH_COLLECTION(i, mNodes)
	{
		const IRenderable* node = *i;
		testStr.AppendFormat("{},", node->Name().c_str());
	}
	Log::Info(testStr);
}

void BaseBufferRenderBatch::Apply()
{
	RETURN_IF_FALSE(RenderingContext::Instance().IsBatchStep());
	BaseProgramRenderPass* pass = RenderingContext::Instance().ProgramRenderPass();
	//set model view matrix
	ShaderAttribute* texCoords = pass->FindAttributeByIndex(ShaderAttributeIndex::TexCoordArray);
	if (texCoords != nullptr)
	{
		mTexcoordBufferObject.Apply();
		texCoords->SetPointerFromBufferObject(mTexcoordBufferObject);
	}

	ShaderAttribute* vertices = pass->FindAttributeByIndex(ShaderAttributeIndex::VertexArray);
	if (vertices != nullptr)
	{
		mVertexBufferObject.Apply();
		vertices->SetPointerFromBufferObject(mVertexBufferObject);
	}

	ShaderAttribute* colors = pass->FindAttributeByIndex(ShaderAttributeIndex::ColorArray);
	if (colors != nullptr)
	{
		mColorBufferObject.Apply();
		colors->SetPointerFromBufferObject(mColorBufferObject);
	}

	ShaderAttribute* normals = pass->FindAttributeByIndex(ShaderAttributeIndex::NormalArray);
	if (normals != nullptr)
	{
		mNormalBufferObject.Apply();
		normals->SetPointerFromBufferObject(mNormalBufferObject);
	}

	mIndexBufferObject.Apply();
}

void BaseBufferRenderBatch::Restore()
{
	mIndexBufferObject.Restore();
	BaseProgramRenderPass* pass = RenderingContext::Instance().ProgramRenderPass();

	ShaderAttribute* normals = pass->FindAttributeByIndex(ShaderAttributeIndex::NormalArray);
	if (normals != nullptr)
	{

		mNormalBufferObject.Restore();
		normals->EnableArray(false);
	}

	ShaderAttribute* colors = pass->FindAttributeByIndex(ShaderAttributeIndex::ColorArray);
	if (colors != nullptr)
	{
		mColorBufferObject.Restore();
		colors->EnableArray(false);
	}

	ShaderAttribute* vertices = pass->FindAttributeByIndex(ShaderAttributeIndex::VertexArray);
	if (vertices != nullptr)
	{
		mVertexBufferObject.Restore();
		vertices->EnableArray(false);
	}

	ShaderAttribute* texCoords = pass->FindAttributeByIndex(ShaderAttributeIndex::TexCoordArray);
	if (texCoords != nullptr)
	{
		mTexcoordBufferObject.Restore();
		texCoords->EnableArray(false);
	}

}


MEDUSA_END;