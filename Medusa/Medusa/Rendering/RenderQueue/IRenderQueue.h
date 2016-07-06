// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Rendering/RenderingTypes.h"
#include "Core/Collection/List.h"
#include "Core/Command/ICommand.h"

MEDUSA_BEGIN;


class IRenderQueue
{
public:
	typedef List<IRenderable*> RenderableNodeList;
public:
	IRenderQueue();
	virtual ~IRenderQueue(void);

	void AddCommand(const Share<IRenderingCommand>& command);
public:
	void Clear();
	void AddNode(IRenderable* node);
	void RemoveNode(IRenderable* node);

	uintp NodeCount()const { return mNodes.Count(); }

	virtual void Draw(RenderingFlags renderingFlags = RenderingFlags::None);
	virtual void Update(RenderableChangedFlags changedFlag) = 0;

public:
	virtual const Share<IRenderTarget>& RenderTarget() const = 0;
	virtual void SetRenderTarget(const Share<IRenderTarget>& val) = 0;

	virtual const Share<Camera>& GetCamera() const = 0;
	virtual void SetCamera(const Share<Camera>& val) = 0;

protected:
	virtual bool OnUpdateCommands(RenderingFlags renderingFlags = RenderingFlags::None);

#ifdef MEDUSA_DEBUG
	static void PrintRenderQueue(const RenderableNodeList& nodes);
#endif
protected:
	List<IRenderable*> mNodes;
	bool mIsNeedToSort;
	bool mIsCommandChanged;
	List<ShareCommand> mCommands;



};

MEDUSA_END;
