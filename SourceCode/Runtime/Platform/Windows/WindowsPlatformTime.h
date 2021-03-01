#ifndef WINDOWS_PLATFORM_TIME_H
#define WINDOWS_PLATFORM_TIME_H

#include <CoreMinimal.h>

class FPlatformTime
{
public:
	static void Tick();

	static float GetSeconds();
	static float GetMilliseconds();
	static float GetMicroseconds();
};

#endif