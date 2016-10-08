// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseListDataBinding.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"
#include "Node/Template/TNodeTemplate.h"
#include "Resource/DataSource/TListDataSource.h"

MEDUSA_BEGIN;


template<typename T, class TCompare = EqualCompare >
class TListDataBinding:public BaseListDataBinding
{
public:
	using SelfType = TListDataBinding<T>;
	using TemplateType = TNodeTemplate<T>;
	using DataSourceType = TListDataSource<T>;
public:
	using BaseListDataBinding::BaseListDataBinding;
	virtual ~TListDataBinding(void)
	{
		SetDataSource(nullptr);
		SAFE_DELETE_DICTIONARY_VALUE(mTemplates);
		mRecentTemplate = nullptr;
	}

public:
	const Share<DataSourceType>& DataSource() const { return mDataSource; }
	void SetDataSource(const Share<DataSourceType>& val)
	{
		RETURN_IF_EQUAL(mDataSource, val);
		if (mDataSource != nullptr)
		{
			mDataSource->OnTotalChanged.UnbindObject(this);
			mDataSource->OnItemAdded.UnbindObject(this);
			mDataSource->OnItemRemoved.UnbindObject(this);
			mDataSource->OnItemUpdated.UnbindObject(this);
		}
		mDataSource = val;
		if (mDataSource != nullptr)
		{
			mDataSource->OnTotalChanged += Bind(&SelfType::OnTotalChangedHelper, this);
			mDataSource->OnItemAdded += Bind(&SelfType::OnItemAddedHelper, this);
			mDataSource->OnItemRemoved += Bind(&SelfType::OnItemAddedHelper, this);
			mDataSource->OnItemUpdated += Bind(&SelfType::OnItemUpdatedHelper, this);
		}
	}
public:
	template<typename TTemplate, typename... TArgs>
	TTemplate* AllocTemplate(TArgs&&... args)
	{
		TTemplate* t = new TTemplate(std::forward<TArgs>(args)...);
		AddTemplate(t);
		return t;
	}

	TemplateType* AddTemplate(TemplateType* val)
	{
		mTemplates.Add(val->Tag(), val);
		mRecentTemplate = val;
		return val;
	}

	const TemplateType* GetTemplate(size_t index)const
	{
		int tag = mDataSource->GetTemplateTag(index);
		if (mRecentTemplate!=nullptr&&mRecentTemplate->Tag()== tag)
		{
			return mRecentTemplate;
		}
		mRecentTemplate= mTemplates.GetOptional(tag, nullptr);
		return mRecentTemplate;
	}

	virtual Size2F GetFixedSize(const Size2F& limitSize = Size2F::Zero)const override 
	{
		const TemplateType* nodeTemplate = GetTemplate(0);
		return nodeTemplate->Measure(mDataSource->At(0), limitSize);
	}

	virtual Size2F Measure(size_t index, const Size2F& limitSize = Size2F::Zero)const override
	{
		const TemplateType* nodeTemplate=GetTemplate(index);
		return nodeTemplate->Measure(mDataSource->At(index), limitSize);
	}
	virtual INode* Load(size_t index, const Size2F& limitSize = Size2F::Zero, INode* reloadNode = nullptr) const override 
	{
		const TemplateType* nodeTemplate = GetTemplate(index);
		return nodeTemplate->Load(mDataSource->At(index), limitSize, reloadNode);
	}


public:
	virtual size_t Count()const override
	{
		return mDataSource->Count();
	}
	virtual int GetTemplateTag(size_t index)const override
	{
		return mDataSource->GetTemplateTag(index);
	}
	virtual bool HasMultipleTag()const override
	{
		return mDataSource->HasMultipleTag();
	}
public:
	virtual bool Push()override
	{
		OnTotalChanged();
		return true;
	}
	virtual bool IsValid()const override
	{
		return !mTemplates.IsEmpty()&&mDataSource != nullptr;
	}
protected:
	void OnTotalChangedHelper()
	{
		OnTotalChanged();
	}
	void OnItemAddedHelper(size_t index)
	{
		OnItemAdded(index);
	}
	void OnItemRemovedHelper(size_t index)
	{
		OnItemRemoved(index);
	}
	void OnItemUpdatedHelper(size_t index)
	{
		OnItemUpdated(index);
	}
protected:
	List<T, TCompare> mItems;
	Size2F mFixedSize{ 0.f,0.f };	//item's fixed size
	Dictionary<int, TemplateType*> mTemplates;
	Share<DataSourceType> mDataSource;

	mutable TemplateType* mRecentTemplate = nullptr;	//weak ptr
};

MEDUSA_END;
