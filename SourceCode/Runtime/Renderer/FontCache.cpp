#include "FontCache.h"

#include <FT/ft2build.h>
#include <FT/freeType.h>

const int32 FontTextureSizeX = 48;
const int32 FontTextureSizeY = 48;
const int32 FontTextureCount = 128;

FFontCache::FFontCache()
	: FontTexture(0)
{
	Characters.Resize(FontTextureCount);
	FontTexture = new FTexture2D(FontTextureSizeX * FontTextureCount, FontTextureSizeY, IF_R8);
}

FFontCache::~FFontCache()
{
	delete FontTexture;
}

void 
FFontCache::LoadFont(const TCHAR *Filename)
{
	FT_Library Library;
	FT_Init_FreeType(&Library);

	FT_Face Face;
	FT_New_Face(Library, Filename, 0, &Face);
	FT_Set_Pixel_Sizes(Face, 0, 48);
	for (uint32 Index = 0; Index < FontTextureCount; ++Index)
	{
		FT_Load_Char(Face, Index, FT_LOAD_RENDER);

		uint8 *FontImage = Face->glyph->bitmap.buffer;
		uint32 FontSizeX = Face->glyph->bitmap.width;
		uint32 FontSizeY = Face->glyph->bitmap.rows;
		uint32 Advance   = Face->glyph->advance.x;
		
		int32 ImageX = Face->glyph->bitmap_left;
		int32 ImageY = Face->glyph->bitmap_top;

		float ImageSizeX = (1.0f / (float)FontTextureCount) * ((float)FontSizeX / (float)FontTextureSizeX);
		float ImageSizeY = (float)FontSizeY / (float)FontTextureSizeY;
	
		FVector2D FontSize = FVector2D(FontSizeX,  FontSizeY);
		FVector2D Bearing  = FVector2D(ImageX,     ImageY);
		FVector2D TexCoord = FVector2D(ImageSizeX, ImageSizeY);

		Characters[Index].FontSize = FontSize;
		Characters[Index].Bearing  = Bearing;
		Characters[Index].TexCoord = TexCoord;
		Characters[Index].Advance  = Advance;

		if (FontSizeX && FontSizeY)
		{
			FontTexture->UpdateTexture(FontImage, Index * FontTextureSizeX, FontTextureSizeY - FontSizeY, FontSizeX, FontSizeY);
		}
	}

	FT_Done_Face(Face);
	FT_Done_FreeType(Library);
}

void
FFontCache::GetFontBoundRect(const FString &InText, float InTextSize, uint32 *OutBoundSizeX, uint32 *OutBoundSizeY) const
{
	*OutBoundSizeX = 0;
	*OutBoundSizeY = 0;

	for (uint32 Index = 0; Index < InText.GetLength(); ++Index)
	{
		const FTextCharacter &Character = Characters[InText[Index]];

		if (*OutBoundSizeY < (float)Character.FontSize.Y * InTextSize)
		{
			*OutBoundSizeY = (float)Character.FontSize.Y * InTextSize;
		}

		*OutBoundSizeX += (float)(Character.Advance >> 6) * InTextSize;
	}
}