FORCEINLINE
FAllocatorInterface::FAllocatorInterface(void *Memory, uint64 MemorySize)
	: MemoryBase(Memory)
	, MemorySize(MemorySize)
	, MemoryUsed(0)
	, MemoryCount(0)
{ }

FORCEINLINE
FAllocatorInterface::~FAllocatorInterface()
{
	Assert(!MemoryUsed && !MemoryCount);

	MemoryBase  = 0;
	MemorySize  = 0;
	MemoryUsed  = 0;
	MemoryCount = 0;
}

FORCEINLINE void *
FAllocatorInterface::GetMemory() const
{
	return MemoryBase;
}

FORCEINLINE uint64
FAllocatorInterface::GetMemorySize() const
{
	return MemorySize;
}

FORCEINLINE uint64
FAllocatorInterface::GetUsedMemory() const
{
	return MemoryUsed;
}

FORCEINLINE uint64
FAllocatorInterface::GetAllocationCount() const
{
	return MemoryCount;
}