// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Pattern/Singleton.h"
#include "Core/String/HeapString.h"
#include "ApplicationDebugInfoFlags.h"
#include "Application/FrameStep.h"
#include "Core/Collection/HashSet.h"
#include "Graphics/GraphicsTypes.h"
#include "Rendering/RenderableChangedFlags.h"
#include "Core/Profile/StopWatch.h"

MEDUSA_BEGIN;


class ApplicationStatics :public Singleton < ApplicationStatics >
{
	friend class Singleton < ApplicationStatics > ;
private:
	ApplicationStatics();
	~ApplicationStatics();
public:
	bool Initialize(ApplicationDebugInfoFlags val);
	void Uninitialize();
	bool IsPrintLog() const { return mIsPrintLog; }
	void SetIsPrintLog(bool val) { mIsPrintLog = val; }

	bool IsShowPerformance() const { return mDebugInfoFlag.IsPerformance(); }
	void ShowPerformance(bool val = true);

	bool IsShowGPU() const { return mDebugInfoFlag.IsGPU(); }
	void ShowGPU(bool val = true);

	bool IsShowTouch() const { return mDebugInfoFlag.IsTouch(); }
	void ShowTouch(bool val = true);
	void SetDebugString(const WStringRef& val) { mDebugString = val; }
	void SetDebugTouch(const Point2F& pos);

	void ShowAll(bool val = true) { ShowPerformance(val); ShowGPU(val); ShowTouch(val); }

	ApplicationDebugInfoFlags DebugInfo() const { return mDebugInfoFlag; }
	void EnableDebugInfo(ApplicationDebugInfoFlags val);

	bool IsEnabled() const { return mEnabled; }
	void Enable(bool val) { mEnabled = val; }

	void Reset();

	void SetElpased(FrameStep step, float val);
	void AddElpased(FrameStep step, float val);
	
	void Update(float dt);
	void Draw(float dt);
	StopWatch& UpdateWatch() { return mUpdateWatch; }

	void Resize(const Size2F& newSize);

	size_t TotalNodeCount() const { return mTotalNodeCount; }
	void AddTotalNodeCount(size_t val);

	size_t UpdateNodeCount() const { return mUpdateNodeCount; }
	void AddUpdateNodeCount(size_t val=1);

	size_t VisitNodeCount() const { return mVisitNodeCount; }
	void AddVisitNodeCount(size_t val);

	void UpdateLabels();
private:
	float mElapseds[(uint)FrameStep::Count];

	size_t mTotalNodeCount;
	size_t mUpdateNodeCount;
	size_t mVisitNodeCount;
	


	bool mEnabled;

	bool mIsDrawingPerformance;
	ILabel* mPerformanceLabel;
	WHeapString mPerformanceString;

	ILabel* mGPULabel;
	bool mIsPrintLog;

	ILabel* mDebugLabel;
	WHeapString mDebugString;

	ApplicationDebugInfoFlags mDebugInfoFlag;

	SingleBatchRenderQueue* mRenderQueue;
	RenderableChangedFlags mRenderQueueChanged;
	StopWatch mUpdateWatch;
};


MEDUSA_END;