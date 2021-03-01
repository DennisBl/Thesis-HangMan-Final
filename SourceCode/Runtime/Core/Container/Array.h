#ifndef ARRAY_H
#define ARRAY_H

#include <CommonTypes.h>
#include <Definitions.h>
#include <Memory/Memory.h>

class FArrayAllocator
{
public:
	void *Allocate(size_t Capacity)
	{
		return FMemory::Malloc(Capacity);
	}

	void Free(void *InData)
	{
		FMemory::Free(InData);
	}

	template <class ElementType>
	void Construct(ElementType *InData)
	{
		FMemory::Construct(InData);
	}

	template <class ElementType>
	void Destruct(ElementType *InData)
	{
		FMemory::Destruct(InData);
	}
};

template <class ElementType>
class TArrayCompareMethod
{
public:
	virtual bool Compare(const ElementType &A, const ElementType &B) const = 0;
};

template <class ElementType, class ElementAllocator>
class TArray
{
typedef std::initializer_list<ElementType> ArrayInitializer;
typedef TArrayCompareMethod<ElementType> CompareMethod;

public:
	FORCEINLINE TArray();
	FORCEINLINE TArray(const TArray &Other);
	FORCEINLINE TArray(const ElementType *Elements, size_t Size);
	FORCEINLINE TArray(const ArrayInitializer &Initializer);

	explicit FORCEINLINE TArray(size_t Count);

	FORCEINLINE ~TArray();

	FORCEINLINE void Reserve(uint32 Count);
	FORCEINLINE void Resize(uint32 Count);
	FORCEINLINE void ResizeUninitialized(uint32 Count);
	FORCEINLINE void Insert(const TArray &InArray, uint32 Index);
	FORCEINLINE void Insert(const ElementType &Element, uint32 Index);
	FORCEINLINE void Insert(const ElementType *Elements, uint32 Index, size_t Size);
	FORCEINLINE void Remove(const ElementType &Element);
	FORCEINLINE void RemoveAt(uint32 Index);
	FORCEINLINE void PushToBottom(uint32 Index);
	FORCEINLINE void PushToTop(uint32 Index);
	FORCEINLINE void Pop();
	FORCEINLINE void Empty();

	FORCEINLINE int32 AddUnique(const ElementType &Element);
	FORCEINLINE int32 Add(const TArray &InArray);
	FORCEINLINE int32 Add(const ElementType &Element);
	FORCEINLINE int32 Add(const ElementType *Elements, size_t Size);
	FORCEINLINE int32 AddUninitialized();

	FORCEINLINE void Sort();
	FORCEINLINE void SortBy(const CompareMethod *CompareMethod);

	FORCEINLINE int32 Contains(const ElementType &Element) const;
	FORCEINLINE int32 Find(const ElementType &Element) const;
	FORCEINLINE int32 IsEmpty() const;

	FORCEINLINE ElementType &Top();
	FORCEINLINE ElementType &Bottom();

	FORCEINLINE const ElementType &Top() const;
	FORCEINLINE const ElementType &Bottom() const;

	FORCEINLINE ElementType *GetData();
	FORCEINLINE const ElementType *GetData() const;

	FORCEINLINE size_t GetCount() const;
	FORCEINLINE size_t GetCapacity() const;

	FORCEINLINE ElementType &operator[](int32 Index);
	FORCEINLINE const ElementType &operator[](int32 Index) const;

	FORCEINLINE TArray &operator =(const TArray &Other);

	FORCEINLINE bool operator==(const TArray &Other) const;
	FORCEINLINE bool operator!=(const TArray &Other) const;

private:
	FORCEINLINE friend       ElementType *begin(      TArray &InArray) { return InArray.GetData(); }
	FORCEINLINE friend const ElementType *begin(const TArray &InArray) { return InArray.GetData(); }
	FORCEINLINE friend       ElementType *end  (	  TArray &InArray) { return InArray.GetData() + InArray.GetCount(); }
	FORCEINLINE friend const ElementType *end  (const TArray &InArray) { return InArray.GetData() + InArray.GetCount(); }

	FORCEINLINE int32 GetSortPartition(ElementType *InData, int32 Left, int32 Right);
	FORCEINLINE void QuickSort(ElementType *InData, int32 Left, int32 Right);
	FORCEINLINE void QuickSortBy(ElementType *InData, int32 Left, int32 Right, const CompareMethod *CompareMethod);

private:
	template <class ElementType, class KeyScript, class KeyAllocator>
	friend class TSet;

	void ResizeInternal(uint32 InMinCount, uint32 InMaxCount, bool bZeroContents = true)
	{
		if (MaxCount != InMaxCount)
		{
			MaxCount = InMaxCount;
			if (MaxCount)
			{
				ElementType *CurrentData = ElementData;
				ElementData = (ElementType *)Allocator.Allocate(MaxCount * sizeof(ElementType));
				if (CurrentData)
				{
					if (MinCount < (int32)InMinCount)
					{
						FMemory::Copy(ElementData, CurrentData, MinCount * sizeof(ElementType));
					}
					else
					{
						FMemory::Copy(ElementData, CurrentData, InMinCount * sizeof(ElementType));
					}

					Allocator.Free(CurrentData);
				}
			}
			else
			{
				Allocator.Free(ElementData);
				ElementData = 0;
			}
		}

		MinCount = InMinCount;
	}

	void InformOfAddition(int32 Slack)
	{
		uint32 CurrentMinCount = MinCount;
		uint32 CurrentMaxCount = MaxCount;

		if (Slack < 0)
		{
			if (!CurrentMinCount && !CurrentMaxCount)
			{
				CurrentMaxCount = 0;
			}
			else
			{
				while (CurrentMaxCount && (CurrentMinCount + Slack) <= (CurrentMaxCount >> 1))
				{
					CurrentMaxCount >>= 1;
				}
			}
		}
		else
		{
			if (!CurrentMinCount && !CurrentMaxCount)
			{
				CurrentMaxCount = 1 << static_cast<uint32>(ceil(log2(CurrentMaxCount + Slack)));
			}
			else
			{
				while ((CurrentMinCount + Slack) > CurrentMaxCount)
				{
					CurrentMaxCount <<= 1;
				}
			}
		}
	
		CurrentMinCount += Slack;
		ResizeInternal(CurrentMinCount, CurrentMaxCount);
	}

	void MoveInternal(uint32 DestinationIndex, uint32 SourceIndex, uint32 Count)
	{
		FMemory::Move(ElementData + DestinationIndex, ElementData + SourceIndex, Count * sizeof(ElementType));
	}

	void CopyToRegion(const ElementType *InElements, uint32 Index, uint32 Count)
	{
		for (uint32 ElementIndex = 0; ElementIndex < Count; ++ElementIndex)
		{
			ElementData[Index + ElementIndex] = InElements[ElementIndex];
		}
	}

	void CopyToEmpty(const ElementType *InElements, size_t InCapacity)
	{
		int32 Slack = InCapacity / sizeof(ElementType);

		InformOfAddition(Slack);
		ConstructItems(ElementData, MinCount);
		CopyToRegion(InElements, 0, MinCount);
	}

	void ConstructItems(ElementType *Address, uint32 Count)
	{
		if (!IsZeroConstructType<ElementType>())
		{
			for (uint32 Index = 0; Index < Count; ++Index)
			{
				Allocator.Construct(Address + Index);
			}
		}
		else
		{
			FMemory::Zero(Address, sizeof(ElementType) * Count);
		}
	}

	void DestructItems(ElementType *Address, uint32 Count)
	{
		if (!IsZeroConstructType<ElementType>())
		{
			for (uint32 Index = 0; Index < Count; ++Index)
			{
				Allocator.Destruct(Address + Index);
			}
		}
	}

private:
	ElementType *ElementData;
	int32 MinCount;
	int32 MaxCount;
	ElementAllocator Allocator;
};

#include "Array.inl"

#endif