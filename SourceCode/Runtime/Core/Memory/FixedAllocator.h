#ifndef MEM_POOL_ALLOCATOR_H
#define MEM_POOL_ALLOCATOR_H

#include "AllocatorInterface.h"

class FFixedAllocator : public FAllocatorInterface
{
public:
	FORCEINLINE FFixedAllocator(void *Memory, uint64 MemorySize, uint64 ObjectSize, uint8 ObjectAlignment);
	FORCEINLINE ~FFixedAllocator();

	FORCEINLINE void *Allocate(uint64 Size, uint8 Alignment) override;
	FORCEINLINE void DeAllocate(void *Address) override;

private:
	FFixedAllocator(const FFixedAllocator &);
	FFixedAllocator &operator=(const FFixedAllocator &);

private:
	void **FreeList;

	uint64 ObjectSize;
	uint64 ObjectAlignment;
};

#include "FixedAllocator.inl"

#endif