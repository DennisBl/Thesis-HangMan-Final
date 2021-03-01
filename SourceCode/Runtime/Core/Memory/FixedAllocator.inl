FORCEINLINE
FFixedAllocator::FFixedAllocator(void *Memory, uint64 MemorySize, uint64 ObjectSize, uint8 ObjectAlignment)
	: FAllocatorInterface(Memory, MemorySize)
	, ObjectSize(ObjectSize)
	, ObjectAlignment(ObjectAlignment)
{
	Assert(ObjectSize >= sizeof(void *));

	uint8 Adjustment = FMemory::CalcAlignment(Memory, ObjectAlignment);
	FreeList = (void **)FMemory::Increment(Memory, Adjustment);

	uint32 ObjectCount = (MemorySize - Adjustment) / ObjectSize;

	void **Pointer = FreeList;
	for (uint32 Index = 0; Index < ObjectCount - 1; Index++)
	{
		*Pointer = FMemory::Increment(Pointer, ObjectSize);
		 Pointer = (void **)*Pointer;
	}

	*Pointer = 0;
}

FORCEINLINE
FFixedAllocator::~FFixedAllocator()
{
	FreeList = 0;
}

FORCEINLINE void *
FFixedAllocator::Allocate(uint64 Size, uint8 Alignment)
{
	Assert(Size == ObjectSize && Alignment == ObjectAlignment);

	if (!FreeList)
	{
		return 0;
	}

	void *Pointer = FreeList;

	FreeList = (void **)(*FreeList);
	MemoryUsed += Size;
	MemoryCount++;

	return Pointer;
}

FORCEINLINE void
FFixedAllocator::DeAllocate(void *Address)
{
	*((void **)Address) = FreeList;

	FreeList = (void **)Address;
	MemoryUsed -= ObjectSize;
	MemoryCount--;
}