/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#include "ProfilerCPUMetrics.h"
#include "ProfilerModule.h"

void 
FProfilerCPUMetricData::BeginMetrics()
{
	LARGE_INTEGER Counter;
	QueryPerformanceCounter(&Counter);
	CycleId = Counter.QuadPart;
}

void
FProfilerCPUMetricData::EndMetrics()
{
	CallCount++;

	LARGE_INTEGER Counter;
	QueryPerformanceCounter(&Counter);
	CycleCount += Counter.QuadPart - CycleId;

	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	Timing = static_cast<float>(CycleCount) / static_cast<float>(Frequency.QuadPart);

	FProfilerModule *ProfilerModule = FProfilerModule::Get();
	ProfilerModule->AddMetric(this);
}