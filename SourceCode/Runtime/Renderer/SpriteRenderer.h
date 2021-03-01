#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "CanvasRenderer.h"

struct FCanvasSpriteItem
{
	const FTexture2D *Sprite;
	int32 X;
	int32 Y;
	int32 SizeX;
	int32 SizeY;
	FColor32 Color;

	FORCEINLINE bool operator==(const FCanvasSpriteItem &Other)
	{
		return Sprite == Other.Sprite &&
			   X == X &&
			   Y == Y &&
			   SizeX == SizeX &&
			   SizeY == SizeY &&
			   Color == Color;
	}
};

__declspec(align(16))
struct FCanvasSpriteRenderData
{
	FVector2D Position;
	FVector2D TexCoord;
	FColor32 Color;
};

class FSpriteRenderer : public FRendererItem
{
public:
	TArray<FCanvasSpriteItem> SpriteItems;

	FVertexShader  *VertexShader;
	FPixelShader   *PixelShader;
	FPipelineState *PipelineState;

public:
	FSpriteRenderer();
	~FSpriteRenderer();

	virtual FSpriteRenderer *GetSpriteRenderer() override
	{
		return this;
	}

	void AddItem(const FCanvasSpriteItem &Item);
	void RemoveItem(const FCanvasSpriteItem &Item);

	virtual void Render() override;
};

#endif