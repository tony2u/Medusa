// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Object/ArrayObjectFactory.h"
#include "RenderStateType.h"

MEDUSA_BEGIN;

class RenderStateFactory :public Singleton<RenderStateFactory>, public ArrayObjectFactory<(uint32)RenderStateType::Count, uint32, IRenderState*()>
{
	friend class Singleton<RenderStateFactory>;
	RenderStateFactory();
	~RenderStateFactory();
public:
	using ArrayObjectFactory<(uint32)RenderStateType::Count, uint32, IRenderState*()>::Create;
	using ArrayObjectFactory<(uint32)RenderStateType::Count, uint32, IRenderState*()>::Register;

	template<typename T>
	Share<IRenderState> Create()
	{
		uint32 index = Math::CountTrailingZero((uint32)T::GetTypeIdStatic());
		return this->Create(index);
	}

	template<typename T>
	void Register()
	{
		uint32 index = Math::CountTrailingZero((uint32)T::GetTypeIdStatic());
		return this->Register<T>(index);
	}

};

MEDUSA_END;
