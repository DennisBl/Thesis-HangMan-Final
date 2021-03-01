#include "CanvasButton.h"
#include "CanvasMenu.h"
#include "CanvasMenuState.h"

FContentBrush::FContentBrush()
    : Sprite(0)
{ }

FContentBrush::FContentBrush(const FColor32 &InColorAndOpacity)
    : Sprite(0)
    , ColorAndOpacity(InColorAndOpacity)
{ }

FContentBrush::FContentBrush(const FTexture2D *InSprite)
    : Sprite(InSprite)
{ }

FContentBrush::FContentBrush(const FTexture2D *InSprite, const FColor32 &InColorAndOpacity)
    : Sprite(InSprite)
    , ColorAndOpacity(InColorAndOpacity)
{ }

FCanvasButton::FCanvasButton()
    : ButtonState(BS_Normal)
    , OwnerMenu(0)
{ }

void 
FCanvasButton::OnHover()
{
    ButtonState = BS_Hovered;
}

void 
FCanvasButton::OnClick()
{
    ButtonState = BS_Clicked;
}

void FCanvasButton::OnRelease()
{
}

void
FCanvasButton::Render(FCanvasRenderer *InCanvasRenderer)
{
    const int32 X     = Position.GetOriginX();
    const int32 Y     = Position.GetOriginY();
    const int32 SizeX = Position.GetSizeX();
    const int32 SizeY = Position.GetSizeY();

    FContentBrush ActiveBrush;
    switch (ButtonState)
    {
    case BS_Disabled:
        ActiveBrush = DisabledBrush;
        break;
    case BS_Normal:
        ActiveBrush = NormalBrush;
        break;
    case BS_Hovered:
        ActiveBrush = HoveredBrush;
        break;
    case BS_Clicked:
        ActiveBrush = ClickedBrush;
        break;
    }

    const FTexture2D *Sprite = ActiveBrush.Sprite;
    if (Sprite)
    {
        const FColor32 &ColorAndOpacity = ActiveBrush.ColorAndOpacity;
        if (!ColorAndOpacity.IsZeroAlpha())
        {
            InCanvasRenderer->DrawSprite(Sprite, X, Y, SizeX, SizeY, ColorAndOpacity, AlignX, AlignY);
        }
    }
    else
    {
        const FColor32 &ColorAndOpacity = ActiveBrush.ColorAndOpacity;
        if (!ColorAndOpacity.IsZeroAlpha())
        {
            InCanvasRenderer->DrawTile(X, Y, SizeX, SizeY, ColorAndOpacity, AlignX, AlignY);
        }
    }

    if (ButtonState != BS_Disabled)
    {
        ButtonState = BS_Normal;
    }
}