#ifndef TILE_RENDERER_H
#define TILE_RENDERER_H

#include "CanvasRenderer.h"

struct FCanvasTileItem
{
	int32 X;
	int32 Y;
	int32 SizeX;
	int32 SizeY;
	FColor32 Color;

	FORCEINLINE bool operator==(const FCanvasTileItem &Other)
	{
		return X == X &&
			   Y == Y &&
			   SizeX == SizeX &&
			   SizeY == SizeY &&
			   Color == Color;
	}
};

__declspec(align(16))
struct FCanvasTileRenderData
{
	FVector2D Position;
	FColor32 Color;
};

class FTileRenderer : public FRendererItem
{
public:
	TArray<FCanvasTileItem> TileItems;

	FVertexShader  *VertexShader;
	FPixelShader   *PixelShader;
	FPipelineState *PipelineState;

public:
	FTileRenderer();
	~FTileRenderer();

	virtual FTileRenderer *GetTileRenderer() override
	{
		return this;
	}

	void AddItem(const FCanvasTileItem &Item);
	void RemoveItem(const FCanvasTileItem &Item);

	virtual void Render() override;
};

#endif