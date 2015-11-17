// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Collection/Dictionary.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/IInitializable.h"

MEDUSA_BEGIN;

class EffectTechniqueGroup:public IInitializable
{
public:
	EffectTechniqueGroup(StringRef name);
	virtual ~EffectTechniqueGroup();
	virtual void Apply();
	virtual void Restore();

	StringRef GetName() const { return mName; }

	virtual bool Initialize();
	virtual bool Uninitialize();

	EffectTechnique* CreateDefaultTechnique(bool setCurrent=true);
	EffectTechnique* CreateTechnique(StringRef name,bool setCurrent=true);
	bool RemoveTechnique(StringRef name);


	EffectTechnique* GetTechniqueByIndex(uint index);
	EffectTechnique* GetTechniqueByName(StringRef name);

	EffectTechnique* CurrentTechnique() const { return mCurrentTechnique; }
	void SetCurrentTechnique(StringRef name);

	IEffect* Effect() { return mEffect; }
	void SetEffect(IEffect* val);
protected:
	HeapString mName;
	EffectTechnique* mCurrentTechnique;
	List<EffectTechnique*> mTechniques;
	Dictionary<HeapString,EffectTechnique*> mTechniqueDict;
	const static StringRef mDefaultTechniqueName;

	IEffect* mEffect;
	
};

MEDUSA_END;