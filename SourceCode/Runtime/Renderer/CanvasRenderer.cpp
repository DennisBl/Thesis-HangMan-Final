#include "CanvasRenderer.h"
#include "TileRenderer.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

FCanvasRenderer::FCanvasRenderer()
{
	PushDepthSortKey(0);
}

FCanvasRenderer::~FCanvasRenderer()
{
	for (FRenderBatch &RenderBatch : RenderBatches)
	{
		FRendererItem *Renderer = RenderBatch.Renderer;
		delete Renderer;
	}
}

void 
FCanvasRenderer::FlushToViewport()
{
	SortElements();
	DrawSortedElements();
	PostDrawElements();
}

void
FCanvasRenderer::SortElements()
{
	RenderBatches.Sort();
}

void 
FCanvasRenderer::DrawSortedElements()
{
	for (FRenderBatch &RenderBatch : RenderBatches)
	{
		FRendererItem *Renderer = RenderBatch.Renderer;
		Renderer->Render();
	}
}

void
FCanvasRenderer::PostDrawElements()
{
	for (FRenderBatch &RenderBatch : RenderBatches)
	{
		FRendererItem *Renderer = RenderBatch.Renderer;
		delete Renderer;
	}

	RenderBatches.Empty();
	DepthSortKeys.Empty();
	PushDepthSortKey(0);
}

void
FCanvasRenderer::PushDepthSortKey(int32 SortKey)
{
	DepthSortKeys.Add(SortKey);
}

void 
FCanvasRenderer::PopDepthSortKey()
{
	DepthSortKeys.Pop();
}

int32
FCanvasRenderer::GetDepthSortKey()
{
	return DepthSortKeys.Top();
}

void 
FCanvasRenderer::DrawTile(int32 X, int32 Y, int32 SizeX, int32 SizeY, const FColor32 &Color, EContentAlignX AlignX, EContentAlignY AlignY)
{
	int32 ResolutionSizeX, ResolutionSizeY;
	FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);

	int32 PositionX = 0;
	switch (AlignX)
	{
	case CX_Left:
		PositionX += X;
		break;
	case CX_Center:
		PositionX += X + ((ResolutionSizeX - SizeX) >> 1);
		break;
	case CX_Right:
		PositionX += X + ResolutionSizeX - SizeX;
		break;
	}

	int32 PositionY = 0;
	switch (AlignY)
	{
	case CY_Top:
		PositionY += ResolutionSizeY - Y - SizeY;
		break;
	case CY_Center:
		PositionY += ((ResolutionSizeY - SizeY) >> 1) - Y;
		break;
	case CY_Bottom:
		PositionY += -Y;
		break;
	}

	FCanvasTileItem TileItem;
	TileItem.X = PositionX;
	TileItem.Y = PositionY;
	TileItem.SizeX = SizeX;
	TileItem.SizeY = SizeY;
	TileItem.Color = Color;

	FTileRenderer *TileRenderer = FindOrCreateTileRenderer();
	TileRenderer->AddItem(TileItem);
}

void 
FCanvasRenderer::DrawSprite(const FTexture2D *Sprite, int32 X, int32 Y, int32 SizeX, int32 SizeY, const FColor32 &Color, EContentAlignX AlignX, EContentAlignY AlignY)
{
	int32 ResolutionSizeX, ResolutionSizeY;
	FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);

	int32 PositionX = 0;
	switch (AlignX)
	{
	case CX_Left:
		PositionX += X;
		break;
	case CX_Center:
		PositionX += X + ((ResolutionSizeX - SizeX) >> 1);
		break;
	case CX_Right:
		PositionX += X + ResolutionSizeX - SizeX;
		break;
	}

	int32 PositionY = 0;
	switch (AlignY)
	{
	case CY_Top:
		PositionY += ResolutionSizeY - Y - SizeY;
		break;
	case CY_Center:
		PositionY += ((ResolutionSizeY - SizeY) >> 1) - Y;
		break;
	case CY_Bottom:
		PositionY += -Y;
		break;
	}

	FCanvasSpriteItem SpriteItem;
	SpriteItem.Sprite = Sprite;
	SpriteItem.X = PositionX;
	SpriteItem.Y = PositionY;
	SpriteItem.SizeX = SizeX;
	SpriteItem.SizeY = SizeY;
	SpriteItem.Color = Color;

	FSpriteRenderer *SpriteRenderer = FindOrCreateSpriteRenderer();
	SpriteRenderer->AddItem(SpriteItem);
}

void 
FCanvasRenderer::DrawText(const FFontCache *FontCache, float FontScale, const FString &Text, int32 X, int32 Y, const FColor32 &Color, EContentAlignX AlignX, EContentAlignY AlignY)
{
	int32 ResolutionSizeX, ResolutionSizeY;
	FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);

	uint32 SizeX, SizeY;
	FontCache->GetFontBoundRect(Text, FontScale, &SizeX, &SizeY);

	int32 PositionX = 0;
	switch (AlignX)
	{
	case CX_Left:
		PositionX += X;
		break;
	case CX_Center:
		PositionX += X + ((ResolutionSizeX - SizeX) >> 1);
		break;
	case CX_Right:
		PositionX += X + ResolutionSizeX - SizeX;
		break;
	}

	int32 PositionY = 0;
	switch (AlignY)
	{
	case CY_Top:
		PositionY += ResolutionSizeY - Y - SizeY;
		break;
	case CY_Center:
		PositionY += ((ResolutionSizeY - SizeY) >> 1) - Y;
		break;
	case CY_Bottom:
		PositionY += -Y;
		break;
	}

	FCanvasTextItem TextItem;
	TextItem.FontCache = FontCache;
	TextItem.FontScale = FontScale;
	TextItem.Text = Text;
	TextItem.X = PositionX;
	TextItem.Y = PositionY;
	TextItem.Color = Color;

	FTextRenderer *TextRenderer = FindOrCreateTextRenderer();
	TextRenderer->AddItem(TextItem);
}

void
FCanvasRenderer::CalcAlignedPosition(int32 X, int32 Y, int32 SizeX, int32 SizeY, int32 *OutAlignedX, int32 *OutAlignedY, EContentAlignX AlignX, EContentAlignY AlignY)
{
	int32 ResolutionSizeX, ResolutionSizeY;
	FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);

	*OutAlignedX = 0;
	switch (AlignX)
	{
	case CX_Left:
		*OutAlignedX += X;
		break;
	case CX_Center:
		*OutAlignedX += X + ((ResolutionSizeX - SizeX) >> 1);
		break;
	case CX_Right:
		*OutAlignedX += X + ResolutionSizeX - SizeX;
		break;
	}

	*OutAlignedY = 0;
	switch (AlignY)
	{
	case CY_Top:
		*OutAlignedY += ResolutionSizeY - Y - SizeY;
		break;
	case CY_Center:
		*OutAlignedY += ((ResolutionSizeY - SizeY) >> 1) - Y;
		break;
	case CY_Bottom:
		*OutAlignedY += -Y;
		break;
	}
}

void
FCanvasRenderer::CalcAlignedPosition(const FIntRect &InPosition, FIntRect *OutAlignedPosition, EContentAlignX AlignX, EContentAlignY AlignY)
{
	int32 AlignedX, AlignedY;
	CalcAlignedPosition(
		InPosition.GetOriginX(),
		InPosition.GetOriginY(),
		InPosition.GetSizeX(),
		InPosition.GetSizeY(),
		&AlignedX,
		&AlignedY,
		AlignX,
		AlignY);

	OutAlignedPosition->Min = FIntPoint(AlignedX, AlignedY);
	OutAlignedPosition->Max = FIntPoint(AlignedX, AlignedY) + InPosition.GetSize();
}

FTileRenderer *
FCanvasRenderer::FindOrCreateTileRenderer()
{
	uint32 DepthSortKey = GetDepthSortKey();
	for (FRenderBatch &RenderBatch : RenderBatches)
	{
		FRendererItem *Renderer = RenderBatch.Renderer;

		FTileRenderer *TileRenderer = Renderer->GetTileRenderer();
		if (TileRenderer && RenderBatch.DepthSortKey == DepthSortKey)
		{
			return TileRenderer;
		}
	}

	FTileRenderer *TileRenderer = new FTileRenderer();

	FRenderBatch RenderBatch;
	RenderBatch.Renderer     = TileRenderer;
	RenderBatch.DepthSortKey = DepthSortKey;
	RenderBatches.Add(RenderBatch);

	return TileRenderer;
}

FSpriteRenderer *
FCanvasRenderer::FindOrCreateSpriteRenderer()
{
	uint32 DepthSortKey = GetDepthSortKey();
	for (FRenderBatch &RenderBatch : RenderBatches)
	{
		FRendererItem *Renderer = RenderBatch.Renderer;

		FSpriteRenderer *SpriteRenderer = Renderer->GetSpriteRenderer();
		if (SpriteRenderer && RenderBatch.DepthSortKey == DepthSortKey)
		{
			return SpriteRenderer;
		}
	}

	FSpriteRenderer *SpriteRenderer = new FSpriteRenderer();

	FRenderBatch RenderBatch;
	RenderBatch.Renderer     = SpriteRenderer;
	RenderBatch.DepthSortKey = DepthSortKey;
	RenderBatches.Add(RenderBatch);

	return SpriteRenderer;
}

FTextRenderer *
FCanvasRenderer::FindOrCreateTextRenderer()
{
	uint32 DepthSortKey = GetDepthSortKey();
	for (FRenderBatch &RenderBatch : RenderBatches)
	{
		FRendererItem *Renderer = RenderBatch.Renderer;

		FTextRenderer *TextRenderer = Renderer->GetTextRenderer();
		if (TextRenderer && RenderBatch.DepthSortKey == DepthSortKey)
		{
			return TextRenderer;
		}
	}

	FTextRenderer *TextRenderer = new FTextRenderer();

	FRenderBatch RenderBatch;
	RenderBatch.Renderer     = TextRenderer;
	RenderBatch.DepthSortKey = DepthSortKey;
	RenderBatches.Add(RenderBatch);

	return TextRenderer;
}