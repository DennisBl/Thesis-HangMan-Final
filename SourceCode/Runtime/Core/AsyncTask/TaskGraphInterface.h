/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#ifndef TASK_GRAPH_INTERFACE_H
#define TASK_GRAPH_INTERFACE_H


#include "../HAL/PlatformThread.h"
#include "../HAL/PlatformProcess.h"

class CORE_API FTaskGraphThread : public FPlatformThread
{
public:
	FTaskGraphThread(int32 Id)
		: Id(Id)
	{ }

	int32 GetId() const
	{
		return Id;
	}

	void ThreadMain();

private:
	int32 Id;
};

class CORE_API FTaskGraphItem : public FRefCountedObject
{
public:
	FTaskGraphThread *CompletedByThread;
	FSemaphore *CompletedSemaphore;

public:
	FTaskGraphItem();
	virtual ~FTaskGraphItem();

	virtual void Execute(FTaskGraphThread *Thread) = 0;

	bool IsCompleted(bool bShouldBlock);
	void PostExecute(FTaskGraphThread *Thread);
};

typedef TRefCountPtr<FTaskGraphItem> FTaskGraphItemRef;

class CORE_API FTaskGraphInterface
{
public:
	static void Initialize(int32 ThreadCount);
	static void Shutdown();
	static bool IsRunning();

	static FTaskGraphInterface *Get();

	virtual uint32 AddTaskGraphItem(FTaskGraphItemRef &TaskGraphItem) = 0;
	virtual void WaitUntilTaskIsComplete(FTaskGraphItemRef &TaskGraphItem) = 0;
	virtual void WaitUntilAllTasksAreComplete() = 0;

	virtual int32 GetThreadCount() const = 0;
};

class CORE_API FTaskGraphSystem : public FTaskGraphInterface
{
public:
	virtual uint32 AddTaskGraphItem(FTaskGraphItemRef &TaskGraphItem) override;
	virtual void WaitUntilTaskIsComplete(FTaskGraphItemRef &TaskGraphItem) override;
	virtual void WaitUntilAllTasksAreComplete() override;

	virtual int32 GetThreadCount() const override;
};

#endif