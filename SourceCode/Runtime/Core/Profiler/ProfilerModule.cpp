/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#include "ProfilerModule.h"

static FProfilerModule ProfilerModuleGlobal;

FProfilerModule *
FProfilerModule::Get()
{
	return &ProfilerModuleGlobal;
}

void
FProfilerModule::AddMetric(FProfilerMetricData *InMetricData)
{
	if (!MetricData.Contains(InMetricData))
	{
		MetricData.Add(InMetricData);
	}
}

void
FProfilerModule::Tick(float TimeDelta)
{
	MetricData.Empty();
}