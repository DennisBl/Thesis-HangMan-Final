/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#include "TaskGraphInterface.h"

#include "../Container/Array.h"
#include "../Math/AtomicCounter.h"

static const uint32 MaxConcurrentTaskQueueCount  = 4098;
static const uint32 MaxConcurrentTaskThreadCount = 128;

class FTaskGraphResources
{
public:
	int32 ThreadCounter;
	FTaskGraphThread *TaskGraphThreads[MaxConcurrentTaskThreadCount];

	FAtomicCounter QueuedTaskCounter;
	FAtomicCounter QueuedTaskRootIndex;
	FAtomicCounter QueuedTaskEndIndex;
	TArray<FTaskGraphItemRef> QueuedTaskCache;

	FSemaphore *ThreadSemaphore;
};

static FTaskGraphResources *Resources;
static FTaskGraphSystem TaskGraphSystemGlobal;

static uint32 AddGraphTaskToQueue(FTaskGraphItemRef TaskGraphItem)
{
	int32 CurrentTaskEndIndex = Resources->QueuedTaskEndIndex;
	int32 NextTaskEndIndex = (CurrentTaskEndIndex + 1) % MaxConcurrentTaskQueueCount;

	Assert(NextTaskEndIndex != Resources->QueuedTaskRootIndex);
	{
		Resources->QueuedTaskCache[CurrentTaskEndIndex] = TaskGraphItem;
		Resources->QueuedTaskCounter++;
		Resources->QueuedTaskEndIndex = NextTaskEndIndex;
		Resources->ThreadSemaphore->Unlock();

		return CurrentTaskEndIndex;
	}
}

static bool RunNextGraphTask(FTaskGraphThread *Thread)
{
	if (!Resources->QueuedTaskCounter)
	{
		return 0;
	}

	int32 CurrentTaskRootIndex = Resources->QueuedTaskRootIndex;
	int32 NextTaskRootIndex = (CurrentTaskRootIndex + 1) % MaxConcurrentTaskQueueCount;

	if (CurrentTaskRootIndex != Resources->QueuedTaskEndIndex)
	{
		int32 Index = Resources->QueuedTaskRootIndex.CompareExchange(NextTaskRootIndex, CurrentTaskRootIndex);

		if (Index == CurrentTaskRootIndex)
		{
			FTaskGraphItemRef Task = Resources->QueuedTaskCache[Index];
			Task->Execute(Thread);
			Task->PostExecute(Thread);
			Resources->QueuedTaskCounter--;
			Resources->QueuedTaskCache[Index] = 0;
		}
	}
	else
	{
		return 0;
	}

	return 1;
}

void
FTaskGraphThread::ThreadMain()
{
	while (1)
	{
		if (!RunNextGraphTask(this))
		{
			Resources->ThreadSemaphore->Lock();
		}
	}
}

FTaskGraphItem::FTaskGraphItem()
	: CompletedByThread(0)
{
	CompletedSemaphore = new FSemaphore(0);
}

FTaskGraphItem::~FTaskGraphItem()
{
	delete CompletedSemaphore;
}

bool
FTaskGraphItem::IsCompleted(bool bShouldBlock)
{
	if (bShouldBlock)
	{
		CompletedSemaphore->Lock();
		return true;
	}

	return CompletedSemaphore->TryLock();
}

void 
FTaskGraphItem::PostExecute(FTaskGraphThread *Thread)
{
	CompletedByThread = Thread;
	CompletedSemaphore->Unlock();
}

void 
FTaskGraphInterface::Initialize(int32 ThreadCount)
{
	Assert(ThreadCount <= MaxConcurrentTaskThreadCount);

	Resources = new FTaskGraphResources();
	Resources->ThreadCounter       = ThreadCount;
	Resources->QueuedTaskCounter   = 0;
	Resources->QueuedTaskRootIndex = 0;
	Resources->QueuedTaskEndIndex  = 0;
	Resources->QueuedTaskCache.Resize(MaxConcurrentTaskQueueCount);
	Resources->ThreadSemaphore = new FSemaphore("TaskGraphInterface", ThreadCount);

	for (int32 ThreadId = 0; ThreadId < ThreadCount; ++ThreadId)
	{ 
		Resources->TaskGraphThreads[ThreadId] = new FTaskGraphThread(ThreadId);
	}
}

void 
FTaskGraphInterface::Shutdown()
{
	for (int32 ThreadId = 0; ThreadId < Resources->ThreadCounter; ++ThreadId)
	{
		delete Resources->TaskGraphThreads[ThreadId];
	}

	delete Resources->ThreadSemaphore;
	delete Resources;
}

bool 
FTaskGraphInterface::IsRunning()
{
	return Resources != 0;
}

FTaskGraphInterface *
FTaskGraphInterface::Get()
{
	return &TaskGraphSystemGlobal;
}

uint32
FTaskGraphSystem::AddTaskGraphItem(FTaskGraphItemRef &TaskGraphItem)
{
	return AddGraphTaskToQueue(TaskGraphItem);
}

void
FTaskGraphSystem::WaitUntilTaskIsComplete(FTaskGraphItemRef &TaskGraphItem)
{
	TaskGraphItem->IsCompleted(true);
}

void
FTaskGraphSystem::WaitUntilAllTasksAreComplete()
{
	while (Resources->QueuedTaskCounter);

	Resources->QueuedTaskCounter   = 0;
	Resources->QueuedTaskRootIndex = 0;
	Resources->QueuedTaskEndIndex  = 0;
}

int32 
FTaskGraphSystem::GetThreadCount() const
{
	return Resources->ThreadCounter;
}