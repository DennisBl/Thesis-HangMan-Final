#ifndef GENERIC_MEMORY_H
#define GENERIC_MEMORY_H

#include <Definitions.h>
#include <CommonTypes.h>
#include <memory.h>

class FGenericMemory
{
public:
	static FORCEINLINE void *Malloc(size_t Capacity)
	{
		return malloc(Capacity);
	}

	static FORCEINLINE void *Calloc(size_t Count, size_t Capacity)
	{
		return calloc(Count, Capacity);
	}

	static FORCEINLINE void *Realloc(void *Address, size_t Capacity)
	{
		return realloc(Address, Capacity);
	}

	static FORCEINLINE void Free(void *Address)
	{
		free(Address);
	}
};

#endif 