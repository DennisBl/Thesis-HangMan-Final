#ifndef ASSET_FRAMEWORK_H
#define ASSET_FRAMEWORK_H

#include <Renderer.h>

template <class TResourceType>
struct TAssetResource
{
	FString Filename;
	TResourceType *Resource;
};

class FAssetManager
{
	typedef TAssetResource<FTexture2D> FTexture2DResource;
	typedef TAssetResource<FFontCache> FFontCacheResource;

public:
	TArray<FTexture2DResource> TextureResources;
	TArray<FFontCacheResource> FontCacheResources;

public:
	virtual void FreeResources();

	static FAssetManager *Get();

	const FTexture2D *FindOrCreateTexture2D(const FString &Filename);
	const FFontCache *FindOrCreateFontCache(const FString &Filename);

private:
	const FTexture2DResource *FindTextureInternal(const FString &Filename);
	const FFontCacheResource *FindFontCacheInternal(const FString &Filename);
};

#endif