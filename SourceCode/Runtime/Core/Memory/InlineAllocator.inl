FORCEINLINE
FInlineAllocator::FInlineAllocator(void *Memory, uint64 MemorySize)
	: FAllocatorInterface(Memory, MemorySize)
	, Memory(Memory)
{
	Assert(MemorySize);
}

FORCEINLINE
FInlineAllocator::~FInlineAllocator()
{
	Memory = 0;
}

FORCEINLINE void *
FInlineAllocator::Allocate(uint64 Size, uint8 Alignment)
{
	Assert(Size);

	uint8 Adjustment = FMemory::CalcAlignment(Memory, Alignment);
	uint64 MemoryRequired = Adjustment + Size;

	if (MemoryUsed + MemoryRequired > MemorySize)
	{
		return 0;
	}

	uint8 *AddressAligned = (uint8 *)Memory + Adjustment;

	Memory = (void *)(AddressAligned + Size);
	MemoryUsed += MemoryRequired;
	MemoryCount++;

	return (void *)AddressAligned;
}

FORCEINLINE void
FInlineAllocator::DeAllocate(void *Address)
{
	Assert(0 && "Use Clear() Instead");
}

FORCEINLINE void
FInlineAllocator::Clear()
{
	Memory = MemoryBase;
	
	MemoryUsed  = 0;
	MemoryCount = 0;
}