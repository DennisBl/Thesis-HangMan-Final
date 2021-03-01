#ifndef MEM_LINEAR_ALLOCATOR_H
#define MEM_LINEAR_ALLOCATOR_H

#include "AllocatorInterface.h"

class FInlineAllocator : public FAllocatorInterface
{
public:
	FORCEINLINE FInlineAllocator(void *Memory, uint64 MemorySize);
	FORCEINLINE ~FInlineAllocator();

	FORCEINLINE void *Allocate(uint64 Size, uint8 Alignment) override;
	FORCEINLINE void DeAllocate(void *Address) override;

	FORCEINLINE void Clear();

private:
	FInlineAllocator(const FInlineAllocator &);
	FInlineAllocator &operator =(const FInlineAllocator &);

private:
	void *Memory;
};

#include "InlineAllocator.inl"

#endif