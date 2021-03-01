#include "WindowsMemory.h"
#include <Memory/Memory.h>
#include <Memory/HeapAllocator.h>

static LPVOID TotalMemory;
static SIZE_T RootCapacity  = 128LL;
static SIZE_T PageCapacity  = 1024LL * 1024LL * 256LL;
static SIZE_T TotalCapacity = 1024LL * 1024LL * 1024LL * 16LL;
static CRITICAL_SECTION CriticalSection;

struct FMemoryAllocation
{
	LPVOID Address;
	FHeapAllocator *ProxyAllocator;
};

struct FMemoryPageResources
{
	FHeapAllocator *Allocator;

	LPVOID Address;
	SIZE_T Offset;
	SIZE_T Capacity;

	~FMemoryPageResources()
	{
		delete Allocator;
		VirtualFree(Address, Capacity, MEM_DECOMMIT);
	}
};

struct FMemoryPage
{
	FMemoryPageResources Resources;
	FMemoryPage *PrevLink;
	FMemoryPage *NextLink;

	FMemoryPage(LPVOID Address, SIZE_T Offset, SIZE_T Capacity)
		: PrevLink(0)
		, NextLink(0)
	{
		Resources.Address = Address;
		Resources.Offset = Offset;
		Resources.Capacity = Capacity;

		VirtualAlloc(Address, Capacity, MEM_COMMIT, PAGE_READWRITE);
		Resources.Allocator = new FHeapAllocator(Address, Capacity);
	}
};

static FMemoryPage *RootAllocator;

void
FPlatformMemory::Init()
{
	InitializeCriticalSection(&CriticalSection);
	TotalMemory = VirtualAlloc(0, TotalCapacity, MEM_RESERVE, PAGE_READWRITE);

	RootAllocator = new FMemoryPage(TotalMemory, 0, PageCapacity);
}

void
FPlatformMemory::Release()
{
	while (RootAllocator)
	{
		FMemoryPage *Temporary = RootAllocator;
		RootAllocator = RootAllocator->NextLink;

		delete Temporary;
	}

	DeleteCriticalSection(&CriticalSection);
	VirtualFree(TotalMemory, 0, MEM_RELEASE);
}

void *
FPlatformMemory::Allocate(size_t Capacity, uint8 Alignment)
{
	LPVOID Output = 0;
	if (RootAllocator && Capacity < PageCapacity)
	{ 
		EnterCriticalSection(&CriticalSection);
		FMemoryPage *Page = RootAllocator;

		while (!Output && Page)
		{
			FHeapAllocator *Allocator = Page->Resources.Allocator;

			SIZE_T AvailableCapacity = Allocator->GetMemorySize() - Allocator->GetUsedMemory();
			if (Capacity < AvailableCapacity)
			{
				Output = Allocator->Allocate(Capacity, Alignment);

				LeaveCriticalSection(&CriticalSection);
				return Output;
			}

			if (!Output && !Page->NextLink)
			{
				const FMemoryPageResources &Resources = Page->Resources;
				SIZE_T Offset = Resources.Offset + Resources.Capacity;
				LPVOID NewAddress = FMemory::Increment(TotalMemory, Offset);
				
				FMemoryPage *NewPage = new FMemoryPage(NewAddress, Offset, PageCapacity);
				NewPage->PrevLink = Page;
				Page->NextLink = NewPage;
			}

			Page = Page->NextLink;
		}
	}

	if (!Output)
	{
		Output = BinnedAllocFromOS(Capacity);
	}

	return Output;
}

void
FPlatformMemory::Release(void *Memory)
{
	if (RootAllocator)
	{ 
		EnterCriticalSection(&CriticalSection);
		FMemoryPage *Page = RootAllocator;

		while (Page)
		{
			const FMemoryPageResources &Resources = Page->Resources;
			LPVOID Head = Resources.Address;
			LPVOID Tail = FMemory::Increment(Head, Resources.Capacity);

			if ((SIZE_T *)Memory > (SIZE_T *)Head &&
				(SIZE_T *)Memory < (SIZE_T *)Tail)
			{
				FHeapAllocator *Allocator = Resources.Allocator;
				Allocator->DeAllocate(Memory);

				if (!Allocator->GetAllocationCount() && Page != RootAllocator)
				{
					FMemoryPage *Temporary = Page;

					if (Page->NextLink)
					{
						Page->PrevLink->NextLink = Page->NextLink;
						Page->NextLink->PrevLink = Page->PrevLink;
					}
					else
					{
						Page->PrevLink->NextLink = 0;
					}

					delete Temporary;
				}
				
				LeaveCriticalSection(&CriticalSection);
				return;
			}

			Page = Page->NextLink;
		}
	}

	BinnedFreeToOS(Memory);
}