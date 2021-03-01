#ifndef CANVAS_RENDERER_H
#define CANVAS_RENDERER_H

#include <OpenGL.h>

class FFontCache;
class FTileRenderer;
class FSpriteRenderer;
class FTextRenderer;

enum EContentAlignX
{
	CX_Left,
	CX_Center,
	CX_Right,
};

enum EContentAlignY
{
	CY_Top,
	CY_Center,
	CY_Bottom,
};

class FRendererItem
{
public:
	virtual ~FRendererItem() { }

	virtual void Render() = 0;

	virtual FTileRenderer   *GetTileRenderer()   { return 0; }
	virtual FSpriteRenderer *GetSpriteRenderer() { return 0; }
	virtual FTextRenderer   *GetTextRenderer()   { return 0; }
};

class FRenderBatch
{
public:
	FRendererItem *Renderer;
	int32 DepthSortKey;

public:
	FORCEINLINE bool operator<=(const FRenderBatch &Other) const
	{
		return DepthSortKey <= Other.DepthSortKey;
	}
};

class FCanvasRenderer
{
public:
	TArray<FRenderBatch> RenderBatches;
	TArray<int32> DepthSortKeys;

public:
	FCanvasRenderer();
	~FCanvasRenderer();

	void FlushToViewport();
	void SortElements();
	void DrawSortedElements();
	void PostDrawElements();

	void PushDepthSortKey(int32 SortKey);
	void PopDepthSortKey();
	int32 GetDepthSortKey();

	void DrawTile(int32 X, int32 Y, int32 SizeX, int32 SizeY, const FColor32 &Color, EContentAlignX AlignX = CX_Left, EContentAlignY AlignY = CY_Top);
	void DrawSprite(const FTexture2D *Sprite, int32 X, int32 Y, int32 SizeX, int32 SizeY, const FColor32 &Color, EContentAlignX AlignX = CX_Left, EContentAlignY AlignY = CY_Top);
	void DrawText(const FFontCache *FontCache, float FontScale, const FString &Text, int32 X, int32 Y, const FColor32 &Color, EContentAlignX AlignX = CX_Left, EContentAlignY AlignY = CY_Top);

	static void CalcAlignedPosition(int32 X, int32 Y, int32 SizeX, int32 SizeY, int32 *OutAlignedX, int32 *OutAlignedY, EContentAlignX AlignX, EContentAlignY AlignY);
	static void CalcAlignedPosition(const FIntRect &InPosition, FIntRect *OutAlignedPosition, EContentAlignX AlignX, EContentAlignY AlignY);

private:
	FTileRenderer   *FindOrCreateTileRenderer();
	FSpriteRenderer *FindOrCreateSpriteRenderer();
	FTextRenderer   *FindOrCreateTextRenderer();
};

#endif