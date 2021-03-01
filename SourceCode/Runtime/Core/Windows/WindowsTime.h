#ifndef WINDOWS_PLATFORM_TIME_H
#define WINDOWS_PLATFORM_TIME_H

#include "WindowsPlatform.h"

class CORE_API FPlatformTime
{
public:
	static void Initialize();

	static FORCEINLINE uint64 Cycles()
	{
		LARGE_INTEGER CurrentTiming;
		QueryPerformanceCounter(&CurrentTiming);

		return CurrentTiming.QuadPart;
	}

	static FORCEINLINE uint64 CPUClock()
	{
		LARGE_INTEGER CurrentCPUClock;
		QueryPerformanceFrequency(&CurrentCPUClock);

		return CurrentCPUClock.QuadPart;
	}

	static double Seconds();
	static double MilliSeconds();
	static double MicroSeconds();
	static double NanoSeconds();

	static void Tick();
};

class CORE_API FNativeTime
{
public:
	static void Initialize();

	static float Seconds();
	static float MilliSeconds();
	static float MicroSeconds();
	static float NanoSeconds();
};

class FTimeStamp
{
public:
	FORCEINLINE void BeginTiming()
	{
		TimeTick = FNativeTime::MilliSeconds();
	}

	FORCEINLINE void EndTiming()
	{
		TimeTick = FNativeTime::MilliSeconds() - TimeTick;
	}

	FORCEINLINE float GetTimeElapsed() const
	{
		return TimeTick;
	}

private:
	float TimeTick;
};

class FScopeStamp : FTimeStamp
{
	enum
	{
		MaxBufferSize = 4098,
	};

public:
	FORCEINLINE FScopeStamp(const TCHAR *PrintText)
		: PrintText(PrintText)
	{
		BeginTiming();
	}

	FORCEINLINE ~FScopeStamp()
	{
		EndTiming();

		TCHAR Buffer[MaxBufferSize];
		sprintf_s(Buffer, "[%s]: %.02f\n", PrintText, GetTimeElapsed());
		OutputDebugStringA(Buffer);
	}

private:
	const TCHAR *PrintText;
};

#endif