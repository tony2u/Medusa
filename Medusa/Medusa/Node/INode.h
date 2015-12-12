// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Runnable/DefaultRunnable.h"

#include "Core/Pattern/Ptr/LazyStrongPtr.h"
#include "Core/Collection/SortedList.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Action/BaseActionRunner.h"
#include "Rendering/IRenderable.h"
#include "Core/Pattern/Runnable/IRunnable.h"
#include "Core/Geometry/Rect2.h"
#include "Core/Pattern/IClone.h"

#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Pattern/Component/IEntity.h"
#include "Node/Layout/ILayoutable.h"

#include "Node/NodeDefines.h"

#include "NodeLayoutArrangeFlags.h"
#include "NodeLayoutChangedFlags.h"
#include "NodeRemoveFlags.h"
#include "NodeUpdateFlags.h"
#include "NodeVisitFlags.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Core/Collection/LinkedList.h"

MEDUSA_BEGIN;

typedef SortedList<INode*, DefaultCompare<INode*>, CustomCompareForPointer<INode*> > NodeList;
//typedef List<INode*,CustomCompareForPointer<INode> > NodeList;

/*
(RenderTarget,Priority,Effect,Material,RenderingStrategy) determined a batch together.

*/


class INode :public IRenderable,
	public IClone<INode*>,
	public RTTIObject,
	public IInitializable,
	public BaseActionRunner<INode>,
	public DefaultRunnable,
	public ILayoutable,
	public IEntity
{
	MEDUSA_DECLARE_RTTI_ROOT;
	friend class InputDispatcher;
	friend class IScene;
public:
	using BaseActionRunner<INode>::FindActionByTag;
	using BaseActionRunner<INode>::IsActionRunningByTag;
	using BaseActionRunner<INode>::PauseActionByTag;
	using BaseActionRunner<INode>::PauseAllActions;
	using BaseActionRunner<INode>::ResumeActionByTag;
	using BaseActionRunner<INode>::ResumeAllActions;
	using BaseActionRunner<INode>::RunAction;
	using BaseActionRunner<INode>::StopActionByTag;
	using BaseActionRunner<INode>::StopAllActions;
	using BaseActionRunner<INode>::UpdateActions;
	using BaseActionRunner<INode>::IsActionRunning;

public:
	INode(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	virtual ~INode(void);

public:
	//node tree

	bool operator<(const INode& node)const { return mDepth < node.mDepth; }
	int Compare(const INode& node)const { return mDepth - node.mDepth; }

	INode* Parent() const { return mParent; }
	IScene* TryGetRootScene()const;
	void SetParent(INode* val);
	bool IsRoot()const { return mParent == nullptr; }

	bool IsManaged() const { return mIsManaged; }
	void EnableManaged(bool val = true) { mIsManaged = val; }

	void RemoveFromParent();
	void DeleteFromParent();

	virtual void AddChild(INode* node);
	virtual bool RemoveChild(INode* node);
	virtual void RemoveAllChilds(NodeRemoveFlags flags = NodeRemoveFlags::OnlyChildren);
	virtual bool DeleteChild(INode* node);
	virtual void DeleteAllChilds(NodeRemoveFlags flags = NodeRemoveFlags::OnlyChildren);
	virtual void Clear(NodeRemoveFlags flags = NodeRemoveFlags::OnlyChildren);

	bool RemoveChild(const StringRef& name);
	bool DeleteChild(const StringRef& name);


	INode* FindChildWithId(uintp id);
	const NodeList& Children() const { return mNodes; }
	NodeList& MutableChildren() { return mNodes; }

	INode* FindChild(StringRef name);
	const INode* FindChild(StringRef name)const;
	INode* FirstChild();
	const INode* FirstChild()const;

	bool HasChild(INode* node)const;
	bool HasChildRecursively(INode* node)const;

	bool HasChild(StringRef name)const;
	bool HasChildRecursively(StringRef name)const;

	INode* FindChildRecursively(StringRef name);
	const INode* FindChildRecursively(StringRef name)const;

	int Depth() const { return mDepth; }
	void SetDepth(int val) { mDepth = val; }
	void ReorderAllChilds();

	int Tag() const { return mTag; }
	void SetTag(int val) { mTag = val; }
protected:
#pragma region Layout
public:
	virtual void UpdateLayout(const Size2F& availableSize = Size2F::Zero)override;

	virtual Rect2F ArrangeSelf(const Rect2F& limitRect = Rect2F::Zero, NodeLayoutArrangeFlags arrangeFlags = NodeLayoutArrangeFlags::None)override;
	virtual bool ArrangeChildren(const Rect2F& limitRect = Rect2F::Zero, NodeLayoutArrangeFlags arrangeFlags = NodeLayoutArrangeFlags::None)override;
	virtual bool ArrangeRecursively(const Rect2F& limitRect = Rect2F::Zero, NodeLayoutArrangeFlags arrangeFlags = NodeLayoutArrangeFlags::None)override;

	Point2F DockToRect(const Rect2F& rect, DockPoint dock, const Point2F& relativePosition = Point2F::Zero);
	Point2F DockToParent(DockPoint dock, const Point2F& relativePosition = Point2F::Zero);
	Point2F DockToScreen(DockPoint dock, const Point2F& relativePosition = Point2F::Zero);

	void StretchToRect(const Rect2F& rect, Stretch stretch, const Scale2F& strecthPercent = Scale2F::One);
	void StretchToParent(Stretch stretch, const Scale2F& strecthPercent = Scale2F::One);
	void StretchToSceen(Stretch stretch, const Scale2F& strecthPercent = Scale2F::One);

protected:
	virtual void Measure(const Size2F& availableSize)override;
	virtual void OnBeforeMeasure(const Size2F& availableSize)override;
	virtual void OnAfterMeasure(const Size2F& availableSize)override;
	virtual void OnLayoutChanged(const ILayoutable& sender, NodeLayoutChangedFlags changedFlag)override;

#pragma endregion Layout

#pragma region Update
public:
	void SetRenderingPriorityRecursively(RenderingPriority val);
	void SetRenderingStrategyRecursively(RenderingStrategy val);
	void SetMeshFixTypeRecursively(MeshFixType val);

	bool UpdateRecursively(float dt, const NodeUpdateFlags& flag = NodeUpdateFlags::None);
	virtual bool Update(float dt, NodeUpdateFlags flag = NodeUpdateFlags::None);
	virtual bool BeforeUpdate(float dt, NodeUpdateFlags flag = NodeUpdateFlags::None);
	virtual bool AfterUpdate(float dt, NodeUpdateFlags flag = NodeUpdateFlags::None);


	virtual bool EnterRecursively();
	virtual bool Enter() { return true; }

	virtual bool ExitRecursively();
	virtual bool Exit() { return true; }

	virtual bool UpdateLogicRecursively();
	virtual bool UpdateLogic() { return true; }

	virtual bool ResetLogicRecursively();
	virtual bool ResetLogic() { return true; }

	virtual void VisitRecursively(IVisitor < INode* >& visitor, RenderableChangedFlags& outFlag, NodeVisitFlags nodeFlag = NodeVisitFlags::None, RenderStateType renderStateFlag = RenderStateType::None);


protected:
	void OnVisitQueueChanged();


	IScene* Scene() const { return mScene; }
	void SetScene(IScene* val) { mScene = val; }

	bool NeedVisit()const { return mNeedVisit; }
	void CompleteVisit() { mNeedVisit = false; }
#pragma endregion Update
#pragma region Event
public:
	//Event
	InputDispatcher& MutableInput();

	bool IsInputEnabled() const { return mInputEnabled; }
	void EnableInput(bool val) { mInputEnabled = val; }

	bool IsInputPassingEnabled() const { return mInputEnabled&&mInputPassingEnabled; }
	void EnableInputPassing();
	void ResetInputPassing();

	virtual bool IsModal()const { return false; }


#pragma endregion Event

#pragma region DataBind
public:
	IDataSource* DataSource() const { return mDataSource; }
	virtual void SetDataSource(IDataSource* val);
	void ReleaseDataSource();
protected:
	virtual void OnDataChanged(const IDataSource& dataSource);
#pragma endregion DataBind

#pragma region Debug
public:
	bool IsDebugDrawEnabled()const { return mDebugDrawShape != nullptr; }
	void EnableDebugDraw(bool val);
#pragma endregion Debug

protected:
	virtual void OnMoveableDirty(MoveableChangedFlags changedFlags)override;
	virtual void OnRenderChanged(RenderableChangedFlags flag)override;
	virtual void OnMeshChanged(RenderableChangedFlags flag)override;

protected:
	int mDepth=0;	//used to indicate updating order
	int mTag=0;

	Dictionary<HeapString, INode*> mNodeDict;
	NodeList mNodes;
	NodeList mManagedNodes;	//nodes managed by engine,weak reference to mNodes

	INode* mParent=nullptr;
	bool mIsManaged=false;

	InputDispatcher* mInputDispatcher=nullptr;

	bool mInputEnabled=true;	//just for self
	bool mInputPassingEnabled=true;	//true means to need to check all children' input dispatcher recursively.

	IDataSource* mDataSource=nullptr;

	//Debug
	IShape* mDebugDrawShape=nullptr;
#pragma region Update
	IScene* mScene=nullptr;
	bool mNeedVisit=false;


#pragma endregion Update

};


MEDUSA_END;

#ifdef MEDUSA_SCRIPT
MEDUSA_SCRIPT_BEGIN;
void RegisterINode(asIScriptEngine* engine);

template <class T>
void RegisterINode_Methods(asIScriptEngine* engine, const char* typeName)
{

}

MEDUSA_SCRIPT_END;
#endif