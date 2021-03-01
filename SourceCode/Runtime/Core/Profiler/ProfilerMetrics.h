/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#ifndef PROFILER_METRICS_H
#define PROFILER_METRICS_H

#include <CommonTypes.h>
#include <Container/Array.h>
#include <Container/String.h>

#ifndef ENABLE_PROFILING
#define ENABLE_PROFILING 1
#endif

class FProfilerMetricData;
class FScopedProfilerMetricData;
class FProfilerCPUMetricData;
class FProfilerGPUMetricData;
class FProfilerRAMMetricData;
class FProfilerModule;

class FProfilerMetricData
{
public:
	FString MetricName;
	FString MetricGroup;

	uint16 ThreadId;
	uint16 CallCount;
	uint64 CycleCount;

	float Timing;

public:
	FProfilerMetricData(FString InMetricName, FString InMetricGroup)
		: MetricName(InMetricName)
		, MetricGroup(InMetricGroup)
		, ThreadId(0)
		, CallCount(0)
		, CycleCount(0)
		, Timing(0.0f)
	{ }

	virtual void BeginMetrics() = 0;
	virtual void EndMetrics() = 0;

	bool IsEqual(const FString &InMetricName) const
	{
		return MetricName == InMetricName;
	}
};

class FScopedProfilerMetricData
{
public:
	FProfilerMetricData *MetricInfo;

public:
	FScopedProfilerMetricData(FProfilerMetricData *InMetricInfo)
		: MetricInfo(InMetricInfo)
	{
		MetricInfo->BeginMetrics();
	}

	~FScopedProfilerMetricData()
	{
		MetricInfo->EndMetrics();
	}
};

#endif