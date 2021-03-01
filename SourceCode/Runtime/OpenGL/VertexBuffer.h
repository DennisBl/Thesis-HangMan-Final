#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <CoreMinimal.h>

class FVertexBuffer
{
public:
	int64 Size;

public:
	FVertexBuffer(int64 InSize, const void *InitialData = 0);
	~FVertexBuffer();

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