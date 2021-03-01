#include "WindowsTime.h"

static LARGE_INTEGER WindowsCurrentTiming;
static LARGE_INTEGER WindowsCurrentCPUClock;

static double GetTimeElapsed()
{
	LARGE_INTEGER CurrentTiming;
	QueryPerformanceCounter(&CurrentTiming);

	const double CurrentCycleCount = static_cast<double>(CurrentTiming.QuadPart - WindowsCurrentTiming.QuadPart);
	const double OneOverClockSpeed = 1.0 / static_cast<double>(WindowsCurrentCPUClock.QuadPart);
	return CurrentCycleCount * OneOverClockSpeed;
}

void
FPlatformTime::Initialize()
{
	QueryPerformanceCounter(&WindowsCurrentTiming);
	QueryPerformanceFrequency(&WindowsCurrentCPUClock);
}

double
FPlatformTime::Seconds()
{
	return GetTimeElapsed();
}

double
FPlatformTime::MilliSeconds()
{
	return GetTimeElapsed() * 1e3;
}

double
FPlatformTime::MicroSeconds()
{
	return GetTimeElapsed() * 1e6;
}

double
FPlatformTime::NanoSeconds()
{
	return GetTimeElapsed() * 1e9;
}

void 
FPlatformTime::Tick()
{
	QueryPerformanceCounter(&WindowsCurrentTiming);
	QueryPerformanceFrequency(&WindowsCurrentCPUClock);
}

void
FNativeTime::Initialize()
{
	QueryPerformanceFrequency(&WindowsCurrentCPUClock);
	QueryPerformanceCounter(&WindowsCurrentTiming);
}

float
FNativeTime::Seconds()
{
	return GetTimeElapsed();
}

float
FNativeTime::MilliSeconds()
{
	return GetTimeElapsed() * 1e3;
}

float
FNativeTime::MicroSeconds()
{
	return GetTimeElapsed() * 1e6;
}

float
FNativeTime::NanoSeconds()
{
	return GetTimeElapsed() * 1e9;
}