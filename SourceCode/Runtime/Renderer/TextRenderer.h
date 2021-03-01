#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "CanvasRenderer.h"
#include "FontCache.h"

struct FCanvasTextItem
{
	const FFontCache *FontCache;
	float FontScale;
	FString Text;
	int32 X;
	int32 Y;
	FColor32 Color;

	FORCEINLINE bool operator==(const FCanvasTextItem &Other)
	{
		return FontCache == Other.FontCache &&
			   Text == Other.Text &&
			   X == X &&
			   Y == Y &&
			   Color == Color;
	}
};

__declspec(align(16))
struct FCanvasTextRenderData
{
	FVector2D Position;
	FVector2D TexCoord;
	FColor32 Color;
};

class FTextRenderer : public FRendererItem
{
public:
	TArray<FCanvasTextItem> TextItems;

	FVertexShader *VertexShader;
	FPixelShader *PixelShader;
	FPipelineState *PipelineState;

public:
	FTextRenderer();
	~FTextRenderer();

	virtual FTextRenderer *GetTextRenderer() override
	{
		return this;
	}

	void AddItem(const FCanvasTextItem &Item);
	void RemoveItem(const FCanvasTextItem &Item);

	virtual void Render() override;
};

#endif