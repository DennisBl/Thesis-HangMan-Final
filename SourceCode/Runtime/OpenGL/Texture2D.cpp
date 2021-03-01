#include "Texture2D.h"
#include "OpenGL.h"

static int32 GetTextureFormat(EImageFormat Format, int32 *OutInternalFormat)
{
	switch (Format)
	{
	case IF_R8:      
		*OutInternalFormat = GL_R8;
		return GL_RED;
		break;
	case IF_R8G8B8A8: 
		*OutInternalFormat = GL_RGBA8;
		return GL_RGBA;
		break;
	}

	return -1;
}

FTexture2D::FTexture2D(int32 InSizeX, int32 InSizeY, EImageFormat InFormat)
	: SizeX(InSizeX)
	, SizeY(InSizeY)
	, InternalFormat(0)
	, Format(0)
	, ChannelCount(ChannelCount)
	, ResourceId(0)
{
	Format = GetTextureFormat(InFormat, &InternalFormat);

	glCreateTextures(GL_TEXTURE_2D, 1, &ResourceId);
	glTextureStorage2D(ResourceId, 1, InternalFormat, SizeX, SizeY);

	glTextureParameteri(ResourceId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(ResourceId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(ResourceId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(ResourceId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

FTexture2D::~FTexture2D()
{
	glDeleteTextures(1, &ResourceId);
}

void 
FTexture2D::UpdateTexture(const void *InData, int32 InOffsetX, int32 InOffsetY, int32 InSizeX, int32 InSizeY)
{
	glTextureSubImage2D(ResourceId, 0, InOffsetX, InOffsetY, InSizeX, InSizeY, Format, GL_UNSIGNED_BYTE, InData);
}

void
FTexture2D::BindTexture() const
{
	glBindTextureUnit(0, ResourceId);
}