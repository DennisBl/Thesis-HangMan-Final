#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include <CoreMinimal.h>

enum EImageFormat
{
	IF_R8,
	IF_R8G8B8A8,
};

class FTexture2D
{
public:
	int32 SizeX;
	int32 SizeY;
	int32 InternalFormat;
	int32 Format;
	int32 ChannelCount;

public:
	FTexture2D(int32 InSizeX, int32 InSizeY, EImageFormat InFormat);
	~FTexture2D();

	void UpdateTexture(const void *InData, int32 InOffsetX, int32 InOffsetY, int32 InSizeX, int32 InSizeY);
	void BindTexture() const;

	FORCEINLINE int32 GetSizeX() const
	{
		return SizeX;
	}

	FORCEINLINE int32 GetSizeY() const
	{
		return SizeY;
	}

	FORCEINLINE uint32 GetResourceId() const
	{
		return ResourceId;
	}

private:
	uint32 ResourceId;
};

#endif