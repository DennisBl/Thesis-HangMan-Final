#ifndef WINDOWS_PLATFORM_MEMORY_H
#define WINDOWS_PLATFORM_MEMORY_H

#include "WindowsPlatform.h"
#include <Memory/UtilityMemory.h>

class CORE_API FPlatformMemory : public FUtilityMemory
{
public:
	static void Init();
	static void Release();

	static void *Allocate(size_t Capacity, uint8 Alignment);
	static void Release(void *Memory);

	static FORCEINLINE void ProtectPage(LPVOID Address, SIZE_T Capacity, bool ReadAccess, bool WriteAccess)
	{
		uint32 AccessMode = 0;
		AccessMode |= ReadAccess ? PAGE_READONLY : 0;
		AccessMode |= WriteAccess ? PAGE_READWRITE : 0;
		AccessMode |= !ReadAccess && !WriteAccess ? PAGE_NOACCESS : 0;

		::VirtualProtect(Address, Capacity, AccessMode, 0);
	}

	static FORCEINLINE LPVOID BinnedAllocFromOS(SIZE_T Capacity)
	{
		return ::VirtualAlloc(0, Capacity, MEM_COMMIT, PAGE_READWRITE);
	}

	static FORCEINLINE void BinnedFreeToOS(LPVOID Address)
	{
		::VirtualFree(Address, 0, MEM_RELEASE);
	}
};

#endif