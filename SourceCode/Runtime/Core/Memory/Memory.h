#ifndef MEMORY_H
#define MEMORY_H

#include "UtilityMemory.h"
#include <Windows/WindowsMemory.h>

class FMemory : public FPlatformMemory
{
public:
	template <class ElementType>
	static FORCEINLINE ElementType *Construct(ElementType *Address)
	{
		return new (Address) ElementType;
	}

	template <class ElementType>
	static FORCEINLINE void Destruct(ElementType *Address)
	{
		Address->~ElementType();
	}

	template <class ElementType>
	static FORCEINLINE ElementType *Increment(ElementType *Address, size_t Amount)
	{
		return reinterpret_cast<ElementType *>((reinterpret_cast<uint8 *>(Address) + Amount));
	}

	template <class ElementType>
	static FORCEINLINE ElementType *Decrement(ElementType *Address, size_t Amount)
	{
		return reinterpret_cast<ElementType *>((reinterpret_cast<uint8 *>(Address) - Amount));
	}

	template <class ElementType>
	static FORCEINLINE ElementType *Align(ElementType *Address, size_t Alignment)
	{
		return reinterpret_cast<ElementType *>((
			reinterpret_cast<uint8 *>(Address) +
			static_cast<uint8 *>(Alignment - 1)) &
			static_cast<uint8 *>(~(Alignment - 1)));
	}

	static FORCEINLINE size_t CalcAlignment(void *Address, size_t Alignment)
	{
		size_t Adjustment = Alignment - (reinterpret_cast<uintptr_t>(Address) & static_cast<uintptr_t>(Alignment - 1));
		return Adjustment == Alignment ? 0 : Adjustment;
	}

	template <class HeaderType>
	static FORCEINLINE size_t CalcAlignment(void *Address, size_t Alignment)
	{
		size_t HeaderCapacity = sizeof(HeaderType);
		size_t Adjustment = CalcAlignment(Address, Alignment);

		if (Adjustment < HeaderCapacity)
		{
			HeaderCapacity -= Adjustment;
			Adjustment += Alignment * (HeaderCapacity / Alignment);

			if (HeaderCapacity & Alignment)
			{
				Adjustment += Alignment;
			}
		}

		return Adjustment;
	}
};

#endif