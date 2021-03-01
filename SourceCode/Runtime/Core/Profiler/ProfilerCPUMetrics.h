/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#ifndef PROFILER_CPU_METRICS_H
#define PROFILER_CPU_METRICS_H

#include "ProfilerMetrics.h"

class CORE_API FProfilerCPUMetricData : public FProfilerMetricData
{
public:
	uint64 CycleId;

public:
	FProfilerCPUMetricData(FString InMetricName, FString InMetricGroup)
		: FProfilerMetricData(InMetricName, InMetricGroup)
		, CycleId(0)
	{ }

	virtual void BeginMetrics() override;
	virtual void EndMetrics() override;
};

#endif