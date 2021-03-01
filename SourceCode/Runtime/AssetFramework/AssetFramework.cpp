#include "AssetFramework.h"

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

static const TCHAR RootDirectory[] = "../../Resources/";

void
FAssetManager::FreeResources()
{
    for (FTexture2DResource &Resource : TextureResources)
    {
        delete Resource.Resource;
    }
    for (FFontCacheResource &Resource : FontCacheResources)
    {
        delete Resource.Resource;
    }
}

static FAssetManager AssetManagerGlobal;

FAssetManager *
FAssetManager::Get()
{
    return &AssetManagerGlobal;
}

const FTexture2D *
FAssetManager::FindOrCreateTexture2D(const FString &Filename)
{
    const FTexture2DResource *Resource = FindTextureInternal(Filename);
    if (Resource)
    {
        return Resource->Resource;
    }
    else
    {
        FString Directory = RootDirectory + Filename;
        const TCHAR *DirectoryData = Directory.GetData();

        int32 ImageSizeX, ImageSizeY;
        void *ImageData = stbi_load(DirectoryData, &ImageSizeX, &ImageSizeY, 0, 4);

        FTexture2D *Texture = new FTexture2D(ImageSizeX, ImageSizeY, IF_R8G8B8A8);
        Texture->UpdateTexture(ImageData, 0, 0, ImageSizeX, ImageSizeY);
        stbi_image_free(ImageData);

        FTexture2DResource TextureResource;
        TextureResource.Filename = Filename;
        TextureResource.Resource = Texture;
        TextureResources.Add(TextureResource);

        return Texture;
    }
}

const FFontCache *
FAssetManager::FindOrCreateFontCache(const FString &Filename)
{
    const FFontCacheResource *Resource = FindFontCacheInternal(Filename);
    if (Resource)
    {
        return Resource->Resource;
    }
    else
    {
        FString Directory = RootDirectory + Filename;
        const TCHAR *DirectoryData = Directory.GetData();

        FFontCache *FontCache = new FFontCache();
        FontCache->LoadFont(DirectoryData);

        FFontCacheResource FontCacheResource;
        FontCacheResource.Filename = Filename;
        FontCacheResource.Resource = FontCache;
        FontCacheResources.Add(FontCacheResource);

        return FontCache;
    }
}

const FAssetManager::FTexture2DResource *
FAssetManager::FindTextureInternal(const FString &Filename)
{
    for (FTexture2DResource &Resource : TextureResources)
    {
        if (Resource.Filename == Filename)
        {
            return &Resource;
        }
    }

    return 0;
}

const FAssetManager::FFontCacheResource *
FAssetManager::FindFontCacheInternal(const FString &Filename)
{
    for (FFontCacheResource &Resource : FontCacheResources)
    {
        if (Resource.Filename == Filename)
        {
            return &Resource;
        }
    }

    return 0;
}