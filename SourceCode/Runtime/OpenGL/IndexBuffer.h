#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <CoreMinimal.h>

class FIndexBuffer
{
public:
	int64 Size;

public:
	FIndexBuffer(int64 InSize, const void *InitialData = 0);
	~FIndexBuffer();

	void *Lock(int64 InOffset, int64 InSize);

	void Bind();

	FORCEINLINE uint32 GetResourceId() const
	{
		return ResourceId;
	}

private:
	uint32 ResourceId;
};

#endif