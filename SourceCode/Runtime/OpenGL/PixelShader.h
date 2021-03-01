#ifndef PIXEL_SHADER_H
#define PIXEL_SHADER_H

#include <CoreMinimal.h>

class FPixelShader
{
public:
	FPixelShader(const FString &InSourceCode);
	~FPixelShader();

	FORCEINLINE uint32 GetResourceId() const
	{
		return ResourceId;
	}

private:
	uint32 ResourceId;
};

#endif