#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include <CoreMinimal.h>

class FVertexShader
{
public:
	FVertexShader(const FString &InSourceCode);
	~FVertexShader();

	FORCEINLINE uint32 GetResourceId() const
	{
		return ResourceId;
	}

private:
	uint32 ResourceId;
};

#endif