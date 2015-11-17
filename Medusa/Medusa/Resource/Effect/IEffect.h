// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "Core/Collection/Dictionary.h"
#include "Core/String/HeapString.h"
#include "Graphics/GraphicsTypes.h"
#include "Core/Pattern/Delegate.h"
#include "Resource/IResource.h"

MEDUSA_BEGIN;

class IEffect:public IResource
{
public:
	IEffect(const FileIdRef& fileId=FileIdRef::Empty);
	virtual ~IEffect();
	virtual ResourceType Type()const{return ResourceType::Effect;}
	static ResourceType ClassGetResourceType(){return ResourceType::Effect;}

	virtual void Apply();
	virtual void Restore();


	virtual bool Initialize();
	virtual bool Uninitialize();

	EffectTechniqueGroup* CreateDefaultGroup(bool setCurrent=true);
	EffectTechniqueGroup* CreateGroup(StringRef name,bool setCurrent=true);

	bool RemoveGroup(StringRef name);

	EffectTechniqueGroup* GetGroupByIndex(uint index);
	EffectTechniqueGroup* GetGroupByName(StringRef name);

	//ShaderConstant* BindUniformBeforeLink(int index,StringRef name);	//called before link
	EffectTechniqueGroup* CurrentTechniqueGroup() const { return mCurrentTechniqueGroup; }
	void SetCurrentTechniqueGroup(StringRef name);

protected:

	EffectTechniqueGroup* mCurrentTechniqueGroup;
	List<EffectTechniqueGroup*> mTechniqueGroups;
	Dictionary<HeapString,EffectTechniqueGroup*> mTechniqueGroupDict;


	const static StringRef mDefaultTechniqueGroupName;
};

MEDUSA_END;