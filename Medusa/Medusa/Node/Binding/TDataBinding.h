// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IDataBinding.h"
#include "Node/Template/TNodeTemplate.h"
#include "Resource/DataSource/TDataSource.h"
MEDUSA_BEGIN;


template<typename T>
class TDataBinding :public IDataBinding
{
public:
	using SelfType = TDataBinding<T>;
	using TemplateType = TNodeTemplate<T>;
	using DataSourceType = TDataSource<T>;
public:
	TDataBinding() {}
	virtual ~TDataBinding(void) 
	{
		SetDataSource(nullptr);
		SAFE_DELETE(mTemplate);
	}
public:
	template<typename TTemplate, typename... TArgs>
	TTemplate* AllocTemplate(TArgs&&... args)
	{
		TTemplate* t = new TTemplate(std::forward<TArgs>(args)...);
		SetTemplate(t);
		return t;
	}


	TemplateType* Template() const { return mTemplate; }
	void SetTemplate(TemplateType* val) { SAFE_ASSIGN(mTemplate, val); }

	const Share<DataSourceType>& DataSource() const { return mDataSource; }
	void SetDataSource(const Share<DataSourceType>& val)
	{
		RETURN_IF_EQUAL(mDataSource, val);
		if (mDataSource!=nullptr)
		{
			mDataSource->OnTotalChanged.UnbindObject(this);
		}
		mDataSource = val;
		if (mDataSource != nullptr)
		{
			mDataSource->OnTotalChanged += Bind(&SelfType::OnTotalChangedHelper, this);
		}
	}

	virtual bool Pull() override
	{
		if (mTemplate != nullptr&&mNode != nullptr)
		{
			return mTemplate->FetchData(mNode, mDataSource->Mutable()) != nullptr;
		}

		return false; 
	}
	virtual bool Push()override 
	{
		if (mTemplate != nullptr&&mNode!=nullptr)
		{
			return mTemplate->Load(mDataSource->Get(),Size2F::Zero, mNode)!=nullptr;
		}

		return false; 
	}

	virtual bool IsValid()const override
	{
		return mTemplate != nullptr&&mDataSource != nullptr;
	}
	virtual Size2F Measure(const Size2F& limitSize = Size2F::Zero)const { return Size2F::Zero; }
	virtual INode* Load(const Size2F& limitSize = Size2F::Zero, INode* reloadNode = nullptr) const { return reloadNode; }
protected:
	void OnTotalChangedHelper()
	{
		Push();
		OnTotalChanged();
	}
protected:
	TemplateType* mTemplate = nullptr;
	Share<DataSourceType> mDataSource;
};

MEDUSA_END;
