FORCEINLINE
FStackAllocator::FStackAllocator(void *Memory, uint64 MemorySize)
	: FAllocatorInterface(Memory, MemorySize)
	, Memory(Memory)
{
	Assert(MemorySize);
}

FORCEINLINE
FStackAllocator::~FStackAllocator()
{
	Memory = 0;
}

FORCEINLINE void *
FStackAllocator::Allocate(uint64 Size, uint8 Alignment)
{
	Assert(Size);

	uint8 Adjustment = FMemory::CalcAlignment<FBlockHeader>(Memory, Alignment);
	uint64 MemoryRequired = Adjustment + Size;

	if (MemoryUsed + MemoryRequired > MemorySize)
	{
		return 0;
	}

	void *MemoryAligned = FMemory::Increment(Memory, Adjustment);
	FBlockHeader *Header = (FBlockHeader *)FMemory::Decrement(MemoryAligned, sizeof(FBlockHeader));

	Header->Adjustment = Adjustment;
	Memory = FMemory::Increment(MemoryAligned, Size);
	PrevMemory = MemoryAligned;

	MemoryUsed += MemoryRequired;
	MemoryCount++;

	return MemoryAligned;
}

FORCEINLINE void
FStackAllocator::DeAllocate(void *Address)
{
	Assert(Address == PrevMemory);

	FBlockHeader *Header = (FBlockHeader *)FMemory::Decrement(Address, sizeof(FBlockHeader));

	Memory = FMemory::Decrement(Address, Header->Adjustment);
	MemoryUsed -= (uint8 *)Memory - (uint8 *)Address + Header->Adjustment;
	MemoryCount--;
}