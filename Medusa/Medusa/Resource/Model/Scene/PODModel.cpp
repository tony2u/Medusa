// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PODModel.h"

#include "Resource/Timeline/TimelineModelFactory.h"
#include "Resource/Material/MaterialFactory.h"

#include "Resource/Timeline/PODCameraFOVTimelineModel.h"
#include "Resource/Timeline/PODJointTimelineModel.h"
#include "Resource/Timeline/PODLightTimelineModel.h"
#include "Resource/Timeline/IdentityTimelineModel.h"
#include "Resource/Material/PODMaterial.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileSystem.h"
#include "Resource/Model/Virtual/VirtualModelNode.h"
#include "Resource/Model/Camera/PODCameraModelNode.h"
#include "Resource/Model/Light/PODLightModelNode.h"
#include "Resource/Model/Mesh/General/PODMesh.h"
#include "Geometry/EulerAngle.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Resource/Model/Mesh/MeshModelNode.h"
#include "Node/Sprite/Sprite.h"

MEDUSA_BEGIN;


bool PODNode::TryGetMatrix( float frame,Matrix4& outMatrix ) const
{
	outMatrix.LoadIdentity();
	RETURN_FALSE_IF(frame<0.f);

	uint frameIndex=(uint)frame;
	float frameBlend=frame-(float)frameIndex;

	outMatrix=Matrix4::Identity;

	if (!AnimationMatrixes.IsEmpty())
	{
		GetMatrix(frameIndex,outMatrix);
	}
	else
	{
		GetScaleMatrix(frameIndex,frameBlend,outMatrix);
		GetRotateMatrix(frameIndex,frameBlend,outMatrix);
		GetTranslateMatrix(frameIndex,frameBlend,outMatrix);
	}

	return true;
}

void PODNode::GetMatrix( uint frameIndex,Matrix4& outMatrix ) const
{
	//first get,use =
	RETURN_IF_EMPTY(AnimationMatrixes);

	if (MEDUSA_FLAG_HAS(AnimationFlags,PODAnimiationFlags::HasMatrix))
	{
		if (!AnimationMatrixIndexes.IsEmpty())
		{
			uint matrixIndex=AnimationMatrixIndexes[frameIndex];
			outMatrix=AnimationMatrixes[matrixIndex];
		}
		else
		{
			outMatrix=AnimationMatrixes[frameIndex];
		}
	}
	else
	{
		outMatrix=AnimationMatrixes[0];	//use first one
	}
}

void PODNode::GetScaleMatrix( uint frameIndex,float frameBlend,Matrix4& outMatrix ) const
{
	//first get,use =

	RETURN_IF_EMPTY(AnimationScales);

	if (MEDUSA_FLAG_HAS(AnimationFlags,PODAnimiationFlags::HasScale))
	{
		if (!AnimationScaleIndexes.IsEmpty())
		{
			MEDUSA_ASSERT_LESS(frameIndex,AnimationScaleIndexes.Size(),"");
			uint index1=AnimationScaleIndexes[frameIndex];
			const PODScale& scale1= AnimationScales[index1];

			if (frameIndex==AnimationScaleIndexes.Size()-1)
			{
				//last frame
				outMatrix=Matrix4::CreateScale(scale1.Scale);
			}
			else
			{
				uint index2=AnimationScaleIndexes[frameIndex+1];
				const PODScale& scale2= AnimationScales[index2];

				Scale3F resultScale=Scale3F::LinearInterpolate(scale1.Scale,scale2.Scale,frameBlend);
				outMatrix=Matrix4::CreateScale(resultScale);

			}

		}
		else
		{
			const PODScale& scale1= AnimationScales[frameIndex];
			if (frameIndex==AnimationScales.Size()-1)
			{
				//last frame
				outMatrix=Matrix4::CreateScale(scale1.Scale);
			}
			else
			{
				const PODScale& scale2= AnimationScales[frameIndex+1];
				Scale3F resultScale=Scale3F::LinearInterpolate(scale1.Scale,scale2.Scale,frameBlend);
				outMatrix=Matrix4::CreateScale(resultScale);
			}
		}
	}
	else
	{
		const PODScale& scale= AnimationScales[0];
		outMatrix=Matrix4::CreateScale(scale.Scale);
	}
}

void PODNode::GetRotateMatrix( uint frameIndex,float frameBlend,Matrix4& outMatrix ) const
{
	RETURN_IF_EMPTY(AnimationRotations);
	if (MEDUSA_FLAG_HAS(AnimationFlags,PODAnimiationFlags::HasRotation))
	{
		if (!AnimationRotationIndexes.IsEmpty())
		{
			MEDUSA_ASSERT_LESS(frameIndex,AnimationRotationIndexes.Size(),"");
			uint index1=AnimationRotationIndexes[frameIndex];
			const Quaternion& q1= AnimationRotations[index1];

			if (frameIndex==AnimationRotationIndexes.Size()-1)
			{
				//last frame
				outMatrix*=Matrix4::CreateFromQuaternion(q1);
			}
			else
			{
				uint index2=AnimationRotationIndexes[frameIndex+1];
				const Quaternion& q2= AnimationRotations[index2];
				Quaternion resultQ=Quaternion::Slerp(q1,q2,frameBlend);
				outMatrix*=Matrix4::CreateFromQuaternion(resultQ);
			}
		}
		else
		{
			const Quaternion& q1= AnimationRotations[frameIndex];
			if (frameIndex==AnimationRotations.Size()-1)
			{
				//last frame
				outMatrix*=Matrix4::CreateFromQuaternion(q1);
			}
			else
			{
				const Quaternion& q2= AnimationRotations[frameIndex+1];
				Quaternion resultQ=Quaternion::Slerp(q1,q2,frameBlend);
				outMatrix*=Matrix4::CreateFromQuaternion(resultQ);
			}
		}
	}
	else
	{
		const Quaternion& q= AnimationRotations[0];
		outMatrix*=Matrix4::CreateFromQuaternion(q);
	}
}

void PODNode::GetTranslateMatrix( uint frameIndex,float frameBlend,Matrix4& outMatrix ) const
{
	RETURN_IF_EMPTY(AnimationPositions);

	if (MEDUSA_FLAG_HAS(AnimationFlags,PODAnimiationFlags::HasPosition))
	{
		if (!AnimationPositionIndexes.IsEmpty())
		{
			MEDUSA_ASSERT_LESS(frameIndex,AnimationPositionIndexes.Size(),"");
			uint index1=AnimationPositionIndexes[frameIndex];
			const Point3F& q1= AnimationPositions[index1];

			if (frameIndex==AnimationPositionIndexes.Size()-1)
			{
				//last frame
				outMatrix*=Matrix4::CreateTranslate(q1);
			}
			else
			{
				uint index2=AnimationPositionIndexes[frameIndex+1];
				const Point3F& q2= AnimationPositions[index2];
				Point3F resultQ=Point3F::LinearInterpolate(q1,q2,frameBlend);
				outMatrix*=Matrix4::CreateTranslate(resultQ);
			}
		}
		else
		{
			const Point3F& q1= AnimationPositions[frameIndex];
			if (frameIndex==AnimationPositions.Size()-1)
			{
				//last frame
				outMatrix*=Matrix4::CreateTranslate(q1);
			}
			else
			{
				const Point3F& q2= AnimationPositions[frameIndex+1];
				Point3F resultQ=Point3F::LinearInterpolate(q1,q2,frameBlend);
				outMatrix*=Matrix4::CreateTranslate(resultQ);
			}
		}
	}
	else
	{
		const Point3F& q= AnimationPositions[0];
		outMatrix*=Matrix4::CreateTranslate(q);
	}
}


PODModel::PODModel(const FileIdRef& fileId):BaseSceneModel(fileId),mBackgroundColor(Color3F::Black),mAmbientColor(Color3F::White),mMeshNodeCount(0),mFrameCount(0),mFlags(0),mFPS(30)
{

}

PODModel::~PODModel(void)
{
	SAFE_DELETE_COLLECTION(mPODNodes);

}

PODNode* PODModel::GetPODNode( StringRef name )
{
	FOR_EACH_COLLECTION(i,mPODNodes)
	{
		PODNode* node=*i;
		if (node->Name==name)
		{
			return node;
		}
	}

	return nullptr;
}

bool PODModel::TryGetWorldMatrix( PODNode* node,float frame,Matrix4& outMatrix ) const
{
	if(node->TryGetMatrix(frame,outMatrix))
	{
		if(node->ParentIndex>=0)
		{
			const PODNode* parentNode=mPODNodes[node->ParentIndex];
			Matrix4 parentMatrix;
			if (parentNode->TryGetMatrix(frame,parentMatrix))
			{
				outMatrix*=parentMatrix;
			}
		}
		return true;
	}

	return false;
	
}

INode* PODModel::Instantiate(InstantiateMode mode /*= InstantiateMode::None*/)const
{
	//create self
	Sprite* sprite = new Sprite();
	sprite->SetMoveable(*this);
	sprite->Initialize();
	//self children
	for(auto* mesh : mMeshNodes)
	{
		auto* child = mesh->CreateCloneInstance();
		sprite->AddChild(child);
	}
	sprite->SetRenderingStrategyRecursively(RenderingStrategy::CustomDrawMesh);

	return sprite;
}

bool PODModel::Initialize(ModelLoadingOptions loadingOptions/*=ModelLoadingOptions::None*/)
{
	RETURN_FALSE_IF_FALSE(BaseSceneModel::Initialize(loadingOptions));

	FOR_EACH_COLLECTION(i,mMaterials)
	{
		PODMaterial* material=(PODMaterial*)*i;
		material->Initialize(mTextureNames);
	}

	Matrix4 outNodeMatrix;

	//order: mesh,light,camera
	uint index=0;
	uint size=static_cast<uint>(mMeshNodes.Count());
	List<IMeshModelNode*> rootMeshes;
	for (;index<size;index++)
	{
		PODNode* podNode=mPODNodes[index];
		IMeshModelNode* meshNode=mMeshNodes[podNode->Index];
		meshNode->SetName(podNode->Name);
		if(podNode->MaterialIndex>=0)
		{
			if (podNode->MaterialIndex<(int)mMaterials.Count())
			{
				IMaterial* material=mMaterials[podNode->MaterialIndex];
				meshNode->SetMaterial(material);
			}
			else
			{
				Log::FormatInfo("Warning: No material index:{} from node:{}",podNode->MaterialIndex,podNode->Name.c_str());
			}
			
		}

		if (podNode->ParentIndex>=0)
		{
			IMeshModelNode* parentMesh=mMeshNodes[podNode->ParentIndex];
			parentMesh->AddChildNode(meshNode);
		}
		else
		{
			rootMeshes.Add(meshNode);
		}

		PODMesh* podMesh= (PODMesh*)meshNode->MutableBaseMeshPtr();
		podMesh->Initialzie();

		if (podNode->TryGetMatrix(0.f, outNodeMatrix))
		{
			meshNode->SetSRTFromMatrix(outNodeMatrix);
		}
		else
		{
			Log::Info("No matrix");
		}

		/*if(TryGetWorldMatrix(podNode,0,outNodeMatrix))
		{
			meshNode->SetSRTFromMatrix(outNodeMatrix);
		}
		else
		{
			Log::Info("No matrix");
		}*/
	}
	mMeshNodes.Clear();
	mMeshNodes=rootMeshes;
	rootMeshes.Clear();

	size=index+static_cast<uint>(mLights.Count());
	for (;index<size;index++)
	{
		PODNode* podNode=mPODNodes[index];
		BaseLightModelNode* light=mLights[podNode->Index];
		light->SetName(podNode->Name);
		
		if (podNode->TryGetMatrix(0.f, outNodeMatrix))
		{
			light->SetSRTFromMatrix(outNodeMatrix);
		}
		else
		{
			Log::Info("No matrix");
		}
	}

	size=index+static_cast<uint>(mCameras.Count());
	for (;index<size;index++)
	{
		PODNode* podNode=mPODNodes[index];
		PODCameraModelNode* camera=(PODCameraModelNode*)mCameras[podNode->Index];
		camera->SetName(podNode->Name);

		if (podNode->TryGetMatrix(0.f, outNodeMatrix))
		{
			camera->SetSRTFromMatrix(outNodeMatrix);
		}
		else
		{
			Log::Info("No matrix");
		}
	}

	//helper node
	for (;index<mPODNodes.Count();index++)
	{
		PODNode* podNode=mPODNodes[index];
		VirtualModelNode* node=new VirtualModelNode(podNode->Name);
		AddVirtualNode(node);

		if (podNode->TryGetMatrix(0.f, outNodeMatrix))
		{
			node->SetSRTFromMatrix(outNodeMatrix);
		}
		else
		{
			Log::Info("No matrix");
		}
	}

	//init animation
	if (!MEDUSA_FLAG_HAS(loadingOptions,ModelLoadingOptions::NoSkeletonAnimation))
	{
		ITimelineModel* ani= CreateSkeletonTimelineModel();
		TimelineModelFactory::Instance().Add(ani);
	}

	if (!MEDUSA_FLAG_HAS(loadingOptions,ModelLoadingOptions::NoCameraAnimation))
	{
		FOR_EACH_COLLECTION(i,mCameras)
		{
			PODCameraModelNode* camera=(PODCameraModelNode*)*i;
			ITimelineModel* ani=CreateCameraTimelineModel(camera->Name());
			TimelineModelFactory::Instance().Add(ani);

		}
	}

	if (!MEDUSA_FLAG_HAS(loadingOptions,ModelLoadingOptions::NoLightAnimation))
	{
		FOR_EACH_COLLECTION(i,mLights)
		{
			PODLightModelNode* light=(PODLightModelNode*)*i;
			ITimelineModel* ani=CreateLightTimelineModel(light->Name());
			TimelineModelFactory::Instance().Add(ani);

		}
	}

	//Force update world matrix
	//UpdateWorldMatrixRecursively();

	return true;
}


ITimelineModel* PODModel::CreateSkeletonTimelineModel() const
{
	IdentityTimelineModel* rootAnimation=new IdentityTimelineModel(mFileId.ToRef());

	List<PODJointTimelineModel*> tempAnimations;
	FOR_EACH_SIZE(i,mPODNodes.Count())	//all nodes
	{
		const PODNode* podNode=mPODNodes[i];
		PODJointTimelineModel* podAnimation=new PODJointTimelineModel(podNode->Name);
		podAnimation->Initialize(podNode);
		tempAnimations.Append(podAnimation);
	}

	FOR_EACH_SIZE(i,mPODNodes.Count())
	{
		const PODNode* podNode=mPODNodes[i];
		if (podNode->ParentIndex>=0)
		{
			//PODJointTimelineModel* parent=tempAnimations[podNode->ParentIndex];
			//parent->AddChild(tempAnimations[i]);
		}
		else
		{
			//rootAnimation->AddChild(tempAnimations[i]);
		}
	}

	return rootAnimation;
}


ITimelineModel* PODModel::CreateCameraTimelineModel(StringRef name) const
{
	FOR_EACH_COLLECTION(i,mCameras)
	{
		PODCameraModelNode* camera=(PODCameraModelNode*)*i;
		if (camera->Name()==name)
		{
			PODCameraFOVTimelineModel* animation=new PODCameraFOVTimelineModel(name);


			if(camera->TargetObjectIndex>=0)
			{
				const PODNode* podNode=mPODNodes[camera->TargetObjectIndex];
				animation->Initialize(name,camera->FOVAnimations,podNode->Name);
			}
			else
			{
				animation->Initialize(name,camera->FOVAnimations);
			}
			return animation;
		}
	}

	return nullptr;
}


ITimelineModel* PODModel::CreateLightTimelineModel( StringRef name ) const
{
	FOR_EACH_COLLECTION(i,mLights)
	{
		PODLightModelNode* light=(PODLightModelNode*)*i;
		if (light->Name()==name)
		{
			PODLightTimelineModel* animation=new PODLightTimelineModel(name);

			if(light->TargetObjectIndex>=0)
			{
				const PODNode* podNode=mPODNodes[light->TargetObjectIndex];
				animation->Initialize(name,podNode->Name);
			}
			else
			{
				animation->Initialize(name);
			}
			return animation;
		}
	}

	return nullptr;
}

Camera* PODModel::CreateCamera(const FileIdRef& fileId, const Size2F& winSize) const
{
	FOR_EACH_COLLECTION(i,mCameras)
	{
		const PODCameraModelNode* camera=(PODCameraModelNode*)*i;
		if (camera->Name() == fileId.Name)
		{
			return camera->CreateCamera(winSize);
		}
	}

	return nullptr;
}

ILight* PODModel::CreateLight(const FileIdRef& fileId) const
{
	FOR_EACH_COLLECTION(i,mLights)
	{
		const PODLightModelNode* light=(PODLightModelNode*)*i;
		if (light->Name() == fileId.Name)
		{
			return light->CreateLight();
		}
	}

	return nullptr;
}


PODModel* PODModel::CreateFromFile(const FileIdRef& fileId ,ModelLoadingOptions loadingOptions/*=ModelLoadingOptions::None*/)
{
	MemoryData fileData= FileSystem::Instance().ReadAllData(fileId);

	return CreateFromData(fileId,fileData,loadingOptions);
}

PODModel* PODModel::CreateFromData( const FileIdRef& fileId,MemoryData data ,ModelLoadingOptions loadingOptions/*=ModelLoadingOptions::None*/)
{
	PODIdentifier identifier;
	uint size=0;
	PODModel* resultModel=new PODModel(fileId);
	MemoryStream ms(data);
	bool isCompleted=false;
	bool isSuccess=true;
	

	while(ReadIdentifier(ms,identifier,size))
	{
		switch((int)identifier)
		{
		case (int)PODIdentifier::Version:
			{
				if (size!=mDefaultVersion.Length()+1)//size include '\0'
				{
					isSuccess=false;
					break;
				}
				resultModel->mVersion=ms.ReadString();

				if (resultModel->mVersion!=resultModel->mDefaultVersion)
				{
					Log::FormatError("Error POD version:{} to {}",resultModel->mVersion.Buffer(),resultModel->mDefaultVersion.Buffer());
					isSuccess=false;
				}
			}
			break;
		case (int)PODIdentifier::ExportOption:
			resultModel->mExportOption=ms.ReadData(size);
			break;
		case (int)PODIdentifier::History:
			resultModel->mHistory=ms.ReadData(size);
			break;
		case (int)PODIdentifier::Scene:
			isSuccess=ReadScene(ms,*resultModel);
			isCompleted=true;
			break;
		case (int)PODIdentifier::Version|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::ExportOption|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::History|(int)PODModel::EndTagMask:
			break;
		case (int)PODIdentifier::Scene|(int)PODModel::EndTagMask:
			isCompleted=true;
			break;
		default:
			ms.Skip(size);
			break;
		}

		BREAK_IF_FALSE(isSuccess);
	}

	if (!isSuccess||!isCompleted)
	{
		SAFE_DELETE(resultModel);
        return nullptr;
	}

	if(!resultModel->Initialize(loadingOptions))
	{
		SAFE_DELETE(resultModel);
	}

	return resultModel;
}

bool PODModel::ReadIdentifier( MemoryStream& stream,PODIdentifier& outIdentifier,uint& outLength )
{
	RETURN_FALSE_IF_FALSE(stream.ReadTo(outIdentifier));
	RETURN_FALSE_IF_FALSE(stream.ReadTo(outLength));

	return !stream.IsEnd();
}

bool PODModel::ReadScene( MemoryStream& stream,PODModel& model )
{
	PODIdentifier identifier;
	uint size=0;
	while(ReadIdentifier(stream,identifier,size))
	{
		switch((int)identifier)
		{
		case (int)PODIdentifier::BackgroundColor:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(model.mBackgroundColor));
			break;
		case (int)PODIdentifier::AmbientColor:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(model.mAmbientColor));
			break;
		case (int)PODIdentifier::NumCamera:
			{
				uint cameraCount;
				RETURN_FALSE_IF_FALSE(stream.ReadTo(cameraCount));
			}

			break;
		case (int)PODIdentifier::NumLight:
			{
				uint lightCount;
				RETURN_FALSE_IF_FALSE(stream.ReadTo(lightCount));
			}

			break;
		case (int)PODIdentifier::NumMesh:
			{
				uint meshCount;
				RETURN_FALSE_IF_FALSE(stream.ReadTo(meshCount));
			}

			break;
		case (int)PODIdentifier::NumNode:
			{
				uint nodeCount;
				RETURN_FALSE_IF_FALSE(stream.ReadTo(nodeCount));
				model.mPODNodes.ReserveSize(nodeCount);
			}

			break;
		case (int)PODIdentifier::NumMeshNode:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(model.mMeshNodeCount));
			break;
		case (int)PODIdentifier::NumTexture:
			{
				uint textureCount;
				RETURN_FALSE_IF_FALSE(stream.ReadTo(textureCount));
				model.mTextureNames.ReserveSize(textureCount);
			}
			break;
		case (int)PODIdentifier::NumMaterial:
			{
				uint materialCount;
				RETURN_FALSE_IF_FALSE(stream.ReadTo(materialCount));
				model.mMaterials.ReserveSize(materialCount);
			}
			break;
		case (int)PODIdentifier::NumFrame:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(model.mFrameCount));
			break;
		case (int)PODIdentifier::Flags:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(model.mFlags));
			break;
		case (int)PODIdentifier::FPS:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(model.mFPS));
			break;
		case (int)PODIdentifier::UserData:
			model.mUserData=stream.ReadData(size);
			break;
		case (int)PODIdentifier::Camera:
			RETURN_FALSE_IF_FALSE(ReadCamera(stream,model));
			break;
		case (int)PODIdentifier::Light:
			RETURN_FALSE_IF_FALSE(ReadLight(stream,model));
			break;
		case (int)PODIdentifier::Material:
			RETURN_FALSE_IF_FALSE(ReadMaterial(stream,model));
			break;
		case (int)PODIdentifier::Mesh:
			RETURN_FALSE_IF_FALSE(ReadMesh(stream,model));
			break;
		case (int)PODIdentifier::Node:
			RETURN_FALSE_IF_FALSE(ReadNode(stream,model));
			break;
		case (int)PODIdentifier::Texture:
			RETURN_FALSE_IF_FALSE(ReadTexture(stream,model));
			break;
		case (int)PODIdentifier::BackgroundColor|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::AmbientColor|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NumCamera|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NumLight|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NumMesh|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NumNode|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NumMeshNode|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NumTexture|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NumMaterial|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NumFrame|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::Flags|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::FPS|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::UserData|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::Camera|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::Light|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::Material|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::Mesh|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::Node|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::Texture|(int)PODModel::EndTagMask:
			break;
		case (int)PODIdentifier::Scene|(int)PODModel::EndTagMask:
			if (
				!model.mMaterials.IsFull()||
				!model.mPODNodes.IsFull()||
				!model.mTextureNames.IsFull()
				)
			{
				return false;
			}
			return true;
		default:
			stream.Skip(size);
			break;
		}

	}

	return true;
}

bool PODModel::ReadCamera( MemoryStream& stream,PODModel& model )
{
	std::unique_ptr<PODCameraModelNode> camera(new PODCameraModelNode(""));
	PODIdentifier identifier;
	uint size=0;

	while(ReadIdentifier(stream,identifier,size))
	{
		switch((int)identifier)
		{
		case (int)PODIdentifier::CameraTargetObjectIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(camera->TargetObjectIndex));
			break;
		case (int)PODIdentifier::CameraFOV:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(camera->FOV));
			break;
		case (int)PODIdentifier::CameraNear:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(camera->Near));
			break;
		case (int)PODIdentifier::CameraFar:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(camera->Far));
			break;
		case (int)PODIdentifier::CameraFOVAnimation:
			RETURN_FALSE_IF_FALSE(stream.ReadToList(size,camera->FOVAnimations));
			break;
		case (int)PODIdentifier::CameraTargetObjectIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::CameraFOV|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::CameraNear|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::CameraFar|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::CameraFOVAnimation|(int)PODModel::EndTagMask:
			break;
		case (int)PODIdentifier::Camera|(int)PODModel::EndTagMask:
			model.AddCamera(camera.release());
			return true;
			break;
		default:
			stream.Skip(size);
			break;
		}

	}

	return true;
}

bool PODModel::ReadLight( MemoryStream& stream,PODModel& model )
{
	std::unique_ptr<PODLightModelNode> light(new PODLightModelNode(""));
	PODIdentifier identifier;
	uint size=0;

	while(ReadIdentifier(stream,identifier,size))
	{
		switch((int)identifier)
		{
		case (int)PODIdentifier::LightTargetObjectIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(light->TargetObjectIndex));
			break;
		case (int)PODIdentifier::LightColor:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(light->Color));
			break;
		case (int)PODIdentifier::LightType:
			RETURN_FALSE_IF_FALSE(stream.ReadTo((int&)light->Type));
			break;
		case (int)PODIdentifier::LightConstantAttenuation:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(light->ConstantAttenuation));
			break;
		case (int)PODIdentifier::LightLinearAttenuation:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(light->LinearAttenuation));
			break;
		case (int)PODIdentifier::LightQuadraticAttenuation:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(light->QuadraticAttenuation));
			break;
		case (int)PODIdentifier::LightFalloffAngle:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(light->FalloffAngle));
			break;
		case (int)PODIdentifier::LightFalloffExponent:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(light->FalloffExponent));
			break;

		case (int)PODIdentifier::LightTargetObjectIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::LightColor|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::LightType|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::LightConstantAttenuation|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::LightLinearAttenuation|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::LightQuadraticAttenuation|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::LightFalloffAngle|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::LightFalloffExponent|(int)PODModel::EndTagMask:
			break;
		case (int)PODIdentifier::Light|(int)PODModel::EndTagMask:
			model.AddLight(light.release());
			return true;

		default:
			stream.Skip(size);
			break;
		}
	}

	return true;
}

bool PODModel::ReadMaterial( MemoryStream& stream,PODModel& model )
{
	std::unique_ptr<PODMaterial> material(new PODMaterial(""));

	PODIdentifier identifier;
	uint size=0;

	while(ReadIdentifier(stream,identifier,size))
	{
		switch((int)identifier)
		{
		case (int)PODIdentifier::MaterialName:
			{
				HeapString name;
				stream.ReadStringTo(name);
				RETURN_FALSE_IF_FALSE(name.Length()+1==size);
				material->SetName(model.Name()+name);
			}

			break;
		case (int)PODIdentifier::MaterialDiffuseTextureIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->DiffuseTextureIndex));
			break;
		case (int)PODIdentifier::MaterialAmbientTextureIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->AmbientTextureIndex));
			break;
		case (int)PODIdentifier::MaterialSpecularColorTextureIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->SpecularColorTextureIndex));
			break;
		case (int)PODIdentifier::MaterialSpecularLevelTextureIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->SpecularLevelTextureIndex));
			break;
		case (int)PODIdentifier::MaterialBumpMapTextureIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->BumpMapTextureIndex));
			break;
		case (int)PODIdentifier::MaterialEmissiveTextureIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->EmissiveTextureIndex));
			break;
		case (int)PODIdentifier::MaterialGlossinessTextureIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->GlossinessTextureIndex));
			break;
		case (int)PODIdentifier::MaterialOpacityTextureIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->OpacityTextureIndex));
			break;
		case (int)PODIdentifier::MaterialReflectionTextureIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->ReflectionTextureIndex));
			break;
		case (int)PODIdentifier::MaterialRefractionTextureIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->RefractionTextureIndex));
			break;
		case (int)PODIdentifier::MaterialOpacity:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->Opacity));
			break;
		case (int)PODIdentifier::MaterialAmbientColor:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->mAmbientColor));
			break;
		case (int)PODIdentifier::MaterialDiffuseColor:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->mDiffuseColor));
			break;
		case (int)PODIdentifier::MaterialSpecularColor:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->mSpecularColor));
			break;
		case (int)PODIdentifier::MaterialShininess:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->Shininess));
			break;
		case (int)PODIdentifier::MaterialEffectFile:
			stream.ReadStringTo(material->EffectFile);
			RETURN_FALSE_IF_FALSE(material->EffectFile.Length()+1==size);
			break;
		case (int)PODIdentifier::MaterialEffectName:
			stream.ReadStringTo(material->EffectName);
			RETURN_FALSE_IF_FALSE(material->EffectName.Length()+1==size);
			break;
		case (int)PODIdentifier::MaterialBlendSrcRGB:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->BlendSrcRGB));
			break;
		case (int)PODIdentifier::MaterialBlendSrcAlpha:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->BlendSrcAlpha));
			break;
		case (int)PODIdentifier::MaterialBlendDestRGB:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->BlendDestRGB));
			break;
		case (int)PODIdentifier::MaterialBlendDestAlpha:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->BlendDestAlpha));
			break;
		case (int)PODIdentifier::MaterialBlendOperationRGB:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->BlendRGBEquation));
			break;
		case (int)PODIdentifier::MaterialBlendOperationAlpha:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->BlendAlphaEquation));
			break;
		case (int)PODIdentifier::MaterialBlendColor:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->BlendColor));
			break;
		case (int)PODIdentifier::MaterialBlendFactor:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->BlendFactor));
			break;
		case (int)PODIdentifier::Flags:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(material->Flags));
			break;
		case (int)PODIdentifier::UserData:
			material->UserData=stream.ReadData(size);
			break;
		case (int)PODIdentifier::MaterialName|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialDiffuseTextureIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialOpacity|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialAmbientColor|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialDiffuseColor|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialSpecularColor|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialShininess|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialEffectFile|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialEffectName|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialAmbientTextureIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialSpecularColorTextureIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialSpecularLevelTextureIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialBumpMapTextureIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialEmissiveTextureIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialGlossinessTextureIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialOpacityTextureIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialReflectionTextureIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialRefractionTextureIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialBlendSrcRGB|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialBlendSrcAlpha|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialBlendDestRGB|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialBlendDestAlpha|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialBlendOperationRGB|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialBlendOperationAlpha|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialBlendColor|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialBlendFactor|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialFlags|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MaterialUserData|(int)PODModel::EndTagMask:
			break;
		case (int)PODIdentifier::Material|(int)PODModel::EndTagMask:
			{
				MaterialFactory::Instance().Add(material.get());
				IMaterial* materialResource=material.release();
				model.mMaterials.Append(materialResource);
				materialResource->Retain();
				return true;
			}

		default:
			stream.Skip(size);
			break;
		}
	}

	return true;
}

bool PODModel::ReadMesh( MemoryStream& stream,PODModel& model )
{
	std::unique_ptr<MeshModelNode<PODMesh>> meshNode(new MeshModelNode<PODMesh>(""));
	PODMesh& mesh=meshNode->MutableMesh();

	PODIdentifier identifier;
	uint size=0;

	while(ReadIdentifier(stream,identifier,size))
	{
		switch((int)identifier)
		{
		case (int)PODIdentifier::MeshVertexCount:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(mesh.mVertexCount));
			break;
		case (int)PODIdentifier::MeshFaceCount:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(mesh.FaceCount));
			break;
		case (int)PODIdentifier::MeshUVWChannelCount:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(mesh.UVWChannelCount));
			break;
		case (int)PODIdentifier::MeshVertexList:
			RETURN_FALSE_IF_FALSE(ReadPODData(stream,mesh.VertexList,identifier,mesh.InterleavedData.IsValid()));
			break;
		case (int)PODIdentifier::MeshFaces:
			//face data always be independent
			RETURN_FALSE_IF_FALSE(ReadPODData(stream,mesh.Faces,identifier,false));
			break;
		case (int)PODIdentifier::MeshStripLengths:
			RETURN_FALSE_IF_FALSE(stream.ReadToList(size,mesh.StripLengths));
			break;
		case (int)PODIdentifier::MeshStripCount:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(mesh.StripCount));
			break;
		case (int)PODIdentifier::MeshNormalList:
			RETURN_FALSE_IF_FALSE(ReadPODData(stream,mesh.NormalList,identifier,mesh.InterleavedData.IsValid()));
			break;
		case (int)PODIdentifier::MeshTangentList:
			RETURN_FALSE_IF_FALSE(ReadPODData(stream,mesh.TangentList,identifier,mesh.InterleavedData.IsValid()));
			break;
		case (int)PODIdentifier::MeshBinormalList:
			RETURN_FALSE_IF_FALSE(ReadPODData(stream,mesh.BinormalList,identifier,mesh.InterleavedData.IsValid()));
			break;
		case (int)PODIdentifier::MeshUVWList:
			{
				PODData uvwList;
				RETURN_FALSE_IF_FALSE(ReadPODData(stream,uvwList,identifier,mesh.InterleavedData.IsValid()));
				mesh.UVWList.Add(uvwList);
			}
			break;
		case (int)PODIdentifier::MeshVertexColorList:
			RETURN_FALSE_IF_FALSE(ReadPODData(stream,mesh.VertexColorList,identifier,mesh.InterleavedData.IsValid()));
			break;
		case (int)PODIdentifier::MeshBoneIndexList:
			RETURN_FALSE_IF_FALSE(ReadPODData(stream,mesh.BoneIndexList,identifier,mesh.InterleavedData.IsValid()));
			break;
		case (int)PODIdentifier::MeshBoneWeights:
			RETURN_FALSE_IF_FALSE(ReadPODData(stream,mesh.BoneWeights,identifier,mesh.InterleavedData.IsValid()));
			break;
		case (int)PODIdentifier::MeshBoneBatchIndexList:
			RETURN_FALSE_IF_FALSE(stream.ReadToList(size,mesh.BoneBatches.BoneBatchIndexList));
			break;
		case (int)PODIdentifier::MeshBoneBatchIndexCounts:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(mesh.BoneBatches.BoneBatchIndexCounts));
			break;
		case (int)PODIdentifier::MeshBoneBatchOffsets:
			RETURN_FALSE_IF_FALSE(stream.ReadToList(size,mesh.BoneBatches.BoneBatchOffsets));
			break;
		case (int)PODIdentifier::MeshBoneBatchMaxCount:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(mesh.BoneBatches.BoneBatchMaxCount));
			break;
		case (int)PODIdentifier::MeshBoneBatchCount:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(mesh.BoneBatches.BoneBatchCount));
			break;
		case (int)PODIdentifier::MeshUnpackMatrix:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(mesh.UnpackMatrix));
			break;
		case (int)PODIdentifier::MeshInterleavedData:
			mesh.InterleavedData=stream.ReadData(size);
			RETURN_FALSE_IF_FALSE(mesh.InterleavedData.Size()==size);
			break;
		case (int)PODIdentifier::MeshVertexCount|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshFaceCount|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshUVWChannelCount|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshVertexList|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshStripLengths|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshStripCount|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshNormalList|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshTangentList|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshBinormalList|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshUVWList|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshVertexColorList|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshBoneIndexList|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshBoneWeights|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshBoneBatchIndexList|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshBoneBatchIndexCounts|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshBoneBatchOffsets|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshBoneBatchMaxCount|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshBoneBatchCount|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshInterleavedData|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshUnpackMatrix|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::MeshFaces|(int)PODModel::EndTagMask:
			break;
		case (int)PODIdentifier::Mesh|(int)PODModel::EndTagMask:
			mesh.FixInterleavedEndianness();
			model.AddMesh(meshNode.release());
			return true;

		default:
			stream.Skip(size);
			break;
		}

	}

	return true;
}

bool PODModel::ReadNode( MemoryStream& stream,PODModel& model )
{
	std::unique_ptr<PODNode> node(new PODNode());
	PODIdentifier identifier;
	uint size=0;

	while(ReadIdentifier(stream,identifier,size))
	{
		switch((int)identifier)
		{
		case (int)PODIdentifier::NodeIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(node->Index));
			break;
		case (int)PODIdentifier::NodeName:
			stream.ReadStringTo(node->Name);
			break;
		case (int)PODIdentifier::NodeMaterialIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(node->MaterialIndex));
			break;
		case (int)PODIdentifier::NodeParentIndex:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(node->ParentIndex));
			break;
		case (int)PODIdentifier::NodeAnimationFlags:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(node->AnimationFlags));
			break;
		case (int)PODIdentifier::NodeAnimationPositionIndexes:
			RETURN_FALSE_IF_FALSE(stream.ReadToList(size,node->AnimationPositionIndexes));
			break;
		case (int)PODIdentifier::NodeAnimationPositions:
			RETURN_FALSE_IF_FALSE(stream.ReadToList(size,node->AnimationPositions));
			break;
		case (int)PODIdentifier::NodeAnimationRotationIndexes:
			RETURN_FALSE_IF_FALSE(stream.ReadToList(size,node->AnimationRotationIndexes));
			break;
		case (int)PODIdentifier::NodeAnimationRotations:
			RETURN_FALSE_IF_FALSE(stream.ReadToList(size,node->AnimationRotations));
			break;
		case (int)PODIdentifier::NodeAnimationScaleIndexes:
			RETURN_FALSE_IF_FALSE(stream.ReadToList(size,node->AnimationScaleIndexes));
			break;
		case (int)PODIdentifier::NodeAnimationScales:
			RETURN_FALSE_IF_FALSE(stream.ReadToList(size,node->AnimationScales));
			break;
		case (int)PODIdentifier::NodeAnimationMatrixIndexes:
			RETURN_FALSE_IF_FALSE(stream.ReadToList(size,node->AnimationMatrixIndexes));
			break;
		case (int)PODIdentifier::NodeAnimationMatrixes:
			// Matrices are stored "Row Major" in memory, and used "Column Major" mathematically.
			RETURN_FALSE_IF_FALSE(stream.ReadToList(size,node->AnimationMatrixes));
			/*for (auto& m:node->AnimationMatrixes)
			{
				m.Transpose();
			}*/
			break;

		case (int)PODIdentifier::NodePosition:	//older format
			{
				Point3F pos;
				RETURN_FALSE_IF_FALSE(stream.ReadTo(pos));
				node->AnimationPositions.Add(pos);
			}
			break;
		case (int)PODIdentifier::NodeRotation:	//older format
			{
				Quaternion q;
				RETURN_FALSE_IF_FALSE(stream.ReadTo(q));
				node->AnimationRotations.Add(q);
			}
			break;

		case (int)PODIdentifier::NodeScale:	//older format
			{
				Scale3F scale;
				RETURN_FALSE_IF_FALSE(stream.ReadTo(scale));
				node->AnimationScales.Add(PODScale(scale));
			}
			break;
		case (int)PODIdentifier::NodeMatrix:	//older format
			{
				Matrix4 matrix;
				RETURN_FALSE_IF_FALSE(stream.ReadTo(matrix));
				node->AnimationMatrixes.Add(matrix);
			}
			break;
		case (int)PODIdentifier::NodeUserData:
			node->UserData=stream.ReadData(size);
			RETURN_FALSE_IF_FALSE(node->UserData.Size()==size);
			break;
		case (int)PODIdentifier::NodeIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeName|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeMaterialIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeParentIndex|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeAnimationFlags|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeAnimationPositionIndexes|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeAnimationPositions|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeAnimationRotationIndexes|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeAnimationRotations|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeAnimationScaleIndexes|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeAnimationScales|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeAnimationMatrixIndexes|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeAnimationMatrixes|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodeUserData|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::NodePosition|(int)PODModel::EndTagMask://older format
		case (int)PODIdentifier::NodeRotation|(int)PODModel::EndTagMask://older format
		case (int)PODIdentifier::NodeScale|(int)PODModel::EndTagMask://older format
		case (int)PODIdentifier::NodeMatrix|(int)PODModel::EndTagMask://older format
			break;
		case (int)PODIdentifier::Node|(int)PODModel::EndTagMask:
			model.mPODNodes.Append(node.release());
			return true;

		default:
			stream.Skip(size);
			break;
		}
	}

	return true;
}


bool PODModel::ReadTexture( MemoryStream& stream,PODModel& model )
{
	PODIdentifier identifier;
	uint size=0;
	HeapString textureName;
	while(ReadIdentifier(stream,identifier,size))
	{
		switch((int)identifier)
		{
		case (int)PODIdentifier::TextureName:
			stream.ReadStringTo(textureName);
			break;
		case (int)PODIdentifier::TextureName|(int)PODModel::EndTagMask:
			break;
		case (int)PODIdentifier::Texture|(int)PODModel::EndTagMask:
			model.mTextureNames.Append(textureName);
			return true;

		default:
			stream.Skip(size);
			break;
		}
	}

	return true;
}


bool PODModel::ReadPODData( MemoryStream& stream,PODData& podData ,PODIdentifier identifier,bool isInterleavedData)
{
	podData.IsInterleaved=isInterleavedData;
    PODIdentifier identifierInt=PODIdentifier::Data;
	uint size=0;

	while(ReadIdentifier(stream,identifierInt,size))
	{
		if (identifierInt==(PODIdentifier)((uint)identifier|PODModel::EndTagMask))
		{
			return true;
		}

		switch((int)identifierInt)
		{
		case (int)PODIdentifier::DataType:
			RETURN_FALSE_IF_FALSE(stream.ReadTo((int&)podData.Type));
			break;
		case (int)PODIdentifier::ComponentCount:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(podData.ComponentCount));
			break;
		case (int)PODIdentifier::Stride:
			RETURN_FALSE_IF_FALSE(stream.ReadTo(podData.Stride));
			break;
		case (int)PODIdentifier::Data:
			if (!podData.IsInterleaved)
			{
				podData.Data=stream.ReadData(size);
				RETURN_FALSE_IF_FALSE(podData.Data.Size()==size);
			}
			else
			{
				int offset;
				RETURN_FALSE_IF_FALSE(stream.ReadTo(offset));
				podData.Data.ForceSetData((byte*)(intp)offset);
			}
			break;

		case (int)PODIdentifier::DataType|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::ComponentCount|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::Stride|(int)PODModel::EndTagMask:
		case (int)PODIdentifier::Data|(int)PODModel::EndTagMask:
			break;
		default:
			stream.Skip(size);
			break;
		}

	}

	return true;
}



const StringRef PODModel::mDefaultVersion="AB.POD.2.0";

MEDUSA_END;
