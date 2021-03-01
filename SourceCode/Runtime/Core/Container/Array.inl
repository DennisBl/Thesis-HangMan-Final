template <class ElementType, class ElementAllocator>
FORCEINLINE
TArray<ElementType, ElementAllocator>::TArray()
	: ElementData(0)
	, MinCount(0)
	, MaxCount(0)
{ }

template <class ElementType, class ElementAllocator>
FORCEINLINE
TArray<ElementType, ElementAllocator>::TArray(const TArray &Other)
	: ElementData(0)
	, MinCount(0)
	, MaxCount(0)
{
	CopyToEmpty(Other.GetData(), Other.GetCapacity());
}

template <class ElementType, class ElementAllocator>
FORCEINLINE
TArray<ElementType, ElementAllocator>::TArray(size_t Count)
	: ElementData(0)
	, MinCount(0)
	, MaxCount(0)
{
	Resize(Count);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE
TArray<ElementType, ElementAllocator>::TArray(const ElementType *Elements, size_t Size)
	: ElementData(0)
	, MinCount(0)
	, MaxCount(0)
{
	Add(Elements, Size);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE
TArray<ElementType, ElementAllocator>::TArray(const ArrayInitializer &Initializer)
	: ElementData(0)
	, MinCount(0)
	, MaxCount(0)
{
	Add(Initializer.begin(), Initializer.size() * sizeof(ElementType));
}

template <class ElementType, class ElementAllocator>
FORCEINLINE
TArray<ElementType, ElementAllocator>::~TArray()
{
	Empty();
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void
TArray<ElementType, ElementAllocator>::Reserve(uint32 Count)
{
	ResizeInternal(MinCount, MaxCount + Count);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void
TArray<ElementType, ElementAllocator>::Resize(uint32 Count)
{
	ResizeInternal(Count, Count);
	ConstructItems(ElementData, Count);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void
TArray<ElementType, ElementAllocator>::ResizeUninitialized(uint32 Count)
{
	ResizeInternal(Count, Count);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void
TArray<ElementType, ElementAllocator>::Insert(const TArray &InArray, uint32 Index)
{
	Insert(InArray.GetData(), Index, InArray.GetCapacity());
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void
TArray<ElementType, ElementAllocator>::Insert(const ElementType &Element, uint32 Index)
{
	Insert(&Element, Index, sizeof(ElementType));
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void
TArray<ElementType, ElementAllocator>::Insert(const ElementType *Element, uint32 Index, size_t Size)
{
	size_t InsertSize = Size / sizeof(ElementType);

	InformOfAddition(InsertSize);
	MoveInternal(Index + InsertSize, Index, MinCount - InsertSize);
	CopyToRegion(Element, Index, InsertSize);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void
TArray<ElementType, ElementAllocator>::Remove(const ElementType &Element)
{
	uint32 Index = Find(Element);

	if (Index != -1)
	{
		RemoveAt(Index);
	}
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void
TArray<ElementType, ElementAllocator>::RemoveAt(uint32 Index)
{
	DestructItems(ElementData + Index, 1);
	MoveInternal(Index, Index + 1, MinCount - Index - 1);
	InformOfAddition(-1);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void 
TArray<ElementType, ElementAllocator>::PushToBottom(uint32 Index)
{
	FMath::Swap(ElementData[0], ElementData[Index]);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void 
TArray<ElementType, ElementAllocator>::PushToTop(uint32 Index)
{
	FMath::Swap(ElementData[Index], ElementData[MinCount - 1]);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void
TArray<ElementType, ElementAllocator>::Pop()
{
	RemoveAt(MinCount - 1);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void
TArray<ElementType, ElementAllocator>::Empty()
{
	DestructItems(ElementData, MinCount);
	Allocator.Free(ElementData);

	ElementData = 0;
	MinCount = 0;
	MaxCount = 0;
}

template <class ElementType, class ElementAllocator>
FORCEINLINE int32
TArray<ElementType, ElementAllocator>::AddUnique(const ElementType &Element)
{
	if (!Contains(Element))
	{
		return Add(Element);
	}

	return Find(Element);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE int32 
TArray<ElementType, ElementAllocator>::Add(const TArray &InArray)
{
	return Add(InArray.GetData(), InArray.GetCapacity());
}

template <class ElementType, class ElementAllocator>
FORCEINLINE int32
TArray<ElementType, ElementAllocator>::Add(const ElementType *Elements, size_t Size)
{
	int32 Slack = Size / sizeof(ElementType);
	int32 CurrentMinCount = MinCount;

	InformOfAddition(Slack);
	ConstructItems(ElementData + MinCount - 1, 1);
	CopyToRegion(Elements, CurrentMinCount, Slack);

	return MinCount - 1;
}

template <class ElementType, class ElementAllocator>
FORCEINLINE int32
TArray<ElementType, ElementAllocator>::Add(const ElementType &Element)
{
	return Add(&Element, sizeof(ElementType));
}

template <class ElementType, class ElementAllocator>
FORCEINLINE int32
TArray<ElementType, ElementAllocator>::AddUninitialized()
{
	InformOfAddition(1);
	ConstructItems(ElementData + MinCount - 1, 1);

	return MinCount - 1;
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void 
TArray<ElementType, ElementAllocator>::Sort()
{
	QuickSort(ElementData, 0, MinCount - 1);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void 
TArray<ElementType, ElementAllocator>::SortBy(const CompareMethod *Method)
{
	QuickSortBy(ElementData, 0, MinCount - 1, Method);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE int32
TArray<ElementType, ElementAllocator>::Contains(const ElementType &Element) const
{
	return Find(Element) != -1;
}

template <class ElementType, class ElementAllocator>
FORCEINLINE int32
TArray<ElementType, ElementAllocator>::Find(const ElementType &Element) const
{
	for (size_t Index = 0; Index < GetCount(); ++Index)
	{
		if (ElementData[Index] == Element)
		{
			return Index;
		}
	}

	return -1;
}

template <class ElementType, class ElementAllocator>
FORCEINLINE int32
TArray<ElementType, ElementAllocator>::IsEmpty() const
{
	return MinCount == 0;
}

template <class ElementType, class ElementAllocator>
FORCEINLINE ElementType &
TArray<ElementType, ElementAllocator>::Bottom()
{
	return ElementData[0];
}

template <class ElementType, class ElementAllocator>
FORCEINLINE ElementType &
TArray<ElementType, ElementAllocator>::Top()
{
	return ElementData[MinCount - 1];
}

template <class ElementType, class ElementAllocator>
FORCEINLINE const ElementType &
TArray<ElementType, ElementAllocator>::Bottom() const
{
	return ElementData[0];
}

template <class ElementType, class ElementAllocator>
FORCEINLINE const ElementType &
TArray<ElementType, ElementAllocator>::Top() const
{
	return ElementData[MinCount - 1];
}

template <class ElementType, class ElementAllocator>
FORCEINLINE ElementType *
TArray<ElementType, ElementAllocator>::GetData()
{
	return ElementData;
}

template <class ElementType, class ElementAllocator>
FORCEINLINE const ElementType *
TArray<ElementType, ElementAllocator>::GetData() const
{
	return ElementData;
}

template <class ElementType, class ElementAllocator>
FORCEINLINE size_t
TArray<ElementType, ElementAllocator>::GetCapacity() const
{
	return GetCount() * sizeof(ElementType);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE size_t
TArray<ElementType, ElementAllocator>::GetCount() const
{
	return MinCount;
}

template <class ElementType, class ElementAllocator>
FORCEINLINE ElementType &
TArray<ElementType, ElementAllocator>::operator[](int32 Index)
{
	return ElementData[Index];
}

template <class ElementType, class ElementAllocator>
FORCEINLINE const ElementType &
TArray<ElementType, ElementAllocator>::operator[](int32 Index) const
{
	return ElementData[Index];
}

template <class ElementType, class ElementAllocator>
FORCEINLINE TArray<ElementType, ElementAllocator> &
TArray<ElementType, ElementAllocator>::operator=(const TArray &Other)
{
	Empty();
	CopyToEmpty(Other.GetData(), Other.GetCapacity());
	return *this;
}

template <class ElementType, class ElementAllocator>
FORCEINLINE bool
TArray<ElementType, ElementAllocator>::operator==(const TArray &Other) const
{
	return MemoryCompare(ElementData, Other.ElementData, MinCount * sizeof(ElementType)) &&
		   MinCount == Other.MinCount &&
		   MaxCount == Other.MaxCount;
}

template <class ElementType, class ElementAllocator>
FORCEINLINE bool
TArray<ElementType, ElementAllocator>::operator!=(const TArray &Other) const
{
	return !(*this == Other);
}

template <class ElementType, class ElementAllocator>
FORCEINLINE int32 
TArray<ElementType, ElementAllocator>::GetSortPartition(ElementType *InData, int32 Left, int32 Right)
{
	const ElementType &Pivot = InData[Right];

	int32 PartitionId = Left - 1;
	for (int32 Index = Left; Index <= Right - 1; Index++)
	{
		if (InData[Index] <= Pivot)
		{
			PartitionId++;
			FMath::Swap(InData[PartitionId], InData[Index]);
		}
	}

	FMath::Swap(InData[PartitionId + 1], InData[Right]);
	return PartitionId + 1;
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void
TArray<ElementType, ElementAllocator>::QuickSort(ElementType *InData, int32 Left, int32 Right)
{
	if (Left < Right)
	{	
		int32 PartitionId = GetSortPartition(InData, Left, Right);
		QuickSort(InData, Left, PartitionId - 1);
		QuickSort(InData, PartitionId + 1, Right);
	}
}

template <class ElementType, class ElementAllocator>
FORCEINLINE void
TArray<ElementType, ElementAllocator>::QuickSortBy(ElementType *InData, int32 Left, int32 Right, const CompareMethod *Method)
{
	size_t Start = Left;
	size_t End = Right;

	size_t PivotIndex = (Left + Right) / 2;
	const ElementType &Pivot = *(InData + PivotIndex);

	while (End > Left || Start < Right)
	{
		while (Method->Compare(InData[Start], InData[PivotIndex]))
		{
			Start++;
		}

		while (!Method->Compare(InData[End], InData[PivotIndex]))
		{
			End--;
		}

		if (Start <= End)
		{
			FMath::Swap(*(InData + Start), *(InData + End));

			Start++;
			End--;
		}
		else
		{
			if (End > Left)
			{
				QuickSortBy(InData, Left, End, Method);
			}

			if (Start < Right)
			{
				QuickSortBy(InData, Start, Right, Method);
			}

			return;
		}
	}
}