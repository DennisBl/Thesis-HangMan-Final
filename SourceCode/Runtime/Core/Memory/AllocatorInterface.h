#ifndef MEM_BASE_ALLOCATOR_H
#define MEM_BASE_ALLOCATOR_H

#include "Memory.h"

struct FMemoryPool
{
	void *Memory;

	uint32 MemorySize;
	uint32 MemoryOffset;
};

class FAllocatorInterface
{
public:
	FORCEINLINE FAllocatorInterface(void *Memory, uint64 MemorySize);
	FORCEINLINE ~FAllocatorInterface();

	virtual void *Allocate(uint64 Size, uint8 Alignment = 4) = 0;
	virtual void DeAllocate(void *Address) = 0;

	FORCEINLINE void *GetMemory() const;

	FORCEINLINE uint64 GetMemorySize() const;
	FORCEINLINE uint64 GetUsedMemory() const;
	FORCEINLINE uint64 GetAllocationCount() const;

protected:
	void *MemoryBase;

	uint64 MemorySize;
	uint64 MemoryUsed;
	uint64 MemoryCount;
};

#include "AllocatorInterface.inl"

#endif