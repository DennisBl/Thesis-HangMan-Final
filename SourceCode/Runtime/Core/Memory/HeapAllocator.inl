FORCEINLINE
FHeapAllocator::FHeapAllocator(void *Memory, uint64 MemorySize)
	: FAllocatorInterface(Memory, MemorySize)
{
	Assert(MemorySize > sizeof(FMemoryPage));

	RootPage = (FMemoryPage *)Memory;
	RootPage->PageSize = MemorySize;
	RootPage->PageLink = 0;
}

FORCEINLINE
FHeapAllocator::~FHeapAllocator()
{
	RootPage = 0;
}

FORCEINLINE void *
FHeapAllocator::Allocate(uint64 Size, uint8 Alignment)
{
	Assert(Size && Alignment);

	FMemoryPage *PrevFreePage = 0;
	FMemoryPage *CurrFreePage = RootPage;

	while (CurrFreePage)
	{
		uint8 Adjustment = FMemory::CalcAlignment<FMemoryHeader>(CurrFreePage, Alignment);
		uint64 TotalSize = Size + Adjustment;

		if (CurrFreePage->PageSize < TotalSize)
		{
			PrevFreePage = CurrFreePage;
			CurrFreePage = CurrFreePage->PageLink;

			continue;
		}

		if (CurrFreePage->PageSize - TotalSize <= sizeof(FMemoryHeader))
		{
			TotalSize = CurrFreePage->PageSize;

			if (PrevFreePage)
			{
				PrevFreePage->PageLink = CurrFreePage->PageLink;
			}
			else
			{
				RootPage = CurrFreePage->PageLink;
			}
		}
		else
		{
			FMemoryPage *NextFreePage = (FMemoryPage *)(FMemory::Increment(CurrFreePage, TotalSize));
			NextFreePage->PageSize = CurrFreePage->PageSize - TotalSize;
			NextFreePage->PageLink = CurrFreePage->PageLink;

			if (PrevFreePage)
			{
				PrevFreePage->PageLink = NextFreePage;
			}
			else
			{
				RootPage = NextFreePage;
			}
		}

		uint8 *AlignedMemory = (uint8 *)CurrFreePage + Adjustment;

		FMemoryHeader *Header = (FMemoryHeader *)(AlignedMemory - sizeof(FMemoryHeader));
		Header->HeaderSize = TotalSize;
		Header->Alignment  = Adjustment;

		MemoryUsed += TotalSize;
		MemoryCount++;

		return (void *)AlignedMemory;
	}

	return 0;
}

FORCEINLINE void
FHeapAllocator::DeAllocate(void *Address)
{
	Assert(Address);

	FMemoryHeader *Header = (FMemoryHeader *)FMemory::Decrement(Address, sizeof(FMemoryHeader));

	uint8 *PageStart = reinterpret_cast<uint8 *>(Address) - Header->Alignment;
	uint8 *PageEnd   = PageStart + Header->HeaderSize;
	uint64   PageSize  = Header->HeaderSize;

	FMemoryPage *PrevFreePage = 0;
	FMemoryPage *CurrFreePage = RootPage;

	while (CurrFreePage)
	{
		if ((uint8 *)CurrFreePage >= PageEnd)
		{
			break;
		}

		PrevFreePage = CurrFreePage;
		CurrFreePage = CurrFreePage->PageLink;
	}

	if (!PrevFreePage)
	{
		PrevFreePage = (FMemoryPage *)PageStart;
		PrevFreePage->PageSize = PageSize;
		PrevFreePage->PageLink = RootPage;

		RootPage = PrevFreePage;
	}
	else if ((uint8 *)PrevFreePage + PrevFreePage->PageSize == PageStart)
	{
		PrevFreePage->PageSize += PageSize;
	}
	else
	{
		FMemoryPage *Temp = (FMemoryPage *)PageStart;
		Temp->PageSize = PageSize;
		Temp->PageLink = PrevFreePage->PageLink;

		PrevFreePage->PageLink = Temp;
		PrevFreePage = Temp;
	}

	if (CurrFreePage && (uint8 *)CurrFreePage == PageEnd)
	{
		PrevFreePage->PageSize = PrevFreePage->PageSize + CurrFreePage->PageSize;
		PrevFreePage->PageLink = CurrFreePage->PageLink;
	}

	MemoryUsed -= PageSize;
	MemoryCount--;
}