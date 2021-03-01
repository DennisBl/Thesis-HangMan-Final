/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#ifndef PROFILER_MODULE_H
#define PROFILER_MODULE_H

#include "ProfilerCPUMetrics.h"

class CORE_API FProfilerModule
{
public:
    TArray<FProfilerMetricData *> MetricData;

public:
    static FProfilerModule *Get();

    virtual void AddMetric(FProfilerMetricData *InMetricData);
    virtual void Tick(float TimeDelta);
};

#if ENABLE_PROFILING
#define PROFILER_CREATE_CPU_STAT(NAME, GROUP) static FProfilerCPUMetricData GLOBAL_CPU_STAT_##NAME(TEXT(#NAME), TEXT(#GROUP));
#define PROFILER_CREATE_GPU_STAT(NAME, GROUP) static FProfilerGPUMetricData GLOBAL_GPU_STAT_##NAME(TEXT(#NAME), TEXT(#GROUP));
#define PROFILER_CREATE_RAM_STAT(NAME, GROUP) static FProfilerRAMMetricData GLOBAL_RAM_STAT_##NAME(TEXT(#NAME), TEXT(#GROUP));

#define PROFILER_BEGIN_CPU_RECORDING(NAME) GLOBAL_CPU_STAT_##NAME.BeginMetrics()
#define PROFILER_BEGIN_GPU_RECORDING(NAME) GLOBAL_GPU_STAT_##NAME.BeginMetrics()

#define PROFILER_END_CPU_RECORDING(NAME) GLOBAL_CPU_STAT_##NAME.EndMetrics()
#define PROFILER_END_GPU_RECORDING(NAME) GLOBAL_GPU_STAT_##NAME.EndMetrics()

#define PROFILER_SCOPE_CPU_RECORDING(NAME) FScopedProfilerMetricData SCOPED_CPU_STAT_##NAME(&GLOBAL_CPU_STAT_##NAME)
#define PROFILER_SCOPE_GPU_RECORDING(NAME) FScopedProfilerMetricData SCOPED_GPU_STAT_##NAME(&GLOBAL_GPU_STAT_##NAME)
#else
#define PROFILER_CREATE_CPU_STAT(NAME)
#define PROFILER_CREATE_GPU_STAT(NAME)
#define PROFILER_CREATE_RAM_STAT(NAME)

#define PROFILER_BEGIN_CPU_RECORDING(NAME)
#define PROFILER_BEGIN_GPU_RECORDING(NAME)

#define PROFILER_END_CPU_RECORDING(NAME)
#define PROFILER_END_GPU_RECORDING(NAME)

#define PROFILER_SCOPE_CPU_RECORDING(NAME)
#define PROFILER_SCOPE_GPU_RECORDING(NAME)
#endif

#endif