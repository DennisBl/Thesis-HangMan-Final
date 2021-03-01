#ifndef UTILITY_MEMORY_H
#define UTILITY_MEMORY_H

#include "GenericMemory.h"

class FUtilityMemory : public FGenericMemory
{
public:
	static FORCEINLINE void *Copy(void *Destination, const void *Source, size_t Capacity)
	{
		return memcpy(Destination, Source, Capacity);
	}

	static FORCEINLINE void *Move(void *Destination, const void *Source, size_t Capacity)
	{
		return memmove(Destination, Source, Capacity);
	}

	static FORCEINLINE void *Fill(void *Address, int32 Value, size_t Capacity)
	{
		return memset(Address, Value, Capacity);
	}

	static FORCEINLINE void *Zero(void *Address, size_t Capacity)
	{
		return memset(Address, 0, Capacity);
	}

	static FORCEINLINE void *Search(void *Address, int32 Value, size_t MaxCount)
	{
		return memchr(Address, Value, MaxCount);
	}

	static FORCEINLINE bool Compare(const void *AddressOne, const void *AddressTwo, size_t Capacity)
	{
		return memcmp(AddressOne, AddressTwo, Capacity) == 0;
	}
};

#endif 