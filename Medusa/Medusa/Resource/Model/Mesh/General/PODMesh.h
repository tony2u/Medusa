// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Graphics/Buffer/MemoryArrayGraphicsBuffer.h"
#include "Graphics/Buffer/MemoryIndexGraphicsBuffer.h"
#include "Geometry/Matrix4.h"
#include "Geometry/Scale3.h"
#include "Core/Memory/MemoryData.h"
MEDUSA_BEGIN;

enum class PODDataType
{
	None,
	Float,
	Int,
	UShort,
	RGBA,
	ARGB,
	D3DCOLOR,
	UBYTE4,
	DEC3N,
	Fixed16_16,
	Byte,
	Short,
	ShortNorm,
	Char,
	CharNorm,
	ByteNorm,
	UShortNorm,
	UInt
};


struct PODData
{
	PODData() :Type(PODDataType::None), ComponentCount(0), Stride(0), IsInterleaved(false)
	{

	}
	~PODData()
	{
		if (!IsInterleaved)
		{
			//Data.Release();
		}
	}
	PODDataType	Type;		/*!< Type of data stored */
	uint		ComponentCount;			/*!< Number of values per vertex */
	uint		Stride;	/*!< Distance in bytes from one array entry to the next */
	MemoryData	Data;		/*!< Actual data (array of values); if mesh is interleaved, this is an OFFSET from pInterleaved */
	bool IsInterleaved;
	void FixInterleavedEndianness(MemoryData interleavedData, uint size);
	static uint GetPODDataComponentByteSize(PODDataType type);

	const byte* GetDataOrOffset()const;
};

struct PODBoneBatches
{
	PODBoneBatches() :BoneBatchMaxCount(0), BoneBatchCount(0)
	{

	}
	List<uint> BoneBatchIndexList;			/*!< Space for nBatchBoneMax bone indices, per batch */
	List<uint> BoneBatchIndexCounts;	/*!< Actual number of bone indices, per batch */
	List<uint> BoneBatchOffsets;		/*!< Offset into triangle array, per batch */
	uint BoneBatchMaxCount;		/*!< Stored value as was passed into Create() */
	uint	BoneBatchCount;			/*!< Number of batches to render */
};

class PODMesh :public IMesh
{
public:
	PODMesh( bool isStatic = false);
	virtual ~PODMesh(void);
	void FixInterleavedEndianness();

	virtual void Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None);
	virtual void Apply();
	virtual void Restore();

	virtual bool Initialzie();
	virtual size_t VertexCount()const { return mVertexCount; }
	virtual size_t IndexCount()const;
	virtual INode* CreateCloneInstance()const;
public:
	bool CopyFrom(const PODMesh& val) { return false; }

public:
	uint			mVertexCount;		/*!< Number of vertices in the mesh */
	uint			FaceCount;		/*!< Number of triangles in the mesh */
	uint			UVWChannelCount;		/*!< Number of texture coordinate channels per vertex */
	PODData			Faces;			/*!< List of triangle indices */
	List<uint>		StripLengths;	/*!< If mesh is stripped: number of tris per strip. */
	uint			StripCount;		/*!< If mesh is stripped: number of strips, length of pnStripLength array. */
	PODData			VertexList;		/*!< List of vertices (x0, y0, z0, x1, y1, z1, x2, etc...) */
	PODData			NormalList;		/*!< List of vertex normals (Nx0, Ny0, Nz0, Nx1, Ny1, Nz1, Nx2, etc...) */
	PODData			TangentList;		/*!< List of vertex tangents (Tx0, Ty0, Tz0, Tx1, Ty1, Tz1, Tx2, etc...) */
	PODData			BinormalList;		/*!< List of vertex binormals (Bx0, By0, Bz0, Bx1, By1, Bz1, Bx2, etc...) */
	List<PODData, NoCompare >	UVWList;			/*!< List of UVW coordinate sets; size of array given by 'nNumUVW' */
	PODData			VertexColorList;	/*!< A colour per vertex */
	PODData			BoneIndexList;		/*!< nNumBones*nNumVertex ints (Vtx0Idx0, Vtx0Idx1, ... Vtx1Idx0, Vtx1Idx1, ...) */
	PODData			BoneWeights;	/*!< nNumBones*nNumVertex floats (Vtx0Wt0, Vtx0Wt1, ... Vtx1Wt0, Vtx1Wt1, ...) */

	PODBoneBatches	BoneBatches;	/*!< Bone tables */
	Matrix4			UnpackMatrix;	/*!< A matrix used for unscaling scaled vertex data created with PVRTModelPODScaleAndConvertVtxData*/

	MemoryData InterleavedData;	/*!< Interleaved vertex data */
private:
	MemoryArrayGraphicsBuffer<byte> mVertexBufferObject;
	MemoryIndexGraphicsBuffer<byte> mIndexBufferObject;

};

MEDUSA_END;