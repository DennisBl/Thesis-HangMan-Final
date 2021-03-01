#ifndef HEAP_ALLOCATOR_H
#define HEAP_ALLOCATOR_H

#include "AllocatorInterface.h"

class FHeapAllocator : public FAllocatorInterface
{
public:
	FORCEINLINE FHeapAllocator(void *Memory, uint64 MemorySize);
	FORCEINLINE ~FHeapAllocator();

	FORCEINLINE void *Allocate(uint64 Size, uint8 Alignment = 4) override;
	FORCEINLINE void DeAllocate(void *Address) override;

private:
	FHeapAllocator(const FHeapAllocator &);
	FHeapAllocator &operator=(const FHeapAllocator &);

protected:
	struct FMemoryHeader
	{
		uint64 HeaderSize;
		uint8 Alignment;
	};

	struct FMemoryPage
	{
		uint64 PageSize;
		FMemoryPage *PageLink;
	};

private:
	FMemoryPage *RootPage;
};

#include "HeapAllocator.inl"

#endif