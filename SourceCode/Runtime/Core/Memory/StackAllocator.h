#ifndef MEM_STACK_ALLOCATOR_H
#define MEM_STACK_ALLOCATOR_H

#include "AllocatorInterface.h"

class FStackAllocator : public FAllocatorInterface
{
public:
	FORCEINLINE FStackAllocator(void *Memory, uint64 MemorySize);
	FORCEINLINE ~FStackAllocator();

	FORCEINLINE void *Allocate(uint64 Size, uint8 Alignment) override;
	FORCEINLINE void DeAllocate(void *Address) override;

private:
	FStackAllocator(const FStackAllocator &);
	FStackAllocator &operator=(const FStackAllocator &);

private:
	struct FBlockHeader
	{
		uint8 Adjustment;
	};

private:
	void *Memory;
	void *PrevMemory;
};

#include "StackAllocator.inl"

#endif