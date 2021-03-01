#ifndef FONT_CACHE_H
#define FONT_CACHE_H

#include <OpenGL.h>

struct FTextCharacter
{
	FVector2D FontSize;
	FVector2D Bearing;
	FVector2D TexCoord;

	uint32 Advance;
};

class FFontCache
{
public:
	FTexture2D *FontTexture;
	TArray<FTextCharacter> Characters;

public:
	FFontCache();
	~FFontCache();

	void LoadFont(const TCHAR *Filename);
	void GetFontBoundRect(const FString &InText, float InTextSize, uint32 *OutBoundSizeX, uint32 *OutBoundSizeY) const;

	const FTexture2D *GetFontTexture() const
	{
		return FontTexture;
	}

	const FTextCharacter &GetCharacter(uint8 Index) const
	{
		return Characters[Index];
	}
};

extern const int32 FontTextureSizeX;
extern const int32 FontTextureSizeY;
extern const int32 FontTextureCount;

#endif