#ifndef CANVAS_BUTTON_H
#define CANVAS_BUTTON_H

#include "CanvasRenderer.h"

class FCanvasMenu;
class FCanvasMenuState;

class FContentBrush
{
public:
    const FTexture2D *Sprite;
    FColor32 ColorAndOpacity;

public:
    FContentBrush();
    FContentBrush(const FColor32 &InColorAndOpacity);
    FContentBrush(const FTexture2D *InSprite);
    FContentBrush(const FTexture2D *InSprite, const FColor32 &InColorAndOpacity);
};

enum EButtonState
{
    BS_Disabled,
    BS_Normal,
    BS_Hovered,
    BS_Clicked,
};

class FCanvasButton
{
public:
    FIntRect Position;
    EButtonState ButtonState;

    EContentAlignX AlignX;
    EContentAlignY AlignY;

    FCanvasMenu *OwnerMenu;

    FContentBrush DisabledBrush;
    FContentBrush NormalBrush;
    FContentBrush HoveredBrush;
    FContentBrush ClickedBrush;

public:
    FCanvasButton();
    virtual ~FCanvasButton() { }

    virtual void OnHover();
    virtual void OnClick();
    virtual void OnRelease();
    
    virtual void Render(FCanvasRenderer *InCanvasRenderer);

    FCanvasMenu *GetMenu();
    FCanvasMenuState *GetMenuState();
};

#endif