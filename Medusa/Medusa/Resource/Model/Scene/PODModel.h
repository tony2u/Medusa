// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/Scene/BaseSceneModel.h"
#include "Resource/Model/Scene/PODDefines.h"
#include "Geometry/Point3.h"
#include "Geometry/Scale3.h"
#include "Geometry/Quaternion.h"
#include "Geometry/Color3.h"
#include "Geometry/Matrix4.h"
#include "Geometry/Matrix4.h"



MEDUSA_BEGIN;



struct PODNode
{
	PODNode():Index(-1),MaterialIndex(-1),ParentIndex(-1)
	{

	}
	virtual ~PODNode(){}
	int			Index;				/*!< Index into mesh, light or camera array, depending on which object list contains this Node */
	HeapString	Name;			/*!< Name of object */
	int		 MaterialIndex;		/*!< Index of material used on this mesh */
	int		ParentIndex;		/*!< Index into MeshInstance array; recursively apply ancestor's transforms after this instance's. */


	PODAnimiationFlags		AnimationFlags;		/*!< Stores which animation arrays the POD Node contains */

	List<uint> AnimationPositionIndexes;
	List<Point3F> AnimationPositions;	/*!< 3 floats per frame of animation. (x,y,z)*/

	List<uint>	AnimationRotationIndexes;
	List<Quaternion> AnimationRotations;	/*!< 4 floats per frame of animation by quaternion format*/

	List<uint> AnimationScaleIndexes;
	List<PODScale,NoCompare> AnimationScales;		/*!< 7 floats per frame of animation. */

	List<uint>	AnimationMatrixIndexes;
	List<Matrix4> AnimationMatrixes;		/*!< 16 floats per frame of animation. */

	MemoryData UserData;

	virtual bool TryGetMatrix(float frame,Matrix4& outMatrix)const;
private:
	void GetMatrix(uint frameIndex,Matrix4& outMatrix)const;
	void GetScaleMatrix(uint frameIndex,float frameBlend,Matrix4& outMatrix)const;
	void GetRotateMatrix(uint frameIndex,float frameBlend,Matrix4& outMatrix)const;
	void GetTranslateMatrix(uint frameIndex,float frameBlend,Matrix4& outMatrix)const;
};

class PODModel:public BaseSceneModel
{
public:
	PODModel(const FileIdRef& fileId);
	virtual ~PODModel(void);
	virtual bool Initialize(ModelLoadingOptions loadingOptions=ModelLoadingOptions::None);
	virtual Share<ITimelineModel> CreateSkeletonTimelineModel()const;
	virtual Share<ITimelineModel> CreateCameraTimelineModel(StringRef name)const;
	virtual Share<ITimelineModel> CreateLightTimelineModel(StringRef name)const;

	virtual Share<Camera> CreateCamera(const FileIdRef& fileId, const Size2F& winSize)const;
	virtual Share<ILight> CreateLight(const FileIdRef& fileId)const;


	static PODModel* CreateFromFile(const FileIdRef& fileId,ModelLoadingOptions loadingOptions=ModelLoadingOptions::None);
	static PODModel* CreateFromData(const FileIdRef& fileId,MemoryData data,ModelLoadingOptions loadingOptions=ModelLoadingOptions::None);

	PODNode* GetPODNode(uint index){return mPODNodes[index];}
	PODNode* GetPODNode(StringRef name);

	bool TryGetWorldMatrix(PODNode* node,float frame,Matrix4& outMatrix)const;

	virtual INode* Instantiate(InstantiateMode mode = InstantiateMode::None)const override;

private:
	static bool ReadIdentifier(MemoryStream& stream,PODIdentifier& outIdentifier,uint& outLength);
	static bool ReadScene(MemoryStream& stream,PODModel& model);
	static bool ReadCamera(MemoryStream& stream,PODModel& model);
	static bool ReadLight(MemoryStream& stream,PODModel& model);
	static bool ReadMaterial(MemoryStream& stream,PODModel& model);
	static bool ReadMesh(MemoryStream& stream,PODModel& model);
	static bool ReadNode(MemoryStream& stream,PODModel& model);
	static bool ReadTexture(MemoryStream& stream,PODModel& model);

	static bool ReadPODData(MemoryStream& stream,PODData& podData,PODIdentifier identifier,bool isInterleavedData);

	static const StringRef mDefaultVersion;
	static const uint StartTagMask=0x00000000;
	static const uint EndTagMask=0x80000000;


private:
	HeapString mVersion;
	MemoryData mExportOption;
	MemoryData mHistory;

	Color3F mBackgroundColor;
	Color3F mAmbientColor;
	uint mMeshNodeCount;	//total number of meshes in the scene (may >=mMeshCount as will include instanced meshes)
	uint mFrameCount;
	uint mFlags;
	uint mFPS;

	List<PODNode*> mPODNodes;
	List<HeapString> mTextureNames;
};

MEDUSA_END;